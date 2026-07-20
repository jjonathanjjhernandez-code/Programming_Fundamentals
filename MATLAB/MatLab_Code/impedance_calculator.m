% To determine your behavior place your black box in series with a shunt
% resistor of your choice and look at its behavior in a low frequency
% state and high frequency......what do you notice?

fprintf("==============================================\n");
disp('Hello! I am here to calculate your impedance value!');
fprintf("Based on your simulations what do you believe is the circuit at hand?\n");
sp_choice = input('Black Box Inside: 1.Series 2.Parallel == ');

if any(sp_choice==1)
    disp('*****Series Calculation*****');
else 
    disp('*****Parallel Calculation*****');
end

% Calculate the Magnitudes over here
V_R = input('V_R = '); %voltage across the shunt
V_Z = input('V_Z = '); %voltage across black box
R_Shunt = input('Shunt_R = ');
Z_magnitude = V_Z/(V_R/R_Shunt);

% Calculate the Phases over here
frequency = input('Frequency = ');
choice = input('1. delta t  2. measured times = ');

if any(choice==1)
    theta = 360 * (input('Delta t = ') / (1/frequency));
else 
    theta = 360 * ((input('VRmag Time through R = ') - input('Vmag Time at Z = ')) / (1/frequency));
end

% Calculate base Z universally first
Z_real = Z_magnitude * cosd(theta);
Z_imag = Z_magnitude * sind(theta);
Z = Z_real + Z_imag*1j;

A = ['Z_MAGNITUDE = ', num2str(Z_magnitude)];
B = ['Z_THETA = ', num2str(theta)];
C = ['Z-Equation = ', num2str(Z)];
disp(A);
disp(B);
disp(C);

% Power Factor is the same regardless of topology
disp('*****Power Factor Calculation*****');
pf = cosd(theta);
D = ['Power Factor = ', num2str(pf)];
disp(D);

disp('*****Component Calculation*****')
omega = 2*pi*frequency;

% Fix: Use sp_choice for topology routing, not choice!
if any(sp_choice==1) % Series calculation
    if any(Z_imag < 0) % Configured as a capacitor
        C_val = -1 / (Z_imag * omega); % Fix: Added negative sign to prevent negative capacitance
        E = ['C = ', num2str(C_val), ' F'];
        disp(E);
    else % Configured as an inductor
        L_value = Z_imag / omega;
        F = ['L = ', num2str(L_value), ' H'];
        disp(F);
    end
    fprintf("==============================================\n");
    
elseif any(sp_choice==2) % Parallel calculation
    % For parallel, it's easier to use Admittance (Y = 1/Z = G + jB)
    Y = 1 / Z; 
    B_susceptance = imag(Y); % Imaginary part of Admittance
    
    if any(B_susceptance > 0) % Capacitive susceptance is positive
        C_val = B_susceptance / omega;
        G_str = ['C = ', num2str(C_val), ' F'];
        disp(G_str)
    else % Inductive susceptance is negative
        L_val = -1 / (B_susceptance * omega); % Fix: Added negative sign to prevent negative inductance
        P = ['L = ', num2str(L_val), ' H'];
        disp(P)
    end
    fprintf("==============================================\n");
end
%{
   Okay so now for real life measuring....this will entail using the Rhode
   &Schwarz RTM3004 10-bit ADC oscilliscope which can prove to be a little
   tricky if unfamiliar with the options provided to you. Maybe not as
   simple as the LTSPICE measurements but we can somewhat approach to this
   sentiment
   *********Voltage Measurements*********
To get voltage measurements we need an example circuit....say we got this:
A Black box{1k+0.47uF series} in series with a Shunt Resistor{1k}
in this order of the circuit
+Vsource--->Node A--+Shunt--->Node B-->+Black Box--->Node C--Vsource-gnd
in ltspice you could do Node A across shunt to Node B to measure
measurement of the shunt resistor but this is not possible with the
oscilliscope since it internally{despite have multiple channels} has all
channels to same ground.
So to measure V_Shunt and V_Black_Box you would obviously need two channels
but....
    --Channel 1 Probe placed at Node A, ref to common gnd Node C{Gives Vsource}
    --Channel 2 Probe placed at Node B, ref to commin gnd Node C{gives V_Black_Box}
Then on the Math channel conduct the Math operation CH1-CH2 and effectively
it gives you the waveform of the measure shunt!

Now as for the phase delay there multiple things we can do but for now i
will mention two!
Method 1: Manual Cursors
Cursor option "Set to Trace"....hopefully displays the cursor Voltage(Y)
and time(X) at the point you show it to!{just move the cursor around to 
desired peak!}

Method 2: Phase Delay Calculation!
Go to the Measure Menu: press the Meas Button 
Select Measurement type-->Time Category-->Phase
Assign your sources and voila 
Displays data

You choose!



%}