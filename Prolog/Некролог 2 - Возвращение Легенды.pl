%p(X,L) - истинно, если элемент X встречается в списке L
p(X,[H|T]):- X=H, !; p(X,T).

%определение множества
set([]).
set([H|T]):- not(p(H,T)), set(T).

%пересечение множеств
in([],_,[]).
in([H|T],B,[H|T1]):- set([H|T]), set(B), p(H,B), in(T,B,T1), !. 
in([_|T],B,C):- in(T,B,C).

%разность множеств
dif([],_,[]).
dif([H|T],B,C):- p(H,B), dif(T,B,C), !.
dif([H|T],B,[H|C]):- set([H|T]), set(B), dif(T,B,C).

%симметрическая разность множеств
sdif(A,B,C):- set(A), set(B), dif(A, B, C1), dif(B, A, C2), append(C1, C2, C).

%подмножество множества
sub([],_).
sub([H|T],B):- set([H|T]), set(B), p(H,B), sub(T,B).

