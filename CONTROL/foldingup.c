#include <foldingup.h>

/*  Returns true if all of the nodes below tableau are closed
 *  Closes nodes that have all children closed
*/

bool ClauseTableauMarkClosedNodes(ClauseTableau_p tableau)
{
	if (!tableau->open)
	{
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
