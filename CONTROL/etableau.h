#include <extension.h>

bool ECloseBranch(ProofState_p proofstate, ProofControl_p proofcontrol, ClauseTableau_p branch, ClauseSet_p extension_candidates);
bool AttemptToCloseBranchesWithSuperposition(ProofState_p proofstate, ProofControl_p proofcontrol, ClauseTableau_p master, ClauseSet_p extension_candidates);
