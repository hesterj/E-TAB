#include <etableau.h>
#include <cco_scheduling.h>

// Forward declaration

Clause_p fake_saturate();

// Function definitions 

Clause_p fake_saturate()
{
	printf("Fake\n");
	return NULL;
}

bool ECloseBranch(ProofState_p proofstate, ProofControl_p proofcontrol, ClauseTableau_p branch, ClauseSet_p extension_candidates)
{
	ClauseSet_p branch_clauses = ClauseSetAlloc();
	ClauseTableau_p node = branch;
	assert(proofstate);
	assert(proofcontrol);
	long proc_limit = 1000;
	printf("# Fork mobile...\n");
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
	//printf("# Done collecting branch.\n");
	//ClauseSetInsertSet(branch_clauses, branch->master->unit_axioms);
	//ClauseSetInsertSet(branch_clauses, extension_candidates);
	//printf("# Inserted axiom clauses.\n");
	// Now attempt saturation
	
	assert(proofstate->axioms);
	//printf("# Number of axioms: %ld\n", proofstate->axioms->members);
	//printf("# Number of unprocessed: %ld\n", proofstate->unprocessed->members);
	//printf("# Number of branch axioms: %ld\n", branch_clauses->members);
	//printf("# Depth of branch: %d\n", branch->depth);
	ClauseSetInsertSet(proofstate->unprocessed, branch_clauses);

	fake_saturate();
	Clause_p success = Saturate(proofstate, proofcontrol, LONG_MAX,
							 proc_limit, LONG_MAX, LONG_MAX, LONG_MAX,
							 LLONG_MAX, LONG_MAX);
	//Clause_p success = NULL;
	//printf("# Bogey\n");
	ClauseSetFree(branch_clauses);
	if (success)
	{
		return true;
	}
	return false;
}

bool AttemptToCloseBranchesWithSuperposition(ProofState_p proofstate, ProofControl_p proofcontrol, ClauseTableau_p master, ClauseSet_p extension_candidates)
{
	//ProofState_p proofstate = master->state;
	//ProofControl_p proofcontrol = master->control;
	TableauSet_p open_branches = master->open_branches;
	int num_open_branches = (int) open_branches->members;
	//printf("Attempting to create %d subjobs\n", num_open_branches);
	pid_t pool[num_open_branches];
	
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
			//printf("# %d OK.\n", i);
			bool closed = ECloseBranch(proofstate, proofcontrol, branch, extension_candidates);
			if (closed)
			{
				printf("Managed to close a local branch with Saturate!\n");
			}
			//printf("# %d Completed.\n", i);
			exit(closed);
		}
		else 
		{
			pool[i] = worker;
		}
	}
	//printf("# Waiting...\n");
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
					printf("Need to fix the status received from forks!\n");
               //exit(status);
            }
            else
            {
               fprintf(GlobalOut, "# No success with fork\n");
            }
         }
         else
         {
            fprintf(GlobalOut, "# Abnormal termination\n");
         }
		}
	}
	
	// Process any results
	
	// Exit and return to tableaux proof search
	printf("Made jobs and successfully killed them.\n");
	return true;
}
