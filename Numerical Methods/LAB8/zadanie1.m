%bed

clc
clear all
close all
% f=@(x) x.^2-2;
% a = 1/4;
% b = 3/4;
% tol = 10^-5;
% x = linspace(a, b, 100);
% newton(f, a, b, tol)
% % 
% 
f=@(x) (1/3)*x.^2-(13/7)*x+11;
a = -10;
b = 10;
tol = 10^-5;
newton(f, a, b, tol)

% f=@(x) x.^4-12*x.^3+x+4;
% a = -2;
% b = 2;
% tol = 10^-5;
% newton(f, a, b, tol)

% f=@(x) -x.^3+3*x.^2-3*x;
% a = -2;
% b = 10;
% tol = 10^-5;
% davidon(f, a, b, tol)

% f=@(x)5*x.^2-12.*x-3;
% a = 0;
% b = 2;
% tol = 10^-5;
% zloty_podzial(f, a, b, tol);

