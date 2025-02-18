function [x_r, n_r, czas_r] = regula(f, a, b, tol, ftol)
if(sign(f(a))==sign(f(b)))
    disp('Brak przedziału izolacji pierwiastka');
    return;
else
    tic
    h = 0.001;
    d2f = @(x) ((f(x+h)-2*f(x)+f(x-h))/h^2);
    i = 1;
    xs = 0;
    x0 = 0;
    if(sign(f(a))==sign(d2f(a)))
        xs = a;
        x0 = b;
    else
        xs = b;
        x0 = a;
    end
    x0 = xs-(f(xs)/(f(x0)-f(xs)))*(x0-xs);
    xk = 0;
    while(abs(x0)>ftol && abs(x0-xk)>tol)
    xk = x0;
    i=i+1;
    x0 = xs-(f(xs)/(f(x0)-f(xs)))*(x0-xs);
    end
    czas_r = toc
    x = a:tol:b;
    % hold on
    % plot(x, f(x))
    % plot(x0,f(x0),'r*')
    % hold off
    n_r = i
    x_r = x0

end
end


