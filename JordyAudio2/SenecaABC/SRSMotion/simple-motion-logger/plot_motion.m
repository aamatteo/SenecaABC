[filename, pathname] = uigetfile('*.log');

x = importdata(fullfile(pathname, filename), ' ');
%x = x.data;

% conversions
x(:,1) = (x(:,1)-x(1,1))/(x(2,1)-x(1,1))*0.01; % ticks to seconds, assume 100 Hz data
x(:,6:8) = rad2deg(x(:,6:8));
x(:,21:23) = rad2deg(x(:,21:23));
x(:,42:44) = rad2deg(x(:,42:44));
x(:,57:62) = x(:,57:62) - 2.70608;
x(:,77) = -x(:,77) + 2.39;

figure;
subplot(2,2,1);
plot(x(:,1), x(:,[9 15 51 24 30]));
title('X acceleration and specific force');
xlabel('time [s]');
ylabel('[m/s^2]');
grid on
legend('a/c acc body','a/c specific force body','sim acc inertial', ...
    'sim acc body derp','sim specific force body');

subplot(2,2,2);
plot(x(:,1), x(:,[10 16 52 25 31]));
title('Y acceleration and specific force');
xlabel('time [s]');
ylabel('[m/s^2]');
grid on
legend('a/c acc body','a/c specific force body','sim acc inertial', ...
    'sim acc body derp','sim specific force body');


subplot(2,2,3);
plot(x(:,1), x(:,[11 17 53 26 32]));
title('Z acceleration and specific force');
xlabel('time [s]');
ylabel('[m/s^2]');
grid on
legend('a/c acc body','a/c specific force body','sim acc inertial', ...
    'sim acc body derp','sim specific force body');

figure;
subplot(2,2,1);
plot(x(:,1), x(:,[6 21]));
title('Roll rate');
xlabel('time [s]');
ylabel('[deg/s]');
grid on
legend('a/c rate','sim rate');

subplot(2,2,2);
plot(x(:,1), x(:,[7 22]));
title('Pitch rate');
xlabel('time [s]');
ylabel('[deg/s]');
grid on
legend('a/c rate','sim rate');

subplot(2,2,3);
plot(x(:,1), x(:,[8 23]));
title('Yaw rate');
xlabel('time [s]');
ylabel('[deg/s]');
grid on
legend('a/c rate','sim rate');

figure;
subplot(2,2,1);
if x(1,75) == -1
    plot(x(:,1), x(:,[39 40 41]));
    legend('x','y', 'z');
else
    plot(x(:,1), x(:,[39 40 41 75 76 77]));
    legend('x','y', 'z', 'x_{meas}', 'y_{meas}', 'z_{meas}');
end
title('Position setpoints');
xlabel('time [s]');
ylabel('[m]');
grid on

subplot(2,2,2);
plot(x(:,1), x(:,[45 46 47]));
title('Velocity setpoints');
xlabel('time [s]');
ylabel('[m/s]');
grid on
legend('x','y', 'z');

subplot(2,2,3);
plot(x(:,1), x(:,[42 43 44]));
title('Euler angle setpoints');
xlabel('time [s]');
ylabel('[deg]');
grid on
legend('\phi','\theta', '\psi');

figure;
subplot(2,2,1);
plot(x(:,1), x(:,57:62));
title('Actuator setpoints');
xlabel('time [s]');
ylabel('[m]');
grid on
legend('1', '2', '3', '4', '5', '6');

subplot(2,2,2);
plot(x(:,1), x(:,63:68));
title('Actuator velocity setpoints');
xlabel('time [s]');
ylabel('[m/s]');
grid on
legend('1', '2', '3', '4', '5', '6');
 
subplot(2,2,3);
plot(x(:,1), x(:,69:74));
title('Actuator acceleration setpoints');
xlabel('time [s]');
ylabel('[m/s^2]');
grid on
legend('1', '2', '3', '4', '5', '6');

