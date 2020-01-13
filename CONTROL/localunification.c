#include <localunification.h>

/*  This method updates the local variables of the node.
 * This is intended to be used on the leaf node of a branch.
 * Variables that are local (do not occur on any open branch but
 * this one) can be treated with the local extension rule and local
 * reduction rule.
 * 
 *   It first iterates up the branch of the node, collecting
 * all variables of the branch.  Then it iterates up the other 
 * open branches of the tableau, removing any variables that occur 
 * in the other branches.
 * 
 *   The method returns the number of local variables for node's 
 * branch.  The local variables stack of node is deleted if it
 * exists.
*/

long UpdateLocalVariables(ClauseTableau_p node)
{
	long num_variables = 0;
	PTree_p local_variables_tree = NULL;
	if (node->local_variables)
	{
		PStackFree(node->local_variables);
	}
	PStack_p local_variables = PStackAlloc();
	// Collect the variables in the current branch
	
	num_variables += CollectVariablesOfBranch(node, local_variables_tree, true);
	
	// Collect the variables of the other branches
	ClauseTableau_p branch_iterator = node->open_branches->anchor->succ;
	PTree_p temp_variable_tree = NULL;
	long other_branches_vars = 0;
	while (branch_iterator != node->open_branches->anchor)
	{
		if (branch_iterator != node)
		{
			other_branches_vars += CollectVariablesOfBranch(branch_iterator, temp_variable_tree, false);
		}
		branch_iterator = branch_iterator->succ;
	}
	PStack_p other_branches_vars_stack = PStackAlloc();
	other_branches_vars = PTreeToPStack(other_branches_vars_stack, temp_variable_tree);
	PTreeFree(temp_variable_tree);
	
	// If a variable occurs in another branch, remove it from the tree of local variables
	
	for (PStackPointer p = 0; p<PStackGetSP(other_branches_vars_stack); p++)
	{
		PTreeDeleteEntry(&local_variables_tree, PStackPopP(other_branches_vars_stack));
	}
	num_variables = PTreeToPStack(local_variables, local_variables_tree);
	printf("Local variables:\n");
	PTreeDebugPrint(GlobalOut, local_variables_tree);
	printf("\n");
	PTreeFree(local_variables_tree);
	node->local_variables = local_variables;
	return num_variables;
}

long CollectVariablesOfBranch(ClauseTableau_p branch, PTree_p branch_vars, bool include_root)
{
	long num_variables = 0;
	ClauseTableau_p iterator = branch;
	while (iterator)
	{
		if ((iterator != branch->master) ^ (include_root))
		{
			num_variables += CollectVariablesAtNode(iterator, branch_vars);
		}
		iterator = iterator->parent;
	}
	return num_variables;
}

/*  At a node in a tableau, there are folding_labels, the label itself, and 
 * unit axioms at the root node.  This method collects all the variables of the aforementioned in to stack.  The number of
 * variables found is returned.
*/

long CollectVariablesAtNode(ClauseTableau_p node, PTree_p var_tree)
{
   long num_collected = 0;
   ClauseCollectVariables(node->label, &var_tree);
	
   Clause_p handle;
   if (node->folding_labels)
   {
	   for(handle = node->folding_labels->anchor->succ; handle!= node->folding_labels->anchor; handle =
			  handle->succ)
	   {
		  num_collected += ClauseCollectVariables(handle, &var_tree);
	   }
   }
   
   if (node->depth == 0)
   {
		for(handle = node->unit_axioms->anchor->succ; handle!= node->unit_axioms->anchor; handle =
				 handle->succ)
		{
			num_collected += ClauseCollectVariables(handle, &var_tree);
		}
	}
	
	return num_collected;
}
