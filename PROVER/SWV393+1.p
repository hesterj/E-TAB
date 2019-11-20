include('Axioms/SWV007+0.ax').
include('Axioms/SWV007+2.ax').
fof(l29_co,conjecture,(
    ! [U] :
      ( ! [V,W] :
          ( pair_in_list(U,V,W)
         => ! [X] :
              ( contains_slb(U,X)
             => ( pair_in_list(remove_slb(U,X),V,W)
                | X = V ) ) )
     => ! [Y,Z,X1,X2] :
          ( ! [X1] :
              ( contains_slb(insert_slb(U,pair(X1,X2)),X1)
             => ( Y = X1
                | pair_in_list(remove_slb(insert_slb(U,pair(X1,X2)),X1),Y,Z) ) )
         <= pair_in_list(insert_slb(U,pair(X1,X2)),Y,Z) ) ) )).

