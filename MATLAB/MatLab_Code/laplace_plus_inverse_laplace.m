%Need to figure out how to write some code for the inverse
%laplace to solve for a time equation!

%Define variables here!
syms s
F = (1/((1000/(100*10^-3))+s));
fprintf('Here is the equation we want to solve for!\nF = ');
disp(F)
f = ilaplace(F)
fprintf('As for the solved eequation here ya go!\nF(t) = ');
disp(f)
%We are going to see if we can implement a user input....
%keep in mind that the user needs to input the return key!{Enter?}
x = input('PLACE SOMETHING IN HERE!\n')
%hmmmm seems to work?