function [sum,difference, product, quotient] = calc_func(firstInput,secondInput)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
arguments (Input)
    firstInput
    secondInput
end

arguments (Output)
    sum
    difference
    product
    quotient
end

sum = firstInput + secondInput;
difference = firstInput - secondInput;
product = firstInput * secondInput;
quotient = firstInput / secondInput;

end