%%Nodal analysis with Nonlinear diode!!!
%{
Is = 10e-14;
Vt = .026;
syms Va Vb
eq_1= Va==15; %this here just represent the power supply!
eq_2= ((Vb-Va)/5) + Is*(exp(Vb/(4*Vt))-1) + ((Vb)/1.3)==0;%for exponential portions SAY exp!
sol = vpasolve([eq_1, eq_2], [Va, Vb]);
Vaa = double(sol.Va);
Vbb = double(sol.Vb);
fprintf('Here are your equations:\nVa = %f\nVb = %f\n', Vaa, Vbb);
%}

%here goes attempt number two!
Is = 10e-14;
Vt = .026;
%need to make a table{a 1D vector in this] of values!
Rload_values = [500 1000 1500 2000 3000 5000];
Rload_values_low = 0.1:0.1:2;
Vb_values = zeros(size(Rload_values));%basically makes a matrix full of zeros and size of Rload_values 6 in this case!
Va_values = zeros(size(Rload_values));
Vb_values_low = zeros(size(Rload_values_low));%basically makes a matrix full of zeros and size of Rload_values 6 in this case!
Va_values_low = zeros(size(Rload_values_low));
I_load_values_low = zeros(size(Rload_values_low));
I_load_value_high = zeros(size(Rload_values));
I_diodes = zeros(size(Rload_values));
syms Va Vb
%calculation for high resistor values
for k = 1:length(Rload_values)
    Rload = Rload_values(k);%temp variable to get value of the 1D vector
    eq_1 = Va==15;
    eq_2 = ((Vb-Va)/5) + Is*(exp(Vb/(4*Vt))-1) + ((Vb)/Rload)==0;%for exponential portions SAY exp!end
    solution = vpasolve([eq_1, eq_2], [Va, Vb]);
    Va_values(k) = double(solution.Va);%the double might be placed to concatenate?
    Vb_values(k) = double(solution.Vb);
    I_load_value_high(k) = Vb_values(k)/Rload;
    I_diodes(k) = Is*(exp(Vb_values(k)/(4*Vt))-1);
end
%calculation for low resistor values
for k = 1:length(Rload_values_low)
    Rload = Rload_values_low(k);%temp variable to get value of the 1D vector
    eq_1 = Va==15;
    eq_2 = ((Vb-Va)/5) + Is*(exp(Vb/(4*Vt))-1) + ((Vb)/Rload)==0;%for exponential portions SAY exp!end
    solution = vpasolve([eq_1, eq_2], [Va, Vb]);
    Va_values_low(k) = double(solution.Va);%the double might be placed to concatenate?
    Vb_values_low(k) = double(solution.Vb);
    I_load_values_low(k) = Vb_values_low(k) / Rload;
end
T=table(Rload_values',Va_values',Vb_values','VariableNames',{'Rload','Va','Vb'});
T_one=table(Rload_values_low',Va_values_low',Vb_values_low','VariableNames',{'Rload_low','Va','Vb'});
disp(T);
disp(T_one)
disp(I_load_value_high);
tiledlayout(3,2); %basically just makes an vector where you can place your plots!
%plotting some current values!
nexttile;
plot(Rload_values_low,I_load_values_low ,'o-', 'LineWidth', 1.5)
xlabel('R_{load} (\Omega)')
ylabel('I_l (A)')
title('Resistor load current vs. load resistance{RL<=2ohms}')
nexttile;
plot(Rload_values_low, Vb_values_low, 'o-', 'LineWidth', 1.5)
xlabel('R_{load} (\Omega)')
ylabel('V_l (V)')
title('Diode node voltage vs. load resistance{RL<=2ohms}')
%plotting some voltage values!
nexttile;
plot(Rload_values,I_load_value_high*1000,'o-', 'LineWidth', 1)%double check your values and scale them up if need be!
xlabel('R_{load} (\Omega)')
ylabel('I_l (mA)')
title('Resistor load current vs. load resistance{RL>=500ohms}')
grid on

nexttile;
plot(Rload_values, Vb_values, 'o-', 'LineWidth', 1.5)
xlabel('R_{load} (\Omega)')
ylabel('V_l (V)')
title('Diode node voltage vs. load resistance{RL>=500ohms}')
grid on

%plotting current values for diodes
nexttile;
plot(Rload_values, I_diodes, 'o-', 'LineWidth', 1.5)
xlabel('R_{load} (\Omega)')
ylabel('I_d (A)')
title('Diode current vs. load resistance{RL>=500ohms}')
grid on
nexttile;
plot(Rload_values, Vb_values, 'o-', 'LineWidth', 1.5)
xlabel('R_{load} (\Omega)')
ylabel('V_d (V)')
title('Diode node voltage vs. load resistance{RL>=500ohms}')
grid on
