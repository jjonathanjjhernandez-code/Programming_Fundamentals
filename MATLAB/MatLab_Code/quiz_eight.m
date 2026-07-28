%just a simple solver for parallel two port network
Z_Port_One = [5 1; 1 7]; 
Z_Port_Two = [5 1; 1 7];

Y_Port_One = inv(Z_Port_One);
Y_Port_Two = inv(Z_Port_Two);
fprintf('Y1 = \n');
disp(Y_Port_One);
fprintf('Y2 = \n');
disp(Y_Port_Two);

Y_total = Y_Port_One + Y_Port_Two;
fprintf('Y_total = \n');
disp(Y_total);

Z_total = inv(Y_total);
fprintf('Z_total = \n');
disp(Z_total);
%the equation for I2 or Io for this scenario
%             -z21*Vg
%I2 =   -----------------------
%     (z11+Zg)*(z22+ZL) - z12*z21
Vg = 50;
Zg = .1;
Zl = 50000;
I2 = (Z_total(2,1)*-1*Vg)/((Z_total(1,1) + Zg)*(Z_total(2,2) + Zl) - Z_total(1,2)*Z_total(2,1));
fprintf('I2 = \n');
disp(I2);
fprintf('I2/Vg = \n');
disp(I2/Vg);
fprintf('inv Y - Z{should be approximately zero} = \n');
disp(inv(Y_Port_One) - Z_Port_One);