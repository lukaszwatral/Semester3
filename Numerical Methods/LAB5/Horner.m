function [w] = Horner(A, n, x)
w = A(1);
for i=2:n
    w = w.* x + A(i);
end
end

