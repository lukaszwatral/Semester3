%skrypt do zadania "Programowanie liniowe - Metoda simpleks (wersja z rozszerzeniami)"

clc
close
clear

%dane pochodzące z treści zadania - tylko tych informacji wymagamy od
%użytkownika, reszta kodu pozostaje dla niego 'czarną magią'

% A=  % macierz współczynników ograniczeń
% B=  % wektor wyrazów wolnych ograniczeń   
% Z=  % wektor przechowujący informację o znaku nierówności
%     np. 1 dla > i >=
%         0 dla =
%        -1 dla < i <=         
% F=  % wektor współczynników funkcji celu

%dane wejściowe
% A = [2 1; 3 3; 2 0];
% B = [10; 24; 8];
% Z = [-1; -1; -1];
% F = [300, 200];

% A = [1 2; -1 2;2 2];
% B = [8;-2;10];
% Z = [-1;1;-1];
% F = [2,3];

A = [-2 -1; 3 3; 2 0];
B = [-10; 24; 8];
Z = [-1; -1; 0];
F = [300, 200];

%1
%opcja - sprawdzenie, czy B jest dodatnie
n = numel(B); 
w = numel(A(1, :));
for i=1:n
    if(B(i)<0)
       A(i, 1) = A(i, 1)*(-1);
       A(i, 2) = A(i, 2)*(-1);
       B(i) = B(i)*(-1);
       Z(i) = Z(i)*(-1);
    end
end

x = numel(A(1, :));
%2
for i=1:n %opcja - postać kanoniczna i zmienne dopełniające
    if(Z(i)==1)
            A(:, (x+i)) = 0;
    F(x+i) = 0;
        A(i, (x+i)) = -1;
    elseif(Z(i)==-1)
            A(:, (x+i)) = 0;
    F(x+i) = 0;
        A(i, (x+i)) = 1;
    end
    Z(i) = 0;
end
x = numel(A(1, :))+1; 
%3
for i=1:n
if(all(A(i, w+1:end) ~= 1)) %opcja - zmienne sztuczne
    A(:, x) = 0;
    F(x) = -10^6;
    A(i, x) = 1;
    x = x+1;
end
end
a = 0;
for i=numel(A(1, :))-w:numel(A(1, :))
    if(any(A(:, i) == 1)) 
        a = a +1;
    end
end
%4
for i=1:a %opcja - wektor bazowy
    Wb(i) = w+find(A(i, w+1:end)==1);
end
Cb = F(Wb); %5
while(1)
F0 = Cb*B; %6
for i=1:numel(A(1, :))
tmp = Cb*A(:, i)-F(i);
WW(1, i) = tmp; %7
end

tab = [0, 0, 0, F];
tmp = [];
tab = vertcat(tab, horzcat(Cb.', Wb.', B, A()));
for i=1:(numel(tab(1, :))-1-numel(F))
tmp(i) = 0;
end
tab = vertcat(tab, [tmp, F0,WW()]);
format short g;
disp(tab)

if(all(WW >= 0)) %8
    display('To jest ostatnia tablica') 
    wynik = "Maksymalna wartość funkcji celu wynosi: " + num2str(F0) + " dla";
    for i=1:w
    wynik = wynik + " x" + i + " = " + num2str(B(find(Wb==i)));
    end
    disp(wynik)
    % display(['Maksymalna wartość funkcji celu wynosi: ', num2str(F0), ' dla x1 = ', num2str(B(find(Wb==1))), ', x2 = ', num2str(B(find(Wb==2)))])
    break;
end
  display('To nie jest ostatnia tablica')
  
  [mink, min_ki] = min(WW);
  KK = A(:, min_ki);
  for i=1:numel(A(:, min_ki))
      if(A(i, min_ki)>0)
  ba(i) = B(i)/A(i, min_ki);
      else
          ba(i) = 99999999999999999;
      end
  end
  [minw, min_wi] = min(ba);
  WK = A(min_wi, :);
  ER = A(min_wi, min_ki);
  Wb(min_wi) = min_ki;
  Cb(min_wi) = F(min_ki);
  WK = WK./ER;
  A(min_wi, :) = WK;
  B(min_wi) = B(min_wi)/ER;
  for i=1:numel(A(:, 1))
  if(i ~= min_wi)
  B(i) = B(i) - A(i, min_ki)*B(min_wi);
  A(i, :) = A(i, :) - A(i, min_ki)*WK;
  end
  end
end
