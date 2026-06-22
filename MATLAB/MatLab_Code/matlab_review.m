%{
1.create a script file that prompts uuser for an outer radius and an inner
radius!
2.check if both inputs are positive and R>r
3.calculate the area of an annulus
4.make a function called annulus_area..compute and output the area
5.call here in the script!
%}
fprintf("when prompted please place an input for R and r!\n");
R = input("R: \n");
r = input("r: \n");
if r<R
    if r<0
        error('both inputs are negative!');
    end
elseif r>R
    error('R needs to be bigger than r');
else
    fprintf("ok\n");
end
fprintf("your inputs qualify for the next round!\n");
%A = annulus_area(R,r);
fprintf("Outer = %.2f m, Inner = %.2f m, Area = %.4f m^2",R,r,annulus_area(R,r));
%A = pi*((R*R)-(r*r));
%fprintf("the value of the area is....\n");
%disp(A);
%{
whos
  Name      Size            Bytes  Class     Attributes

  A         1x1                 8  double              
  R         1x1                 8  double              
  ans       1x2                16  double              
  p         1x4                32  double              
  r         1x1                 8  double              
  t         1x9                72  double              
  tc        9x1                72  double              
  tsq       1x9                72  double  
Functions have their own workspace, separate from the base workspace. 
Therefore, none of the calls to the function triarea overwrite the value 
of a in the base workspace
%}