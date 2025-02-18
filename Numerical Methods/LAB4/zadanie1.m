clc
clear all
close all

n = 3000;
A = rand(n, n);

A = A + n * eye(n, n);

x = ones(n, 1);

b = A * x;

% A = [4 1; 1 2]
% 
% b = [8; 9]

% A = [1 1 1; 1 2 3; 1 3 4]
% 
% b = [3; 0; -2]

% format("longE")
% tic
% iterP(A, b, 0.01)
% toc
% format("default")
% tic
% eliminGC(A, b)
% toc

xx = [0.010240,0.010968, 0.010931, 0.015455,0.026324, 0.077461, 0.200099, 0.338535];
yy = [0.008701, 0.011623, 0.038131, 0.327928, 4.128788, 67.511632, 293.885399, 882.160421];
plot(xx)
xticklabels({'10x10', '100x100', '200x200', '500x500', '1000x1000', '2000x2000', '3000x3000', '5000x5000'});
title('Wykres dla funkcji iterP')
figure
plot(yy)
xticklabels({'10x10', '100x100', '200x200', '500x500', '1000x1000', '2000x2000', '3000x3000', '5000x5000'});
title('Wykres dla funkcji eliminGC')