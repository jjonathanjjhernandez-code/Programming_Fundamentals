%keep a note on your equations and the amount of variables present in your
%solver.....variables must equate or exceed amount of equations to be
%solved!
%testing linear equation solver for a specific use
syms v_plus vs v1 v_minus voa vx vo io ia vi is s r l c
%Solution to finding the output to the amplifier
equation_one = (v_plus-vs)/2000 + v_plus/(2000000/s)==0;
equation_two = (v_minus-voa)/4000 + v_minus/4000==0;
equation_three = v_plus==v_minus;
solution = solve([equation_one,equation_two,equation_three],[v_plus,voa,v_minus]);
voaa =  solution.voa;
%fprintf('VOA = \n');
%pretty(voaa);
%Conducting voltage division to get the (voltage output capacitor)/voltage
%input
v_oc = ((2000000/s)/(2000+2000000/s))*voaa;
%fprintf('VOC = \n');
%pretty(simplify(v_oc));

%sike doing some mumbo jumbo stuff!
v11 = (1+1/s+3*s+2);
z11 = v11;
disp(simplify(z11));
z_myst = (s+1)/(s+1/s+s) + s+1;
%fprintf('Z_tot = \n')
%disp(simplify(z_myst))

%equation solver for the regular laplace stuff!
eq_one = (v1-(1/3))/(s+1) + (v1 - (-1/(3*s)))/(1+1/s) + v1 ==0;
sol_one = solve(eq_one,v1);
v11 = sol_one;
il = (v11-(1/3))/(s+1);
fprintf('V1 = \n');
disp(simplify(v11));
fprintf('IL = \n');
disp(simplify(il));
il_t = ilaplace(il);
fprintf('I(t) = \n');
disp(simplify(il_t));

%some transfer function calculator
nodal_one = (vx-vi)/(2*s+5) + vx/(1/s) + vx/(2*s + 5)==0;
nodal_sol_one = solve(nodal_one,vx);
fprintf('Vx = \n');
pretty(simplify(nodal_sol_one));
Io = nodal_sol_one*(1/(2*s+5));
fprintf('Io/vi = \n');
Io_vi = Io/vi;
pretty(Io_vi);
Value = 1/(4*(10*1j)^3 + 20*(10*1j)^2 + 29*(10*1j) + 10);
disp(Value);

%another transfer function!
equation_one  = (vo-vs)/(2*10) + vo/(s*.1) + vo/(1000/s)==0;
transfer_sol1 = solve(equation_one,vo);
fprintf('Vo = \n');
pretty(transfer_sol1);

%need to calculate some a parameters once again!
l1 = [1 0; 1/(2*s) 1];
r1 = [1 2; 0 1];
c1 = [1 0; 0.5*s 1];
r2 = [1 4; 0 1];
a_params = l1*r1*c1*r2;
fprintf('A matrix  = \n');
disp(simplify(a_params));

%calculation of a two port parameter based on the a-parameters given!
a_parameters = [2 300; .005 1.5];
i2 = -(80)/(a_parameters(1,1)*600 + a_parameters(1,2) + a_parameters(2,1)*600*100 + a_parameters(2,2)*100);
fprintf('I2 = \n');
disp(i2);
i1 = (-1)*(a_parameters(2,1)*600 + a_parameters(2,2))*i2;
fprintf('I1 = \n');
disp(i1);
p_i2 = (i2^2)*600; %power provided to the impedance load
p_i1 = (i1^2)*100; %pwer provided to the impedance source
p_total = 80*i1 - p_i1; %total power because think about it....if our total power is whatever the VG
%is providing then that source impdance is some sort of internal resistance
%in a way?...
fprintf('Total Power = \n');
disp(p_total);