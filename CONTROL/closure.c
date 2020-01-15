#include <closure.h>

/*  Simple wrapper for branch contradiction testing
 *  Checks the label of tab for contradiction against the labels of its parents
*/

bool ClauseTableauBranchClosureRuleWrapper(ClauseTableau_p tab)
{
	Subst_p subst;
	assert(tab);
	assert(tab->label);
	long num_local_variables = UpdateLocalVariables(tab);
	if (num_local_variables)
	{
		printf("Local variables found!\n");
	}	

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

/*
 *  Attempt closure rule on all the open branches of the tableau.
 *  Returns the total number of closures that were accomplished.
 *  If there are no more open branches (a closed tableau was found),
 *  return the negative of the total number of branches closed.
*/

int AttemptClosureRuleOnAllOpenBranches(ClauseTableau_p tableau)
{
	int num_branches_closed = 0;
	ClauseTableau_p open_branch = tableau->open_branches->anchor->succ;
	while (open_branch != tableau->open_branches->anchor)
	{
		if (ClauseTableauBranchClosureRuleWrapper(open_branch))
		{
			num_branches_closed += 1;
			open_branch->open = false;
			open_branch = open_branch->succ;
			TableauSetExtractEntry(open_branch->pred);
			if (open_branch == tableau->open_branches->anchor)
			{
				open_branch = open_branch->succ;
			}
			if (tableau->open_branches->members == 0)
			{
				return -num_branches_closed;
			}
		}
		else
		{
			open_branch = open_branch->succ;
		}
	}
	return num_branches_closed;
}
