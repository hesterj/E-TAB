#ifndef CLAUSETABLEAUX

#define CLAUSETABLEAUX

#include <clb_os_wrapper.h>
#include <cio_signals.h>
#include <ccl_fcvindexing.h>
#include <che_heuristics.h>
#include <che_axiomscan.h>
#include <che_to_autoselect.h>
#include <cco_clausesplitting.h>
#include <cco_forward_contraction.h>
#include <cco_interpreted.h>
#include <ccl_satinterface.h>
#include <time.h>
#include <arpa/inet.h>
#include <clb_plist.h>

typedef struct clausetableau 
{
	PStack_p predicates;
	PStack_p functions;
	bool open;
	int depth;
	
	Clause_p label;
	ClauseSet_p active;
	ClauseSet_p passive;
	ClauseSet_p recently_active;
	DStr_p info;
	long id;  // If a clause was split on a node, this is the id of the clause used to split.
	bool head_lit;  //If this node was made as a head literal in an extension step, it is true.  Otherwise false.
	
	ProofState_p state;
	ProofControl_p control;
	
	TB_p          terms;
	Sig_p         signature;
	
	// Tableau set cell stuff...
	struct tableau_set_cell* set;
	struct tableau_set_cell* master_set;  // For controlling sets of distinct tableau
	struct tableau_set_cell* open_branches;
	
	struct clausetableau* active_branch; // active branch for making multiple copies of the same tableau
	
	struct clausetableau* pred;
	struct clausetableau* succ;
	struct clausetableau* master_pred;
	struct clausetableau* master_succ;
	
	// Children
	int arity;
	struct clausetableau* *children;
	
	// Tableau pointers...
	struct clausetableau* master;
   struct clausetableau* parent;      
	
}ClauseTableau, *ClauseTableau_p;

typedef PStack_p ClauseStack_p;

#define ClauseTableauCellAlloc() (ClauseTableau*)SizeMalloc(sizeof(ClauseTableau))
#define ClauseTableauCellFree(junk) SizeFree(junk, sizeof(ClauseTableau))
#define ClauseTableauArgArrayAlloc(arity) ((ClauseTableau_p*)SizeMalloc((arity)*sizeof(ClauseTableau_p)))
#define ClauseTableauArgArrayFree(junk, arity) SizeFree((junk),(arity)*sizeof(ClauseTableau_p))
//#define ClauseTableauArgArrayFree(junk) SizeFree(junk, sizeof())
ClauseTableau_p ClauseTableauAlloc();
void ClauseTableauInitialize(ClauseTableau_p handle, ProofState_p state);
void ClauseTableauFree(ClauseTableau_p trash);
ClauseTableau_p ClauseTableauMasterCopy(ClauseTableau_p tab);
ClauseTableau_p ClauseTableauChildCopy(ClauseTableau_p tab, ClauseTableau_p parent);
ClauseTableau_p ClauseTableauChildAlloc(ClauseTableau_p parent);
ClauseTableau_p ClauseTableauChildLabelAlloc(ClauseTableau_p parent, Clause_p label);
ClauseTableau_p ClauseTableauExpansionRule(ClauseTableau_p parent);
void ClauseTableauApplySubstitution(ClauseTableau_p tab, Subst_p subst);
void ClauseTableauApplySubstitutionToNode(ClauseTableau_p tab, Subst_p subst);
ClauseSet_p ClauseSetApplySubstitution(TB_p bank, ClauseSet_p set, Subst_p subst);
Clause_p ClauseApplySubst(Clause_p clause,  TB_p bank, Subst_p subst);

void ClauseTableauScoreActive(ClauseTableau_p tab);
void ClauseTableauPrint(ClauseTableau_p tab);

void HCBClauseSetEvaluate(HCB_p hcb, ClauseSet_p clauses);

ClauseSet_p ClauseSetCopy(TB_p bank, ClauseSet_p set);
ClauseSet_p ClauseSetFlatCopy(TB_p bank, ClauseSet_p set);

Clause_p ClauseCopyFresh(Clause_p clause);

TFormula_p TFormulaNegAlloc(TB_p terms, TFormula_p form);
Subst_p ClauseContradictsClause(ClauseTableau_p tab, Clause_p a, Clause_p b);
Subst_p ClauseContradictsSet(ClauseTableau_p tab, Clause_p leaf, ClauseSet_p set);
Subst_p ClauseTableauClosureRule(ClauseTableau_p tab);
Subst_p ClauseContradictsBranch(ClauseTableau_p tab, Clause_p clause);
bool ClauseTableauClosureRuleWrapper(ClauseTableau_p tab);
bool ClauseTableauBranchClosureRuleWrapper(ClauseTableau_p tab);

ClauseTableau_p TableauStartRule(ClauseTableau_p tab, Clause_p start);
int ClauseTableauAssertCheck(ClauseTableau_p tab);

/*  Now for tableau sets...
 * 
 * 
*/

typedef struct tableau_set_cell
{
	ClauseTableau_p anchor;
	long members;
}TableauSetCell, *TableauSet_p;


#define TableauSetCellAlloc()    (TableauSetCell*)SizeMalloc(sizeof(TableauSetCell))
#define TableauSetCellFree(junk) SizeFree(junk, sizeof(TableauSetCell))

#define      TableauSetEmpty(set)\
             ((set)->anchor->succ == (set)->anchor)
#define      TableauMasterSetEmpty(set)\
             ((set)->anchor->master_succ == (set)->anchor)

TableauSet_p TableauSetAlloc();
TableauSet_p TableauSetCopy(TableauSet_p set);
void TableauSetInsert(TableauSet_p list, ClauseTableau_p set);
void ClauseTableauPrintBranch(ClauseTableau_p branch);
ClauseTableau_p   TableauSetExtractFirst(TableauSet_p list);
ClauseTableau_p TableauSetExtractEntry(ClauseTableau_p set);
void TableauSetFree(TableauSet_p handle);

TableauSet_p TableauMasterSetAlloc();
TableauSet_p TableauMasterSetCopy(TableauSet_p set);
void TableauMasterSetInsert(TableauSet_p list, ClauseTableau_p set);
ClauseTableau_p   TableauMasterSetExtractFirst(TableauSet_p list);
ClauseTableau_p TableauMasterSetExtractEntry(ClauseTableau_p set);
void TableauMasterSetFree(TableauSet_p handle);
void ClauseTableauCollectLeaves(ClauseTableau_p tab, TableauSet_p leaves);

#endif
