%need a calculator to do the impedance calculation for me!
%this is it!
% Recall from the relationship
%Z = V_Z/I
%I = V_R/R
%Assuming both the known resistor and the black box impedance are in series
i = (1.0170663)/(2000);
t = 360*(((10.858469*10^-3)-(13.364269*10^-3))/(.01));
z_mag = (1.7219894)/(i);
test = (90*.01745329);
r = z_mag*cos(t*(.01745329));
X = ['helo',num2str(r)];
%disp(X);
imag = z_mag*sin(t*(.01745329));
z = r + 1i * imag; % Combine real and imaginary parts to form the complex impedance
afreq = 2*pi*100;
C = 1/(imag*afreq);

disp('helo am here to calculate your impedance value!');
sp_choice = input('Black Box Inside: 1.Series 2.Parallel == ');
if any(sp_choice==1)
    disp('*****Series Calculation*****');
else 
    disp('Parallel Calculation');
end
V_R = input('V_R = ');
V_Z = input('V_Z = ');
i_r = V_R/input('R = ');
A = ['i_r = ', num2str(i_r)];
disp(A);
choice = input('1. delta t 2.measured times = ');
if any(choice==1)
 theta  = 360 * (input('Delta t = ')/(1/input('frequency = ')));
else 
 theta = 360 * ((input('Vmag Time at R = ') - (input('Vmag Time at Z = ')))/(1/input('frequency = ')));
end
B = ['theta = ',num2str(theta)];
disp(B);
disp('going to display the impedance value now!')
ZMAG = V_Z/i_r;
real = ZMAG*cos(theta*.01745329);
imaginary = ZMAG*sin(theta*.01745329);
Z = real + 1j * imaginary;
C = ['Z_MAG = ',num2str(ZMAG)];
disp(C);
D = ['Z = ',num2str(Z)];
disp(D);
user_input_choice = input('1.Black Box 2.Regular Series = ');
if any(user_input_choice==2)
    if any(imaginary<0)
        disp('Our impedance reflects a capacitor');
        omegac = 2*pi*(input('frequency = '));
        Cap= (1/(omegac*abs(imaginary)));
        E = ['C = ',num2str(Cap),'F'];
        disp(E);
    else
        disp('Our impedance reflects an inductor')
        omegal = 2*pi*(input('frequency = '));
        L = (imaginary/omegal);
        F = ['L = ', num2str(L),'H'];
        disp(F);
    end
else
    disp('hehe');
end
disp('now to display the power factor of the system!')
%real_power = V_Z*i_r*cos(theta*.01745329);
%reactive_power = (V_Z*i_r)*sin(theta*.01745329);
%G = ['Real Power = ',num2str(real_power),'\nReactive Powere = ',num2str(reactive_power)];
%apparent_power =  sqrt(abs(real_power^2)+(abs(reactive_power^2)));
power_factor = cos(theta*.01745329);
H = ['Power factor = ', num2str(power_factor)];
disp(H);
fprintf("\n\n\n");