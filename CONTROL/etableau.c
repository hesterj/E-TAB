#include <etableau.h>
#include <cco_scheduling.h>

// Forward declaration


// Function definitions 

int ECloseBranch(ProofState_p proofstate, ProofControl_p proofcontrol, ClauseTableau_p branch, ClauseSet_p extension_candidates)
{
	ClauseSet_p branch_clauses = ClauseSetAlloc();
	ClauseTableau_p node = branch;
	assert(proofstate);
	assert(proofcontrol);
	long proc_limit = 1000;
	//printf("# Fork mobile...\n");
	while (node)
	{
		//assert(node->set == NULL);
		Clause_p label = node->label;
		ClauseSetInsert(branch_clauses, label);
		if (node->folding_labels)
		{
			ClauseSetInsertSet(branch_clauses, node->folding_labels);
		}
		node = node->parent;
	}
	assert(proofstate->axioms);
	//printf("# Number of axioms: %ld\n", proofstate->axioms->members);
	//printf("# Number of unprocessed: %ld\n", proofstate->unprocessed->members);
	//printf("# Number of branch axioms: %ld\n", branch_clauses->members);
	//printf("# Depth of branch: %d\n", branch->depth);
	//ClauseSetInsertSet(proofstate->unprocessed, branch_clauses);
	
	// Process the clauses of the branch first!
	EvaluateClauseSet(proofstate, proofcontrol, branch_clauses);
	Clause_p clause = ProcessClauseSet(proofstate, proofcontrol, branch_clauses, LONG_MAX);
	printf("Manually processed clause set.\n");
	if (clause)
	{
		printf("# Contradiction found while processing branch clauses\n");
		return PROOF_FOUND;
	}
	
	//~ while (!ClauseSetEmpty(branch_clauses))
	//~ {
		//~ Clause_p clause = ProcessClauseSet(proofstate, proofcontrol, branch_clauses, LONG_MAX);
		//~ printf("Manually processed a clause.\n");
		//~ if (clause)
		//~ {
			//~ printf("# Contradiction found while processing branch clauses\n");
			//~ return PROOF_FOUND;
		//~ }
	//~ }
	ClauseSetFree(branch_clauses);
	
	// Now do normal saturation
	Clause_p success = Saturate(proofstate, proofcontrol, LONG_MAX,
							 proc_limit, LONG_MAX, LONG_MAX, LONG_MAX,
							 LLONG_MAX, LONG_MAX);
	//ClauseSetFree(branch_clauses);
	if (success)
	{
		return PROOF_FOUND;
	}
	return OUT_OF_MEMORY;
}

bool AttemptToCloseBranchesWithSuperposition(ProofState_p proofstate, ProofControl_p proofcontrol, ClauseTableau_p master, ClauseSet_p extension_candidates)
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
		branches[i] = handle;
		handle = handle->succ;
	}
	
	int raw_status = 0, status = OTHER_ERROR;
	pid_t worker = 0, respid;
	//printf("Creating %d new processes:\n", num_open_branches);
	// Create new processes and try to close the respective branches with E's saturation
	for (int i=0; i<num_open_branches; i++)
	{
		fflush(GlobalOut);
		worker = fork();
		if (worker == 0) // We are in the child process 
		{
			// Collect the branch clauses
			ClauseTableau_p branch = branches[i];
			SilentTimeOut = true;
			int branch_status = ECloseBranch(proofstate, proofcontrol, branch, extension_candidates);
			exit(branch_status);
		}
		else 
		{
			pool[i] = worker;
			return_status[i] = 0;
		}
	}
	//printf("# Waiting...\n");
	bool all_successful = true;
	for (int i=0; i<num_open_branches; i++)
	{
		respid = -1;
		while(respid == -1)
		{
			worker = pool[i];
			respid = waitpid(worker, &raw_status, 0);
			//printf("Fork %d dead, respid %d, status %d.\n", worker, respid, raw_status);
			if(WIFEXITED(raw_status))
         {
            status = WEXITSTATUS(raw_status);
            if((status == SATISFIABLE) || (status == PROOF_FOUND))
            {
					printf("Proof found on branch!\n");
					return_status[i] = 1;
            }
            else
            {
					all_successful = false;
               //fprintf(GlobalOut, "# No success with fork\n");
            }
         }
         else
         {
            fprintf(GlobalOut, "# Abnormal termination\n");
         }
		}
	}
	
	// Process any results
	
	if (all_successful)
	{
		printf("All remaining open branches were closed with E!\n");
		exit(0);
	}
	
	// Exit and return to tableaux proof search
	printf("Made jobs and successfully killed them.\n");
	return true;
}
