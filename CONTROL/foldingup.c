#include <foldingup.h>


void ClauseTableauMarkClosedNodes(ClauseTableau_p tableau)
{
	PStack_p leaves = PStackAlloc();
	ClauseTableauCollectLeavesStack(tableau, leaves);
	
}
