clc
%Define variables with the syms!
syms v(t)

%Define the equation you want to solve for
Dv = diff(v,t)%You could be solving for Voltage/Current

%Once you decided which variable you are going to solve for place your
%constants
ode = diff(v,t,2) + 1250*diff(v,t) + 781250*v == 214843750
cond = [v(0)==150 Dv(0)==34375]
Dsol(t) = dsolve(ode,cond)
%to make the differential equation just be mindful that you are trying to
%solve for current!
