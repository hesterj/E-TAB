#include <foldingup.h>

/*  Returns true if all of the nodes below tableau are closed
 *  Closes nodes that have all children closed
*/

bool ClauseTableauMarkClosedNodes(ClauseTableau_p tableau)
{
	if (!tableau->open)
	{
		printf("tableau is marked as closed\n");
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
		printf("all children closed, arity %d\n", tableau->arity);
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

/*  Simple wrapper for CollectDominatedMarkings
*/

ClauseSet_p CollectDominatedMarkingsWrapper(ClauseTableau_p tableau)
{
	ClauseSet_p marks = ClauseSetAlloc();
	CollectDominatedMarkings(tableau, marks);
	return marks;
}

/*  For all of the nodes below tableau, collect the markings in to 
 *  the clause set.  As used in folding up, all of the nodes below
 *  should have a marking, as they have been closed by an extension 
 *  step or a closure (reduction) rule.
*/

void CollectDominatedMarkings(ClauseTableau_p tableau, ClauseSet_p marks)
{
	if (tableau->mark)
	{
		assert(!(tableau->open));
		ClauseSetInsert(marks, tableau->mark);
	}
	for (int i=0; i<tableau->arity; i++)
	{
		CollectDominatedMarkings(tableau->children[i], marks);
	}
}

PStack_p NodesThatDominateTableauFromMarks(ClauseTableau_p tableau, ClauseSet_p marks)
{
	PStack_p dominating_nodes = PStackAlloc();
	ClauseTableau_p father = tableau->parent;
	while(father->parent)
	{
		if ()
		parent = father->parent;
	}
}
