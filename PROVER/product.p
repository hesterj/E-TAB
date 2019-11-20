fof(product, axiom, ( ! [X,A]:
	( member(X,product(A))
	<=> ![Y]:
	(member(Y,A) => member(X,Y))))).
