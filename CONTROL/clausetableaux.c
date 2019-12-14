#include "clausetableaux.h"

int clausesetallocs_counter = 1;  

// Functions for clausetableaux.h

/*  The open branches for each distinct tableau MUST be initialized on creation,
 *  not by this method.
 * 
 * 
*/

ClauseTableau_p ClauseTableauAlloc()
{
	ClauseTableau_p handle = ClauseTableauCellAlloc();
	handle->depth = 0;
	handle->position = 0;
	handle->arity = 0;
	handle->unit_axioms = NULL;
	//handle->mark = NULL;
	handle->mark_int = 0;
	handle->folding_labels = NULL;
	handle->set = NULL;
	handle->head_lit = false;
	handle->id = 0;
	handle->max_var = 0;
	handle->info = NULL;
	handle->master_set = NULL;
	handle->active_branch = NULL;
	handle->pred = NULL;
	handle->control = NULL;
	handle->succ = NULL;
	handle->master_pred = NULL;
	handle->master_succ = NULL;
	handle->open_branches = NULL;
	handle->children = NULL;
	handle->label = NULL;
	handle->master = handle;
	handle->parent = NULL;
	handle->open = true;
	return handle;
}

/*  This copies the master node of a tableau and its children,
 *  set up for use with method of connection tableaux.
 * 
*/

ClauseTableau_p ClauseTableauMasterCopy(ClauseTableau_p tab)
{
	assert(tab->master == tab);  // Masters have themselves as master
	TB_p bank = tab->terms;
	
	ClauseTableau_p handle = ClauseTableauCellAlloc();
	handle->arity = tab->arity;
	handle->info = NULL;
	handle->depth = tab->depth;
	handle->position = tab->position;
	
	assert(handle->depth == 0);
	assert(tab->unit_axioms);
	
	//handle->unit_axioms = ClauseSetCopy(bank, tab->unit_axioms);
	handle->unit_axioms = tab->unit_axioms;
	handle->set = NULL;
	handle->master_set = NULL;
	handle->pred = NULL;
	handle->id = tab->id;
	handle->mark_int = tab->mark_int;
	/*
	if (tab->mark)
	{
		handle->mark = ClauseCopy(tab->mark, bank);
	}
	else
	{
		handle->mark = NULL;
	}
	*/
	if (tab->folding_labels)
	{
		handle->folding_labels = ClauseSetCopy(bank, tab->folding_labels);
	}
	else
	{
		handle->folding_labels = NULL;
	}
	handle->head_lit = tab->head_lit;
	handle->succ = NULL;
	handle->master_pred = NULL;
	handle->master_succ = NULL;
	handle->active_branch = NULL;
	handle->max_var = tab->max_var;
	handle->open_branches = TableauSetAlloc();
	handle->terms = tab->terms;
	handle->control = tab->control;
	
	if (tab->label)
	{
		handle->label = ClauseCopy(tab->label, bank);
		assert(handle->label);
	}
	else 
	{
		handle->label = NULL;
	}
	handle->master = handle;
	handle->parent = NULL;
	
	if (tab->arity == 0) // tab does not have children
	{
		handle->open = true;
		TableauSetInsert(handle->open_branches, handle);
	}
	else
	{
		handle->open = tab->open;
	}
	
	if (tab->arity)
	{
		handle->children = ClauseTableauArgArrayAlloc(tab->arity);
		for (int i=0; i<tab->arity; i++)
		{
			handle->children[i] = ClauseTableauChildCopy(tab->children[i], handle);
		}
	}
	else 
	{
		handle->children = NULL;
	}
	return handle;
}

ClauseTableau_p ClauseTableauChildCopy(ClauseTableau_p tab, ClauseTableau_p parent)
{
	TB_p bank = tab->terms; //Copy tableau tab
	assert(parent->unit_axioms);
	ClauseTableau_p handle = ClauseTableauCellAlloc();
	handle->unit_axioms = parent->unit_axioms;
	handle->info = NULL;
	handle->open_branches = parent->open_branches;
	handle->control = parent->control;
	handle->set = NULL;
	handle->id = tab->id;
	handle->head_lit = tab->head_lit;
	handle->max_var = parent->max_var;
	handle->active_branch = NULL;
	handle->signature = parent->signature;
	handle->terms = parent->terms;
	handle->mark_int = tab->mark_int;
	handle->parent = parent;
	handle->master = parent->master;
	handle->depth = 1+parent->depth;
	handle->position = tab->position;
	assert(handle->depth > 0);
	assert((handle->depth = parent->depth + 1));
	handle->state = parent->state;
	handle->open = tab->open;
	handle->arity = tab->arity;
	/*
	if (tab->mark)
	{
		handle->mark = ClauseCopy(tab->mark, bank);
	}
	else
	{
		handle->mark = NULL;
	}
	*/
	if (tab->folding_labels)
	{
		handle->folding_labels = ClauseSetCopy(bank, tab->folding_labels);
	}
	else
	{
		handle->folding_labels = NULL;
	}
	if (tab->master->active_branch == tab)
	{
		handle->master->active_branch = handle;
		assert(handle->arity == 0);
	}
	
	if (tab->label)
	{
		handle->label = ClauseCopy(tab->label, handle->terms);
		assert(handle->label);
	}
	else
	{
		tab->label = NULL;
	}
	if ((handle->arity == 0) && (handle->open)) // If one of the open branches is found during copying, add it to the collection of open branches
	{
		TableauSetInsert(handle->open_branches, handle);
	}
	
	if (tab->arity)
	{
		handle->children = ClauseTableauArgArrayAlloc(tab->arity);
		
		for (int i=0; i<tab->arity; i++)
		{
			handle->children[i] = ClauseTableauChildCopy(tab->children[i], handle);
		}
	}
	else 
	{
		handle->children = NULL;
	}
	
	return handle;
}

void ClauseTableauInitialize(ClauseTableau_p handle, ProofState_p initial)
{
	handle->signature = initial->signature;
	handle->state = initial;
	handle->terms = initial->terms;
}

ClauseTableau_p ClauseTableauChildAlloc(ClauseTableau_p parent, int position)
{
	ClauseTableau_p handle = ClauseTableauCellAlloc();
	parent->open = true; // We only want leaf nodes in the collection of open breanches
	
	handle->unit_axioms = parent->unit_axioms;
	handle->open_branches = parent->open_branches;
	handle->depth = parent->depth + 1;
	handle->position = position;
	handle->control = parent->control;
	handle->label = NULL;
	handle->max_var = parent->max_var;
	handle->info = NULL;
	handle->active_branch = NULL;
	handle->set = NULL;
	handle->mark_int = 0;
	//handle->mark = NULL;
	handle->folding_labels = NULL;
	handle->id = 0;
	handle->head_lit = false;
	handle->master_set = NULL;
	handle->pred = NULL;
	handle->succ = NULL;
	handle->master_pred = NULL;
	handle->master_succ = NULL;
	handle->children = NULL;
	handle->signature = parent->signature;
	handle->terms = parent->terms;
	handle->parent = parent;
	handle->master = parent->master;
	handle->state = parent->state;
	handle->open = true;
	handle->arity = 0;
	return handle;
}

ClauseTableau_p ClauseTableauChildLabelAlloc(ClauseTableau_p parent, Clause_p label, int position)
{
	ClauseTableau_p handle = ClauseTableauCellAlloc();
	assert(parent);
	assert(label);
	parent->arity += 1;
	handle->depth = parent->depth + 1;
	handle->position = position;
	handle->unit_axioms = parent->unit_axioms;
	handle->open_branches = parent->open_branches;
	handle->label = label;
	handle->id = 0;
	handle->head_lit = false;
	handle->control = parent->control;
	handle->max_var = parent->max_var;
	handle->set = NULL;
	//handle->mark = NULL;
	handle->mark_int = 0;
	handle->folding_labels = NULL;
	handle->info = NULL;
	handle->active_branch = NULL;
	handle->master_set = NULL;
	handle->pred = NULL;
	handle->succ = NULL;
	handle->master_pred = NULL;
	handle->master_succ = NULL;
	handle->signature = parent->signature;
	handle->children = NULL;
	handle->terms = parent->terms;
	handle->parent = parent;
	handle->master = parent->master;
	handle->state = parent->state;
	handle->open = true;
	handle->arity = 0;
	assert(!handle->set);
	return handle;
}

/*  Sets the relevant fields to NULL after free'ing
*/

void ClauseTableauFree(ClauseTableau_p trash)
{
	if (trash->label)
	{
		ClauseFree(trash->label);
		trash->label = NULL;
	}
	if (trash->info)
	{
		DStrFree(trash->info);
	}
	/*
	if (trash->mark)
	{
		ClauseFree(trash->mark);
	}
	*/
	if (trash->folding_labels)
	{
		ClauseSetFree(trash->folding_labels);
	}
	if (trash->children)
	{
		for (int i=0; i<trash->arity; i++)
		{
			ClauseTableauFree(trash->children[i]);
			trash->children[i] = NULL;
		}
		ClauseTableauArgArrayFree(trash->children, trash->arity);
		trash->children = NULL;
	}
	if (trash->depth == 0 && trash->open_branches)
	{
		TableauSetFree(trash->open_branches);
		trash->open_branches = NULL;
	}
	/*
	if (trash->depth == 0 && trash->unit_axioms)
	{
		ClauseSetFree(trash->unit_axioms);
		trash->unit_axioms = NULL;
	}
	*/
	ClauseTableauCellFree(trash);
}

void HCBClauseSetEvaluate(HCB_p hcb, ClauseSet_p clauses)
{
	Clause_p handle = clauses->anchor->succ;
	while (handle != clauses-> anchor)
	{
		HCBClauseEvaluate(hcb, handle);
		handle = handle->succ;
	}
}

/*  Apply subst to the entire tableau
*/

void ClauseTableauApplySubstitution(ClauseTableau_p tab, Subst_p subst)
{
	if (PStackGetSP(subst) == 0)
	{
		return;
	}
	
	ClauseTableau_p master = tab->master;
	ClauseTableauApplySubstitutionToNode(master, subst);
}

FunCode ClauseSetGetMaxVar(ClauseSet_p set)
{
	FunCode max_funcode = 0;
	Clause_p start_label = set->anchor->succ;
   PStack_p start_subterms = PStackAlloc();
   while (start_label != set->anchor)
   {
		ClauseCollectSubterms(start_label, start_subterms);
		start_label = start_label->succ;
	}
	Term_p temp_term = NULL;
	for (PStackPointer p = 0; p<PStackGetSP(start_subterms); p++)
	{
		temp_term = PStackElementP(start_subterms, p);
		if (TermIsVar(temp_term))
		{
			FunCode var_funcode = temp_term->f_code;
			//printf("%ld ", var_funcode);
			if (var_funcode <= max_funcode)
			{
				max_funcode = var_funcode;
			}
		}
	}
	//printf("\n");
	PStackFree(start_subterms);
	if (max_funcode == 0)
	{
		return -2;
	}
	//printf("max_funcode: %ld\n", max_funcode);
	return max_funcode;
}

/*  Recursively apply subst to the clauses in tab, and tab's children
*/

void ClauseTableauApplySubstitutionToNode(ClauseTableau_p tab, Subst_p subst)
{
	
	assert(tab->label);
	
	Clause_p new_label = ClauseCopy(tab->label, tab->terms);
	ClauseFree(tab->label);
	assert(new_label);
	tab->label = new_label;
	
	for (int i=0; i<tab->arity; i++)
	{
		ClauseTableauApplySubstitutionToNode(tab->children[i], subst);
	}
}

/*-----------------------------------------------------------------------
//
// Function: TFormulaNegAlloc()
//
//   Return a formula equivalent to ~form. If form is of the form ~f,
//   return f, otherwise ~form.
//
// Global Variables: -
//
// Side Effects    : Memory operations
//
/----------------------------------------------------------------------*/
/*
TFormula_p TFormulaNegAlloc(TB_p terms, TFormula_p form)
{
   if(form->f_code == terms->sig->not_code)
   {
      return form->args[0];
   }
   return TFormulaFCodeAlloc(terms, terms->sig->not_code,
                             form, NULL);
}
*/

/*  Checks if clause directly contradicts another, using a most general unifier. 
 *  If so, return true and APPLY THE SUBSTITUTION USED TO THE ENTIRE TABLEAU (!)
*/

Subst_p ClauseContradictsClauseOld(ClauseTableau_p tab, Clause_p a, Clause_p b)
{
	if (a==b) return NULL;  // Easy case...
	
	//printf("Checking ClauseContradictsClause\n");
	
	if (ClauseLiteralNumber(a) != 1 || ClauseLiteralNumber(b) != 1) return NULL; //Only interested in unit contradiction
	
	TB_p bank = tab->terms;
	TFormula_p a_neg, b_neg, a_neg_nnf, b_neg_nnf;
	
	Subst_p subst;
	TFormula_p a_tform = TFormulaClauseEncode(tab->terms, a);
	TFormula_p b_tform = TFormulaClauseEncode(tab->terms, b);
	
	a_neg = TFormulaNegAlloc(bank, a_tform);
	b_neg = TFormulaNegAlloc(bank, b_tform);
	a_neg_nnf = TFormulaNNF(bank, a_neg, 1);
	b_neg_nnf = TFormulaNNF(bank, b_neg, 1);
	
	a_neg = TermDerefAlways(a_neg);
	b_neg = TermDerefAlways(b_neg);
	a_neg_nnf = TermDerefAlways(a_neg_nnf);
	b_neg_nnf = TermDerefAlways(b_neg_nnf);
	
	subst = SubstAlloc();

	if (SubstComputeMgu(a_tform, b_neg_nnf, subst))
	{
		printf("# Contradiction: ");
		ClausePrint(GlobalOut, a, true);
		printf("   ");
		ClausePrint(GlobalOut, b, true);
		printf("\n");
		if (!PStackGetSP(subst))
		{
			return subst;
		}
		
		return subst;
	}
	else if (SubstComputeMgu(b_tform, a_neg_nnf, subst))
	{
		printf("# Contradiction: ");
		ClausePrint(GlobalOut, a, true);
		printf("   ");
		ClausePrint(GlobalOut, b, true);
		printf("\n");
		if (!PStackGetSP(subst))
		{
			return subst;
		}
		
		return subst;
	}
	SubstDelete(subst);
	
	return NULL;
}

Subst_p ClauseContradictsClause(ClauseTableau_p tab, Clause_p a, Clause_p b)
{
	assert (tab && a && b);
	if (a==b) return NULL;  // Easy case...
	if (!ClauseIsUnit(a) || !ClauseIsUnit(b)) return NULL;
	Eqn_p a_eqn = a->literals;
	Eqn_p b_eqn = b->literals;
	//TB_p bank = tab->terms;
	
	if (EqnIsPositive(a_eqn) && EqnIsPositive(b_eqn)) return NULL;
	if (EqnIsNegative(a_eqn) && EqnIsNegative(b_eqn)) return NULL;
	
	Subst_p subst = SubstAlloc();
	
	if (EqnUnify(a_eqn, b_eqn, subst))
	{
		return subst;
	}
	
	SubstDelete(subst);
	
	return NULL;
}

ClauseSet_p ClauseSetFlatCopy(TB_p bank, ClauseSet_p set)
{
	Clause_p handle, temp;
	ClauseSet_p new = ClauseSetAlloc();
	for (handle = set->anchor->succ; handle != set->anchor; handle = handle->succ)
	{
		temp = ClauseFlatCopy(handle);
		ClauseSetInsert(new, temp);
	}
	return new;
}

ClauseSet_p ClauseSetCopy(TB_p bank, ClauseSet_p set)
{
	Clause_p handle, temp;
	assert(set);
	ClauseSet_p new = ClauseSetAlloc();
	for (handle = set->anchor->succ; handle != set->anchor; handle = handle->succ)
	{
		assert(handle);
		temp = ClauseCopy(handle,bank);
		ClauseSetInsert(new, temp);
	}
	return new;
}

/*
*/

ClauseSet_p ClauseSetApplySubstitution(TB_p bank, ClauseSet_p set, Subst_p subst)
{
	Clause_p handle, temp;
	ClauseSet_p new = ClauseSetAlloc();
	
	for (handle = set->anchor->succ; handle != set->anchor; handle = handle->succ)
	{
		temp = ClauseCopy(handle, bank);
		ClauseSetInsert(new, temp);
	}
	return new;
}

/*  Needs testing
*/

Subst_p ClauseContradictsSet(ClauseTableau_p tab, Clause_p leaf, ClauseSet_p set)
{
	assert(set->anchor);
	Clause_p handle = set->anchor->succ;
	Subst_p subst = NULL;
	while (handle != set->anchor)
	{
		if ((subst = ClauseContradictsClause(tab, leaf, handle)))
		{
			return subst;
		}
		handle = handle->succ;
	}
	return NULL;
}

/* Should only be called on closed tableau, as in order to collect the leaves, open branches
 *  must be removed from their tableau set.
*/

void ClauseTableauPrint(ClauseTableau_p tab)
{
	//TableauSet_p leaves = TableauSetAlloc();
	PStack_p leaves = PStackAlloc();
	ClauseTableauCollectLeavesStack(tab, leaves);
	//ClauseTableauCollectLeaves(tab, leaves);
	//ClauseTableau_p handle = leaves->anchor->succ;
	printf("# Printing the branches of the tableau:\n");
	/*
	while ((handle = TableauSetExtractFirst(leaves)))
	{
		ClauseTableauPrintBranch(handle);printf("\n");
	}
	*/
	for (PStackPointer p = 0; p<PStackGetSP(leaves); p++)
	{
		ClauseTableau_p handle = PStackElementP(leaves, p);
		ClauseTableauPrintBranch(handle);printf("\n");
	}
	//TableauSetFree(leaves);
	PStackFree(leaves);
	printf("\n# Done.\n");
}

bool TableauDominatesNode(ClauseTableau_p tab, ClauseTableau_p node)
{
	ClauseTableau_p climber = node;
	while (climber)
	{
		if (climber == tab) return true;
		climber = climber->parent;
	}
	return false;
}

/*  Only call on closed tableau.  Collects the leaves (no children nodes).
 * 
*/

void ClauseTableauCollectLeaves(ClauseTableau_p tab, TableauSet_p leaves)
{
	if (tab->arity == 0) // found a leaf
	{
		assert(!tab->set);
		TableauSetInsert(leaves, tab);
	}
	for (int i=0; i<tab->arity; i++)
	{
		ClauseTableauCollectLeaves(tab->children[i], leaves);
	}
}

/*  
 * Collects the leaves below a tableau node
*/

void ClauseTableauCollectLeavesStack(ClauseTableau_p tab, PStack_p leaves)
{
	if (tab->arity == 0) // found a leaf
	{
		PStackPushP(leaves, tab);
	}
	for (int i=0; i<tab->arity; i++)
	{
		ClauseTableauCollectLeavesStack(tab->children[i], leaves);
	}
}

/*  Checks clause for contradiction against the nodes of tab
 *  Used to avoid allocating tableau children until we know there is a successful extension
 * 
*/

Subst_p ClauseContradictsBranch(ClauseTableau_p tab, Clause_p clause)
{
	assert(tab);
	assert(tab->label);
	assert(tab->unit_axioms);
	Subst_p subst = NULL;
	Clause_p parent_label;
	// Check against the unit axioms
	Clause_p unit_handle = tab->unit_axioms->anchor->succ;
	while (unit_handle != tab->unit_axioms->anchor)
	{
		assert(unit_handle);
		Clause_p fresh_unit = ClauseCopyFresh(unit_handle, tab);
		if ((subst = ClauseContradictsClause(tab, clause, unit_handle)))
		{
			ClauseFree(fresh_unit);
			tab->mark_int = (tab->depth)-1; // mark the root node
			return subst;
		}
		ClauseFree(fresh_unit);
		unit_handle = unit_handle->succ;
	}
	
	// Check against the tableau
	if ((subst = ClauseContradictsClause(tab, tab->label, clause)))
	{
		tab->mark_int = 0; // this shouldn't happen- marking itself?
		return subst;
	}
	ClauseTableau_p temporary_tab = tab;
	int distance_up = 1;
	while (temporary_tab->parent)
	{
		parent_label = temporary_tab->parent->label;
		if ((subst = ClauseContradictsClause(tab, parent_label, clause)))
		{
			tab->mark_int = distance_up;
			printf("distance_up: %d\n", distance_up);
			return subst;
		}
		distance_up += 1;
		temporary_tab = temporary_tab->parent;
	}
	
	return subst;
}

/*  Simple wrapper for branch contradiction testing
 *  Checks the label of tab for contradiction against the labels of its parents
*/

bool ClauseTableauBranchClosureRuleWrapper(ClauseTableau_p tab)
{
	Subst_p subst;
	assert(tab);
	assert(tab->label);
	if ((subst = ClauseContradictsBranch(tab, tab->label)))
	{
		if (!PStackGetSP(subst))  // Only subst needed was identity
		{
			SubstDelete(subst);
			return true;
		}
		ClauseTableauApplySubstitution(tab, subst);
		SubstDelete(subst);
		return true;
	}
	return false;
}

void ClauseTableauPrintBranch(ClauseTableau_p branch)
{
	ClauseTableau_p depth_check = branch;
	printf("\033[1;33m");
	while (depth_check->depth != 0)
	{
		assert(depth_check->label);
		assert(depth_check->id >= 0);
		printf("%d,%d,%ld,%d ", depth_check->depth,depth_check->arity, depth_check->id,depth_check->mark_int);ClausePrint(GlobalOut, depth_check->label, true);
		if (depth_check->head_lit)
		{
			printf(" x");
		}
		printf("\n");
		depth_check = depth_check->parent;
	}
	assert (depth_check->depth == 0);
	assert (depth_check->label);
	printf("%d,%d,%ld,%d ", depth_check->depth,depth_check->arity, depth_check->id,depth_check->mark_int);ClausePrint(GlobalOut, depth_check->label, true);printf("\n");
	printf("\033[0m");
}

Clause_p ClauseApplySubst(Clause_p clause,  TB_p bank, Subst_p subst)
{
   Clause_p new_clause;
   Term_p variable_in_clause __attribute__((unused));
   assert(clause);
   new_clause = ClauseCopy(clause, bank);
   return new_clause;
}

/*-----------------------------------------------------------------------
//
// Function: ClauseCopyFresh()
//
//   Create a variable-fresh copy of clause.  Every variable that is 
//   in the clause is replaced with a fresh one.  variable_subst is the address of the 
//   substitution replacing the old variables with new ones.  Must be free'd afterwards!
//
//	John Hester
// Global Variables: -
//
// Side Effects    : Memory operations
//
/----------------------------------------------------------------------*/

Clause_p ClauseCopyFresh(Clause_p clause, ClauseTableau_p tableau)
{
   PTree_p variable_tree;
   PStack_p variables;
   PStackPointer p;
   Subst_p subst;
   Term_p old_var, fresh_var;
   Clause_p handle;
   VarBank_p variable_bank;
   
   assert(clause);
   
   variable_bank = clause->literals->bank->vars;
   variables = PStackAlloc();
   variable_tree = NULL;
   //VarBankSetVCountsToUsed(variable_bank);
   subst = SubstAlloc();
   
   ClauseCollectVariables(clause, &variable_tree);
   PTreeToPStack(variables, variable_tree);
   PTreeFree(variable_tree);
   
   //printf("Clause being copied: ");ClausePrint(GlobalOut, clause, true);printf("\n");
   
   for (p = 0; p < PStackGetSP(variables); p++)
   {
	   old_var = PStackElementP(variables, p);
	   //fresh_var = VarBankGetFreshVar(variable_bank, old_var->type);  // 2 is individual sort
	   //printf("tableau max var: %ld\n", tableau->master->max_var);
	   tableau->master->max_var -= 2;
	   fresh_var = VarBankVarAssertAlloc(variable_bank, tableau->master->max_var, old_var->type);
	   assert(fresh_var != old_var);
	   assert(fresh_var->f_code != old_var->f_code);
	   if (fresh_var->f_code == old_var->f_code)
	   {
			//printf("continuing\n"); 
			exit(0);
			continue;
		}
	   SubstAddBinding(subst, old_var, fresh_var);
	   //printf("The subst: %ld %ld\n", fresh_var->f_code, old_var->f_code);
	   //SubstPrint(GlobalOut, subst, tableau->terms->sig, DEREF_NEVER);
	   //printf("\n");
   }
   
	//printf("max_var %ld\n", tableau->master->max_var);
   
   handle = ClauseCopy(clause, clause->literals->bank);
   
   SubstDelete(subst);
   PStackFree(variables);

   return handle;
}


ClauseTableau_p TableauStartRule(ClauseTableau_p tab, Clause_p start)
{
	Eqn_p literals, lit;
	TB_p bank = tab->terms;
	int arity = 0;
	Clause_p new_clause;
	ClauseTableau_p child;
	assert(!(tab->label));
	assert(!(tab->arity));
	assert(tab->master_set);
	assert(start);
	assert(tab->unit_axioms);
	
	arity = ClauseLiteralNumber(start);
	tab->arity = arity;
	tab->open = true;
	TableauSetExtractEntry(tab); // no longer open
	assert(tab->open_branches->members == 0);
	tab->label = ClauseCopy(start, bank);
	assert(tab->label);
	//ClauseGCMarkTerms(tab->label);
	
	if (tab->label->ident >= 0) tab->id = tab->label->ident;
	else tab->id = tab->label->ident - LONG_MIN;
	
	assert(arity > 0);
	tab->children = ClauseTableauArgArrayAlloc(arity);
	literals = EqnListCopy(start->literals, bank);

	for (int i=0; i<arity; i++)
	{
		lit = EqnListExtractFirst(&literals);
		tab->children[i] = ClauseTableauChildAlloc(tab, i);
		child = tab->children[i];
		new_clause = ClauseAlloc(lit);
		ClauseRecomputeLitCounts(new_clause);
		child->label = new_clause;
		//ClauseGCMarkTerms(child->label); // Do not delete clauses that are labels we could use
		assert(child->label);
		TableauSetInsert(child->open_branches, child);
	}
	
	EqnListFree(literals);
	
	return tab;
}

// Goes through the children to tableau to ensure that all of the nodes have labels
// returns number of nodes checked

int ClauseTableauAssertCheck(ClauseTableau_p tab)
{
	int num_nodes = 0;
	assert(tab->label);
	if (tab->parent)
	{
		assert(tab->depth > 0);
	}
	for (int i=0; i<tab->arity; i++)
	{
		assert(tab->children[i]);
		assert(tab->children[i]->depth == tab->depth + 1);
		num_nodes += ClauseTableauAssertCheck(tab->children[i]);
	}
	return num_nodes;
}

TableauSet_p TableauSetAlloc()
{
   TableauSet_p set = TableauSetCellAlloc();

   set->members = 0;
   set->anchor  = ClauseTableauAlloc();
   set->anchor->succ = set->anchor;
   set->anchor->pred = set->anchor;

   return set;
}

TableauSet_p TableauSetCopy(TableauSet_p set)
{
	return NULL;
}

void TableauSetInsert(TableauSet_p list, ClauseTableau_p tab)
{
   assert(list);
   assert(tab);
   assert(!tab->set);

   tab->succ = list->anchor;
   tab->pred = list->anchor->pred;
   list->anchor->pred->succ = tab;
   list->anchor->pred = tab;
   tab->set = list;
   list->members++;
}

ClauseTableau_p TableauSetExtractEntry(ClauseTableau_p fset)
{
   assert(fset);
   assert(fset->set);

   fset->pred->succ = fset->succ;
   fset->succ->pred = fset->pred;
   fset->set->members--;
   fset->set = NULL;
   fset->succ = NULL;
   fset->pred = NULL;

   return fset;
}

ClauseTableau_p   TableauSetExtractFirst(TableauSet_p list)
{
   assert(list);

   if(TableauSetEmpty(list))
   {
      return NULL;
   }
   return TableauSetExtractEntry(list->anchor->succ);
}

/*  Don't actually free the members of set- this must have already been free'd
 * 
 * 
*/

void TableauSetFree(TableauSet_p set)
{
	ClauseTableauCellFree(set->anchor);
	TableauSetCellFree(set);
}

TableauSet_p TableauMasterSetAlloc()
{
   TableauSet_p set = TableauSetCellAlloc();

   set->members = 0;
   set->anchor  = ClauseTableauAlloc();
   set->anchor->master_succ = set->anchor;
   set->anchor->master_pred = set->anchor;

   return set;
}

TableauSet_p TableauMasterSetCopy(TableauSet_p set)
{
	return NULL;
}

void TableauMasterSetInsert(TableauSet_p list, ClauseTableau_p tab)
{
   assert(list);
   assert(tab);
   assert(!tab->master_set);

   tab->master_succ = list->anchor;
   tab->master_pred = list->anchor->master_pred;
   list->anchor->master_pred->master_succ = tab;
   list->anchor->master_pred = tab;
   tab->master_set = list;
   list->members++;
}

ClauseTableau_p TableauMasterSetExtractEntry(ClauseTableau_p fset)
{
   assert(fset);
   assert(fset->master_set);

   fset->master_pred->master_succ = fset->master_succ;
   fset->master_succ->master_pred = fset->master_pred;
   fset->master_set->members--;
   fset->master_set = NULL;
   fset->master_succ = NULL;
   fset->master_pred = NULL;

   return fset;
}

ClauseTableau_p   TableauMasterSetExtractFirst(TableauSet_p list)
{
   assert(list);

   if(TableauMasterSetEmpty(list))
   {
      return NULL;
   }
   return TableauMasterSetExtractEntry(list->anchor->master_succ);
}

void TableauMasterSetFree(TableauSet_p set)
{
	ClauseTableau_p handle = NULL;
	while (set->members > 0)
	{
		handle = TableauMasterSetExtractFirst(set);
		ClauseTableauFree(handle);
	}
	ClauseTableauFree(set->anchor);
	TableauSetCellFree(set);
}
