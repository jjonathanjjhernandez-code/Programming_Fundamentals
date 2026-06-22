%{
Cool, here I am in the script file for the MATLAB code...not bad for an IDE
completely forgot how this thing looked like....
===========================================================
            ==**Matrices and Arrays**==
===========================================================
The whole schmidt of MATLAB apparently is because it is a tool mainly made
for matrix operations....which is pretty neat!
Everything in MATLAB is an array or a matrix. You can create them in the
command window or in a script

===========================================================
            ==***Array Creation***==
===========================================================
 
    NOTE:the two dashes indicate terminal use...best practice is to use
    sequential steps like this script!

(1-Dimenstional Matrix)
>> a = [1 2 3 4]
 a = 1×4
      1     2     3     4    (layout of the matrix)
(2-Dimensional Matrix) 
>>a = [1 3 5; 2 4 6; 7 8 10]
 a = 3×3

      1     3     5
      2     4     6
      7     8    10  (layout of the matrix)


===========================================================
         ==***Simple Matrix Operations***==
===========================================================
>> a = [1 3 5; 2 4 6; 7 8 10] 
>>a + 10 (where 'a' is a matrix of your choice)
 ans = 3×3

     11    13    15
     12    14    16
     17    18    20

---------------------------------------------------------------------------
grabs all the elements individually and does element operation sin(a)
>>sin(a)
 ans = 3×3

     0.8415    0.1411   -0.9589
     0.9093   -0.7568   -0.2794
     0.6570    0.9894   -0.5440
---------------------------------------------------------------------------
 >>a (transpose of a matrix) <---transpose_of_a = a';
 Matrix a before Transpose:
      1     3     5
      2     4     6
      7     8    10
 Transpose of matrix a:
 ans = 3×3
      1     2     7
      3     4     8
      5     6    10
---------------------------------------------------------------------------
 There will be more operations to come but you are better off using this 
website https://www.mathworks.com/campaigns/offers/matlab-basic-functions-
reference-cheat-sheet.html!
 Now as for writing script files for these operations and any other that you
 may need....well that requires more documnetation BUT here is an example
 provided by MATLAB(super duper simple)
 sphere = [x , y , z];
 r=1;
 A = 4*pi*r^2;
 V = (4/3)*pi*r^3;

 fprintf("The area of the sphere is %d.\n", A);
 fprintf("The volume of the sphere is %d.\n", V)
 (Which to be fair looks a LOT like C code....)

==========================================================
          ==***Array Indexing***==
==========================================================
 A = [1 2 3 4; 5 6 7 8; 9 10 11 12; 13 14 15 16]
      1     2     3     4
      5     6     7     8
      9    10    11    12
     13    14    15    16
 >>A(4<---row,2<---column)  = 14
 you can set variables to specific indices of the arrays...

 >>A(1:3,2) <---in rows 1-3 print the 2nd column
      2
      6
     10
 >>A(3,:) <---print all of the columns in row 3
      9    10    11    12

============================================================
          ==***Workspace Variables***==
============================================================
 Now funny enough all of the variables we instantiated are popping up in the
 "workspace". The workspace contains variables that you create within or
 import into MATLAB from data files or other programs. For example, these
 statements create variables D and E in the workspace
 D = magic(4);
 B = rand(3,5,2);
 You can view the contents of the workspace using whos
 (with the clear command you can eliminate all variables in the workspace if memory is needed)
 Now Workspace variables DO NOT presist after you exit MATLAB. You can save
 your data for later use with the 'save' command,
 save myfile.mat
 Saving preserves the workspace in your CURRENT working folder in a
 compressed file with a .mat extension, called a MAT-file.
 Restoring data from a MAT-file into the workspace use load
 load myfile.mat
Here are some commands to be aware of....
    --whos: lists all current variables in the workspace and their sizes
    --clear: wipes all variables from memory(good practice to place this
 at the very top script)
    --clc: clears the visual text in the command window
    --save myfile.mat: saves the current workspace variables into
    compressed MAT-file in your working directory
    --load myfile.mat: Restores those variables into memory

============================================================
            ==***Text and Characters***==
============================================================
 You are even allowed a characters and arrays of letters 
 t = "Hello, World!";
 or
 q = "Something ""quoted"" and something else."
 or even
 f= 71;
 c = (f-32)/1.8;
 tempText  = "Temperature is " + c + "C";
 tempText = 
 "Temperature is 21.6667C"

 Not only that we can have an array of strings...
 A = ["a", "bb", "ccc", "dddd", "eeeeee", "fffffff"]
 A = 
      "a"       "bb"      "ccc"
      "dddd"    "eeeeee"   "fffffff"
 strlength(A)
    ans = 
      1    2    3
 
     4    6    7
============================================================
            ==***Calling Function***==
============================================================
 just like in C or C++ just call the function???
 basically the same thing....
 exampe: you defined a function named max(takes one parameter)
 A = [1 3 5]
 max(A)
 ans = 
 5
 For multiple outputs....
 [minA, maxA] = bounds(A)
 minA = 
 1
 maxA = 
 5
 For functions that take inputs of text...
 disp("hello world")
 and of course a simple void function that takes no inputs
 name_of_function

 )Example of a simple script calling built-in functions
 sphere = [x,y,z];
 r=1;
 Area = 4*pi*r^2;
 Volume = (4/3)*pi*r^3;
 fprintf("The area of the sphere is %f.\n", Area);
============================================================
            ==***2-D and 3-D Plots***==
============================================================
To create two-dimensional line plots, we use the plot function.
For example, plotting the sine function over a lineraly spaced vector of values from 0 to 2pi:
x = linespace(0,2*pi);
y = sin(x);
plot(x,y)<--- a third argument like "r--" means a red dashed line
For those type of specifications they are called line specification. Each specification can include characters for the line, color, style, and marker.
A marker is a symbol that appears at each plotted data point, such as a +, o, or *.
For example, "g:*" requests a dotted green line with * markers.

Labeling the axes is as such...
xlabel("x-axis")
ylabel("sin(x)--y-axis")
title ("Plot of the Sine function")

This is where most of the magic happens...
linespace generates evenly spaced points between 0 and 2*pi
>> x = linespace(0,2*pi);
>> y = sin(x);

r--* is a line specficiation: Red color, dashed line, asterik markers
>> plot(x,y, 'r--*');

>> xlabel("Time(s)");
>> ylabel("Amplitude");
>> title("Plot of the Sine function!");
>> grid on; <---adds grid on the background of the plot graph

plotting a 3d trajectory(e.g, ...a spatial path)
>> z_path = 0:0.1:10;
>> x_path = sin(z_path);
>> y_path = cos(z_path);
>> plot3(x_path,y_path_z_path, 'b-o');
>> title('3D Trajectory Mapping');
%}