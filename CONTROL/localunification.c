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

int UpdateLocalVariables(ClauseTableau_p node)
{
	if (node->local_variables)
	{
		PStackFree(node->local_variables);
	}
	PStack_p local_variables = PStackAlloc();
	
	ClauseTableau_p iterator = node;
	
}

/*  At a node in a tableau, there are folding_labels, the label itself, and 
 * unit axioms at the root node.  This method collects all the variables of the aforementioned in to stack.  The number of
 * variables found is returned.
*/

long CollectVariablesAtNode(ClauseTableau_p node, PStack_p stack)
{
	PTree_p var_tree = NULL;
	ClauseCollectVariables(node->label, &var_tree);
	PTreeToPStack(stack, var_tree);
	PTreeFree(var_tree);
	
	Clause_p handle;
   for(handle = node->folding_labels->anchor->succ; handle!= node->folding_labels->anchor; handle =
          handle->succ)
   {
      var_tree = NULL;
      ClauseCollectVariables(handle, &var_tree);
      PTreeToPStack(stack, var_tree);
      PTreeFree(var_tree);
   }
   
   if (node->depth == 0)
   {
		for(handle = node->unit_axioms->anchor->succ; handle!= node->unit_axioms->anchor; handle =
				 handle->succ)
		{
			var_tree = NULL;
			ClauseCollectVariables(handle, &var_tree);
			PTreeToPStack(stack, var_tree);
			PTreeFree(var_tree);
		}
	}
	
	return PStackGetSP(stack);
}
