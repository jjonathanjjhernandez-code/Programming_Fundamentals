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
C = [1]
D = [1*10^(-9) 2.2*10^(-5) 1 0]
[coeff, roots, k_num] = residue(C,D)
fprintf('holy moly!\n')
%Inverse Laplace
