function [T, Wx] = zad3(X,Y,arg)
n = length(X);
T = zeros(n-1);
Wx = Y(1);
for j=1:n-1
    for i=n:-1:j+1
        Y(i) = (Y(i)-Y(i-1))/(X(i)-X(i-j));
        T(i-1, j) = Y(i);
    end
end
    for j = 1:n-1
        tmp = T(j, j);
        for i = 1:j
            tmp = tmp * (arg - X(i));
        end
        Wx = Wx + tmp;
    end
    Wx
end
