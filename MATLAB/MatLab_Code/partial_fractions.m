%Testing out some matlab functions!

%Partial Fraction Example COMPLETED
%As a simple explanation of the code provided variable C will represent 
% your the constant of the numerator of your partial fraction
%The same story goes for variable D just in the case of your denominators
%
%What residue does is expand the partial fraction and assuming once you
%get your partial fraction you can now move on to condut the inverse
%laplace!

%Partial Fraction Expansion
C = [160 1400 1500] %numerator
D = [5 25 0] %denominator
[coeff, roots, k_num] = residue(C,D)

fprintf('holy moly!\n');
%Inverse Laplace
syms s
f = ((12)/(s+5))+4/s
A = ilaplace(f)