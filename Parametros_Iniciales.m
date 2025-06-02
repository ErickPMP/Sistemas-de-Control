clc
clear all

load('MOTOR_ESCA.mat')
% Obtener los parametros del motor DC 
t = out.tout;
u = out.u_n;
theta = out.theta_n;
omega = out.omega_n;
crrnt = out.crrnt_n;

%% Experimento 01
K  = 0.2;
KT = 0.1;
b  = 0.001;
L  = 0.03;
R  = 10;
J  = 0.0001;

% %% Experimento 02
% K  = 0.35;
% KT = 0.15;
% b  = 0.002;
% L  = 0.045;
% R  = 48;
% J  = 0.00012;
% 
% %% Experimento 03
% K  = 0.25;
% KT = 0.12;
% b  = 0.0015;
% L  = 0.035;
% R  = 50;
% J  = 0.00014;
% 
% %% Experimento 04
% K  = 0.4;
% KT = 0.18;
% b  = 0.003;
% L  = 0.05;
% R  = 43;
% J  = 0.00009;
