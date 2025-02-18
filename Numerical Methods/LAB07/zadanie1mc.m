clc
clear all
close all

X = [5, 10, 20, 30, 40, 50, 65, 70, 80, 85, 90, 100, 110, 120, 130, 135, 140, 150, 153, 155, 160, 165];
Y = [0, 7, 16, 23, 27, 29, 30, 37, 44, 45, 30, 20, 13, 9, 6, 5, 6, 12, 20, 25, 18, 0];
x = [5, 10, 20, 30, 40, 45, 50, 60, 70, 80, 90, 100, 110, 120, 130, 135, 140, 150, 155, 160, 165];
y = [0, -6, -12, -16, -29, -30, -23, -21, -22, -21, -20, -19, -15, -12, -8, -5, -6, -10, -20, -12, 0];
Hq = 5:1:165;


hold on
Vq = interp1(X, Y, Hq, "makima");
plot(X, Y, 'ob', Hq, Vq, 'b');
Vq = interp1(x, y, Hq, "makima");
plot(x, y, 'ob', Hq, Vq, 'b')


line([5, 5], [min(interp1(x, y, Hq, "makima")), max(interp1(X, Y, Hq, "makima"))])
line([165, 165], [min(interp1(x, y, Hq, "makima")), max(interp1(X, Y, Hq, "makima"))])
line([5, 165], [min(interp1(x, y, Hq, "makima")), min(interp1(x, y, Hq, "makima"))])
line([5, 165], [max(interp1(X, Y, Hq, "makima")), max(interp1(X, Y, Hq, "makima"))])
% line([5, 165], [0, 0])

n=500;
hit=0;
for i=1:n/2
x0 = 5+rand()*160;
y0 = rand()*min(interp1(x, y, Hq, "makima"));
if(y0<interp1(x, y, x0))
plot(x0, y0, 'r.')
else
plot(x0, y0, 'g.')
hit=hit+1;
end

x0 = 5+rand()*160;
y0 = rand()*max(interp1(X, Y, Hq, "makima"));
if(y0>interp1(X, Y, x0))
plot(x0, y0, 'r.')
else
plot(x0, y0, 'g.')  
hit = hit+1;
end
end
hold off
pole = (165-5)*(max(interp1(X, Y, Hq, "makima"))-min(interp1(x, y, Hq, "makima")));
calka = (hit/n)*pole
titleString = sprintf('Metoda Monte Carlo z liczbą strzałów 500, wynik = %d', calka);
title(titleString)