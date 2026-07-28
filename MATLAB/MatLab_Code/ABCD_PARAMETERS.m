syms s
one = [1 1; 0 1];
two = [1 s; 0 1];
three = [1 0; s 1];
four  = [1 s; 0 1];
five = [1 0; s+1 1];
ABCD = one*two*three*four*five;
disp(simplify(ABCD));