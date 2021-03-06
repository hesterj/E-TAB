//include <extension.h>
#include <foldingup.h>

typedef struct branch_saturation
{
	ProofState_p proofstate;
	ProofControl_p proofcontrol;
	ClauseTableau_p master;
}BranchSaturationCell, *BranchSaturation_p;

#define BranchSaturationCellAlloc()    (BranchSaturationCell*)SizeMalloc(sizeof(BranchSaturationCell))
#define BranchSaturationCellFree(junk) SizeFree(junk, sizeof(BranchSaturationCell))

BranchSaturation_p BranchSaturationAlloc(ProofState_p proofstate, ProofControl_p proofcontrol, ClauseTableau_p master);
int ECloseBranch(ProofState_p proofstate, ProofControl_p proofcontrol, 
					  ClauseTableau_p branch);
int AttemptToCloseBranchesWithSuperposition(BranchSaturation_p jobs);
