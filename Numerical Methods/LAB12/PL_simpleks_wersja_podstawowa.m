%skrypt do zadania "Programowanie liniowe - Metoda simpleks (wersja podstawowa)"

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
% %dane wejściowe 
% A = [2 1 1 0 0; 3 3 0 1 0; 2 0 0 0 1];
% B = [10; 24; 8];
% Z = [-1; -1; -1];
% F = [300, 200, 0, 0, 0];
% Wb = [3, 4, 5];

% A = [1 2 1 0 0; 1 -2 0 1 0; 2 2 0 0 1];
% B = [8;2;10];
% Z = [-1;-1;-1];
% F = [2, 3, 0, 0, 0];
% Wb = [3, 4, 5];

A = [2 1 -1 0 1 0; 3 3 0 1 0 0; 2 0 0 0 0 1];
B = [10; 24; 8];
Z = [-1; -1; 0];
F = [300, 200, 0, 0, -10^6, -10^6];
Wb = [5, 4, 6];


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
    for i=1:2
    wynik = wynik + " x" + i + " = " + num2str(B(find(Wb==i)));
    end
    disp(wynik)
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
