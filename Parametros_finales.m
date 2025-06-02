clc
clear all

load('MOTOR_SENO.mat');
t_exp = out.tout;
u = out.u_n;
theta_exp = out.theta_n;
omega_exp = out.omega_n;
crrnt_exp = out.crrnt_n;

J = 0.00020714;
K = 0.24607;
KT = 0.10001;
L = 0.01809;
R = 18.611;
b = 0.00053228;

Ts_sim = 0.001;
exp_sen = sim('modelo_para_pruebas',90);

theta_sim = exp_sen.theta;
omega_sim = exp_sen.omega;
crrnt_sim = exp_sen.crrnt;
t_sim = exp_sen.tout;


plot(t_exp, omega_exp);
hold on
plot(t_sim, omega_sim,'LineWidth',2);
grid on;
