include('Axioms/zfc.ax').
include('Axioms/definitions.p').

fof(cardorder,conjecture, ![W,X,Y,Z]: ( (cardinality(W)=X & cardinality(Y)=Z) => (X=Z | member(X,Z) | member(Z,X)) ) ).
