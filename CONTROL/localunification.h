#ifndef LOCALUNI
#define LOCALUNI

#include <clausetableaux.h>

int UpdateLocalVariables(ClauseTableau_p node);
int CollectVariablesAtNode(ClauseTableau_p node, PStack_p stack);

#endif
