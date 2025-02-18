%bd
clc
clear all
close all
% f = @(x) cos(x); %<0, 2>
% f = @(x) 2.^-x + exp(x) + 2*cos(x) -6 %<1, 3>
% f = @(x) (x+2).^5 %<-3, 0>
% f = @(x) exp(x-1)-2 %<-1, 2>
% f = @(x) log(x+2/3) %<-0.5, 2>
%f = @(x) x.^3-2*x-5 %<0, 3>
% %f = @(x) sin(x);
% regula(@(x) cos(x), 0, 2, 10^-5, 10^-4)
% regula(@(x) 2.^-x + exp(x) + 2*cos(x) -6, 1, 3, 10^-5,10^-4)
%regula(@(x) (x+2).^5, -3, 0, 10^-5,10^-4)
% regula(@(x) exp(x-1)-2, -1, 2, 10^-5,10^-4)
% regula(@(x) log(x+2/3), -0.5, 2, 10^-5,10^-4)
% regula(@(x) x.^3-2*x-5, 0, 3, 10^-5,10^-4)
% newton(@(x) cos(x), 0, 2, 10^-5, 10^-4)
%newton(@(x) 2.^-x + exp(x) + 2*cos(x) -6, 1, 3, 10^-5,10^-4)
% newton(@(x) (x+2).^5, -3, 0, 10^-5,10^-4)
% newton(@(x) exp(x-1)-2, -1, 2, 10^-5,10^-4)
% newton(@(x) log(x+2/3), -0.5, 2, 10^-5,10^-4)
% newton(@(x) x.^3-2*x-5, 0, 3, 10^-5,10^-4)

% a=-1;
% b=1;
% tol = 10^-5;
% ftol = 10^-4;
% f = @(x) exp(x)+2*x;
% 
% format("default")
% x_r = regula(f, a, b, tol, ftol);
% x_n = newton(f, a, b, tol, ftol);
% x = a:tol:b;
%     hold on
%     plot(x, f(x))
%     plot(x_r,f(x_r),'g*')
%     plot(x_n,f(x_n),'r*')
%     title('e^x+2x')
%     legend('Funkcja', "Metoda regula falsi", "Metoda Newtona(stycznych)", 'Location', 'NorthWest')
%     hold off

a=-2;
b=2;
tol = 10^-5;
ftol = 10^-4;
f = @(x) x.^3-2*x.^2+4

x_r = regula(f, a, b, tol, ftol);
x_n = newton(f, a, b, tol, ftol);
x = a:tol:b;
    hold on
    plot(x, f(x))
    plot(x_r,f(x_r),'g*')
    plot(x_n,f(x_n),'r*')
    title('x^3-2x^2+4')
    legend('Funkcja', "Metoda regula falsi", "Metoda Newtona(stycznych)", 'Location', 'NorthWest')
    hold off