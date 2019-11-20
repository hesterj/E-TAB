cnf(product_total_function1,axiom,
    ( product(X,Y,e_4)
    | product(X,Y,e_5)
    | product(X,Y,e_3)
    | product(X,Y,e_2)
    | product(X,Y,e_1)
    | ~ group_element(Y)
    | ~ group_element(X) )).

cnf(e_5_greater_e_3,axiom,
    ( greater(e_5,e_3) )).

cnf(e_4_is_not_e_5,axiom,
    ( ~ equalish(e_4,e_5) )).

cnf(product_left_cancellation,axiom,
    ( ~ product(W,Y,X)
    | ~ product(Z,Y,X)
    | equalish(W,Z) )).

cnf(qg2_2,negated_conjecture,
    ( ~ product(X2,Y2,Z1)
    | ~ product(Z2,X1,Y1)
    | equalish(Y1,Y2)
    | ~ product(Z2,X2,Y2)
    | ~ product(X1,Y1,Z1) )).

cnf(e_1_is_not_e_5,axiom,
    ( ~ equalish(e_1,e_5) )).

cnf(e_3_is_not_e_2,axiom,
    ( ~ equalish(e_3,e_2) )).

cnf(cycle4,axiom,
    ( ~ cycle(X,Y)
    | ~ next(X,W)
    | ~ next(Z,Z1)
    | equalish(Y,Z1)
    | ~ greater(Y,e_0)
    | ~ cycle(W,Z) )).

cnf(cycle2,axiom,
    ( cycle(X,e_0)
    | cycle(X,e_3)
    | cycle(X,e_4)
    | cycle(X,e_2)
    | cycle(X,e_1)
    | ~ group_element(X) )).

cnf(e_1_then_e_2,axiom,
    ( next(e_1,e_2) )).

cnf(e_4_then_e_5,axiom,
    ( next(e_4,e_5) )).

cnf(e_2_greater_e_0,axiom,
    ( greater(e_2,e_0) )).

cnf(e_0_then_e_1,axiom,
    ( next(e_0,e_1) )).

cnf(e_3_is_not_e_4,axiom,
    ( ~ equalish(e_3,e_4) )).

cnf(e_5_greater_e_2,axiom,
    ( greater(e_5,e_2) )).

cnf(e_1_is_not_e_3,axiom,
    ( ~ equalish(e_1,e_3) )).

cnf(e_4_is_not_e_2,axiom,
    ( ~ equalish(e_4,e_2) )).

cnf(e_4_greater_e_2,axiom,
    ( greater(e_4,e_2) )).

cnf(qg2_1,negated_conjecture,
    ( ~ product(X2,Y2,Z1)
    | ~ product(Z2,X2,Y2)
    | equalish(X1,X2)
    | ~ product(Z2,X1,Y1)
    | ~ product(X1,Y1,Z1) )).

cnf(e_3_greater_e_2,axiom,
    ( greater(e_3,e_2) )).

cnf(e_5_greater_e_1,axiom,
    ( greater(e_5,e_1) )).

cnf(e_1_is_not_e_2,axiom,
    ( ~ equalish(e_1,e_2) )).

cnf(element_3,axiom,
    ( group_element(e_3) )).

cnf(e_1_greater_e_0,axiom,
    ( greater(e_1,e_0) )).

cnf(e_4_greater_e_3,axiom,
    ( greater(e_4,e_3) )).

cnf(cycle5,axiom,
    ( ~ cycle(X,Z1)
    | ~ cycle(W,Z2)
    | ~ greater(Y,X)
    | ~ greater(Z1,Z2)
    | ~ next(Y,W)
    | ~ cycle(Y,e_0) )).

cnf(e_1_is_not_e_4,axiom,
    ( ~ equalish(e_1,e_4) )).

cnf(e_2_is_not_e_1,axiom,
    ( ~ equalish(e_2,e_1) )).

cnf(e_2_then_e_3,axiom,
    ( next(e_2,e_3) )).

cnf(e_2_is_not_e_5,axiom,
    ( ~ equalish(e_2,e_5) )).

cnf(e_5_greater_e_0,axiom,
    ( greater(e_5,e_0) )).

cnf(e_5_is_not_e_3,axiom,
    ( ~ equalish(e_5,e_3) )).

cnf(cycle3,axiom,
    ( cycle(e_5,e_0) )).

cnf(e_2_greater_e_1,axiom,
    ( greater(e_2,e_1) )).

cnf(element_5,axiom,
    ( group_element(e_5) )).

cnf(cycle1,axiom,
    ( ~ cycle(X,Y)
    | equalish(Y,Z)
    | ~ cycle(X,Z) )).

cnf(e_2_is_not_e_4,axiom,
    ( ~ equalish(e_2,e_4) )).

cnf(product_idempotence,axiom,
    ( product(X,X,X) )).

cnf(cycle7,axiom,
    ( ~ cycle(X,Y)
    | ~ greater(Y,e_0)
    | equalish(Z,X1)
    | ~ next(X,X1)
    | ~ product(X,e_1,Z) )).

cnf(e_3_is_not_e_1,axiom,
    ( ~ equalish(e_3,e_1) )).

cnf(product_right_cancellation,axiom,
    ( ~ product(X,Z,Y)
    | equalish(W,Z)
    | ~ product(X,W,Y) )).

cnf(e_5_is_not_e_1,axiom,
    ( ~ equalish(e_5,e_1) )).

cnf(product_total_function2,axiom,
    ( ~ product(X,Y,W)
    | ~ product(X,Y,Z)
    | equalish(W,Z) )).

cnf(e_3_greater_e_0,axiom,
    ( greater(e_3,e_0) )).

cnf(e_5_is_not_e_2,axiom,
    ( ~ equalish(e_5,e_2) )).

cnf(e_3_is_not_e_5,axiom,
    ( ~ equalish(e_3,e_5) )).

cnf(e_5_is_not_e_4,axiom,
    ( ~ equalish(e_5,e_4) )).

cnf(e_4_is_not_e_1,axiom,
    ( ~ equalish(e_4,e_1) )).

cnf(e_3_greater_e_1,axiom,
    ( greater(e_3,e_1) )).

cnf(element_4,axiom,
    ( group_element(e_4) )).

cnf(e_3_then_e_4,axiom,
    ( next(e_3,e_4) )).

cnf(e_4_greater_e_1,axiom,
    ( greater(e_4,e_1) )).

cnf(element_2,axiom,
    ( group_element(e_2) )).

cnf(cycle6,axiom,
    ( ~ product(X,e_1,Y)
    | ~ greater(Y,X)
    | ~ cycle(X,e_0) )).

cnf(e_5_greater_e_4,axiom,
    ( greater(e_5,e_4) )).

cnf(e_2_is_not_e_3,axiom,
    ( ~ equalish(e_2,e_3) )).

cnf(element_1,axiom,
    ( group_element(e_1) )).

cnf(e_4_greater_e_0,axiom,
    ( greater(e_4,e_0) )).

cnf(e_4_is_not_e_3,axiom,
    ( ~ equalish(e_4,e_3) )).

