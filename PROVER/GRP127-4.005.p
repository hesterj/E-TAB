cnf(e_4_is_not_e_2,axiom,
    ( ~ equalish(e_4,e_2) )).

cnf(e_3_is_not_e_4,axiom,
    ( ~ equalish(e_3,e_4) )).

cnf(qg3_1,negated_conjecture,
    ( product(Y,X,Z1)
    | ~ product(Z2,Y,X)
    | ~ product(Z1,Y,Z2) )).

cnf(product_total_function2,axiom,
    ( ~ product(X,Y,Z)
    | equalish(W,Z)
    | ~ product(X,Y,W) )).

cnf(column_surjectivity,axiom,
    ( ~ group_element(X)
    | ~ group_element(Y)
    | product(X,e_1,Y)
    | product(X,e_2,Y)
    | product(X,e_3,Y)
    | product(X,e_4,Y)
    | product(X,e_5,Y) )).

cnf(e_1_is_not_e_3,axiom,
    ( ~ equalish(e_1,e_3) )).

cnf(qg3_2,negated_conjecture,
    ( ~ product(Z2,Y,X)
    | ~ product(Y,X,Z1)
    | product(Z1,Y,Z2) )).

cnf(e_1_is_not_e_5,axiom,
    ( ~ equalish(e_1,e_5) )).

cnf(element_5,axiom,
    ( group_element(e_5) )).

cnf(e_5_is_not_e_4,axiom,
    ( ~ equalish(e_5,e_4) )).

cnf(e_4_is_not_e_3,axiom,
    ( ~ equalish(e_4,e_3) )).

cnf(e_2_is_not_e_3,axiom,
    ( ~ equalish(e_2,e_3) )).

cnf(e_1_is_not_e_4,axiom,
    ( ~ equalish(e_1,e_4) )).

cnf(product_right_cancellation,axiom,
    ( ~ product(X,W,Y)
    | ~ product(X,Z,Y)
    | equalish(W,Z) )).

cnf(e_2_is_not_e_5,axiom,
    ( ~ equalish(e_2,e_5) )).

cnf(element_3,axiom,
    ( group_element(e_3) )).

cnf(e_2_is_not_e_1,axiom,
    ( ~ equalish(e_2,e_1) )).

cnf(e_5_is_not_e_3,axiom,
    ( ~ equalish(e_5,e_3) )).

cnf(e_2_is_not_e_4,axiom,
    ( ~ equalish(e_2,e_4) )).

cnf(qg3,negated_conjecture,
    ( ~ product(Z1,Y,Z2)
    | product(Z2,Y,X)
    | ~ product(Y,X,Z1) )).

cnf(e_3_is_not_e_5,axiom,
    ( ~ equalish(e_3,e_5) )).

cnf(product_idempotence,axiom,
    ( product(X,X,X) )).

cnf(row_surjectivity,axiom,
    ( ~ group_element(Y)
    | product(e_4,X,Y)
    | product(e_5,X,Y)
    | product(e_3,X,Y)
    | product(e_2,X,Y)
    | product(e_1,X,Y)
    | ~ group_element(X) )).

cnf(e_5_is_not_e_2,axiom,
    ( ~ equalish(e_5,e_2) )).

cnf(e_4_is_not_e_5,axiom,
    ( ~ equalish(e_4,e_5) )).

cnf(element_4,axiom,
    ( group_element(e_4) )).

cnf(product_total_function1,axiom,
    ( ~ group_element(Y)
    | product(X,Y,e_4)
    | product(X,Y,e_5)
    | product(X,Y,e_3)
    | product(X,Y,e_2)
    | product(X,Y,e_1)
    | ~ group_element(X) )).

cnf(e_1_is_not_e_2,axiom,
    ( ~ equalish(e_1,e_2) )).

cnf(e_3_is_not_e_1,axiom,
    ( ~ equalish(e_3,e_1) )).

cnf(element_2,axiom,
    ( group_element(e_2) )).

cnf(e_3_is_not_e_2,axiom,
    ( ~ equalish(e_3,e_2) )).

cnf(element_1,axiom,
    ( group_element(e_1) )).

cnf(e_5_is_not_e_1,axiom,
    ( ~ equalish(e_5,e_1) )).

cnf(product_left_cancellation,axiom,
    ( ~ product(W,Y,X)
    | ~ product(Z,Y,X)
    | equalish(W,Z) )).

cnf(e_4_is_not_e_1,axiom,
    ( ~ equalish(e_4,e_1) )).

