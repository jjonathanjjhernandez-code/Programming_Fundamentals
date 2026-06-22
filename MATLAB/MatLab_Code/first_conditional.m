%write a script that asks the user for a number x, then prints:
%whatever it needs to print based on some conditions....
fprintf("When prompted to place any number from negative infinity to infinity!\n");
x =input('Input for variable x: ');
if (x<0)
    fprintf('Negative\n');
elseif x < 10
    fprintf('small\n');
elseif x < 100
    fprintf('medium\n');
else
    fprintf('large\n');
end