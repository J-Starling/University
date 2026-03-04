unique([]):-!.
unique([Head|Tail]):-
   member(Head, Tail), !, fail;
   unique(Tail).

witness(клод).
witness(жак).
witness(дик).

indication(_,_,_).

solve(Solve):- Solve = [indication(X, Y, Z)],
witness(X), witness(Y), witness(Z), unique([X, Y, Z]),
anekdot(Solve),
write(X), writeln(" говорит правду."),
write(Y), write(" и "), write(Z), write(" лгут.").

statement1(Solve):- member(indication(клод,_,_), Solve); member(indication(жак,_,_), Solve).
statement2(Solve):- member(indication(жак,_,_), Solve); member(indication(дик,_,_), Solve).
statement3(Solve):- member(indication(дик,_,_), Solve); member(indication(_,_,дик), Solve).

anekdot(Solve):- 
statement1(Solve),
statement2(Solve),
statement3(Solve).

% solve([indication(_,_,_)])
