#include "tableauproc.h"

/*  Global Variables
*/

int branch_number = 0;
long num_axioms = 0;
long dive_depth = 10;

/*  Forward Declarations
*/

/*  Function Definitions
*/


/*  Identify a single negated conjecture to form the tableau branches.
 *  If there is no conjecture return NULL.  
 *  Returns the first conjecture found, if there are multiple they will not affect the tableau.
 * 
*/

WFormula_p ProofStateGetConjecture(ProofState_p state)
{
	WFormula_p handle = state->f_axioms->anchor->succ;
	while (handle != state->f_axioms->anchor)
	{
		if (FormulaIsConjecture(handle))
		{
			//FormulaSetExtractEntry(handle);
			return handle;
		}
		handle = handle->succ;
	}
	return NULL;
}

ClauseTableau_p ConnectionTableauSaturate(ProofState_p state, ProofControl_p control, int max_depth)
{
	problemType = PROBLEM_FO;
	assert(max_depth);
   ClauseTableau_p initial_tab = ClauseTableauAlloc();
   ClauseTableau_p resulting_tab = NULL;
   //ClauseTableau_p new_tab;
   TableauSet_p distinct_tableaux = TableauMasterSetAlloc();
   //int arity;
   
   initial_tab->open_branches = TableauSetAlloc();
   TableauSet_p open_branches = initial_tab->open_branches;
   TableauSetInsert(open_branches, initial_tab);
   initial_tab->control = NULL;
   
   assert(state->axioms->members > 0);
   ClauseTableauInitialize(initial_tab, state);
	
	// Create a tableau for each axiom using the start rule
   Clause_p start_label = initial_tab->active->anchor->succ;
   while (start_label != initial_tab->active->anchor)
   {
		ClauseTableau_p beginning_tableau = ClauseTableauMasterCopy(initial_tab);
		TableauMasterSetInsert(distinct_tableaux, beginning_tableau);
		beginning_tableau = TableauStartRule(beginning_tableau, start_label);
		start_label = start_label->succ;
	}
	
	ClauseSet_p extension_candidates = ClauseSetCopy(state->terms, initial_tab->active);
	ClauseTableauFree(initial_tab);  // Free the  initialization tableau used to make the tableaux with start rule
	
	assert(distinct_tableaux);
	
	printf("Start rule applications: %ld\n", distinct_tableaux->members);
	
	for (int current_depth = 1; current_depth < max_depth; current_depth++)
	{
		resulting_tab = ConnectionTableauProofSearch(state, 
																	control, 
																	distinct_tableaux, 
																	extension_candidates, 
																	current_depth);
		if (resulting_tab) break;  // Closed tableau found
	}
	
	ClauseSetFree(extension_candidates);
   
   printf("Connection tableau proof search finished.\n");
   
   if (!resulting_tab)
   {
	  printf("ConnectionTableauProofSearch returns NULL. Failure.\n");
   }
   
   TableauMasterSetFree(distinct_tableaux);
   
	return resulting_tab;
}

ClauseTableau_p ConnectionTableauProofSearch(ProofState_p state, ProofControl_p control,
										     TableauSet_p distinct_tableaux,
										     ClauseSet_p extension_candidates,
										     int max_depth)
{
	assert(distinct_tableaux);
	ClauseTableau_p active_tableau = NULL;
	ClauseTableau_p open_branch = NULL;
	assert(distinct_tableaux->anchor->master_succ);
	/*
	ClauseSet_p extension_candidates = 
	ClauseSetCopy(distinct_tableaux->anchor->master_succ->terms, distinct_tableaux->anchor->master_succ->active); // These are the clauses that can be split
	*/
	printf("Extension candidates: \n");
	ClauseSetPrint(GlobalOut, extension_candidates, true);
	printf("\n");
	int number_of_extensions = 0;
	long old_number_of_distinct_tableaux = distinct_tableaux->members;
	assert(old_number_of_distinct_tableaux);
	
	active_tableau = distinct_tableaux->anchor->master_succ;
	while (active_tableau != distinct_tableaux->anchor) // iterate over the active tableaux
	{
		printf("Number of distinct tableaux: %ld\n", distinct_tableaux->members);
		if (active_tableau->open_branches->members == 0)
		{
			printf("Closed tableau found!\n");
			ClauseTableauPrint(active_tableau);
			return active_tableau;
		}
		assert(active_tableau->label);
		assert(active_tableau->master_set);
		ClauseTableauAssertCheck(active_tableau);
		open_branch = active_tableau->open_branches->anchor->succ;
		number_of_extensions = 0;
		while (open_branch != active_tableau->open_branches->anchor) // iterate over the open branches of the current tableau
		{
			number_of_extensions = 0;
			if (ClauseTableauBranchClosureRuleWrapper(open_branch))
			{
				printf("Branch closed with closure rule.\n");
				open_branch->open = false;
				open_branch = open_branch->succ;
				TableauSetExtractEntry(open_branch->pred);
				continue;
			}
			if (open_branch->depth > max_depth)
			{
				printf("Reached max depth.\n");
				open_branch = open_branch->succ;
				continue;
			}
			Clause_p selected = extension_candidates->anchor->succ;
			while (selected != extension_candidates->anchor) // iterate over the clauses we can split on the branch
			{
				number_of_extensions += ClauseTableauExtensionRuleAttemptOnBranch(open_branch,
																										distinct_tableaux,
																										selected);
				if (open_branch->open_branches->members == 0)
				{
					return open_branch->master;
				}
				selected = selected->succ;
			}
			// If we extended on the open branch with one or more clause, we need to move to a new active tableau.
			if (number_of_extensions > 0)
			{
				printf("Did %d extensions.\n", number_of_extensions);
				goto next_tableau;
			}
			open_branch = open_branch->succ;
		}
		next_tableau:
		printf("New number of distinct tableaux: %ld\n", distinct_tableaux->members);
		assert(active_tableau != active_tableau->master_succ);
		active_tableau = active_tableau->master_succ;
		if (number_of_extensions > 0)
		{
			ClauseTableau_p trash = active_tableau->master_pred;
			TableauMasterSetExtractEntry(trash);
			ClauseTableauFree(trash);
			printf("Extracted tableau that had a branch expanded on %d times\n", number_of_extensions);
		}
		assert(active_tableau);
		printf("Old number of distinct tableaux: %ld, Now we have: %ld\n",old_number_of_distinct_tableaux, distinct_tableaux->members);
		old_number_of_distinct_tableaux = distinct_tableaux->members;
		number_of_extensions = 0;
	}
	printf("Went through all of the possible tableaux.\n");
	
	//ClauseSetFree(extension_candidates);
	return NULL;
}
