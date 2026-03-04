%квадратная матрица
msqr([],_).
msqr([H|T],G):-length(H,G),msqr(T,G).
msq([H|T]):-length([H|T],M),msqr(T,G),M is G.

%истинно, если квадратная матрица
matrix([H|T]):-msqr([H|T],_).

spisk([],[]).
spisk([H|T],G):-spisk(T,J),append(H,J,G).

%максимальный элемент квадратной матрицы
maxfrommatrix([H|T],N,G):-msq([H|T]),length([H|T],N),spisk([H|T],J),max(J,G).

max([],[]).
max([H|T],G):-length([H|T],L),L>1,max(T,J),(J > H,G is J;G is H);G is H.

%вектор из максимумов (по строкам) матрицы
vectmax([],[]).
vectmax([H|T],G):-matrix([H|T]),max(H,J),vectmax(T,K),append([J],K,G).

minus([],[]).
minus([H|T],[D|K]):-minus(T,K),D is 0-H.

razostanovka([],[]).
razostanovka([H|T],G):-minus(T,D),razostanovka(D,K),append([H],K,G).

razymiplikacia(_,[],_,_,0).
razymiplikacia([H|T],[HA|HT],A,S,F):-S is A+1,minor([H|T],S,[HH|TT]),det([HH|TT],G),J=HA * G,
    razymiplikacia([H|T],HT,S,_,D),F is J + D.

m([HA|HT],[HA|HT]).
%определитель матрицы
det([A],G):-length(A,B),B is 1,G is A.
det([H|T],F):-msq([H|T]),razostanovka(H,A),m(A,[HA|HT]),razymiplikacia([H|T],[HA|HT],-1,_,F),!.

minor([_|T],A,[HH|TT]):-isklych(T,A,[HH|TT]).
isklych([],_,[]).
isklych([H|T],A,[HH|TT]):-isk(H,A,HH),isklych(T,A,TT).

isk([],_,[]).
isk([H|T],A,[H|TI]):-not(A is 0),G is A-1,isk(T,G,TI).
isk([_|T],A,TI):-G is A-1,isk(T,G,TI).

%истинно, если A и B линейно зависимые вектора
lineral([H|T],[HH|TT]):-lineral([H|T],[HH|TT],_).
lineral([],[],_).
lineral([H|T],[HH|TT],A):-not(H is 0;HH is 0);(A is HH/H,lineral(T,TT,A)).

pyst(_,[]).
vectvid([[A]|[B]],[A|B]).
repiskl([H|T],_,_,[H|T]):-msqr([H|T],1).
repiskl([H|T],A,R,K):-J is R-(A+1),isklych([H|T],J,D),M is A+1,repiskl(D,M,R,K).
transposenar([H|T],G,A,R,[HH|TT]):-repiskl([H|T],A,R,K),vectvid(K,HH),G is A+1,(not(G is R),transposenar([H|T],_,G,R,TT);pyst(_,TT)).
%транспонированная матрица
transpose([H|T],[HH|TT]):-length([H|T],R),transposenar([H|T],_,0,R,[HH|TT]).

