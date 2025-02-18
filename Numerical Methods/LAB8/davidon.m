function [xmin] = davidon(f, a, b, tol)
h = 0.001;
x = linspace(a, b, 100);
hold on
plot(x, f(x), 'r')
df = @(x) ((f(x+h)-f(x-h))/(2*h));
Z = (3*(f(a)-f(b)))/(b-a) + df(a) + df(b);
Q = sqrt(Z.^2-df(a)*df(b));
tic
xm = b-((df(b)+Q-Z)/(df(b)-df(a)+2*Q))*(b-a);
iter = 1;
% plot(xm, f(xm), 'g*')
while(abs(df(xm))>=tol)
    plot(xm, f(xm), 'g*');
    if(df(a)<0 && df(b)>0)
    if(df(xm)>0)
        b = xm;
    elseif(df(xm)<0)
        a = xm;
    end
    
    Z = (3*(f(a)-f(b)))/(b-a) + df(a) + df(b);
Q = sqrt(Z.^2-df(a)*df(b));
xm = b-((df(b)+Q-Z)/(df(b)-df(a)+2*Q))*(b-a);
iter = iter+1;
    else
        break;
    end
end
iter
if(xm<a)
    xm = a;
elseif(xm>b)
    xm = b;
end
toc
xm
plot(xm, f(xm), 'bo');
title("Metoda Davidona")
hold off
end

