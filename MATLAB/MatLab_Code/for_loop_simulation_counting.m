%write a script that: 
%prompts the user for n
%computes the sum from 1 to n
%prints the updated total at every iteration
fprintf('when prompted to please input an integer!\n');
n = input('input integer here: ');
sum = 0;
for i = 1:1:n
    fprintf('helo here is current total: %d\n', sum+i);
end