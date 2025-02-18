clc
close all
clear all

%i=1:n; -5.12<=x(i)<=5.12

%f = @()
[x, y] = meshgrid[-5:1:5], [-5:1:5]
[n] = x
i = 1:n
f = @(x,y) 10.*n+sum(x(i)^2-10.*cos(2.*pi.*x(i))