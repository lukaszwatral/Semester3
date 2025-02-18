clc
clear all
close all
x = 40545
y = 70226
% x = single(x)
% y = single(y)
x1 = int32(x)
y1 = int32(y)
%f = @(x,y) 9*x^4-y^4+2*y^2
f = @(x,y) (3*x^2-y^2+1)*(3*x^2+y^2-1)+1

v = f(x1, y1)
% int16(v)
% int32(v)
% int64(v)