#include <foldingup.h>

/*  Returns true if all of the nodes below tableau are closed
 *  Closes nodes that have all children closed
*/

bool ClauseTableauMarkClosedNodes(ClauseTableau_p tableau)
{
	if (!tableau->open)
	{
		//printf("tableau is marked as closed\n");
		return true;
	}
	int arity = tableau->arity;
	if (arity == 0)
	{
		return false;
	}
	bool all_children_closed = true;
	// Check to see if all the children are actually superclosed
	for (int i = 0; i < arity; i++)
	{
			ClauseTableau_p child = tableau->children[i];
			bool child_is_superclosed = ClauseTableauMarkClosedNodes(child);
			if (!child_is_superclosed) // there is a child that is open or whose children are open
			{
				all_children_closed = false;
			}
	}
	if (all_children_closed)
	{
		//printf("all children closed, arity %d\n", tableau->arity);
		tableau->open = false;
		return true;
	}
	else
	{
		tableau->open = true;
		return false;
	}
	return false;
}

ClauseTableau_p PStackGetDeepestTableauNode(PStack_p stack)
{
	int deepest_depth = 0;
	ClauseTableau_p deepest = NULL;
	for (PStackPointer p=0; p<PStackGetSP(stack); p++)
	{
		ClauseTableau_p temp = PStackElementP(stack, p);
		if (temp->depth > deepest_depth)
		{
			deepest = temp;
			deepest_depth = deepest->depth;
		}
	}
	return deepest;
}

/*  marks are the integer distance from a node to the dominating node it was closed with
 * 
*/

Clause_p FoldingUpGetLabelFromMark(ClauseTableau_p tableau, int mark)
{
	while (mark)
	{
		tableau = tableau->parent;
		mark -= 1;
	}
	return tableau->label;
}

ClauseTableau_p FoldingUpGetNodeFromMark(ClauseTableau_p tableau, int mark)
{
	while (mark)
	{
		tableau = tableau->parent;
		mark -= 1;
	}
	return tableau;
}

/*  Simple wrapper for CollectDominatedMarkings
*/

PStack_p CollectDominatedMarkingsWrapper(ClauseTableau_p tableau)
{
	PStack_p dominated_markings = PStackAlloc();
	CollectDominatedMarkings(tableau, dominated_markings);
	return dominated_markings;
}

/*  For all of the nodes below tableau, collect the markings in to 
 *  the stack.  As used in folding up, all of the branches below
 *  should have a marking at the leaf, as they have been closed by an extension 
 *  step or a closure (reduction) rule.
*/


void CollectDominatedMarkings(ClauseTableau_p tableau, PStack_p stack)
{
	if (tableau->mark_int > 0)
	{
		ClauseTableau_p mark = FoldingUpGetNodeFromMark(tableau, tableau->mark_int);
		PStackPushP(stack, mark);
	}
	for (int i=0; i<tableau->arity; i++)
	{
		CollectDominatedMarkings(tableau->children[i], stack);
	}
}



PStack_p NodesThatDominateTableauFromMarks(ClauseTableau_p tableau, PStack_p marks)
{
	PStack_p dominating_nodes = PStackAlloc();
	for (PStackPointer p = 0; p<PStackGetSP(marks); p++)
	{
		ClauseTableau_p mark = PStackElementP(marks, p);
		if (TableauDominatesNode(mark, tableau))
		{
			PStackPushP(dominating_nodes, mark);
		}
	}
	return dominating_nodes;
}

int FoldingUp(ClauseTableau_p node)
{
	PStack_p dominated_markings = CollectDominatedMarkingsWrapper(node);
	PStack_p dominators = NodesThatDominateTableauFromMarks(node, dominated_markings);
	PStackFree(dominated_markings);
	if ((PStackGetSP(dominators) == 0) ||
		((PStackGetSP(dominators) == 1) && (PStackElementP(dominators,0) == node->master)))
	{
		// Case 1: Add the negation of the label of node to the literals at the root (node->master)
	}
	else
	{
		// Case 2: Get the deepest path node, add the negation of the label of the node to the parent of deepest
		ClauseTableau_p deepest = PStackGetDeepestTableauNode(dominators);
		assert(deepest);
		if (!(deepest->parent))
		{
			//  We are at the master node, probably because of unit axioms... Not quite case 2, 
		}
		else
		{
			// The actual case 2
			assert(deepest->depth > 0);
		}
		
	}
	return 1;
}

