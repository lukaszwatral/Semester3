function [X] = iterP(A, b, e)
l = length(A);
Ab = [A b];
for i=1:l
    Ab(i, :) = Ab(i, :) / Ab(i, i);
    Ab(i, i) = 0;
end
W = Ab(:, 1:1:l);
W = W*(-1);
Z = Ab(:, l+1);
X = zeros(l, 1);
for i=1:100
    Y = X;
    X = W * X + Z;
    V(:, i) = X
    if(max(abs(X - Y))<=e);
    iteracja = i;
    break;
    end
end
iteracja
end

