clc
close all
clear all


u.okno = figure 

set(u.okno)

set(u.okno, 'name', 'Zadanie 1', 'numbertitle', 'off')

set(u.okno, 'color', [0.18, 0.12, 0.02])

u.napis =  uicontrol('Style','text', 'Position',[175,300,200,50],'String','Podaj kolor');
u.edycja =  uicontrol('Style','edit', 'Position',[175,200,200,50])
u.przycisk = uicontrol('Style', 'pushbutton', 'Position', [175, 100, 200, 50], 'String', 'OK', 'Callback', {@zadanie2_funkcja,u})

%poniżej polecenia do zadania 3.
set(u.napis, 'units', 'normalized')
set(u.edycja, 'units', 'normalized')
set(u.przycisk, 'units', 'normalized')

