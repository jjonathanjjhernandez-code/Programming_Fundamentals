%need to make me a calculator that that does the bode plot!
%say you got the equation....
%       S^2 + 0.1s + 7.5
%H(S) = -----------------
%       s^4+0.12s^3+9s^2
%
%thus you can make the input as such....
%H = tf([1 0.1 7.5], [1 0.12 9 00 ])
%bode (H)
H = tf([-1], [1 1]);
bode(H);