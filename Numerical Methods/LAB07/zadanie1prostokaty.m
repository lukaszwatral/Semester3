clc
clear all
close all

X = [5, 10, 20, 30, 40, 50, 65, 70, 80, 85, 90, 100, 110, 120, 130, 135, 140, 150, 153, 155, 160, 165];
Y = [0, 7, 16, 23, 27, 29, 30, 37, 44, 45, 30, 20, 13, 9, 6, 5, 6, 12, 20, 25, 18, 0];
x = [5, 10, 20, 30, 40, 45, 50, 60, 70, 80, 90, 100, 110, 120, 130, 135, 140, 150, 155, 160, 165];
y = [0, -6, -12, -16, -29, -30, -23, -21, -22, -21, -20, -19, -15, -12, -8, -5, -6, -10, -20, -12, 0];
Hq = 5:1:165;

h = 1;
p1 = 0;
p2 = 0;
for i=5:h:165-h
    line([i, i+h], [interp1(X, Y, i+h/2, "makima"), interp1(X, Y, i+h/2, "makima")])
    line([i, i+h], [interp1(x, y, i+h/2, "makima"), interp1(x, y, i+h/2, "makima")])
    line([i, i], [0, interp1(X, Y, i+h/2, "makima")])
    line([i, i], [0, interp1(x, y, i+h/2, "makima")])
    line([i+h, i+h], [0, interp1(X, Y, i+h/2, "makima")])
    line([i+h, i+h], [0, interp1(x, y, i+h/2, "makima")])
    line([5, 165], [0, 0])
    if(i<165)
    p1 = p1 + interp1(X, Y, i+h/2, "makima");
    p2 = p2 + abs(interp1(x, y, i+h/2, "makima"));
    end
end
pole = p1*h + p2*h;
hold on
Vq = interp1(X, Y, Hq, "makima");
plot(X, Y, 'ob', Hq, Vq, 'b');
Vq = interp1(x, y, Hq, "makima");
plot(x, y, 'ob', Hq, Vq, 'b')
hold off
titleString = sprintf('Metoda prostokątów z krokiem 10, wynik = %d', pole);
title(titleString)