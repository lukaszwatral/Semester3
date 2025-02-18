clc
close all
clear all


[x,y]=meshgrid([-10:0.5:10],[-10:0.5:10]);

f = @(x,y) x.^2 + y.^2

w = f(x,y);

figure
%plot3(x,y,w,'r.')
%hold on
surf(x, y, w)
colormap("hot")