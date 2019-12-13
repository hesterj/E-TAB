#ifndef FOLDINGUP
#define FOLDINGUP

#include <clausetableaux.h>

bool ClauseTableauMarkClosedNodes(ClauseTableau_p tableau);

ClauseSet_p CollectDominatedMarkingsWrapper(ClauseTableau_p tableau);
void CollectDominatedMarkings(ClauseTableau_p tableau, ClauseSet_p marks);

PStack_p NodesThatDominateTableauFromMarks(ClauseTableau_p tableau, ClauseSet_p marks);

#endif
