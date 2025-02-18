function [x_n, n_n, czas_n] = test(f, a, b, tol, ftol)
if(sign(f(a))==sign(f(b)))
    disp('Brak przedziału izolacji pierwiastka')
    return;
end
tic
xk = (a+b)/2;
i = 1;
h = 0.0001;
d2f = @(x) ((f(x+h)-2*f(x)+f(x-h))/(h^2));
if(sign(f(a))==sign(d2f(a)))
        x0 = a;
else
        x0 = b;
end
df = @(x) (f(x0+h)-f(x0-h))/ (2*h);
while (abs(f(xk))>ftol && abs(xk-x0)>tol)
x0 = xk;
xk = x0 - f(x0)/df(x0);
i = i + 1;
end
czas_n = toc
x_n = xk
n_n = i
x = a:tol:b;
    % hold on
    % plot(x, f(x))
    % plot(xk,f(xk),'g*')
    % hold off
end