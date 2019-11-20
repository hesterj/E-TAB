%--------------------------------------------------------------------------
% File     : MSC008-1.010 : TPTP v7.2.0. Released v1.0.0.
% Domain   : Miscellaneous
% Problem  : The (in)constructability of Graeco-Latin Squares
% Version  : [Rob63] axioms : Especial.
% English  : The constructibility of Graeco-Latin squares of order 4t+2.
%            This is impossible for t=0,1, but possible for all other
%            cases. The size is the size of the squares.

% Refs     : [Rob63] Robinson (1963), Theorem Proving on the Computer
% Source   : [TPTP]
% Names    :

% Status   : Satisfiable
% Rating   : 1.00 v2.1.0
% Syntax   : Number of clauses     :   61 (   6 non-Horn;  46 unit;  54 RR)
%            Number of atoms       :  136 (   0 equality)
%            Maximal clause size   :   10 (   2 average)
%            Number of predicates  :    3 (   0 propositional; 2-3 arity)
%            Number of functors    :   10 (  10 constant; 0-0 arity)
%            Number of variables   :   51 (   0 singleton)
%            Maximal term depth    :    1 (   1 average)
% SPC      : CNF_SAT_EPR

% Comments :
%          : tptp2X: -f tptp -s10 MSC008-1.g
%--------------------------------------------------------------------------
cnf(p_1_is_not_p_2,axiom,
    ( ~ eq(p_1,p_2) )).

cnf(p_1_is_not_p_3,axiom,
    ( ~ eq(p_1,p_3) )).

cnf(p_1_is_not_p_4,axiom,
    ( ~ eq(p_1,p_4) )).

cnf(p_1_is_not_p_5,axiom,
    ( ~ eq(p_1,p_5) )).

cnf(p_1_is_not_p_6,axiom,
    ( ~ eq(p_1,p_6) )).

cnf(p_1_is_not_p_7,axiom,
    ( ~ eq(p_1,p_7) )).

cnf(p_1_is_not_p_8,axiom,
    ( ~ eq(p_1,p_8) )).

cnf(p_1_is_not_p_9,axiom,
    ( ~ eq(p_1,p_9) )).

cnf(p_1_is_not_p_10,axiom,
    ( ~ eq(p_1,p_10) )).

cnf(p_2_is_not_p_3,axiom,
    ( ~ eq(p_2,p_3) )).

cnf(p_2_is_not_p_4,axiom,
    ( ~ eq(p_2,p_4) )).

cnf(p_2_is_not_p_5,axiom,
    ( ~ eq(p_2,p_5) )).

cnf(p_2_is_not_p_6,axiom,
    ( ~ eq(p_2,p_6) )).

cnf(p_2_is_not_p_7,axiom,
    ( ~ eq(p_2,p_7) )).

cnf(p_2_is_not_p_8,axiom,
    ( ~ eq(p_2,p_8) )).

cnf(p_2_is_not_p_9,axiom,
    ( ~ eq(p_2,p_9) )).

cnf(p_2_is_not_p_10,axiom,
    ( ~ eq(p_2,p_10) )).

cnf(p_3_is_not_p_4,axiom,
    ( ~ eq(p_3,p_4) )).

cnf(p_3_is_not_p_5,axiom,
    ( ~ eq(p_3,p_5) )).

cnf(p_3_is_not_p_6,axiom,
    ( ~ eq(p_3,p_6) )).

cnf(p_3_is_not_p_7,axiom,
    ( ~ eq(p_3,p_7) )).

cnf(p_3_is_not_p_8,axiom,
    ( ~ eq(p_3,p_8) )).

cnf(p_3_is_not_p_9,axiom,
    ( ~ eq(p_3,p_9) )).

cnf(p_3_is_not_p_10,axiom,
    ( ~ eq(p_3,p_10) )).

cnf(p_4_is_not_p_5,axiom,
    ( ~ eq(p_4,p_5) )).

cnf(p_4_is_not_p_6,axiom,
    ( ~ eq(p_4,p_6) )).

cnf(p_4_is_not_p_7,axiom,
    ( ~ eq(p_4,p_7) )).

cnf(p_4_is_not_p_8,axiom,
    ( ~ eq(p_4,p_8) )).

cnf(p_4_is_not_p_9,axiom,
    ( ~ eq(p_4,p_9) )).

cnf(p_4_is_not_p_10,axiom,
    ( ~ eq(p_4,p_10) )).

cnf(p_5_is_not_p_6,axiom,
    ( ~ eq(p_5,p_6) )).

cnf(p_5_is_not_p_7,axiom,
    ( ~ eq(p_5,p_7) )).

cnf(p_5_is_not_p_8,axiom,
    ( ~ eq(p_5,p_8) )).

cnf(p_5_is_not_p_9,axiom,
    ( ~ eq(p_5,p_9) )).

cnf(p_5_is_not_p_10,axiom,
    ( ~ eq(p_5,p_10) )).

cnf(p_6_is_not_p_7,axiom,
    ( ~ eq(p_6,p_7) )).

cnf(p_6_is_not_p_8,axiom,
    ( ~ eq(p_6,p_8) )).

cnf(p_6_is_not_p_9,axiom,
    ( ~ eq(p_6,p_9) )).

cnf(p_6_is_not_p_10,axiom,
    ( ~ eq(p_6,p_10) )).

cnf(p_7_is_not_p_8,axiom,
    ( ~ eq(p_7,p_8) )).

cnf(p_7_is_not_p_9,axiom,
    ( ~ eq(p_7,p_9) )).

cnf(p_7_is_not_p_10,axiom,
    ( ~ eq(p_7,p_10) )).

cnf(p_8_is_not_p_9,axiom,
    ( ~ eq(p_8,p_9) )).

cnf(p_8_is_not_p_10,axiom,
    ( ~ eq(p_8,p_10) )).

cnf(p_9_is_not_p_10,axiom,
    ( ~ eq(p_9,p_10) )).

cnf(reflexivity,axiom,
    ( eq(X,X) )).

cnf(symmetry,axiom,
    ( ~ eq(X,Y)
    | eq(Y,X) )).

cnf(latin_element_is_unique,axiom,
    ( ~ latin(Row,Column,Label1)
    | ~ latin(Row,Column,Label2)
    | eq(Label1,Label2) )).

cnf(latin_column_is_unique,axiom,
    ( ~ latin(Row,Column1,Label)
    | ~ latin(Row,Column2,Label)
    | eq(Column1,Column2) )).

cnf(latin_row_is_unique,axiom,
    ( ~ latin(Row1,Column,Label)
    | ~ latin(Row2,Column,Label)
    | eq(Row1,Row2) )).

cnf(greek_element_is_unique,axiom,
    ( ~ greek(Row,Column,Label1)
    | ~ greek(Row,Column,Label2)
    | eq(Label1,Label2) )).

cnf(greek_column_is_unique,axiom,
    ( ~ greek(Row,Column1,Label)
    | ~ greek(Row,Column2,Label)
    | eq(Column1,Column2) )).

cnf(greek_row_is_unique,axiom,
    ( ~ greek(Row1,Column,Label)
    | ~ greek(Row2,Column,Label)
    | eq(Row1,Row2) )).

cnf(latin_cell_element,axiom,
    ( latin(Row,Column,p_1)
    | latin(Row,Column,p_2)
    | latin(Row,Column,p_3)
    | latin(Row,Column,p_4)
    | latin(Row,Column,p_5)
    | latin(Row,Column,p_6)
    | latin(Row,Column,p_7)
    | latin(Row,Column,p_8)
    | latin(Row,Column,p_9)
    | latin(Row,Column,p_10) )).

cnf(latin_column_required,axiom,
    ( latin(Row,p_1,Label)
    | latin(Row,p_2,Label)
    | latin(Row,p_3,Label)
    | latin(Row,p_4,Label)
    | latin(Row,p_5,Label)
    | latin(Row,p_6,Label)
    | latin(Row,p_7,Label)
    | latin(Row,p_8,Label)
    | latin(Row,p_9,Label)
    | latin(Row,p_10,Label) )).

cnf(latin_row_required,axiom,
    ( latin(p_1,Column,Label)
    | latin(p_2,Column,Label)
    | latin(p_3,Column,Label)
    | latin(p_4,Column,Label)
    | latin(p_5,Column,Label)
    | latin(p_6,Column,Label)
    | latin(p_7,Column,Label)
    | latin(p_8,Column,Label)
    | latin(p_9,Column,Label)
    | latin(p_10,Column,Label) )).

cnf(greek_cell_element,axiom,
    ( greek(Row,Column,p_1)
    | greek(Row,Column,p_2)
    | greek(Row,Column,p_3)
    | greek(Row,Column,p_4)
    | greek(Row,Column,p_5)
    | greek(Row,Column,p_6)
    | greek(Row,Column,p_7)
    | greek(Row,Column,p_8)
    | greek(Row,Column,p_9)
    | greek(Row,Column,p_10) )).

cnf(greek_column_required,axiom,
    ( greek(Row,p_1,Label)
    | greek(Row,p_2,Label)
    | greek(Row,p_3,Label)
    | greek(Row,p_4,Label)
    | greek(Row,p_5,Label)
    | greek(Row,p_6,Label)
    | greek(Row,p_7,Label)
    | greek(Row,p_8,Label)
    | greek(Row,p_9,Label)
    | greek(Row,p_10,Label) )).

cnf(greek_row_required,axiom,
    ( greek(p_1,Column,Label)
    | greek(p_2,Column,Label)
    | greek(p_3,Column,Label)
    | greek(p_4,Column,Label)
    | greek(p_5,Column,Label)
    | greek(p_6,Column,Label)
    | greek(p_7,Column,Label)
    | greek(p_8,Column,Label)
    | greek(p_9,Column,Label)
    | greek(p_10,Column,Label) )).

    
fof(garbage, negated_conjecture,
    ( ~ greek(Row1,Column1,Label1)
    | ~ latin(Row1,Column1,Label2)
    | ~ greek(Row2,Column2,Label1)
    | ~ latin(Row2,Column2,Label2)
    | eq(Column1,Column2) ) &
    ( ~ greek(Row1,Column1,Label1)
    | ~ latin(Row1,Column1,Label2)
    | ~ greek(Row2,Column2,Label1)
    | ~ latin(Row2,Column2,Label2)
    | eq(Row1,Row2) )).



%--------------------------------------------------------------------------
