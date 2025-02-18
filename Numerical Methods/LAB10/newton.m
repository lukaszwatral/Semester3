clc
clear all
close all

x1a = -10;
x1b = 10;
x2a = -10;
x2b = 10;
[x,y]=meshgrid([x1a:0.01:x1b],[x2a:0.01:x2b]);
% f = @(x, y)x.^2+2.*x.*y+3*y.^2;
f = @(x1, x2)x1.^2+2*x1+x2.^2;
Pk = [2; 4];
P0 = Pk;
h = 1;
subplot(1, 2, 1)
hold on
plot(Pk(1, 1), Pk(2, 1), 'r.')
plot(Pk(1, 1), Pk(2, 1), 'go')
text(Pk(1, 1)+0.2, Pk(2, 1)+0.2, ' Ps')
contour(x, y, f(x, y))
dx = @(x, y) (f(x+h, y)-f(x, y))/h;
dy = @(x, y) (f(x, y+h)-f(x, y))/h;
d2x = @(x, y) (f(x+h, y)-2*f(x, y)+f(x-h, y))/(h^2);
d2y = @(x, y) (f(x, y+h)-2*f(x, y)+f(x, y-h))/(h^2);
dxy = @(x, y) (f(x+h, y+h) - f(x+h, y-h) - f(x-h, y+h) + f(x-h, y-h))/(4*h^2);
tol = 0.01;
iter = 0;
tic
for i=1:100
    tmp = P0;
    P0 = Pk;
    grad = [dx(Pk(1, 1), Pk(2, 1)); dy(Pk(1, 1), Pk(2, 1))];
    H = [d2x(Pk(1, 1), Pk(2, 1)), dxy(Pk(1, 1), Pk(2, 1)); dxy(Pk(1, 1), Pk(2, 1)), d2y(Pk(1, 1), Pk(2, 1))];
    H = H^(-1);
    Pk = P0 - H*grad;
    plot(Pk(1, 1), Pk(2, 1), 'r.')
    iter = i;
    if(Pk == [0; 0])
        break;
    elseif((abs(f(Pk(1, 1), Pk(2,1))-f(P0(1, 1), P0(2,1)))<tol))
        break;
    elseif(abs(f(Pk(1, 1), Pk(2,1))-f(tmp(1, 1), tmp(2,1)))==0)
        break;
    end

end
toc
plot(Pk(1, 1), Pk(2, 1), 'go')
text(Pk(1, 1)+0.2, Pk(2, 1)+0.2, ' Pmin')
hold off
Pmin = Pk
iter
Fmin = f(Pk(1, 1), Pk(2, 1))
title("Wartość funkcji w Pmin("+Pmin(1, 1)+", "+Pmin(2, 1)+") = "+Fmin)
subplot(1, 2, 2)
[x,y]=meshgrid([x1a:0.5:x1b],[x2a:0.5:x2b]);
surf(x, y, f(x, y))
% title("f(x, y) = x^2+2*x*y+3*y^2")
title("f(x, y) = x^2+2*x+y^2");