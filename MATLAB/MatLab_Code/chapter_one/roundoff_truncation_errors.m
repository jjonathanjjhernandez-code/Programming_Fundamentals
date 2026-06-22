%{
==**Introduction**==
The primary objective of this chapter is to acquaint you with the major
sources of erros involved in numerical methods..
==========================================================
         ==**Errors & Accuracy and Precesion**==
==========================================================
Engineers and scientists constantly find themselves having to accomplish
objectives based on uncertain information. Too many factors are at play
whenever we encounter real interactions of the world, causing us to guess
or to approximate expected behaviors. Because of those predictions we
inherently have deviations from the actual measurements we expect to see.
If these deviations are systematically high or low, then we might need to
develop a new model.
BUT, if they are randomly distributed and tightly grouped around the
expected prediction values, then the deviations might be considerded
negligible and the model deemed adequate. We will cover topics related ton
the identification, quantification, and minimization of these errors.

Now errors can be characterized based on two words: accuracy and precesion
Accuracy: refers to how CLOSELY a computed or measured agrees with the true
value.
Precision: refers to how closely individual computed or measured values
agree with each other.

Inaccuracy(also called bias) is defined as systematic deviation from the
truth.

Imprecesion(also called uncertainty) referers to the magnitude of the
scatter.
{To better understand these concepts search up accuracy vs precision target
practice!}
Either way numerical methods should be sufficiently accurate or unbiased to
meet the requirements of a problem. They should also be precise enough for
adequate design.
==========================================================
                ==**Error Definitions**==
==========================================================
Numerical erros arise from the use of approximations to represent exact
mathematical operations and quantaties.
Where....
True value = approximation + error
then to account for magnitudes of the quantaties being used, we can
normalize the error to the true value
True fractional relative error(epsilon t) = 
(true value - approximation)/(true value) <--- this is based on relativity
of whatever you are measuring!

But there is a problem....true values are usually never provided ESPECIALLY
if you are simulating!
So we can do...
Epsilon(error is normalized to approximate value) = 
(approximate error)/(approximation measurement)

In iteration cases...
Epsilon = (present approximation - previous approximation)/(present approx.)

Ex) In mathematics, functions can often be represented by infinite
series.
For example, the exponential function can be computed using
e^x = 1+x+(X^2)/2 + (x^3)/3! + ....+(x^n)/(n!)
thus as more terms are added in sequence the better the approximation for
the true value of e^x.

It is also convenient to relate these errors to the number of significant
figures in the approximation....using this principle.....
epsilon s = (.5*10^(2-n))% <---where n represents the # of sig. figs.
==========================================================
  ==**Computer Algorithm for Iterative Calculations**==
==========================================================
{NoTe: target errors simply are just references for your approximation 
values...recall statistics!}

function [estimated_value, approx_rel_error, iterations] = calculate_exponential(x, target_error, max_iterations)
    % Calculates the Maclaurin series of the exponential function e^x
    
    % --- Apply Default Values ---
    % If target_error is not provided or is empty, default to 0.0001%
    if nargin < 2 || isempty(target_error)
        target_error = 0.0001;
    end
    
    % If max_iterations is not provided or is empty, default to 50 loops
    if nargin < 3 || isempty(max_iterations)
        max_iterations = 50;
    end
    
    % --- Initialization ---
    iterations = 1; 
    current_estimate = 1;        % First term of the Maclaurin series
    approx_rel_error = 100;      % Start with 100% error
    
    % --- Iterative Calculation ---
    while true % 'true' is cleaner than '1' for infinite loops
        
        previous_estimate = current_estimate;
        
        % Add the next term of the series: (x^n) / n!
        current_estimate = current_estimate + (x ^ iterations) / factorial(iterations);
        
        iterations = iterations + 1;
        
        % Calculate the approximate relative error (if estimate isn't zero)
        if current_estimate ~= 0
            approx_rel_error = abs((current_estimate - previous_estimate) / current_estimate) * 100;
        end
        
        % Check stopping criteria: target error reached OR max iterations hit
        if approx_rel_error <= target_error || iterations >= max_iterations
            break;
        end
        
    end
    
    % --- Final Output Assignment ---
    estimated_value = current_estimate;
    
end
%}
