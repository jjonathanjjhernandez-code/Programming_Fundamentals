%{
We will use MATLAB simulation to see the response of our filter circuits.
For simulation, you will need the transfer functions of both filter
circuits. In both filters, R = 1.6k and C = 0.01uF. For the second filter
R1 = 10k, R2 = 12k, R3 = 10k, R4 = 1.5k, and C = 0.01uF. With the above
values for resistors and capacitors, the transfer functions will have the
folling form.......
    1st Filter:
                1
        H1 = ----------
              1+(RCs

    2nd Filter
                                2.2*1.15
        H2 = -------------------------------------------------
            (RC)^4*s^4 + 2.65(RC)^3s^3 + 3.48(RC)^2s^2 + 2.65RCs + 1
Construct a frequency array as follows....
w = [0:100:10000]

Construct the coefficient vectors as follows
b = [coefficients of numerator separated by comma]
a = [coefficients of denominator separated by comma

Use the MATLAB 'freqs' function to generate a frequnecy response of the
corresponding filter.
Plot the frequency response of both filters on a single graph using the
MATLAB function
Apply the above procedure for  both filters.
Note the frequency response you obtained from the MATLAB simulation that is
gain versus angular frequency in radian. You can also plot the gain vs Hz.
In that csase, you use f = omega/[2*pi]
%}

w=[0:5000:150000];%  this will be the frequnecy array
y=[0:0.5:3.5];
coeff_eq_numerator_one = [1];%for filter number one
coeff_eq_numerator_two = [2.53];%for filter number two
coeff_eq_denominator_one = [.000016 1];%for filter number one
coeff_eq_denominator_two = [6.5536*10^-20 1.08544*10^-14 8.9088*10^-10 4.24*10^-5 1];%for filter number two


%this returns the complex frequency response of the analog filter specified by the coefficient vectors b and a, evaluated at the angular frequencies w
h = freqs(coeff_eq_numerator_one,coeff_eq_denominator_one,w);
h_two = freqs(coeff_eq_numerator_two,coeff_eq_denominator_two,w);
magnitude_eq_one = abs(h);
magnitude_eq_two = abs(h_two);

%can't really use the plot() function since all of the vectors are off
figure;
loglog(w,magnitude_eq_one);
xlabel("Frequency (rad/s)");
ylabel("Magnitude");
hold on
loglog(w,magnitude_eq_two);
legend('1st Order','4th Order');