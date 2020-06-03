#include <etableau.h>
#include <cco_scheduling.h>

// Forward declaration


// Function definitions 

int ECloseBranch(ProofState_p proofstate, 
					  ProofControl_p proofcontrol, 
					  ClauseTableau_p branch)
{
	ClauseSet_p branch_clauses = ClauseSetAlloc();
	ClauseTableau_p node = branch;
	assert(proofstate);
	assert(proofcontrol);
	long proc_limit = 1000;
	while (node)
	{
		//assert(node->set == NULL);
		if (node != node->master)
		{
			//Clause_p label = ClauseCopyFresh(node->label, branch);
			Clause_p label = node->label;
			label->weight = ClauseStandardWeight(label);
			ClauseSetIndexedInsertClause(branch_clauses, label);
		}
		if (node->folding_labels)
		{
			ClauseSetIndexedInsertClauseSet(branch_clauses, node->folding_labels);
		}
		node = node->parent;
	}
	
	//printf("# Unprocessed clauses of proofstate:\n");
	//ClauseSetPrint(GlobalOut, proofstate->unprocessed, true);
	//printf("\n");
	
	printf("# Number of branch axioms: %ld\n", branch_clauses->members);
	ClauseSetSetProp(branch_clauses, CPInitial);
	ClauseSetSetProp(branch_clauses, CPLimitedRW);
	
	ClauseSet_p axioms = proofstate->axioms;
	ClauseSet_p unproc = proofstate->unprocessed;
	proofstate->axioms = branch_clauses;
	proofstate->unprocessed = ClauseSetAlloc();
	ProofStateInit(proofstate, proofcontrol);
	Clause_p success = Saturate(proofstate, proofcontrol, LONG_MAX,
							 proc_limit, LONG_MAX, LONG_MAX, LONG_MAX,
							 LLONG_MAX, LONG_MAX);
	if (success)
	{
		printf("Superposition contradiction purely within branch!\n");
		return PROOF_FOUND;
	}
	assert(proofstate->unprocessed->members == 0);
	ClauseSetFree(proofstate->unprocessed);
	proofstate->unprocessed = NULL;
	proofstate->axioms = axioms;
	proofstate->unprocessed = unproc;
	assert(proofstate->unprocessed);
	
	//~ printf("# Number of axioms: %ld\n", proofstate->axioms->members);
	//~ printf("# Number of unprocessed: %ld\n", proofstate->unprocessed->members);
	//~ printf("# Number of processed: %ld\n", ProofStateProcCardinality(proofstate));
	//~ printf("# Depth of branch: %d\n", branch->depth);
	//~ printf("# tmp store empty? %d\n", ClauseSetEmpty(proofstate->tmp_store));
	
	ClauseSetFree(branch_clauses);
	// Now do normal saturation
	printf("# Saturating branch...\n");
	success = Saturate(proofstate, proofcontrol, LONG_MAX,
							 proc_limit, LONG_MAX, LONG_MAX, LONG_MAX,
							 LLONG_MAX, LONG_MAX);
	//ClauseSetFree(branch_clauses);
	//~ printf("# Exited saturation...\n");
	if (success)
	{
		printf("Saturate returned empty clause.\n");
		//ProofStateStatisticsPrint(GlobalOut, proofstate);
		return PROOF_FOUND;
	}
	return RESOURCE_OUT;
}

bool AttemptToCloseBranchesWithSuperposition(ProofState_p proofstate, 
															ProofControl_p proofcontrol, 
															ClauseTableau_p master)
{
	//ProofState_p proofstate = master->state;
	//ProofControl_p proofcontrol = master->control;
	TableauSet_p open_branches = master->open_branches;
	int num_open_branches = (int) open_branches->members;
	//printf("Attempting to create %d subjobs\n", num_open_branches);
	pid_t pool[num_open_branches];
	int return_status[num_open_branches];
	
	// Collect the branches in the array
	ClauseTableau_p handle = open_branches->anchor->succ;
	ClauseTableau_p branches[num_open_branches];
	for (int i=0; i<num_open_branches; i++)
	{
		assert(handle != master->open_branches->anchor);
		if (BranchIsLocal(handle)) branches[i] = handle;
		else branches[i] = NULL;
		handle = handle->succ;
	}
	
	int raw_status = 0, status = OTHER_ERROR;
	pid_t worker = 0, respid;
	//printf("Creating %d new processes:\n", num_open_branches);
	// Create new processes and try to close the respective branches with E's saturation
	for (int i=0; i<num_open_branches; i++)
	{
		if (branches[i] == NULL) // If the branch is not local, do not fork.
		{
			pool[i] = NULL;
			return_status[i] = RESOURCE_OUT;
			continue;
		}
		fflush(GlobalOut);
		worker = fork();
		if (worker == 0) // We are in the child process 
		{
			// Collect the branch clauses
			ClauseTableau_p branch = branches[i];
			assert(branches[i]);
			SilentTimeOut = true;
			int branch_status = ECloseBranch(proofstate, proofcontrol, branch);
			exit(branch_status);
		}
		else 
		{
			pool[i] = worker;
			return_status[i] = RESOURCE_OUT;
		}
	}
	//printf("# Waiting...\n");
	bool any_successful = false;
	bool all_successful = false;
	int successful_count = 0;
	for (int i=0; i<num_open_branches; i++)
	{
		respid = -1;
		while(respid == -1)
		{
			//~ if (branches[i] == NULL)
			//~ {
				//~ printf("Nonlocal branch\n");
				//~ continue;
			//~ }
			worker = pool[i];
			if (worker == 0) break;
			respid = waitpid(worker, &raw_status, 0);
			//printf("Fork %d dead, respid %d, status %d.\n", worker, respid, raw_status);
			if (WIFEXITED(raw_status))
         {
            status = WEXITSTATUS(raw_status);
            if (status == SATISFIABLE)
            {
					printf("Satisfiable branch!\n");
					return_status[i] = SATISFIABLE;
					break;
				}
            if (status == PROOF_FOUND)
            {
					printf("Proof found on branch!\n");
					ClauseTableau_p closed_branch = branches[i];
					TableauSetExtractEntry(closed_branch);
					closed_branch->open = false;
					closed_branch->saturation_closed = true;
					return_status[i] = PROOF_FOUND;
					any_successful = true;
					successful_count++;
					break;
            }
            else
            {
					//printf("#%d", status);
               //fprintf(GlobalOut, "# No success with fork\n");
            }
         }
         else if (WIFSIGNALED(raw_status))
         {
				Error("#%d %d Signalled termination\n", raw_status, respid);
			}
         else
         {
            Error("#%d %d Abnormal termination\n", raw_status, respid);
         }
		}
	}
	
	// Process any results
	
	if (successful_count == num_open_branches)
	{
		all_successful = true;
		printf("# All remaining open branches were closed with E.\n");
		printf("# SZS status Theorem\n");
		ClauseTableauPrintDOTGraph(master);
		exit(0);
	}
	//~ else if (any_successful)
	//~ {
		//~ printf("# Marking saturation closed branches as such.\n");
		//~ for (int i=0; i<num_open_branches; i++)
		//~ {
			//~ if (return_status[i] == SATISFIABLE)
			//~ {
				//~ printf("# Branch satisfiable\n");
				//~ printf("# SZS status Satisfiable\n");
				//~ exit(0);
			//~ }
			//~ if (return_status[i] == PROOF_FOUND)
			//~ {
				//~ ClauseTableau_p closed_branch = branches[i];
				//~ TableauSetExtractEntry(closed_branch);
				//~ closed_branch->open = false;
			//~ }
		//~ }
		//~ return true;
	//~ }
	// Exit and return to tableaux proof search
	return false;
}
