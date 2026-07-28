%dummy equation solver
syms v1 vo s i1 i2
impedance_one = ((50+(.2*s)+4244482.173/s)*3000)/((50+(.2*s)+4244482.173/s)+3000);
transfer_function = (4000)/(impedance_one + 500 + 2000)==0;
solution = solve([equation_one,equation_two],[v1,vo]);
vo_vi = solution.vo;
fprintf('=============================\nV1 = \n\n')
pretty(simplify(impedance_one));
fprintf('\n\n=============================\n\n');

fprintf('=============================\nVo/vi = \n\n');
%transer_mag = v11*(2000/(50+2000));
pretty(vo_vi);
fprintf('\n\n=============================\n\n');
