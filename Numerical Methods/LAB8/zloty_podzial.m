function xmin = zloty_podzial(f, a, b, tol)
x = linspace(a, b, 100);
h=0.001;
hold on
plot(x, f(x), 'r')
df = @(x) ((f(x+h)-f(x-h))/(2*h));
zp = (sqrt(5)-1)/2;
iter = 1;
tic
x1 = b-zp*(b-a);
x2 = a+zp*(b-a);
while((b-a)>=tol)
    if(f(x1)<f(x2))
        b= x2;
        x2 = x1;
        x1 = b-zp*(b-a);
        plot(b, f(b), 'g*');
    else
        a = x1;
        x1 = x2;
        x2 = a+zp*(b-a)
        plot(a, f(a), 'g*');
    end
    iter = iter+1;
end
xmin = (a+b)/2;
toc
iter
xmin
plot(xmin, f(xmin), 'bo');
title("Metoda złotego podziału z kolejnymi iteracjami")
hold off
end

