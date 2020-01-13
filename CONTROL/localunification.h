#ifndef LOCALUNI
#define LOCALUNI

#include <clausetableaux.h>

long UpdateLocalVariables(ClauseTableau_p node);
long CollectVariablesAtNode(ClauseTableau_p node, PTree_p *var_tree);
long CollectVariablesOfBranch(ClauseTableau_p branch, PTree_p branch_vars, bool include_root);

#endif
