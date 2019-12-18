#include "tableauproc.h"
#include <omp.h>

/*  Global Variables
*/

int branch_number = 0;
long num_axioms = 0;
long dive_depth = 10;

/*  Forward Declarations
*/

/*  Function Definitions
*/

/*-----------------------------------------------------------------------
//
// Function: ClauseSetMoveNonUnits()
//
//   Move all unit-clauses from set to nonunits, return number of
//   clauses moved.
//
// Global Variables: -
//
// Side Effects    : -
//
/----------------------------------------------------------------------*/

long ClauseSetMoveUnits(ClauseSet_p set, ClauseSet_p units)
{
   Clause_p handle;

   assert(set);
   assert(units);
   assert(!set->demod_index);
   assert(!set->demod_index);

   handle = set->anchor->succ;
   long count = 0;
   while(handle != set->anchor)
   {
		assert(handle);
      if(ClauseLiteralNumber(handle) == 1)
      {
			count++;
			handle = handle->succ;
			assert(handle->pred);
			Clause_p unit = ClauseSetExtractEntry(handle->pred);
			ClauseSetInsert(units, unit);
         //ClauseSetMoveClause(units, handle->pred);
      }
      else
      {
			handle = handle->succ;
		}
   }
   return count;
}


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

ClauseTableau_p ConnectionTableauProofSearch(TableauSet_p distinct_tableaux,
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
	printf("# Extension candidates: \n");
	ClauseSetPrint(GlobalOut, extension_candidates, true);
	printf("\n");
	int number_of_extensions = 0;
	long old_number_of_distinct_tableaux = distinct_tableaux->members;
	assert(old_number_of_distinct_tableaux);
	TableauControl_p control = TableauControlAlloc();
	long MAX_TABLEAUX = 2500000;
	
	active_tableau = distinct_tableaux->anchor->master_succ;
	while (active_tableau != distinct_tableaux->anchor) // iterate over the active tableaux
	{
		printf("# Number of distinct tableaux: %ld\n", distinct_tableaux->members);
		if (control->closed_tableau)
		{
			printf("Success\n");
			exit(0);
		}
		else if (distinct_tableaux->members == 1)
		{
			printf("The only tableau has %ld open branches.\n", distinct_tableaux->anchor->master_succ->open_branches->members);
			assert(distinct_tableaux->anchor->master_succ);
			//ClauseTableauPrint(distinct_tableaux->anchor->master_succ);
		}
		if (active_tableau->open_branches->members == 0)
		{
			bool all_branches_closed = ClauseTableauMarkClosedNodes(active_tableau);
			printf("# Closed tableau found! %d\n", all_branches_closed);
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
				assert(open_branch);
				assert(open_branch->open_branches);
				assert(open_branch->open_branches->members >= 0);
				
				printf("# Branch closed with closure rule. %ld remaining.\n", active_tableau->open_branches->members);
				open_branch->open = false;
				open_branch = open_branch->succ;
				TableauSetExtractEntry(open_branch->pred);
				if (open_branch->parent == NULL)
				{
					printf("Open branch is the root node- danger.\n");
				}
				if (ClauseTableauMarkClosedNodes(open_branch->parent))
				{
					printf("Was able to close an open branch after marking closed, %ld remaining.\n", open_branch->open_branches->members);
					int folded_up = FoldUpAtNode(open_branch->parent);
					printf("Folded up %d nodes after closure rule\n", folded_up);
				}
				if (active_tableau->open_branches->members == 0)
				{
					control->closed_tableau = open_branch->master;
					bool all_branches_closed = ClauseTableauMarkClosedNodes(control->closed_tableau);
					printf("All branches closed... %d\n", all_branches_closed);
					ClauseTableauPrint(control->closed_tableau);
					return control->closed_tableau;
				}
				continue;
			}
			else if (open_branch->depth > max_depth)
			{
				//printf("Reached max depth.\n");
				open_branch = open_branch->succ;
				continue;
			}
			Clause_p selected = extension_candidates->anchor->succ;
			while (selected != extension_candidates->anchor) // iterate over the clauses we can split on the branch
			{
				number_of_extensions += ClauseTableauExtensionRuleAttemptOnBranch(control,
																										open_branch,
																										distinct_tableaux,
																										selected);
				if (control->closed_tableau)
				{
					bool all_branches_closed = ClauseTableauMarkClosedNodes(control->closed_tableau);
					printf("Closed tableau... %d\n", all_branches_closed);
					ClauseTableauPrint(control->closed_tableau);
					return control->closed_tableau;
				}
				if (distinct_tableaux->members > MAX_TABLEAUX)
				{
					return NULL;
				}
				selected = selected->succ;
			}
			// If we extended on the open branch with one or more clause, we need to move to a new active tableau.
			if (number_of_extensions > 0)
			{
				//printf("Did %d extensions.\n", number_of_extensions);
				goto next_tableau;
			}
			open_branch = open_branch->succ;
		}
		next_tableau:
		//printf("New number of distinct tableaux: %ld\n", distinct_tableaux->members);
		assert(active_tableau != active_tableau->master_succ);
		active_tableau = active_tableau->master_succ;
		if (number_of_extensions > 0)
		{
			printf("Number of active tableau before extension-free step: %ld\n", distinct_tableaux->members);
			ClauseTableau_p trash = active_tableau->master_pred;
			TableauMasterSetExtractEntry(trash);
			ClauseTableauFree(trash);
			//printf("Extracted tableau that had a branch expanded on %d times\n", number_of_extensions);
		}
		assert(active_tableau);
		//printf("Old number of distinct tableaux: %ld, Now we have: %ld\n",old_number_of_distinct_tableaux, distinct_tableaux->members);
		old_number_of_distinct_tableaux = distinct_tableaux->members;
		number_of_extensions = 0;
	}
	
	printf("# Went through all of the possible tableaux\n");
	
	//ClauseSetFree(extension_candidates);
	return NULL;
}

/*  Create clausal connection tableau for the active clause set.
 *  If there is more than one, the start rule will be applied one at a time.
 *  After all the tableaux have been built up to the max depth (or MAX_TABLEAU has been exceeded),
 *  without success, the next start rule application is checked.  
 *  Opportunity for paralellism here, as all the start rule applications could be 
 *  done without too much duplication of the TB_p as would happen if every tableau
 *  had its own term bank.
*/

Clause_p ConnectionTableauSerial(TB_p bank, ClauseSet_p active, int max_depth)
{
	/*
	printf("Clauses:\n");
	ClauseSetPrint(GlobalOut, active, true);
	printf("Terms %ld:\n", bank->term_store.entries);
	TBPrintBankInOrder(GlobalOut, bank);
	*/
   problemType = PROBLEM_FO;
   assert(max_depth);
   if (active->members == 0) return NULL;
   ClauseSet_p unit_axioms = ClauseSetAlloc();
   ClauseSet_p extension_candidates = ClauseSetCopy(bank, active);
   long number_of_units = ClauseSetMoveUnits(extension_candidates, unit_axioms);
   printf("# Number of units: %ld Number of non-units: %ld Number of axioms: %ld\n", number_of_units,
																										extension_candidates->members,
																										active->members);
   assert(number_of_units == unit_axioms->members);
   if (extension_candidates->members == 0)
   {
		ClauseSetFree(unit_axioms);
		ClauseSetFree(extension_candidates);
		return NULL;
	}
   
   ClauseTableau_p initial_tab = ClauseTableauAlloc();
   ClauseTableau_p resulting_tab = NULL;
   TableauSet_p starting_tableaux = TableauMasterSetAlloc();
   
   initial_tab->open_branches = TableauSetAlloc();
   TableauSet_p open_branches = initial_tab->open_branches;
   TableauSetInsert(open_branches, initial_tab);
   
   //ClauseSetPrint(GlobalOut, active, true);printf("\n");
   
   FunCode max_var = ClauseSetGetMaxVar(active);
   assert(max_var <= 0);
   
   initial_tab->terms = bank;
   initial_tab->signature = NULL;
   initial_tab->state = NULL;
   
   //  Move all of the unit clauses to be on the initial tableau
   initial_tab->unit_axioms = unit_axioms;
   //ClauseSetGCMarkTerms(unit_axioms);
   
	ClauseTableau_p beginning_tableau = NULL;
	// Create a tableau for each axiom using the start rule
   Clause_p start_label = extension_candidates->anchor->succ;
   while (start_label != extension_candidates->anchor)
   {
		beginning_tableau = ClauseTableauMasterCopy(initial_tab);
		beginning_tableau->max_var = max_var;
		TableauMasterSetInsert(starting_tableaux, beginning_tableau);
		beginning_tableau = TableauStartRule(beginning_tableau, start_label);
		start_label = start_label->succ;
	}
	
	
	ClauseTableauFree(initial_tab);  // Free the  initialization tableau used to make the tableaux with start rule
	
	
	printf("# Start rule applications: %ld\n", starting_tableaux->members);
	
	TableauSet_p distinct_tableaux = NULL;
	restart:
	VarBankPushEnv(bank->vars);
	distinct_tableaux = TableauMasterSetAlloc();
	assert(distinct_tableaux);
	assert(extension_candidates->anchor->succ);
	beginning_tableau = TableauMasterSetExtractFirst(starting_tableaux);
	TableauMasterSetInsert(distinct_tableaux, beginning_tableau);
	assert(distinct_tableaux->members == 1);
	for (int current_depth = 1; current_depth < max_depth; current_depth++)
	{
		resulting_tab = ConnectionTableauProofSearch(distinct_tableaux, // This is where the magic happens
													 extension_candidates, 
													 current_depth);
		if (resulting_tab)
		{
			printf("Closed tableau found!\n");
			break;
		}
	}
	if (!resulting_tab)
	{
		TableauMasterSetFree(distinct_tableaux);
		distinct_tableaux = NULL;
		if (starting_tableaux->members > 0)
		{
			VarBankPopEnv(bank->vars);
			//long freed = TBGCSweep(bank);
			//ClauseSetGCMarkTerms(extension_candidates);
			//ClauseSetGCMarkTerms(unit_axioms);
			//printf("Number of terms recovered: %ld\n", freed);
			goto restart;
		}
	}
	
	ClauseSetFree(extension_candidates);
   
   printf("# Connection tableau proof search finished.\n");

   if (distinct_tableaux)
   {
		TableauMasterSetFree(distinct_tableaux);
	}
   if (!resulting_tab)
   {
	  printf("# ConnectionTableauProofSearch returns NULL. Failure.\n");
	  return NULL;
   }
   if (resulting_tab)
   {
		printf("Proof search tableau success!\n");
		Clause_p empty = EmptyClauseAlloc();
		return empty;
	}
	return NULL;
}

/*  As ConnectionTableauSerial, but builds tableau on all start rule
 *  applications at once.  Does not use any multhreading.
*/

Clause_p ConnectionTableauBatch(TB_p bank, ClauseSet_p active, int max_depth)
{
	/*
	printf("Clauses:\n");
	ClauseSetPrint(GlobalOut, active, true);
	printf("Terms %ld:\n", bank->term_store.entries);
	TBPrintBankInOrder(GlobalOut, bank);
	*/
   problemType = PROBLEM_FO;
   assert(max_depth);
   if (active->members == 0) return NULL;
   ClauseSet_p unit_axioms = ClauseSetAlloc();
   ClauseSet_p extension_candidates = ClauseSetCopy(bank, active);
   long number_of_units = ClauseSetMoveUnits(extension_candidates, unit_axioms);
   printf("# Number of units: %ld Number of non-units: %ld Number of axioms: %ld\n", number_of_units,
																										extension_candidates->members,
																										active->members);
   assert(number_of_units == unit_axioms->members);
   if (extension_candidates->members == 0)
   {
		ClauseSetFree(unit_axioms);
		ClauseSetFree(extension_candidates);
		return NULL;
	}
   
   ClauseTableau_p initial_tab = ClauseTableauAlloc();
   ClauseTableau_p resulting_tab = NULL;
   TableauSet_p distinct_tableaux = TableauMasterSetAlloc();
   
   initial_tab->open_branches = TableauSetAlloc();
   TableauSet_p open_branches = initial_tab->open_branches;
   TableauSetInsert(open_branches, initial_tab);
   
   //ClauseSetPrint(GlobalOut, active, true);printf("\n");
   
   FunCode max_var = ClauseSetGetMaxVar(active);
   assert(max_var <= 0);
   
   initial_tab->terms = bank;
   initial_tab->signature = NULL;
   initial_tab->state = NULL;
   
   //  Move all of the unit clauses to be on the initial tableau
   initial_tab->unit_axioms = unit_axioms;
   //ClauseSetGCMarkTerms(unit_axioms);
   
	ClauseTableau_p beginning_tableau = NULL;
	// Create a tableau for each axiom using the start rule
   Clause_p start_label = extension_candidates->anchor->succ;
   while (start_label != extension_candidates->anchor)
   {
		beginning_tableau = ClauseTableauMasterCopy(initial_tab);
		beginning_tableau->max_var = max_var;
		TableauMasterSetInsert(distinct_tableaux, beginning_tableau);
		beginning_tableau = TableauStartRule(beginning_tableau, start_label);
		start_label = start_label->succ;
	}
	
	
	ClauseTableauFree(initial_tab);  // Free the  initialization tableau used to make the tableaux with start rule
	
	
	printf("# Start rule applications: %ld\n", distinct_tableaux->members);
	
	VarBankPushEnv(bank->vars);
	for (int current_depth = 1; current_depth < max_depth; current_depth++)
	{
		resulting_tab = ConnectionTableauProofSearch(distinct_tableaux, // This is where the magic happens
													 extension_candidates, 
													 current_depth);
		if (resulting_tab)
		{
			printf("Closed tableau found!\n");
			break;
		}
	}
	
	ClauseSetFree(extension_candidates);
	VarBankPopEnv(bank->vars);
   
   printf("# Connection tableau proof search finished.\n");

   if (distinct_tableaux) // Free the tableux
   {
		TableauMasterSetFree(distinct_tableaux);
		distinct_tableaux = NULL;
	}
   if (!resulting_tab) // failure
   {
	  printf("# ConnectionTableauProofSearch returns NULL. Failure.\n");
	  return NULL;
   }
   if (resulting_tab) // success
   {
		printf("Proof search tableau success!\n");
		Clause_p empty = EmptyClauseAlloc();
		return empty;
	}
	return NULL;
}
