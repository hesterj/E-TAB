fof(f07,axiom,(
    ! [C,B,A] : mult(ld(A,mult(B,A)),ld(A,mult(C,A))) = ld(A,mult(mult(B,C),A)) )).

fof(f04,axiom,(
    ! [B,A] : B = ld(A,mult(A,B)) )).

fof(goals,conjecture,(
    ! [X0,X1] :
    ? [X2] : mult(mult(X0,X0),mult(X1,X1)) = mult(X2,X2) )).

fof(f03,axiom,(
    ! [B,A] : mult(A,ld(A,B)) = B )).

fof(f05,axiom,(
    ! [B,A] : mult(A,B) = mult(B,A) )).

fof(f06,axiom,(
    ! [D,C,B,A] : ld(mult(A,B),mult(A,mult(B,mult(C,D)))) = mult(ld(mult(A,B),mult(A,mult(B,C))),ld(mult(A,B),mult(A,mult(B,D)))) )).

fof(f02,axiom,(
    ! [A] : mult(unit,A) = A )).

fof(f01,axiom,(
    ! [A] : A = mult(A,unit) )).

