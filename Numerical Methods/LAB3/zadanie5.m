clc
clear all
close all

x = [exp(1), -pi, sqrt(2), -psi(1), log10(2)]
y = [1486.2497, 878366.9879, -22.37492, 4773714.647, 0.000185049]

w1 = x*y'
w2 = sum(x.*y)
w3 = 0;
for i = 1:5
    w3 = w3+x(i)*y(i);
end
w3
w4 = 0;
for i = 5:-1:1
    w4 = w4+x(i)*y(i);
end
w4
w5=0;
for i = 2:2:5
    w5 = w5+x(i)*y(i);
end
for i = 1:2:5
    w5 = w5+x(i)*y(i);
end
w5

t = categorical({'w2', 'w3', 'w4', 'w5'});
b = [abs(w2-w1), abs(w3-w1), abs(w4-w1), abs(w5-w1)]
bar(t, b)
title('Wykres słupkowy błędu')