#include <extension.h>

int ECloseBranch(ProofState_p proofstate, ProofControl_p proofcontrol, 
					  ClauseTableau_p branch);
bool AttemptToCloseBranchesWithSuperposition(ProofState_p proofstate, 
															ProofControl_p proofcontrol, 
															ClauseTableau_p master);
