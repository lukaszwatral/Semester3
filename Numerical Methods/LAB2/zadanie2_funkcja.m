function [] = zadanie2_funkcja(h, ~,u)
kolor = get(u.edycja, 'String');

try
    set(u.okno, 'color', kolor)
    sprawdz_wektor(kolor)
catch
    set(u.okno, 'color', 'white')
end
end