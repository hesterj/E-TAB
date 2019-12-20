#ifndef TABLEAUSATURATE

#define TABLEAUSATURATE

#include <extension.h>

WFormula_p ProofStateGetConjecture(ProofState_p state);

bool TFormulasShareVariables(Sig_p sig, TFormula_p a, TFormula_p b);

Clause_p ConnectionTableauSerial(TB_p bank, ClauseSet_p active, int max_depth);
Clause_p ConnectionTableauBatch(TB_p bank, ClauseSet_p active, int max_depth);
Clause_p ConnectionTableauParallel(TB_p bank, ClauseSet_p active, int max_depth);
ClauseTableau_p ConnectionTableauProofSearch(TableauSet_p distinct_tableaux,
															ClauseSet_p extension_candidates, int max_depth);
															
ClauseTableau_p ConnectionTableauPostSearch(TableauSet_p distinct_tableaux, int max_depth);
														
long ClauseSetMoveUnits(ClauseSet_p set, ClauseSet_p units);
    

#endif
