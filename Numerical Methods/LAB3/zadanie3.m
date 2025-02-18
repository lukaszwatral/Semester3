clc
clear all
close all
d = 10^(-3)
format('longE')

x = linspace(2-d, 2+d, 1000)
a = (x-2)

f1 = @(x) a.^4
%f2 = @(x) x.*x.*x.*x-x.*x.*x+x.*x-x+16
f2 = @(x) x.^4 - 8*x.^3 + 24*x.^2 - 32.*x + 16
t = max(abs(f1(x)-f2(x)))

hold on
plot(x, f1(x), 'k')
plot(x, f2(x), 'y')
title(t)

figure
plot(x, f1(x), 'y')
plot(x, f2(x), 'b')
axis([1.9998, 2.0002, -0.025*10e-13, 0.025*10e-13])
title('Wycinek wykresu')

figure
plot(x, f1(x)-f2(x))
title('Wykres błędu')