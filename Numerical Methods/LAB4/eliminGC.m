function [X] = eliminGC(A, b)
Ab = [A b];
n = length(A);
X = zeros(n, 1);
for i=1:n
    if(Ab(i,i)==0)
        for j=i:n
            if(Ab(j, i)==max(Ab(:, i)))
                Ab([i j], :) = Ab([j i], :);
            end
        end
    end
    for j=(i+1):n
    Ab(i, :) = Ab(i, :) / Ab(i, i);
    Ab(j, :) = Ab(j, :) - Ab(j, i)*Ab(i, :);
    end
end
Ab(n, :) = Ab(n, :) / Ab(n, n);
for i=1:n
X(i) = Ab(i, n+1);
end
for i=n-1:-1:1
    for j=i+1:n
    X(i) = X(i) - Ab(i, j)*X(j);
    end
end
end