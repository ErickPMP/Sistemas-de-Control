clc;
clear all;

s = tf('s');
w0 = 8;                 % Frecuencia de corte (rad/seg)
G = 1/((s/w0) + 1);     % Funcion de transferencia
Fs = 100;               % Frecuencia de muestreo (Hz)
Ts = 1/Fs;              % Periodo de muestreo (seg)
Gd = c2d(G,Ts,'zoh')    % Sistema digital

%%

clc;
clear all;

s = tf('s');
w0 = 10;                 % Frecuencia de corte (rad/seg)
e = 0.4;
G = (w0^2)/(s^2 + 2*w0*e*s + w0^2);     % Funcion de transferencia
Fs = 10;                                % Frecuencia de muestreo (Hz)
Ts = 1/Fs;                              % Periodo de muestreo (seg)
Gd = c2d(G,Ts,'zoh')                    % Sistema digital

step(Gd)
