clc
clear all
syms i(t)
Di = diff(i,t)
ode = diff(i,t,2) + 12*diff(i,t) + 32*i == 32
cond = [i(0)==0 Di(0)==0]
Dsol(t) = dsolve(ode,cond)