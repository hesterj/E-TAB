#include "extension.h"
#include "clausetableaux.h"

TableauExtension_p TableauExtensionAlloc(Clause_p selected,
										 Subst_p subst, 
										 Clause_p head_clause, 
										 ClauseSet_p other_clauses, 
										 ClauseTableau_p parent)
{
	TableauExtension_p handle = TableauExtensionCellAlloc();
	handle->selected = selected;
	handle->subst = subst;
	handle->head_clause = head_clause;
	handle->other_clauses = other_clauses;
	handle->parent = parent;
	handle->succ = NULL;
	return handle;
}

/*  Does not free all objects pointed to.  For use after an extension step has been done.
 * 
*/

void TableauExtensionFree(TableauExtension_p ext)
{
	//SubstDelete(ext->subst);
	//ClauseFree(ext->head_clause);
	//ClauseSetFree(ext->other_clauses);
	TableauExtensionCellFree(ext);
}

ClauseSet_p ClauseStackToClauseSet(ClauseStack_p stack)
{
	PStackPointer number_of_clauses = PStackGetSP(stack);
	ClauseSet_p clauses = ClauseSetAlloc();
	for (PStackPointer i=0; i<number_of_clauses; i++)
	{
		ClauseSetInsert(clauses, PStackElementP(stack, i));
	}
	return clauses;
}

/*-----------------------------------------------------------------------
//
// Function: ClauseSetFreeAnchor()
//
//   Delete a clauseset anchor, removing the clauses from the set but not free'ing them.
//   Warning: May cause memory leaks if you lose track of the clauses!
//
// Global Variables: -
//
// Side Effects    : Memory operations
//
/----------------------------------------------------------------------*/

void ClauseSetFreeAnchor(ClauseSet_p junk)
{
   assert(junk);

   Clause_p handle = NULL;
   
   while ((handle = ClauseSetExtractFirst(junk)))
   {
	   // extract all of the clauses
   }

   if(junk->demod_index)
   {
      PDTreeFree(junk->demod_index);
   }
   if(junk->fvindex)
   {
      FVIAnchorFree(junk->fvindex);
   }
   PDArrayFree(junk->eval_indices);
   ClauseCellFree(junk->anchor);
   DStrFree(junk->identifier);
   ClauseSetCellFree(junk);
}

ClauseSet_p SplitClauseFresh(TB_p bank, Clause_p clause)
{
	ClauseSet_p set = ClauseSetAlloc();
	VarBankSetVCountsToUsed(bank->vars);
	Clause_p fresh_clause = ClauseCopyFresh(clause);
	Eqn_p literals = EqnListCopy(fresh_clause->literals, bank);
	Eqn_p lit = NULL;
	Clause_p leaf_clause = NULL;
	short literal_number = ClauseLiteralNumber(fresh_clause);
	for (short i=0; i < literal_number; i++)
	{
		lit = EqnListExtractFirst(&literals);
		leaf_clause = ClauseAlloc(lit);
		ClauseSetInsert(set, leaf_clause);
	}
	EqnListFree(literals);
	ClauseFree(fresh_clause);
	assert(set->members == literal_number);
	return set;
}

/*  Actually does an extension rule application.  head_literal_location is the PStackPointer corresponding of the head clause in 
 * 	new_leaf_clauses.  literal_number is the number of literals in the clause that is being split in the extension rule application.
 *  This method is only called by ClauseTableauExtensionRuleAttempt.  If this method is called there is likely a Subst_p active!
*/

ClauseTableau_p ClauseTableauExtensionRule(TableauSet_p distinct_tableaux, TableauExtension_p extension)
{
	// Create a copy of the master tableau of the extension rule's tableau.
	// Insert the newly created master tableau in to the distinct_tableaux. 
	ClauseTableau_p old_tableau_master = extension->parent->master;
	old_tableau_master->active_branch = extension->parent;
	ClauseTableau_p tableau_copy = ClauseTableauMasterCopy(old_tableau_master);  //there may be a subst active
	
	assert(extension->parent->id == 0);
	assert(old_tableau_master->parent == NULL);
	assert(distinct_tableaux);
	assert(tableau_copy->open_branches);
	assert(tableau_copy->open_branches->members > 0);
	assert(tableau_copy->active_branch);
	assert(tableau_copy->master == tableau_copy);
	assert(extension->selected);
	
	TableauMasterSetInsert(distinct_tableaux, tableau_copy);
	
	// Do the extension rule on the active branch of the newly created tableau
	
	ClauseTableau_p parent = tableau_copy->active_branch;
	if (extension->selected->ident >= 0) parent->id = extension->selected->ident;
	else parent->id = extension->selected->ident - LONG_MIN;
	
	// 
	
	Clause_p head_literal_clause = NULL;
	TB_p bank = parent->terms;
	ClauseSet_p new_leaf_clauses_set = ClauseSetAlloc(); // Copy the clauses of the extension
	for (Clause_p handle = extension->other_clauses->anchor->succ;
					  handle != extension->other_clauses->anchor;
					  handle = handle->succ)
	{
		Clause_p subst_applied = ClauseCopy(handle, bank);
		ClauseSetInsert(new_leaf_clauses_set, subst_applied);
		if (extension->head_clause == handle)
		{
			head_literal_clause = subst_applied;
		}
	}
	long number_of_children = new_leaf_clauses_set->members;
	
	assert(head_literal_clause);
	assert(number_of_children == extension->other_clauses->members);
	assert(head_literal_clause->set == new_leaf_clauses_set);
	
	parent->children = ClauseTableauArgArrayAlloc(number_of_children);
	Clause_p leaf_clause = NULL;
	// Create children tableau for the leaf labels.  The head literal is labelled as closed.
	for (long p=0; p < number_of_children; p++)
	{
		leaf_clause = ClauseSetExtractFirst(new_leaf_clauses_set);
		assert(leaf_clause);
		parent->children[p] = ClauseTableauChildLabelAlloc(parent, leaf_clause);
		if (leaf_clause == head_literal_clause)
		{
			parent->children[p]->open = false; 
			parent->children[p]->head_lit = true;
		}
		else
		{
			TableauSetInsert(parent->open_branches, parent->children[p]);
			parent->children[p]->open = true;
		}
	}
	// The work is done- try to close the remaining branches
	SubstDelete(extension->subst);
	for (long p = 0; p<number_of_children; p++)
	{
		ClauseTableau_p child = parent->children[p];
		if (child->open)
		{
			if (ClauseTableauBranchClosureRuleWrapper(child))
			{
				TableauSetExtractEntry(child);
				child->open = false;
			}
		}
	}
	
	if (parent->master->open_branches->members == 0)
	{
		printf("Found closed tableau early in extension.\n");
		exit(0);
	}
	
	assert(number_of_children == parent->arity);
	assert(parent->set);
	assert(parent->open);
	assert(parent->arity == number_of_children);
	TableauSetExtractEntry(parent);
	parent->open = false;
	
	// There is no need to apply the substitution to the tablaeu, it has already been done by copying labels.
	ClauseSetFreeAnchor(new_leaf_clauses_set); // the members of this set are now labels
	return parent;
}

/*  Do all of the extension rules possible with the selected clause.
 *  There may be multiple literals extension can be done with.
 *  The resulting tableaux are added to distinct_tableaux.
 *  At the end, when all of the new tableaux are created, the original tableau is removed from
 *  distinct_tableaux.
*/

int ClauseTableauExtensionRuleAttemptOnBranch(ClauseTableau_p open_branch, 
															 TableauSet_p distinct_tableaux,
															 Clause_p selected)
{
	int extensions_done = 0;
	ClauseSet_p new_leaf_clauses = SplitClauseFresh(open_branch->terms, selected);
	//ClauseTableau_p parent = open_branch->parent;
	Subst_p subst = NULL;
	Clause_p leaf_clause = new_leaf_clauses->anchor->succ;
	
	//assert(open_branch->master->master_set);
	while (leaf_clause != new_leaf_clauses->anchor)
	{
		assert(open_branch);
		assert(open_branch != open_branch->open_branches->anchor);
		assert(open_branch->parent);
		assert(open_branch->label);
		assert(open_branch->arity == 0);
		assert(leaf_clause);
		assert(selected);
		
		// Here we are only doing the first possible extension- need to create a list of all of the extensions and do them...
		// The subst, leaf_clause, new_leaf_clauses, will have to be reset, but the open_branch can remain the same since we have not affected it.
		if ((subst = ClauseContradictsClause(open_branch, leaf_clause, open_branch->label))) // stricter extension step
		{
			printf("\033[1;31m");
			printf("Extension step possible! d%da%d\n", open_branch->depth, ClauseLiteralNumber(selected));
			printf("\033[0m");
			Clause_p head_clause = leaf_clause;
			TableauExtension_p extension_candidate = TableauExtensionAlloc(selected, 
																		   subst, 
																		   head_clause, 
																		   new_leaf_clauses, 
																		   open_branch);
			ClauseTableauExtensionRule(distinct_tableaux, extension_candidate);
			TableauExtensionFree(extension_candidate);
			extensions_done++;
			if (open_branch->open_branches->members == 0)
			{
				return extensions_done;
			}
			// The substitution has been deleted, the tableau parent is unchanged, so we can continue.
		}
		leaf_clause = leaf_clause->succ;
	}
   
   //  OK We're done
   ClauseSetFree(new_leaf_clauses);
	return extensions_done;
}
