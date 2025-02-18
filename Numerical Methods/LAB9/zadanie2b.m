clc
clear all
close all

a = 1;
x1a = -10;
x1b = 10;
x2a = -10;
x2b = 10;
[x1,x2]=meshgrid([x1a:0.01:x1b],[x2a:0.01:x2b]);
% f = @(x1, x2)x1.^2+2.*x1.*x2+3*x2.^2;
% f = @(x1, x2)x1.^2+2*x1+x2.^2;
e1 = [1, 0];
e2 = [0, 1];
e3 = [-1, 0];
e4 = [0, -1];
e5 = [1/sqrt(2), 1/sqrt(2)];
e6 = [-1/sqrt(2), 1/sqrt(2)];
e7 = [1/sqrt(2), -1/sqrt(2)];
e8 = [-1/sqrt(2), -1/sqrt(2)];
subplot(1, 2, 1)
hold on
contour(x1, x2, f(x1,x2));
axis square
% ps = [x1a+rand()*abs(x1a-x1b), x1a+rand()*abs(x1a-x1b)];
% ps = [-3, 7];
% ps = [2, -1];
iter = 0;
plot(ps(1,1), ps(1, 2), 'ro')
text(ps(1, 1)+0.2, ps(1, 2)+0.2, ' Ps')
tic
while(1)
p1 = ps+a*e1;
p2 = ps+a*e2;
p3 = ps+a*e3;
p4 = ps+a*e4;
p5 = ps+a*e5;
p6 = ps+a*e6;
p7 = ps+a*e7;
p8 = ps+a*e8;
fp1 = f(p1(1, 1), p1(1, 2));
fp2 = f(p2(1, 1), p2(1, 2));
fp3 = f(p3(1, 1), p3(1, 2));
fp4 = f(p4(1, 1), p4(1, 2));
fp5 = f(p5(1, 1), p5(1, 2));
fp6 = f(p6(1, 1), p6(1, 2));
fp7 = f(p7(1, 1), p7(1, 2));
fp8 = f(p8(1, 1), p8(1, 2));
fps = f(ps(1, 1), ps(1, 2));
fmin = min([fp1, fp2, fp3, fp4, fp5, fp6, fp7, fp8, fps]);
iter = iter + 1;
if(fmin==fp1)
    line([ps(1, 1), p1(1, 1)], [ps(1, 2), p1(1, 2)]);
    plot(p1(1,1), p1(1, 2), 'r.')
    ps = p1;
elseif(fmin==fp2)
    line([ps(1, 1), p2(1, 1)], [ps(1, 2), p2(1, 2)]);
    plot(p2(1,1), p2(1, 2), 'r.')
    ps = p2;
elseif(fmin==fp3) 
    line([ps(1, 1), p3(1, 1)], [ps(1, 2), p3(1, 2)]);
    plot(p3(1,1), p3(1, 2), 'r.')
    ps = p3;
elseif(fmin==fp4)
    line([ps(1, 1), p4(1, 1)], [ps(1, 2), p4(1, 2)]);
    plot(p4(1,1), p4(1, 2), 'r.')
    ps = p4;
elseif(fmin==fp5)
    line([ps(1, 1), p5(1, 1)], [ps(1, 2), p5(1, 2)]);
    plot(p5(1,1), p5(1, 2), 'r.')
    ps = p5;
elseif(fmin==fp6)
    line([ps(1, 1), p6(1, 1)], [ps(1, 2), p6(1, 2)]);
    plot(p6(1,1), p6(1, 2), 'r.')
    ps = p6;
elseif(fmin==fp7)
    line([ps(1, 1), p7(1, 1)], [ps(1, 2), p7(1, 2)]);
    plot(p7(1,1), p7(1, 2), 'r.')
    ps = p7;
elseif(fmin==fp8)
    line([ps(1, 1), p8(1, 1)], [ps(1, 2), p8(1, 2)]);
    plot(p8(1,1), p8(1, 2), 'r.')
    ps = p8;
else 
    plot(ps(1,1), ps(1, 2), 'w.')
    break;
end
if(iter>1500)
    break;
end
end
toc
iter
pmin = ps
fmin = f(ps(1, 1), ps(1, 2))
plot(pmin(1, 1), pmin(1, 2), 'go')
text(pmin(1, 1)+0.2, pmin(1, 2)+0.2, ' Pmin')
hold off
title("Wartość funkcji w Pmin("+pmin(1, 1)+", "+pmin(1, 2)+") = "+fmin)
[x1,x2]=meshgrid([-10:1:10],[-10:1:10]);
subplot(1, 2, 2)
surf(x1, x2, f(x1,x2));
% title("f(x1, x2) = x1^2+2*x1*x2+3*x2^2")
% title("f(x1, x2) = x1^2+2*x1+x2^2");
