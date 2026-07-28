%Need a script to solve linear system of equations....
%will try to implement that here!
syms v1 v2 va s
I1 = 1;
I2 = 0;
equation_one = (v1-va)/s + v1==I1;
equation_two =  (v2)/(1/s) + v2 + (v2-va)/s==I2;
equation_three = (va-v1)/s + (va-v2)/s + (va)/(1/s)==0;
sol = solve([equation_one,equation_two,equation_three],[v1,v2,va]);
z11 = sol.v1;
z21 = sol.v2;
fprintf('z11 = %s\nz21 = %s\n',z11,z21);

%A = ['z11 = ',num2str(double(z11)), ' z21 =
%',num2str(double(z21))];%numeric
%disp(A); %numeric


I1 = 0;
I2 = 1;
equation_one = (v1-va)/s + v1==I1;
equation_two =  (v2)/(1/s) + v2 + (v2-va)/s==I2;
equation_three = (va-v1)/s + (va-v2)/s + (va)/(1/s)==0;
sol = solve([equation_one,equation_two,equation_three],[v1,v2,va]);
z12 = sol.v1;
z22 = sol.v2;
fprintf('z12 = %s\nz22 = %s',z12,z22);%symbolic
%B = ['z12 = ',num2str(double(z12)), ' z22 = ',num2str(double(z22))];%numeric
%disp(B); %numeric

%Augmented Matrix represented as....
%|2   1   1  2  |
%|-1  1  -1  3  |
%|1   2   3 -10 |
%{
%Convert into the form AX=B
[A,B] = equationsToMatrix([equation1,equation2,equation3],[x,y,z]);
%finally use linsolve to get your results!
X = linsolve(A,B);

%Here is another way of doing the same thing!
sol = solve([equation1,equation2,equation3],[x,y,z]);
xSol = sol.x;
display(xSol);
ySol = sol.y;
display(ySol);
zSol = sol.z;
display(zSol);
%}
%The inputs to solve are a vector of equations, and a vector of variables
%to solve the equations for!
%The function solve returns the solutions in a structured array.
%To access the the solutions, index into the array!
