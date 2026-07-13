%Need a script to solve linear system of equations....
%will try to implement that here!
syms x y z
equation1 = 2*x+y+z==2;
equation2 = -x + y -z ==3;
equation3 = x+2*y+3*z==-10;
%Augmented Matrix represented as....
%|2   1   1  2  |
%|-1  1  -1  3  |
%|1   2   3 -10 |
%Convert into the form AX=B
[A,B] = equationsToMatrix([equation1,equation2,equation3],[x,y,z]);
%finally use linsolve to get your results!
X = linsolve(A,B)

%Here is another way of doing the same thing!
sol = solve([equation1,equation2,equation3],[x,y,z]);
xSol = sol.x;
display(xSol);
ySol = sol.y;
display(ySol);
zSol = sol.z;
display(zSol);
%The inputs to solve are a vector of equations, and a vector of variables
%to solve the equations for!
%The function solve returns the solutions in a structured array.
%To access the the solutions, index into the array!
