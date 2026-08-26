%ONE MOE SCRIPT BAIBY!
syms v_phi vo s
equation_one = (v_phi-(600/s))/10  + v_phi/(10/s) + (v_phi-vo)/(20*s)==0;
equation_two = (vo-v_phi)/(20*s) + vo/140 == -.25*v_phi;
solution = solve([equation_one,equation_two],[v_phi,vo]);
v_phi = solution.v_phi;
vo = solution.vo;
fprintf('Vo = \n');
pretty(simplify(vo));
%going to print this in time domain!
i_vo = ilaplace(vo);
fprintf('Vo(t) = \n');
pretty(simplify(i_vo));