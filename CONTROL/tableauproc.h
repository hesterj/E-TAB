#ifndef TABLEAUSATURATE

#define TABLEAUSATURATE

#include <extension.h>

WFormula_p ProofStateGetConjecture(ProofState_p state);

bool TFormulasShareVariables(Sig_p sig, TFormula_p a, TFormula_p b);

ClauseTableau_p ConnectionTableauSaturate(ProofState_p state, ProofControl_p control, int max_depth);
ClauseTableau_p ConnectionTableauProofSearch(ProofState_p state, ProofControl_p control, TableauSet_p distinct_tableaux,
															ClauseSet_p extension_candidates, int max_depth);
    

#endif
