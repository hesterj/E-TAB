fof(encrypt_k1Enck2_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,X1,X2),iknows(atoms(n1,n1,X5),enc(X6,n1,X8,X9,X10,X11,X12,X13,X14)))
     <= p(state(X0,X1,X2),iknows(atoms(n1,n1,X5),enc(X6,n0,X8,X9,X10,X11,X12,X13,X14))) ) )).

fof(encrypt_k2Enck1_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,X1,X2),iknows(atoms(n1,n1,X5),enc(X6,X7,X8,n0,X10,X11,X12,X13,X14)))
     => p(state(X0,X1,X2),iknows(atoms(n1,n1,X5),enc(X6,X7,X8,n1,X10,X11,X12,X13,X14))) ) )).

fof(wrap_hn1k3_hn1k3_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,X1,h(n1,n1,X3,X4,X5,X6,n1)),iknows(X8,enc(X9,X10,X11,X12,X13,X14,X15,X16,n0)))
     => p(state(X0,X1,h(n1,n1,X3,X4,X5,X6,n1)),iknows(X8,enc(X9,X10,X11,X12,X13,X14,X15,X16,n1))) ) )).

fof(decrypt_hn1k3_k2Enck3_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,X1,h(n1,X2,X3,X4,n1,X6,X7)),iknows(atoms(X8,n0,X10),enc(X11,X12,X13,X14,X15,n1,X17,X18,X19)))
     => p(state(X0,X1,h(n1,X2,X3,X4,n1,X6,X7)),iknows(atoms(X8,n1,X10),enc(X11,X12,X13,X14,X15,n1,X17,X18,X19))) ) )).

fof(encrypt_hn1k3_k3Enck3_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,X1,h(n1,X2,X3,n1,X5,X6,X7)),iknows(atoms(X8,X9,n1),enc(X11,X12,X13,X14,X15,X16,X17,X18,n0)))
     => p(state(X0,X1,h(n1,X2,X3,n1,X5,X6,X7)),iknows(atoms(X8,X9,n1),enc(X11,X12,X13,X14,X15,X16,X17,X18,n1))) ) )).

fof(set_attr_hn1k1_extractable_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(h(n1,X0,X1,X2,X3,X4,n1),X6,X7),X8)
     => p(state(h(n1,X0,X1,X2,X3,X4,n0),X6,X7),X8) ) )).

fof(unwrap_hn1k2_hn1k1_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(h(n0,X0,X1,X2,X3,X4,X5),h(n1,X6,n1,X8,X9,X10,X11),X12),iknows(X13,enc(X14,n1,X16,X17,X18,X19,X20,X21,X22)))
     => p(state(h(n1,X0,X1,X2,X3,X4,n1),h(n1,X6,n1,X8,X9,X10,X11),X12),iknows(X13,enc(X14,n1,X16,X17,X18,X19,X20,X21,X22))) ) )).

fof(encrypt_k2Enck2_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,X1,X2),iknows(atoms(X3,n1,X5),enc(X6,X7,X8,X9,n0,X11,X12,X13,X14)))
     => p(state(X0,X1,X2),iknows(atoms(X3,n1,X5),enc(X6,X7,X8,X9,n1,X11,X12,X13,X14))) ) )).

fof(encrypt_hn1k2_k3Enck2_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,h(n1,X1,X2,n1,X4,X5,X6),X7),iknows(atoms(X8,X9,n1),enc(X11,X12,X13,X14,X15,X16,X17,n0,X19)))
     => p(state(X0,h(n1,X1,X2,n1,X4,X5,X6),X7),iknows(atoms(X8,X9,n1),enc(X11,X12,X13,X14,X15,X16,X17,n1,X19))) ) )).

fof(decrypt_hn1k3_k1Enck3_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,X1,h(n1,X2,X3,X4,n1,X6,X7)),iknows(atoms(n1,X9,X10),enc(X11,X12,n1,X14,X15,X16,X17,X18,X19)))
     <= p(state(X0,X1,h(n1,X2,X3,X4,n1,X6,X7)),iknows(atoms(n0,X9,X10),enc(X11,X12,n1,X14,X15,X16,X17,X18,X19))) ) )).

fof(intruder_decrypt_k2Enck3_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,X1,X2),iknows(atoms(X3,n1,X5),enc(X6,X7,X8,X9,X10,n1,X12,X13,X14)))
     <= p(state(X0,X1,X2),iknows(atoms(X3,n0,n1),enc(X6,X7,X8,X9,X10,n1,X12,X13,X14))) ) )).

fof(encrypt_hn1k1_k1Enck1_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(h(n1,X0,X1,n1,X3,X4,X5),X6,X7),iknows(atoms(n1,X9,X10),enc(n1,X12,X13,X14,X15,X16,X17,X18,X19)))
     <= p(state(h(n1,X0,X1,n1,X3,X4,X5),X6,X7),iknows(atoms(n1,X9,X10),enc(n0,X12,X13,X14,X15,X16,X17,X18,X19))) ) )).

fof(set_attr_hn1k2_sensitive_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,h(n1,X1,X2,X3,X4,n1,X6),X7),X8)
     <= p(state(X0,h(n1,X1,X2,X3,X4,n0,X6),X7),X8) ) )).

fof(wrap_hn1k3_hn1k2_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,h(n1,X1,X2,X3,X4,X5,n1),h(n1,n1,X8,X9,X10,X11,X12)),iknows(X13,enc(X14,X15,X16,X17,X18,n1,X20,X21,X22)))
     <= p(state(X0,h(n1,X1,X2,X3,X4,X5,n1),h(n1,n1,X8,X9,X10,X11,X12)),iknows(X13,enc(X14,X15,X16,X17,X18,n0,X20,X21,X22))) ) )).

fof(co1,conjecture,(
    ? [X,Y,X1,X2,X3] : p(X,iknows(atoms(n1,X1,X2),Y)) )).

fof(wrap_hn1k2_hn1k1_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(h(n1,X0,X1,X2,X3,X4,n1),h(n1,n1,X7,X8,X9,X10,X11),X12),iknows(X13,enc(X14,n0,X16,X17,X18,X19,X20,X21,X22)))
     => p(state(h(n1,X0,X1,X2,X3,X4,n1),h(n1,n1,X7,X8,X9,X10,X11),X12),iknows(X13,enc(X14,n1,X16,X17,X18,X19,X20,X21,X22))) ) )).

fof(set_attr_hn1k1_sensitive_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(h(n1,X0,X1,X2,X3,n0,X5),X6,X7),X8)
     => p(state(h(n1,X0,X1,X2,X3,n1,X5),X6,X7),X8) ) )).

fof(intruder_decrypt_k3Enck3_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,X1,X2),iknows(atoms(X3,X4,n1),enc(X6,X7,X8,X9,X10,X11,X12,X13,n1)))
     <= p(state(X0,X1,X2),iknows(atoms(X3,X4,n1),enc(X6,X7,X8,X9,X10,X11,X12,X13,n1))) ) )).

fof(unwrap_hn1k1_hn1k3_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(h(n1,X0,n1,X2,X3,X4,X5),X6,h(n1,X7,X8,X9,X10,X11,n1)),iknows(X13,enc(X14,X15,X16,X17,X18,X19,n1,X21,X22)))
     <= p(state(h(n1,X0,n1,X2,X3,X4,X5),X6,h(n0,X7,X8,X9,X10,X11,X12)),iknows(X13,enc(X14,X15,X16,X17,X18,X19,n1,X21,X22))) ) )).

fof(wrap_hn1k3_hn1k1_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(h(n1,X0,X1,X2,X3,X4,n1),X6,h(n1,n1,X8,X9,X10,X11,X12)),iknows(X13,enc(X14,X15,n1,X17,X18,X19,X20,X21,X22)))
     <= p(state(h(n1,X0,X1,X2,X3,X4,n1),X6,h(n1,n1,X8,X9,X10,X11,X12)),iknows(X13,enc(X14,X15,n0,X17,X18,X19,X20,X21,X22))) ) )).

fof(set_attr_hn1k2_unwrap_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,h(n1,n0,n1,n0,X4,X5,X6),X7),X8)
     <= p(state(X0,h(n1,n0,n0,n0,X4,X5,X6),X7),X8) ) )).

fof(encrypt_k3Enck2_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,X1,X2),iknows(atoms(X3,n1,n1),enc(X6,X7,X8,X9,X10,X11,X12,n0,X14)))
     => p(state(X0,X1,X2),iknows(atoms(X3,n1,n1),enc(X6,X7,X8,X9,X10,X11,X12,n1,X14))) ) )).

fof(wrap_hn1k2_hn1k3_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,h(n1,n1,X2,X3,X4,X5,X6),h(n1,X7,X8,X9,X10,X11,n1)),iknows(X13,enc(X14,X15,X16,X17,X18,X19,X20,n0,X22)))
     => p(state(X0,h(n1,n1,X2,X3,X4,X5,X6),h(n1,X7,X8,X9,X10,X11,n1)),iknows(X13,enc(X14,X15,X16,X17,X18,X19,X20,n1,X22))) ) )).

fof(decrypt_hn1k1_k1Enck1_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(h(n1,X0,X1,X2,n1,X4,X5),X6,X7),iknows(atoms(n1,X9,X10),enc(n1,X12,X13,X14,X15,X16,X17,X18,X19)))
     <= p(state(h(n1,X0,X1,X2,n1,X4,X5),X6,X7),iknows(atoms(n0,X9,X10),enc(n1,X12,X13,X14,X15,X16,X17,X18,X19))) ) )).

fof(domain_constraints,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( ( ( X0 = n1
        <~> X0 = n0 )
        & ( X1 = n0
        <~> X1 = n1 )
        & ( n1 = X2
        <~> n0 = X2 )
        & ( n1 = X3
        <~> X3 = n0 )
        & ( X7 = n0
        <~> X7 = n1 )
        & ( n0 = X10
        <~> X10 = n1 )
        & ( n0 = X12
        <~> X12 = n1 )
        & ( X13 = n0
        <~> X13 = n1 )
        & ( n0 = X15
        <~> n1 = X15 )
        & ( X16 = n0
        <~> n1 = X16 )
        & ( n0 = X17
        <~> X17 = n1 )
        & ( X18 = n1
        <~> X18 = n0 )
        & ( X19 = n1
        <~> n0 = X19 )
        & ( X20 = n0
        <~> n1 = X20 )
        & ( X24 = n0
        <~> X24 = n1 )
        & ( n1 = X25
        <~> n0 = X25 )
        & ( n0 = X26
        <~> n1 = X26 )
        & ( X29 = n1
        <~> X29 = n0 )
        & ( X30 = n1
        <~> n0 = X30 )
        & ( X31 = n1
        <~> X31 = n0 )
        & ( n0 = X32
        <~> n1 = X32 )
        & ( X28 = n1
        <~> n0 = X28 )
        & ( X27 = n1
        <~> n0 = X27 )
        & ( n0 = X23
        <~> n1 = X23 )
        & ( X22 = n1
        <~> X22 = n0 )
        & ( X21 = n0
        <~> n1 = X21 )
        & ( X14 = n0
        <~> n1 = X14 )
        & ( X11 = n0
        <~> X11 = n1 )
        & ( n0 = X9
        <~> n1 = X9 )
        & ( n1 = X8
        <~> n0 = X8 )
        & ( X6 = n0
        <~> n1 = X6 )
        & ( X5 = n1
        <~> X5 = n0 )
        & ( X4 = n1
        <~> X4 = n0 ) )
     <= p(state(h(X0,X1,X2,X3,X4,X5,X6),h(X7,X8,X9,X10,X11,X12,X13),h(X14,X15,X16,X17,X18,X19,X20)),iknows(atoms(X21,X22,X23),enc(X24,X25,X26,X27,X28,X29,X30,X31,X32))) ) )).

fof(unwrap_hn1k1_hn1k2_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(h(n1,X0,n1,X2,X3,X4,X5),h(n0,X6,X7,X8,X9,X10,X11),X12),iknows(X13,enc(X14,X15,X16,n1,X18,X19,X20,X21,X22)))
     => p(state(h(n1,X0,n1,X2,X3,X4,X5),h(n1,X6,X7,X8,X9,X10,n1),X12),iknows(X13,enc(X14,X15,X16,n1,X18,X19,X20,X21,X22))) ) )).

fof(set_attr_hn1k2_encrypt_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,h(n1,n0,n0,n1,X4,X5,X6),X7),X8)
     <= p(state(X0,h(n1,n0,n0,n0,X4,X5,X6),X7),X8) ) )).

fof(decrypt_hn1k2_k3Enck2_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,h(n1,X1,X2,X3,n1,X5,X6),X7),iknows(atoms(X8,X9,n0),enc(X11,X12,X13,X14,X15,X16,X17,n1,X19)))
     => p(state(X0,h(n1,X1,X2,X3,n1,X5,X6),X7),iknows(atoms(X8,X9,n1),enc(X11,X12,X13,X14,X15,X16,X17,n1,X19))) ) )).

fof(unwrap_hn1k3_hn1k3_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,X1,h(n1,X2,n1,X4,X5,X6,X7)),iknows(X8,enc(X9,X10,X11,X12,X13,X14,X15,X16,n1)))
     => p(state(X0,X1,h(n1,X2,n1,X4,X5,X6,n1)),iknows(X8,enc(X9,X10,X11,X12,X13,X14,X15,X16,n1))) ) )).

fof(set_attr_hn1k3_sensitive_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,X1,h(n1,X2,X3,X4,X5,n0,X7)),X8)
     => p(state(X0,X1,h(n1,X2,X3,X4,X5,n1,X7)),X8) ) )).

fof(intruder_decrypt_k3Enck2_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,X1,X2),iknows(atoms(X3,n1,n0),enc(X6,X7,X8,X9,X10,X11,X12,n1,X14)))
     => p(state(X0,X1,X2),iknows(atoms(X3,X4,n1),enc(X6,X7,X8,X9,X10,X11,X12,n1,X14))) ) )).

fof(unwrap_hn1k2_hn1k3_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,h(n1,X1,n1,X3,X4,X5,X6),h(n1,X7,X8,X9,X10,X11,n1)),iknows(X13,enc(X14,X15,X16,X17,X18,X19,X20,n1,X22)))
     <= p(state(X0,h(n1,X1,n1,X3,X4,X5,X6),h(n0,X7,X8,X9,X10,X11,X12)),iknows(X13,enc(X14,X15,X16,X17,X18,X19,X20,n1,X22))) ) )).

fof(set_attr_hn1k1_decrypt_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(h(n1,n0,X1,X2,n1,X4,X5),X6,X7),X8)
     <= p(state(h(n1,n0,X1,X2,n0,X4,X5),X6,X7),X8) ) )).

fof(decrypt_hn1k1_k2Enck1_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(h(n1,X0,X1,X2,n1,X4,X5),X6,X7),iknows(atoms(X8,n0,X10),enc(X11,X12,X13,n1,X15,X16,X17,X18,X19)))
     => p(state(h(n1,X0,X1,X2,n1,X4,X5),X6,X7),iknows(atoms(X8,n1,X10),enc(X11,X12,X13,n1,X15,X16,X17,X18,X19))) ) )).

fof(intruder_decrypt_k2Enck1_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,X1,X2),iknows(atoms(n1,n0,X5),enc(X6,X7,X8,n1,X10,X11,X12,X13,X14)))
     => p(state(X0,X1,X2),iknows(atoms(X3,n1,X5),enc(X6,X7,X8,n1,X10,X11,X12,X13,X14))) ) )).

fof(decrypt_hn1k2_k2Enck2_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,h(n1,X1,X2,X3,n1,X5,X6),X7),iknows(atoms(X8,n1,X10),enc(X11,X12,X13,X14,n1,X16,X17,X18,X19)))
     <= p(state(X0,h(n1,X1,X2,X3,n1,X5,X6),X7),iknows(atoms(X8,n0,X10),enc(X11,X12,X13,X14,n1,X16,X17,X18,X19))) ) )).

fof(intruder_decrypt_k2Enck2_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,X1,X2),iknows(atoms(X3,n1,X5),enc(X6,X7,X8,X9,n1,X11,X12,X13,X14)))
     => p(state(X0,X1,X2),iknows(atoms(X3,n1,X5),enc(X6,X7,X8,X9,n1,X11,X12,X13,X14))) ) )).

fof(decrypt_hn1k1_k3Enck1_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(h(n1,X0,X1,X2,n1,X4,X5),X6,X7),iknows(atoms(X8,X9,n0),enc(X11,X12,X13,X14,X15,X16,n1,X18,X19)))
     => p(state(h(n1,X0,X1,X2,n1,X4,X5),X6,X7),iknows(atoms(X8,X9,n1),enc(X11,X12,X13,X14,X15,X16,n1,X18,X19))) ) )).

fof(set_attr_hn1k3_unwrap_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,X1,h(n1,n0,n1,n0,X5,X6,X7)),X8)
     <= p(state(X0,X1,h(n1,n0,n0,n0,X5,X6,X7)),X8) ) )).

fof(unwrap_hn1k2_hn1k2_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,h(n1,X1,n1,X3,X4,X5,X6),X7),iknows(X8,enc(X9,X10,X11,X12,n1,X14,X15,X16,X17)))
     => p(state(X0,h(n1,X1,n1,X3,X4,X5,n1),X7),iknows(X8,enc(X9,X10,X11,X12,n1,X14,X15,X16,X17))) ) )).

fof(encrypt_hn1k3_k1Enck3_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,X1,h(n1,X2,X3,n1,X5,X6,X7)),iknows(atoms(n1,X9,X10),enc(X11,X12,n1,X14,X15,X16,X17,X18,X19)))
     <= p(state(X0,X1,h(n1,X2,X3,n1,X5,X6,X7)),iknows(atoms(n1,X9,X10),enc(X11,X12,n0,X14,X15,X16,X17,X18,X19))) ) )).

fof(encrypt_k1Enck3_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,X1,X2),iknows(atoms(n1,X4,n1),enc(X6,X7,n1,X9,X10,X11,X12,X13,X14)))
     <= p(state(X0,X1,X2),iknows(atoms(n1,X4,n1),enc(X6,X7,n0,X9,X10,X11,X12,X13,X14))) ) )).

fof(set_attr_hn1k3_extractable_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,X1,h(n1,X2,X3,X4,X5,X6,n1)),X8)
     => p(state(X0,X1,h(n1,X2,X3,X4,X5,X6,n0)),X8) ) )).

fof(decrypt_hn1k3_k3Enck3_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,X1,h(n1,X2,X3,X4,n1,X6,X7)),iknows(atoms(X8,X9,n1),enc(X11,X12,X13,X14,X15,X16,X17,X18,n1)))
     <= p(state(X0,X1,h(n1,X2,X3,X4,n1,X6,X7)),iknows(atoms(X8,X9,n0),enc(X11,X12,X13,X14,X15,X16,X17,X18,n1))) ) )).

fof(encrypt_k2Enck3_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,X1,X2),iknows(atoms(X3,n1,n1),enc(X6,X7,X8,X9,X10,n0,X12,X13,X14)))
     => p(state(X0,X1,X2),iknows(atoms(X3,n1,n1),enc(X6,X7,X8,X9,X10,n1,X12,X13,X14))) ) )).

fof(intruder_decrypt_k1Enck3_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,X1,X2),iknows(atoms(n1,X4,X5),enc(X6,X7,n1,X9,X10,X11,X12,X13,X14)))
     <= p(state(X0,X1,X2),iknows(atoms(n0,X4,n1),enc(X6,X7,n1,X9,X10,X11,X12,X13,X14))) ) )).

fof(set_attr_hn1k1_wrap_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(h(n1,n0,n0,X2,n0,X4,X5),X6,X7),X8)
     => p(state(h(n1,n1,n0,X2,n0,X4,X5),X6,X7),X8) ) )).

fof(encrypt_hn1k2_k2Enck2_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,h(n1,X1,X2,n1,X4,X5,X6),X7),iknows(atoms(X8,n1,X10),enc(X11,X12,X13,X14,n0,X16,X17,X18,X19)))
     => p(state(X0,h(n1,X1,X2,n1,X4,X5,X6),X7),iknows(atoms(X8,n1,X10),enc(X11,X12,X13,X14,n1,X16,X17,X18,X19))) ) )).

fof(intruder_decrypt_k1Enck1_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,X1,X2),iknows(atoms(n1,X4,X5),enc(n1,X7,X8,X9,X10,X11,X12,X13,X14)))
     => p(state(X0,X1,X2),iknows(atoms(n1,X4,X5),enc(n1,X7,X8,X9,X10,X11,X12,X13,X14))) ) )).

fof(decrypt_hn1k2_k1Enck2_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,h(n1,X1,X2,X3,n1,X5,X6),X7),iknows(atoms(n1,X9,X10),enc(X11,n1,X13,X14,X15,X16,X17,X18,X19)))
     <= p(state(X0,h(n1,X1,X2,X3,n1,X5,X6),X7),iknows(atoms(n0,X9,X10),enc(X11,n1,X13,X14,X15,X16,X17,X18,X19))) ) )).

fof(encrypt_hn1k2_k1Enck2_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,h(n1,X1,X2,n1,X4,X5,X6),X7),iknows(atoms(n1,X9,X10),enc(X11,n1,X13,X14,X15,X16,X17,X18,X19)))
     <= p(state(X0,h(n1,X1,X2,n1,X4,X5,X6),X7),iknows(atoms(n1,X9,X10),enc(X11,n0,X13,X14,X15,X16,X17,X18,X19))) ) )).

fof(set_attr_hn1k3_encrypt_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,X1,h(n1,n0,n0,n1,X5,X6,X7)),X8)
     <= p(state(X0,X1,h(n1,n0,n0,n0,X5,X6,X7)),X8) ) )).

fof(set_attr_hn1k2_extractable_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,h(n1,X1,X2,X3,X4,X5,n1),X7),X8)
     => p(state(X0,h(n1,X1,X2,X3,X4,X5,n0),X7),X8) ) )).

fof(encrypt_hn1k1_k2Enck1_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(h(n1,X0,X1,n1,X3,X4,X5),X6,X7),iknows(atoms(X8,n1,X10),enc(X11,X12,X13,n1,X15,X16,X17,X18,X19)))
     <= p(state(h(n1,X0,X1,n1,X3,X4,X5),X6,X7),iknows(atoms(X8,n1,X10),enc(X11,X12,X13,n0,X15,X16,X17,X18,X19))) ) )).

fof(intruder_decrypt_k1Enck2_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,X1,X2),iknows(atoms(n1,X4,X5),enc(X6,n1,X8,X9,X10,X11,X12,X13,X14)))
     <= p(state(X0,X1,X2),iknows(atoms(n0,n1,X5),enc(X6,n1,X8,X9,X10,X11,X12,X13,X14))) ) )).

fof(unwrap_hn1k1_hn1k1_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(h(n1,X0,n1,X2,X3,X4,n1),X6,X7),iknows(X8,enc(n1,X10,X11,X12,X13,X14,X15,X16,X17)))
     <= p(state(h(n1,X0,n1,X2,X3,X4,X5),X6,X7),iknows(X8,enc(n1,X10,X11,X12,X13,X14,X15,X16,X17))) ) )).

fof(initial_state,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] : p(state(h(n1,n0,n0,n0,n0,n0,n1),h(n1,n0,n0,n0,n0,n0,n0),h(n0,n0,n0,n0,n0,n0,n0)),iknows(atoms(n0,n0,n1),enc(n0,n0,n0,n0,n0,n0,n0,n0,n0))) )).

fof(encrypt_hn1k1_k3Enck1_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(h(n1,X0,X1,n1,X3,X4,X5),X6,X7),iknows(atoms(X8,X9,n1),enc(X11,X12,X13,X14,X15,X16,n1,X18,X19)))
     <= p(state(h(n1,X0,X1,n1,X3,X4,X5),X6,X7),iknows(atoms(X8,X9,n1),enc(X11,X12,X13,X14,X15,X16,n0,X18,X19))) ) )).

fof(unwrap_hn1k3_hn1k2_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,h(n1,X1,X2,X3,X4,X5,n1),h(n1,X7,n1,X9,X10,X11,X12)),iknows(X13,enc(X14,X15,X16,X17,X18,n1,X20,X21,X22)))
     <= p(state(X0,h(n0,X1,X2,X3,X4,X5,X6),h(n1,X7,n1,X9,X10,X11,X12)),iknows(X13,enc(X14,X15,X16,X17,X18,n1,X20,X21,X22))) ) )).

fof(wrap_hn1k1_hn1k3_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(h(n1,n1,X1,X2,X3,X4,X5),X6,h(n1,X7,X8,X9,X10,X11,n1)),iknows(X13,enc(X14,X15,X16,X17,X18,X19,n1,X21,X22)))
     <= p(state(h(n1,n1,X1,X2,X3,X4,X5),X6,h(n1,X7,X8,X9,X10,X11,n1)),iknows(X13,enc(X14,X15,X16,X17,X18,X19,n0,X21,X22))) ) )).

fof(encrypt_k3Enck3_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,X1,X2),iknows(atoms(X3,X4,n1),enc(X6,X7,X8,X9,X10,X11,X12,X13,n1)))
     <= p(state(X0,X1,X2),iknows(atoms(X3,X4,n1),enc(X6,X7,X8,X9,X10,X11,X12,X13,n0))) ) )).

fof(set_attr_hn1k2_decrypt_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,h(n1,n0,X2,X3,n1,X5,X6),X7),X8)
     <= p(state(X0,h(n1,n0,X2,X3,n0,X5,X6),X7),X8) ) )).

fof(set_attr_hn1k3_decrypt_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,X1,h(n1,n0,X3,X4,n1,X6,X7)),X8)
     <= p(state(X0,X1,h(n1,n0,X3,X4,n0,X6,X7)),X8) ) )).

fof(encrypt_k3Enck1_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,X1,X2),iknows(atoms(n1,X4,n1),enc(X6,X7,X8,X9,X10,X11,n1,X13,X14)))
     <= p(state(X0,X1,X2),iknows(atoms(n1,X4,n1),enc(X6,X7,X8,X9,X10,X11,n0,X13,X14))) ) )).

fof(encrypt_k1Enck1_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,X1,X2),iknows(atoms(n1,X4,X5),enc(n0,X7,X8,X9,X10,X11,X12,X13,X14)))
     => p(state(X0,X1,X2),iknows(atoms(n1,X4,X5),enc(n1,X7,X8,X9,X10,X11,X12,X13,X14))) ) )).

fof(intruder_decrypt_k3Enck1_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,X1,X2),iknows(atoms(X3,X4,n1),enc(X6,X7,X8,X9,X10,X11,n1,X13,X14)))
     <= p(state(X0,X1,X2),iknows(atoms(n1,X4,n0),enc(X6,X7,X8,X9,X10,X11,n1,X13,X14))) ) )).

fof(wrap_hn1k2_hn1k2_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,h(n1,n1,X2,X3,X4,X5,n1),X7),iknows(X8,enc(X9,X10,X11,X12,n1,X14,X15,X16,X17)))
     <= p(state(X0,h(n1,n1,X2,X3,X4,X5,n1),X7),iknows(X8,enc(X9,X10,X11,X12,n0,X14,X15,X16,X17))) ) )).

fof(encrypt_hn1k3_k2Enck3_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,X1,h(n1,X2,X3,n1,X5,X6,X7)),iknows(atoms(X8,n1,X10),enc(X11,X12,X13,X14,X15,n1,X17,X18,X19)))
     <= p(state(X0,X1,h(n1,X2,X3,n1,X5,X6,X7)),iknows(atoms(X8,n1,X10),enc(X11,X12,X13,X14,X15,n0,X17,X18,X19))) ) )).

fof(set_attr_hn1k2_wrap_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,h(n1,n1,n0,X3,n0,X5,X6),X7),X8)
     <= p(state(X0,h(n1,n0,n0,X3,n0,X5,X6),X7),X8) ) )).

fof(set_attr_hn1k1_encrypt_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(h(n1,n0,n0,n1,X3,X4,X5),X6,X7),X8)
     <= p(state(h(n1,n0,n0,n0,X3,X4,X5),X6,X7),X8) ) )).

fof(wrap_hn1k1_hn1k2_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(h(n1,n1,X1,X2,X3,X4,X5),h(n1,X6,X7,X8,X9,X10,n1),X12),iknows(X13,enc(X14,X15,X16,n0,X18,X19,X20,X21,X22)))
     => p(state(h(n1,n1,X1,X2,X3,X4,X5),h(n1,X6,X7,X8,X9,X10,n1),X12),iknows(X13,enc(X14,X15,X16,n1,X18,X19,X20,X21,X22))) ) )).

fof(wrap_hn1k1_hn1k1_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(h(n1,n1,X1,X2,X3,X4,n1),X6,X7),iknows(X8,enc(n1,X10,X11,X12,X13,X14,X15,X16,X17)))
     <= p(state(h(n1,n1,X1,X2,X3,X4,n1),X6,X7),iknows(X8,enc(n0,X10,X11,X12,X13,X14,X15,X16,X17))) ) )).

fof(set_attr_hn1k1_unwrap_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(h(n1,n0,n0,n0,X3,X4,X5),X6,X7),X8)
     => p(state(h(n1,n0,n1,n0,X3,X4,X5),X6,X7),X8) ) )).

fof(set_attr_hn1k3_wrap_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(X0,X1,h(n1,n1,n0,X4,n0,X6,X7)),X8)
     <= p(state(X0,X1,h(n1,n0,n0,X4,n0,X6,X7)),X8) ) )).

fof(unwrap_hn1k3_hn1k1_command,axiom,(
    ! [X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21,X22,X23,X24,X25,X26,X27,X28,X29,X30,X31,X32,X33] :
      ( p(state(h(n0,X0,X1,X2,X3,X4,X5),X6,h(n1,X7,n1,X9,X10,X11,X12)),iknows(X13,enc(X14,X15,n1,X17,X18,X19,X20,X21,X22)))
     => p(state(h(n1,X0,X1,X2,X3,X4,n1),X6,h(n1,X7,n1,X9,X10,X11,X12)),iknows(X13,enc(X14,X15,n1,X17,X18,X19,X20,X21,X22))) ) )).

