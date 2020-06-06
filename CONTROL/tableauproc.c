#include "tableauproc.h"

/*  Global Variables
*/

int branch_number = 0;
long num_axioms = 0;
long dive_depth = 10;

/*  Forward Declarations
*/

long move_new_tableaux_to_distinct(TableauSet_p distinct_tableaux, PStack_p new_tableaux);

/*  Function Definitions
*/

long move_new_tableaux_to_distinct(TableauSet_p distinct_tableaux, PStack_p new_tableaux)
{
	long num_moved = 0;
	while (!PStackEmpty(new_tableaux))
	{
		ClauseTableau_p new_tab = PStackPopP(new_tableaux);
		assert(new_tab->master_set == NULL);
		assert(new_tab->set == NULL);
		TableauMasterSetInsert(distinct_tableaux, new_tab);
		num_moved += 1;
	}
	return num_moved;
}

/*-----------------------------------------------------------------------
//
// Function: ClauseSetMoveNonUnits()
//
//   Move all unit-clauses from set to nonunits, return number of
//   clauses moved.xc
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

ClauseTableau_p ConnectionTableauProofSearch(ProofState_p proofstate, ProofControl_p proofcontrol, TableauSet_p distinct_tableaux,
										     ClauseSet_p extension_candidates,
										     int max_depth,
										     PStack_p new_tableaux)
{
	assert(distinct_tableaux);
	ClauseTableau_p active_tableau = NULL;
	ClauseTableau_p open_branch = NULL;
	assert(distinct_tableaux->anchor->master_succ);
	
	int number_of_extensions = 0;
	TableauControl_p control = TableauControlAlloc();
	long MAX_TABLEAUX = 8000000;
	
	active_tableau = distinct_tableaux->anchor->master_succ;
	while (active_tableau != distinct_tableaux->anchor) // iterate over the active tableaux
	{
		assert(active_tableau->master_pred == distinct_tableaux->anchor);
		assert(active_tableau->label);
		assert(active_tableau->master_set);
		
		#ifndef DNDEBUG
		ClauseTableauAssertCheck(active_tableau);
		#endif
		
		number_of_extensions = 0;
		
		if (control->closed_tableau || active_tableau->open_branches->members == 0)
		{
			fprintf(GlobalOut, "# Success, closed tableau found.\n");
			fprintf(GlobalOut, "# SZS status Theorem");
			ClauseTableauPrintDOTGraph(control->closed_tableau);
			return active_tableau;
		}
		else if (distinct_tableaux->members == 1)
		{
			fprintf(GlobalOut, "# The only tableau has %ld open branches.\n", distinct_tableaux->anchor->master_succ->open_branches->members);
			assert(distinct_tableaux->anchor->master_succ);
			//ClauseTableauPrint(distinct_tableaux->anchor->master_succ);
		}
		
		open_branch = active_tableau->open_branches->anchor->succ;
		
		if (open_branch->depth > 2)
		{
			int saturation_closed = AttemptToCloseBranchesWithSuperposition(proofstate, 
																						 proofcontrol, 
																						 active_tableau->master);
			if (saturation_closed > 0)
			{
				assert(active_tableau);
				assert(active_tableau->open_branches->members > 0);
				open_branch = active_tableau->open_branches->anchor->succ;
			}
		}
		
		PStack_p tmp_new_tableaux = PStackAlloc();
		ClauseTableau_p closed_tableau = ConnectionCalculusExtendOpenBranches(active_tableau, 
																					   new_tableaux, 
																					   control,
																					   distinct_tableaux,
																					   extension_candidates,
																					   max_depth);
		if (closed_tableau)
		{
			fprintf(GlobalOut, "# Success, closed tableau found.\n");
			fprintf(GlobalOut, "# SZS status Theorem");
			return closed_tableau;
		}
		PStackPushStack(new_tableaux, tmp_new_tableaux);
		PStackFree(tmp_new_tableaux);
		active_tableau = active_tableau->master_succ;
	}
	
	// Went through all possible tableaux... failure
	return NULL;
}

/*  As ConnectionTableauSerial, but builds tableau on all start rule
 *  applications at once.  Does not use any multhreading.
*/

Clause_p ConnectionTableauBatch(ProofState_p proofstate, ProofControl_p proofcontrol, TB_p bank, ClauseSet_p active, int max_depth, int tableauequality)
{
   problemType = PROBLEM_FO;
   PList_p conjectures = PListAlloc();
   PList_p non_conjectures = PListAlloc();
   //bool conjectures_present = false;
   ClauseSet_p extension_candidates = NULL;
   ClauseSetSplitConjectures(active, conjectures, non_conjectures);
   if (PListEmpty(conjectures))
   {
		printf("# No conjectures.\n");
		extension_candidates = ClauseSetCopy(bank, active);
	}
	else
	{
		//conjectures_present = true;
		extension_candidates = ClauseSetAlloc();
		PList_p handle;
		for(handle=conjectures->succ;
		handle != conjectures;
		handle = handle->succ)
		{
			Clause_p conj_handle = handle->key.p_val;
			printf("# Conjecture clause: ");ClausePrint(GlobalOut, conj_handle, true);printf("\n");
			ClauseSetExtractEntry(conj_handle);
			ClauseSetProp(conj_handle, CPTypeConjecture);
			ClauseSetInsert(extension_candidates, conj_handle);
		}
		
	}
   assert(max_depth);
   ClauseSet_p unit_axioms = ClauseSetAlloc();
   
   if (extension_candidates->members == 0) // Should not happen...
   {
		ClauseSetInsertSet(extension_candidates, unit_axioms);
	}
   
   ClauseTableau_p initial_tab = ClauseTableauAlloc();
   ClauseTableau_p resulting_tab = NULL;
   TableauSet_p distinct_tableaux = TableauMasterSetAlloc();
   
   initial_tab->open_branches = TableauSetAlloc();
   TableauSet_p open_branches = initial_tab->open_branches;
   TableauSetInsert(open_branches, initial_tab);
   
   FunCode max_var = ClauseSetGetMaxVar(active);
   assert(max_var <= 0);
   
   initial_tab->terms = bank;
   initial_tab->signature = NULL;
   initial_tab->state = NULL;
   
   //  Move all of the unit clauses to be on the initial tableau
   initial_tab->unit_axioms = unit_axioms;
   
	ClauseTableau_p beginning_tableau = NULL;
	
	// Create a tableau for each axiom using the start rule
   Clause_p start_label = extension_candidates->anchor->succ;
   while (start_label != extension_candidates->anchor)
   {
		if (ClauseQueryProp(start_label, CPTypeConjecture))
		{
			printf("# Conjecture start rule!\n");
		}
		beginning_tableau = ClauseTableauMasterCopy(initial_tab);
		beginning_tableau->max_var = max_var;
		TableauMasterSetInsert(distinct_tableaux, beginning_tableau);
		beginning_tableau = TableauStartRule(beginning_tableau, start_label);
		start_label = start_label->succ;
	}
	
	if (active->members > 0)
	{
		while (!ClauseSetEmpty(active))
		{
			Clause_p non_conj = ClauseSetExtractFirst(active);
			ClauseSetInsert(extension_candidates, non_conj);
		}
	}
	if (tableauequality)
	{
		ClauseSet_p equality_axioms = EqualityAxioms(bank);
		ClauseSetInsertSet(extension_candidates, equality_axioms);
		ClauseSetFree(equality_axioms);
	}
	ClauseTableauFree(initial_tab);  // Free the  initialization tableau used to make the tableaux with start rule
	
	printf("# Start rule applications: %ld\n", distinct_tableaux->members);
	
	VarBankPushEnv(bank->vars);
	PStack_p new_tableaux = PStackAlloc();  // The collection of new tableaux made by extionsion rules.
	// New tableaux are added to the collection of distinct tableaux when the depth limit is increased, as new
	// tableaux are already at the max depth.  
	for (int current_depth = 1; current_depth < max_depth; current_depth++)
	{
		assert(proofstate);
		assert(proofcontrol);
		assert(distinct_tableaux);
		assert(extension_candidates);
		assert(current_depth);
		assert(new_tableaux);
		resulting_tab = ConnectionTableauProofSearch(proofstate, proofcontrol, distinct_tableaux, // This is where the magic happens
													 extension_candidates, 
													 current_depth,
													 new_tableaux);
		long num_moved = move_new_tableaux_to_distinct(distinct_tableaux, new_tableaux);
		if (num_moved == 0) printf("# No new tableaux???\n");
		printf("# Increasing maximum depth to %d\n", current_depth + 1);
		if (resulting_tab)
		{
			//ClauseTableauPrintDOTGraph(resulting_tab);
			printf("Closed tableau found before increasing depth!\n");
			break;
		}
	}
	
	PStackFree(new_tableaux);
	ClauseSetFree(extension_candidates);
	ClauseSetFree(unit_axioms);
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

ClauseTableau_p ConnectionCalculusExtendOpenBranches(ClauseTableau_p active_tableau, PStack_p new_tableaux,
																							TableauControl_p control,
																							TableauSet_p distinct_tableaux,
																							ClauseSet_p extension_candidates,
																							int max_depth)
{
	PStack_p tab_tmp_store = PStackAlloc();
	PStack_p tab_trash = PStackAlloc();
	int number_of_extensions = 0;
	
	ClauseTableau_p open_branch = active_tableau->open_branches->anchor->succ;
	while (open_branch != active_tableau->open_branches->anchor) // iterate over the open branches of the current tableau
	{
		//printf("Branch iter\n");
		if (open_branch->depth > max_depth)
		{
			//depth_exceeded = true;
			open_branch = open_branch->succ;
			//printf("# Max depth exceeded on branch\n");
			continue;
		}
		int fold_close_cycle_test = FoldUpCloseCycle(open_branch->master);
		//printf("Foldup close cycle: %d\n", fold_close_cycle_test);
		if (fold_close_cycle_test > 0)
		{
			//printf("# Branches closed, resetting to first open branch.\n");
			open_branch = active_tableau->open_branches->anchor->succ;
		}
		else if (fold_close_cycle_test == 0);
		else
		{
			//printf("# Closed tableau found in fold-close cycle.\n");
			assert(active_tableau->open_branches->members == 0);
			bool all_branches_closed = ClauseTableauMarkClosedNodes(active_tableau);
			fprintf(GlobalOut, "# SZS status Theorem\n");
			return active_tableau;
		}

		Clause_p selected = extension_candidates->anchor->succ;
		while (selected != extension_candidates->anchor) // iterate over the clauses we can split on the branch
		{
			//printf("Ext candidate iter\n");
			int branch_extensions = 0;
			branch_extensions += ClauseTableauExtensionRuleAttemptOnBranch(control,
																									open_branch,
																									distinct_tableaux,
																									selected,
																									tab_tmp_store);
			number_of_extensions += branch_extensions;
			//printf("# Did %d extensions on open branch of depth %d\n", number_of_extensions, open_branch->depth);
			if (control->closed_tableau)
			{
				fprintf(GlobalOut, "# SZS status Theorem\n");
				return control->closed_tableau;
			}
			if (branch_extensions == 0)
			{
				printf("Failed to extend on a branch, should clear tab_tmp_store and move to new tableau.\n");
				break;
			}
			selected = selected->succ;
		}
		// If we extended on the open branch with one or more clause, we need to move to a new active tableau.
		
		PStackPushStack(new_tableaux, tab_tmp_store);
		
		open_branch = open_branch->succ;
	}
	return NULL;
}
