%write a script that:
%starts with x = 50
%subtracts 7 in each iteration
%stops when x<=5 using a while loop
fprintf('go to count down from 50 subtracting by 7!\n');
x = 50;
while (x>5)
    fprintf('helo here is your number: %d\n',x);
    x =x-7;
end