//include <extension.h>
#include <foldingup.h>

int ECloseBranch(ProofState_p proofstate, ProofControl_p proofcontrol, 
					  ClauseTableau_p branch);
int AttemptToCloseBranchesWithSuperposition(ProofState_p proofstate, 
															ProofControl_p proofcontrol, 
															ClauseTableau_p master);
