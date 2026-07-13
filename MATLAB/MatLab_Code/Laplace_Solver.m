%clc;
clear;
% === Define your transfer function here! ===
% Define symbolic variables
syms v1 v2 vl s t


%Define Equations for Linear System!
eq1 = (v1-(1/s))/1 + (v1-(1/s))/(1/s) + (v1-v2)/s == 0;
eq2 = vl == v1-v2;
eq3 = (v2-v1)/s + v2 == 0;

%Solve Linear Equations using the solve function
sol = solve([eq1,eq2 ,eq3], [v1,v2,vl])

sol_vl = simplify(sol.vl); %Solve for vl in this scenario....
disp('Vl(s) = ');
pretty(sol_vl);
%Inverse Laplace of Vl(s)
vl_t = simplify(ilaplace(sol_vl,s,t));%convert s into t
disp('vl(t) = ');
pretty(vl_t);
% at 0+
vl_0p = limit(vl_t,t,0, 'right');
disp('vl(0+) = ');
disp(vl_0p);
%Steady - State Infinity
v_ss = limit(vl_t,t,inf);
disp('vl(inf) = ');
disp(v_ss);