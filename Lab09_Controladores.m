% % Control de Corriente
% Num=[J b];
% Den=[L*J (R*J+L*b) R*b+K*KT];
% Gs=tf(Num,Den)
% sisotool(Gs)
% max 0.17 Amperes  Corriente - P 1000 I 30 PI 15 Y 7
% max 34 rad/s
% max 12 V
% % Control de Velocidad
% Num=[K];
% Den=[L*J (R*J+L*b) R*b+K*KT]; % Velocidad - P 8 I 4.2
% Gs=tf(Num,Den);
% sisotool(Gs)
% % Control de Posición
Num=[K];
Den=[L*J (R*J+L*b) R*b+K*KT 0];
Gs=tf(Num,Den);
sisotool(Gs)
