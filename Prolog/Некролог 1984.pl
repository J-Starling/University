unique([]):-!.
unique([Head|Tail]):-
   member(Head, Tail), !, fail;
   unique(Tail).

student(алиса).
student(елизавета).
student(сева).
student(роман).

day(вторник).
day(среда).
day(четверг).
day(пятница).

schedule(_,_).

solve(Solve):- Solve = [schedule(X, XDay), schedule(Y, YDay), schedule(Z, ZDay), schedule(W, WDay)],
student(X), student(Y), student(Z), student(W), unique([X, Y, Z, W]), 
day(XDay), day(YDay), day(ZDay), day(WDay), unique([XDay,YDay,ZDay,WDay]),
anekdot(Solve),
writeln("Расписание:"),
write(X), write(' - '), writeln(XDay),
write(Y), write(' - '), writeln(YDay),
write(Z), write(' - '), writeln(ZDay),
write(W), write(' - '), writeln(WDay).

ultimatum1(Solve):- not(member(schedule(сева,вторник), Solve)), not(member(schedule(роман,вторник), Solve)).
ultimatum2(Solve):- (member(schedule(сева,среда), Solve); member(schedule(роман,четверг), Solve)) -> member(schedule(елизавета,пятница), Solve).
ultimatum3(Solve):- not(member(schedule(алиса,четверг), Solve)) -> member(schedule(елизавета,среда), Solve).
ultimatum4(Solve):- (member(schedule(алиса,среда), Solve); member(schedule(роман,среда), Solve)) -> member(schedule(сева,пятница), Solve).
ultimatum5(Solve):- not(member(schedule(роман,пятница), Solve)) -> (member(schedule(алиса,вторник), Solve), member(schedule(сева,среда), Solve)).

anekdot(Solve):- 
ultimatum1(Solve),
ultimatum2(Solve);
ultimatum3(Solve),
ultimatum4(Solve),
ultimatum5(Solve).

% solve([schedule(алиса,_), schedule(елизавета,_), schedule(сева,_), schedule(роман,_)])
