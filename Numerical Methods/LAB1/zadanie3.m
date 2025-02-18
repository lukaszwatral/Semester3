clc
close all
clear all

[x,y]=meshgrid([-10:0.5:10],[-10:0.5:10]);

f = @(x,y) x.^2 + y.^2

w = f(x,y);
subplot(2,2,1)
plot3(x,y,w, '.b')
subplot(2,2,2)
mesh(x,y,w)
subplot(2,2,3)
surf(x,y,w)
subplot(2,2,4)
surfl(x,y,w)