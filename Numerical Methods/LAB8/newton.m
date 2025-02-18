function xk = newton(f, a, b, tol)
xk = (b-a)*rand();
h=0.001;
df = @(x) ((f(x+h)-f(x-h))/(2*h));
d2f = @(x) (f(x+h)-2*f(x)+f(x-h))/(h.^2);
iter = 0;
% plot(xk, f(xk), 'g*')
tic
while(df(xk)>=tol)
    xk = xk-(df(xk)/d2f(xk));
    iter = iter+1;
end
if(xk<a)
    xk = a;
elseif(xk>b)
    xk = b;
    plot(xk, f(xk), 'g*')
end
toc
x = linspace(a, b, 100);
iter
xk
hold on
plot(x, f(x), 'r')
plot(xk, f(xk), 'bo');
title("Metoda Newtona")
hold off
end

