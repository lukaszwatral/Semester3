%skrypt do zadania "Programowanie liniowe - Metoda graficzna"

clc
close
clear

%dane pochodz¹ce z treœci zadania - tylko tych informacji wymagamy od
%u¿ytkownika, reszta kodu pozostaje dla niego 'czarn¹ magi¹'

% A=  % macierz wspó³czynników ograniczeñ
% B=  % wektor wyrazów wolnych ograniczeñ   
% Z=  % wektor przechowuj¹cy informacjê o znaku nierównoœci
%     np. 1 dla > i >=
%         0 dla =
%        -1 dla < i <=         
% F=  % wektor wspó³czynników funkcji celu 

% 
% A = [2 1;
%      3 3;
%      2 0;
%      1 0;
%      0 1];
% B = [10;
%      24;
%       8;
%       0;
%       0];
% Z = [-1;
%      -1;
%      -1;
%       1;
%       1];
% F = [300, 200];

% A = [3 2; 4 5; 1 0; 0 1];
% B = [6; 20; 0; 0];
% Z = [-1; 1; 1; 1];
% F = [0, 0];
% 
% A = [0.6 0.2; 0.1 0.1; 1 0; 0 1];
% B = [300; 100; 0; 0];
% Z = [-1; -1; 1; 1];
% F = [50, 30];

%-----------------
% wszystko od tego miejsca, to obliczenia na podstawie wprowadzonych
% informacji
%--- opcja

% opcja - do zrobienia na koñcu, jak bêdzie dzia³a³a wersja podstawowa 
% nale¿y sprawdziæ czy w wektorze B s¹ same dodatnie wartoœci
[w, k] = size(A);
n = numel(A(1, :));
for i=1:w %opcja
    if(B(i)<0)
       A(i, 1) = A(i, 1)*(-1);
       A(i, 2) = A(i, 2)*(-1);
       B(i) = B(i)*(-1);
       Z(i) = Z(i)*(-1);
    end
end
%poszukujemy wszystkich rozwi¹zañ par ograniczeñ
tmp = 1;
for i=1:w
    for j=i+1:w
        x = [A(i, :); A(j, :)]^(-1)*[B(i, :); B(j, :)];
        if(isnan(x(1, :))==0 && isnan(x(2, :))==0 && isinf(x(1, :))==0 && isinf(x(2, :))==0)
            X(1, tmp) = x(1, :);
            X(2, tmp) = x(2, :);
            tmp = tmp +1;
        end
    end
end

% najtrudniejszy etap - wydobycie ze wszystkich rozwi¹zañ tylko rozwi¹ñ
% dopuszczalnych
tmp = 1;
for i=1:numel(X(1, :))
    flag = 1;
    for j=1:w
        tmp2 = A(j, :)*X(:, i);
        if(Z(j, :)==-1)
            if(tmp2>B(j, :))
                flag = 0;
            end
        elseif(Z(j, :)==1)
            if(tmp2<B(j, :))
                flag = 0;
            end
        else
            if(tmp2~=B(j, :))
                flag = 0;
            end
        end
    end
    if(flag == 1)
    XX(1, tmp) = X(1, i);
        XX(2, tmp) = X(2, i);
        tmp = tmp + 1;
    end
end
if(exist('XX', 'var') == 1)
    hold on
for i=1:numel(XX(1, :))
    plot(XX(1, i), XX(2, i), 'r.', MarkerSize=10)
end
    
hold off
maxval = max(XX(:));
x = linspace(0, maxval, 100);
y = linspace(0, maxval, 100);
hold on
plot(x, 0*x, color='g')
plot(0*x, y, color ='g')
%rysujemy ograniczenia
for i=1:w
plot(x, -A(i, 1)/A(i, 2)*x+B(i, 1)/A(i, 2), 'g');
if(A(i, 2)==0)
    plot(linspace(B(i, 1)/A(i, 1), B(i, 1)/A(i, 1), 100), y, 'g')
end
end
hold off
% kolorujemy obszar rozwi¹zañ dopuszczalnych
hold on
K = convhull(XX(1, :),XX(2, :));
fill(XX(1, K),XX(2, K), 'cyan');
hold off

% obliczamy dla którego rozwi¹zania dopuszczalnego funkcja celu przyjmuje
% wartoœæ najwiêksz¹`
max = 0;
for i=1:numel(XX(1, :))
    if(max < (F(1, 1)*XX(1, i)+F(1, 2)*XX(2, i)))
        max = F(1, 1)*XX(1, i)+F(1, 2)*XX(2, i);
        maxpoint = [XX(1, i), XX(2, i)];
    end
end
% rysujemy (polecenie plot) funkcjê celu tak aby przechodzi³a przez punkt, w którym
% przyjmuje najwiêksz¹ wartoœæ 
m = -F(1, 1)/F(1, 2);
b = maxpoint(1, 2) - m * maxpoint(1,1);
hold on
plot(x, m*x+b, 'r')
plot(maxpoint(1, 1), maxpoint(1, 2), 'kp', MarkerSize=10, LineWidth=2)
hold off
% wykres otrzymuje tytu³
title(['Maksymalna wartoœæ funkcji celu wynosi: ', num2str(max), ' dla x = ', num2str(maxpoint(1, 1)), ', y = ', num2str(maxpoint(1, 2))])
display(['Maksymalna wartoœæ funkcji celu wynosi: ', num2str(max), ' dla x = ', num2str(maxpoint(1, 1)), ', y = ', num2str(maxpoint(1, 2))])
else
x = linspace(0, 10, 100);
y = linspace(0, 10, 100);
    hold on
plot(x, 0*x, color='g')
plot(0*x, y, color ='g')
for i=1:w
plot(x, -A(i, 1)/A(i, 2)*x+B(i, 1)/A(i, 2), 'g');
if(A(i, 2)==0)
    plot(linspace(B(i, 1)/A(i, 1), B(i, 1)/A(i, 1), 100), y, 'g')
end
end
hold off
    display('Brak rozwi¹zañ dopuszczalnych');
end
    
