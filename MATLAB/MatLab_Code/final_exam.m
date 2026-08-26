%Question NUmber Two for the FInal
syms  v1 vs s va
%Phase One
equation_one = (v1-vs)/2 + v1/(2/s) + v1/(2/s + 2) ==0;
solution = solve(equation_one, v1);
fprintf('V1 = \n');
pretty(simplify(solution));
%Phase Two
Vo = solution*(2/(2+2/s));
fprintf('Vo = \n');
pretty(simplify(Vo));


%Question Number Four
ZP1 = [1 3+s; 0 1];
YP1 = [1 0; s/6 1];
AP1 = ZP1*YP1;
fprintf('A1 = \n');
disp(AP1);
AP2 = AP1;
AB11 =  AP1(1,1)*AP2(1,1) + AP1(1,2)*AP2(2,1);
AB12 =  AP1(1,1)*AP2(1,2) + AP1(1,2)*AP2(2,2);
AB21 =  AP1(2,1)*AP2(1,1) + AP1(2,2)*AP2(2,1);
AB22 =  AP1(2,1)*AP2(1,2) + AP1(2,2)*AP2(2,2);


AB = [AB11 AB12; AB21 AB22];
fprintf('Big Network A parameters = \n');
disp(simplify(AB));
AB_multiply = AP1*AP2;
fprintf('Big Network A params based off multiplication = \n');
disp(simplify(AB_multiply));
I2_I1 = (-1)/(AB(2,1)*30000 + AB(2,2));
fprintf('I2/I1 = \n');
pretty(simplify(I2_I1))

%Question Number One
eq_one = (va-15)/8 + (va+8)/(2+4*s)  + (12*va*s + 96*s)/(2+4*s)== 4;
sol_one = solve(eq_one,va);
fprintf('v1 = \n');
pretty(simplify(sol_one));
vy = ((sol_one+8)/(2+4*s))*2;
fprintf('Vy = \n');
pretty(simplify(vy));
fprintf('Vy(t) = \n');
pretty(ilaplace(simplify(vy)));