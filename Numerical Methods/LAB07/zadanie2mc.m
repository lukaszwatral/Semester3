clc
clear all
close all
f = @(x) sin(x);
x = linspace(-pi, pi, 1000);
line([-pi, pi], [1, 1])
line([-pi, pi], [-1, -1])
line([-pi, -pi], [-1, 1])
line([pi, pi], [-1, 1])
line([-pi, pi], [0, 0])
n = 10000;
hit=0;
hold on
plot(x, f(x), 'b')
for i=1:n/4
x0 = rand()*pi;
y0 = rand()*1;
if(y0>f(x0) || y0<0)
plot(x0, y0, 'r.')
else
plot(x0, y0, 'g.')
hit=hit+1;
end
x0 = rand()*pi;
y0 = rand()*(-1);
if(y0>f(x0) || y0<0)
plot(x0, y0, 'r.')
else
plot(x0, y0, 'g.')
hit=hit+1;
end
x0 = rand()*(-pi);
y0 = rand()*1;
if(y0<f(x0) || y0>0)
plot(x0, y0, 'r.')
else
plot(x0, y0, 'g.')
hit=hit+1;
end
x0 = rand()*(-pi);
y0 = rand()*(-1);
if(y0<f(x0) || y0>0)
plot(x0, y0, 'r.')
else
plot(x0, y0, 'g.')
hit=hit+1;
end
end
hold off
pole = (2*pi*2);
calka = (hit/n)*pole
titleString = sprintf('Metoda Monte Carlo z liczbą strzałów 10000, wynik = %d', calka);
title(titleString)

%Zwiększenie liczby strzałów nie zawsze wpływa pozytywnie na dokładność
%wyniku, ze względu na pseudolosowość liczb wynik może wyjść raz
%dokładniejszy, a kolejnym razem mniej