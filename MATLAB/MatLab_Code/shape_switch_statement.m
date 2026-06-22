%write a script that asks the user to enter a shape name and then use a
%switch structure to display a short description of that shape
fprintf('when prompted type out one of the following choices!\ncircle\nsquare\ntriangle\nrectangle\notherwise\n');
shape  = lower(input('Shape: ', 's'));
switch shape
    case 'circle'
        fprintf('A circle has infinite symmetry and is defined by its radius.\n');
    case 'square'
        fprintf('A square has 4 equal sides and 4 right angles.\n');
    case 'triangle'
        fprintf('A triangle has 3 sides and its angles sum to 180 degrees.\n');
    case 'rectangle'
        fprintf('A rectangle has 4 sides with opposite sides equal.\n');
    otherwise
        fprintf('Unknown shape.\n');
end