%Define x and y data points
x = [1 3 5 7 9];
y = [2 4 5 6 10];
%Compute linear regression coefficients
%p(1) = slope, p(2) = intercept
p = polyfit(x,y,1);

%Evaluate the fitted line at x values
Y = polyval(p,x);

%Plot original data points
plot(x,y,'o','MarkerSize',8,'LineWidth',2)
%Keep current figure for next plot
hold on
%Plot regression line
plot(x,Y,'LineWidth',2)
%Add grid
grid on
%Label axes
xlabel('x')
ylabel('y')
%Add title
title('Linear Regression')
%Add Legend
legend('Data','Best-Fit Line')