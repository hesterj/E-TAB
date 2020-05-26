#include <etableau.h>

bool ECloseBranch(ClauseTableau_p branch, ClauseSet_p extension_candidates)
{
	ClauseSet_p branch_clauses = ClauseSetAlloc();
	ClauseTableau_p node = branch;
	long proc_limit = 10000;
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
	printf("# Done collecting branch.\n");
	ClauseSetInsertSet(branch_clauses, branch->master->unit_axioms);
	ClauseSetInsertSet(branch_clauses, extension_candidates);
	printf("# Inserted axiom clauses.\n");
	// Now attempt saturation
	ProofState_p proofstate = branch->master->state;
	ProofControl_p proofcontrol = branch->master->control;
	
	proofstate->axioms = branch_clauses;
	assert(proofstate->axioms);
	printf("# Number of axioms: %ld\n", proofstate->axioms->members);
	printf("# Number of branch axioms: %ld\n", branch_clauses->members);
	printf("# Depth of branch: %d\n", branch->depth);

	Clause_p success = Saturate(proofstate, proofcontrol, LONG_MAX,
							 proc_limit, LONG_MAX, LONG_MAX, LONG_MAX,
							 LLONG_MAX, LONG_MAX);
	printf("# Bogey\n");
	ClauseSetFree(branch_clauses);
	if (success)
	{
		return true;
	}
	return false;
}

bool AttemptToCloseBranchesWithSuperposition(ClauseTableau_p master, ClauseSet_p extension_candidates)
{
	ProofState_p proofstate = master->state;
	ProofControl_p proofcontrol = master->control;
	TableauSet_p open_branches = master->open_branches;
	int num_open_branches = (int) open_branches->members;
	printf("Attempting to create %d subjobs\n", num_open_branches);
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
	
	int status = 0;
	pid_t wpid = 0;
	pid_t worker = 0;
	printf("Creating new processes:\n", num_open_branches);
	// Create new processes and try to close the respective branches with E's saturation
	for (int i=0; i<num_open_branches; i++)
	{
		worker = fork();
		if (worker == 0) // We are in the child process 
		{
			// Collect the branch clauses
			ClauseTableau_p branch = branches[i];
			printf("# %d OK.\n", i);
			bool closed = ECloseBranch(branch, extension_candidates);
			if (closed)
			{
				printf("Managed to close a local branch with Saturate!\n");
			}
			printf("# %d Completed.\n", i);
			exit(0);
		}
		else 
		{
			pool[i] = worker;
		}
	}
	assert(worker == 0);
	printf("# Waiting...\n");
	while (wait(&status) > 0);
	// Terminate the processes
	for (int i=0; i<num_open_branches; i++)
	{
		kill(pool[i], SIGTERM);
	}
	
	printf("Made jobs and successfully killed them.\n");
	return true;
}
