%This script is for the calculations of z,y,a,b,h,g parameters!
%they seem to be interconnected with one another....but as long as you know
%two of them you should be fine.....

%Now as far as we need to know about two-port networks is that they are
%used to determine behavior only on the input and outputs of terminals of 
%circuits......now of course there may be circuitry or components in
%between the two terminal ports but our techniques of open/closing certain
%terminal ends we can get our parameter values and go from there...
%we will try to understand and interpret their significance piece by piece

%place your impedance values here!
%|z11    z12|
%|z21    z22|


z11 = input('z11 = ');
z12 = input('z12 = ');
z21 = input('z21 = ');
z22 = input('z22 = ');

%delta z = (z11)(z22) - (z12)(z21)
delta_z = (z11*z22) - (z12*z21);

%compute your admittance parameters over here
y11 = (z22)/(delta_z);
y12 = (-z12)/(delta_z);
y21 = (-z21)/(delta_z);
y22 = (z11)/(delta_z);

%admittance display symbolically
%fprintf('y11 = %s\ty12 = %s\ny21 = %s\ty22 = %s',y11,y12,y21,y22);

%display your admittance parameters over here!---numerically
%A = ['y11 = ', num2str(y11), ' y12 = ', num2str(y12), ' y21 = ', num2str(y21), ' y22 = ', num2str(y22)];
%disp(A);

%compute your transmission parameters over here
% 'a' parameters
a11 = (z11)/(z21);
a12 = (delta_z)/(z21);
a21 = (1)/(z21);
a22 = (z22)/(z21);
%a display symbolically
%fprintf('a11 = %s\ta12 = %s\na21 = %s\ta22 = %s',a11,a12,a21,a22);

%numeric a
%B = ['a11 = ', num2str(a11), ' a12 = ', num2str(a12), ' a21 = ', num2str(a21), ' a22 = ', num2str(a22)];
%disp(B);

% 'b' parameters
b11 = (z22)/(z12);
b12 = (delta_z)/(z12);
b21 = (1)/(z12);
b22 = (z11)/(z12);
%b parameters display symbolically
%fprintf('b11 = %s\tb12 = %s\nb21 = %s\tb22 = %s',b11,b12,b21,b22);

%numeric b
%C = ['b11 = ', num2str(b11), ' b12 = ', num2str(b12), ' b21 = ', num2str(b21), ' b22 = ', num2str(b22)];
%disp(C);

%compute hybrid parameters
% 'h' parameters
h11 = (delta_z)/(z22);
h12 = (z12)/(z22);
h21 = -(z21)/(z22);
h22 = (1)/(z22);
%h display symbolically
%fprintf('h11 = %s\th12 = %s\nh21 = %s\th22 = %s',h11,h12,h21,h22);

%numeric h
D = ['h11 = ', num2str(h11), ' h12 = ', num2str(h12), ' h21 = ', num2str(h21), ' h22 = ', num2str(h22)];
disp(D);

% 'g' parameters
g11 = (1)/(z11);
g12 = -(z12)/(z11);
g21 = (z21)/(z11);
g22 = (delta_z)/(z11);
%admittance display symbolically
%fprintf('g11 = %s\tg12 = %s\ng21 = %s\tg22 = %s',g11,g12,g21,g22);

%numeric g
%E = ['g11 = ', num2str(g11), ' g12 = ', num2str(g12), ' g21 = ', num2str(g21), ' g22 = ', num2str(g22)];
%disp(E);
