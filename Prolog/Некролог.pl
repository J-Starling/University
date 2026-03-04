add(A,0,A):- !.
add(A,s(B),s(C)):- add(A,B,C).

mult(0,B,0):- !.
mult(s(A),B,C):- add(X,B,C), mult(A,B,X).

g_t(s(A),0):- !.
g_t(s(A),s(B)):-g_t(A,B).

gcd(A, 0, A) :- !.
gcd(A, B, C) :- not(0 is B), R is A mod B, gcd(B, R, C).

q_r(A, B, C, D) :- C is A div B, D is A mod B.

prime(N, A) :- findnsols(N,B,p(B),L), !, last(L,A).
pint(1).
pint(X):- pint(Y), X is Y+1.
p(A):- pint(A), A>1, A1 is A - 1, notdiv(A,A1).
notdiv(_,1):- !.
notdiv(A,B):- B>1, X is A mod B, X\=0, B1 is B - 1, notdiv(A,B1).

fib(1,[1]):- !.
fib(2,[1,1]):- !.
fib(N,A):- N>2, N1 is N-1, N2 is N-2, fib(N1, B1), last(B1, A1), fib(N2, B2), last(B2, A2), 
    A_ is A1 + A2, append(B1, [A_], A). 
