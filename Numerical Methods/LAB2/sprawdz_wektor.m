function sprawdz_wektor(wektor)
wektor = str2num(wektor)
    if numel(wektor) >= 4
        error('Błąd');
    end
end