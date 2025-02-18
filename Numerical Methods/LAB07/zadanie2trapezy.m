clc
clear all
close all
f = @(x) sin(x);
x = linspace(-pi, pi, 100);
line([-pi, pi], [1, 1])
line([-pi, pi], [-1, -1])
line([-pi, -pi], [-1, 1])
line([pi, pi], [-1, 1])
line([-pi, pi], [0, 0])
hold on
plot(x, f(x), 'r')
hold off
a = -pi;
b = pi;
n = length(x);
h = 2*pi/n;
calka = 0.5*(abs(f(a))+f(b));
for i=1:n-1
    line([a+(i-1)*h, a+i*h], [f(a+(i-1)*h), f(a+i*h)])
    line([a+i*h, a+i*h], [0, f(a+i*h)])
    calka = calka + abs(f(a+i*h));
end
line([a+(n-1)*h, a+n*h], [f(a+(n-1)*h), f(a+n*h)])
calka = h*calka
titleString = sprintf('Metoda trapezów z krokiem h = %d, wynik = %d', 2*pi/n,calka);
title(titleString)

%Im mniejsza wartość kroku, tym wynik jest dokładniejszy, tzn. im więcej
%trapezów utworzymy, tym wynik będzie dokładniejszy