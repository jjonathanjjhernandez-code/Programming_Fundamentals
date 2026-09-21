%This the part from 3kHz to 4kHz
answer_ls = integral(@lastpart_function,3000,4000);
X=['From 3kHz to 4kHz: ' num2str(answer_ls)];
disp(X);
%This is the part from....should yield something like 21933.01091 b/s
answer_ls = integral(@secondpart_function,3000,4000);
X=['From 300Hz to 1kHz: ' num2str(answer_ls)];
disp(X);
