clc
close all
clear all


x = 1:0.1:10;
y = sin(x);
z = cos(x);

hold on
plot(x, y, ':pr')
plot(x, z, '-.hb')

figure
plot(x,y,'r',x,z,'b')
hold off

figure
subplot(2,3,1)
plot(x, y, 'r')
title('Wykres sinus')
subplot(2,3,5)
plot(x, z, 'b')
title('Wykres cosinus')