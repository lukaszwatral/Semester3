clc
clear all
close all
x = linspace(-1, 1, 3)
x = x';
n = length(x);
A = zeros(n);
for i=1:n
    A(:, i) = x.^(i-1);
end
f = @(x) 1./(25*x.^2+1);
y = f(x);

a = flip(inv(A)*f(x));
%b = inv(vander(x))*f(x)

subplot(2, 2, 1)
hold on
plot(x, y, 'r', Marker='o', MarkerEdgeColor='b')
plot(x, Horner(a, 3, x), 'g', Marker='o', MarkerEdgeColor='k')
title('Mała liczba węzłów(3)')
hold off

x = linspace(-1, 1, 15)
x = x';
n = length(x);
A = zeros(n);
for i=1:n
    A(:, i) = x.^(i-1);
end
f = @(x) 1./(25*x.^2+1);
y = f(x);

a = flip(inv(A)*f(x));

subplot(2, 2, 2)
hold on
plot(x, y, 'r', Marker='o', MarkerEdgeColor='b')
plot(x, Horner(a, 15, x), 'g', Marker='o', MarkerEdgeColor='k')
title('Średnia liczba węzłów(15)')
hold off

x = linspace(-1, 1, 35)
x = x';
n = length(x);
A = zeros(n);
for i=1:n
    A(:, i) = x.^(i-1);
end
f = @(x) 1./(25*x.^2+1);
y = f(x);

a = flip(inv(A)*f(x));

subplot(2, 2, 3)
hold on
plot(x, y, 'r', Marker='o', MarkerEdgeColor='b')
plot(x, Horner(a, 35, x), 'g', Marker='o', MarkerEdgeColor='k')
title('Duża liczba węzłów(35)')
hold off

x = linspace(-1, 1, 47)
x = x';
n = length(x);
A = zeros(n);
for i=1:n
    A(:, i) = x.^(i-1);
end
f = @(x) 1./(25*x.^2+1);
y = f(x);

a = flip(inv(A)*f(x));

subplot(2, 2, 4)
hold on
plot(x, y, 'r', Marker='o', MarkerEdgeColor='b')
plot(x, Horner(a, 47, x), 'g', Marker='o', MarkerEdgeColor='k')
title('Bardzo duża liczba węzłów(47)')
hold off
