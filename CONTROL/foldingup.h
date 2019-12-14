#ifndef FOLDINGUP
#define FOLDINGUP

#include <clausetableaux.h>

bool ClauseTableauMarkClosedNodes(ClauseTableau_p tableau);
#define ClauseTableauNodeIsClosed(tab) ClauseTableauMarkClosedNodes(tab)

PStack_p CollectDominatedMarkingsWrapper(ClauseTableau_p tableau);
void CollectDominatedMarkings(ClauseTableau_p tableau, PStack_p stack);

PStack_p NodesThatDominateTableauFromMarks(ClauseTableau_p tableau, PStack_p marks);

Clause_p FoldingUpGetLabelFromMark(ClauseTableau_p tableau, int mark);
ClauseTableau_p FoldingUpGetNodeFromMark(ClauseTableau_p tableau, int mark);

ClauseTableau_p PStackGetDeepestTableauNode(PStack_p stack);

int FoldUpAtNode(ClauseTableau_p node);
void ClauseTableauEdgeInsert(ClauseTableau_p edge, Clause_p clause);

#endif
