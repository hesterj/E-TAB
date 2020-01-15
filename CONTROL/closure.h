#ifndef CLOSURE
#define CLOSURE

#include <localunification.h>

bool ClauseTableauBranchClosureRuleWrapper(ClauseTableau_p tab);
int AttemptClosureRuleOnAllOpenBranches(ClauseTableau_p tableau);

#endif
