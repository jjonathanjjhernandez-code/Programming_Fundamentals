%Need to do a simple 2nd ODE solver
%Requires you to know the initial conditions of your circuits
%if you do not know them it is best to just do the laplace!
syms i(t)
Di = diff(i,t)
ode = diff(i,t,2) + 12*diff(i,t) + 32*i == 32
cond = [i(0)==0 Di(0)==0]
Dsol(t) = dsolve(ode,cond)