clc
close all
clear all


u.okno = figure 

set(u.okno)

set(u.okno, 'name', 'Zadanie 1', 'numbertitle', 'off')

kolor = get(u.okno, 'color');

%set(u.okno, 'color', [0; 0; 0])
set(u.okno, 'color', [0.18, 0.12, 0.02])

u.napis =  uicontrol('Style','text', 'Position',[100,300,200,50],'String','Napis');
u.edycja =  uicontrol('Style','edit', 'Position',[100,200,200,50],'String','Edycja'); 
u.przycisk = uicontrol('Style', 'pushbutton', 'Position', [100, 100, 200, 50], 'String', 'OK', 'Callback', {@zadanie1_2, u})

