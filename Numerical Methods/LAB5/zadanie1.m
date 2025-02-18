clc
clear all
close all

X = [5, 10, 20, 30, 40, 50, 65, 70, 80, 85, 90, 100, 110, 120, 130, 135, 140, 150, 153, 155, 160, 165];
Y = [0, 7, 16, 23, 27, 29, 30, 37, 44, 45, 30, 20, 13, 9, 6, 5, 6, 12, 20, 25, 18, 0];
x = [5, 10, 20, 30, 40, 45, 50, 60, 70, 80, 90, 100, 110, 120, 130, 135, 140, 150, 155, 160, 165];
y = [0, -6, -12, -16, -29, -30, -23, -21, -22, -21, -20, -19, -15, -12, -8, -5, -6, -10, -20, -12, 0];
Hq = 5:1:165;
subplot(2, 2, 1)
Vq = interp1(X, Y, Hq, "pchip");
hold on
plot(X, Y, 'or', Hq, Vq, 'b');
Vq = interp1(x, y, Hq, "pchip");
plot(x, y, 'or', Hq, Vq, 'b');
hold off
title('pchip')

subplot(2, 2, 2)
hold on
Vq = interp1(X, Y, Hq, "linear");
plot(X, Y, 'or', Hq, Vq, 'b');
Vq = interp1(x, y, Hq, "linear");
plot(x, y, 'or', Hq, Vq, 'b')
hold off
title('linear')

subplot(2, 2, 3)
hold on
Vq = interp1(X, Y, Hq, "spline");
plot(X, Y, 'or', Hq, Vq, 'b');
Vq = interp1(x, y, Hq, "spline");
plot(x, y, 'or', Hq, Vq, 'b')
hold off
title('spline')

subplot(2, 2, 4)
hold on
Vq = interp1(X, Y, Hq, "makima");
plot(X, Y, 'or', Hq, Vq, 'b');
Vq = interp1(x, y, Hq, "makima");
plot(x, y, 'or', Hq, Vq, 'b')
hold off
title('makima')