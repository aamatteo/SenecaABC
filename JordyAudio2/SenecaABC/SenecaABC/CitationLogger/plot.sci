// SciLab plotting function for CitationLogger
// OS 13JAN2005

logfile = xgetfile('*.log');

//x=read(logfile,-1, 51);
x = fscanfMat(logfile);

firstidx=x(1,1)
lastidx=x(length(x(:,1)),1)

xset("window", 0)

subplot(221);

plot2d(x(:,1), x(:,2), style=[1]);
plot2d(x(:,1), x(:,3), style=[2]);
plot2d(x(:,1), x(:,4), style=[3]);
plot2d(x(:,1), x(:,5), style=[4]);
plot2d(x(:,1), x(:,6), style=[5]);
xtitle('input signals [rad]');
xgrid(1);
legends(['ux(da)';'uy(de)';'uz(dr)';'throttle_left';'throttle_right'],[1 2 3 4 5], 1)

subplot(222);

plot2d(x(:,1), x(:,11), style=[1]);
plot2d(x(:,1), x(:,12), style=[2]);
plot2d(x(:,1), x(:,13), style=[3]);
xtitle('rotation rates [rad/s]');
xgrid(1);
legends(['p';'q';'r'],[1 2 3], 1)

subplot(223);

plot2d(x(:,1), x(:,23), style=[1]);
plot2d(x(:,1), x(:,24), style=[2]);
plot2d(x(:,1), x(:,25), style=[3]);
xtitle('rotation accelerations [rad/s]');
xgrid(1);
legends(['pdot';'qdot';'rdot'],[1 2 3], 1)

subplot(224);

plot2d(x(:,1), x(:,15), style=[1]);
plot2d(x(:,1), x(:,16), style=[2]);
xtitle('angle of attack and slideslip [rad]');
xgrid(1);
legends(['alpha';'beta'],[1 2], 1)

xset("window", 1)

subplot(221);

plot2d(x(:,1), x(:,2), style=[1]);
plot2d(x(:,1), x(:,3), style=[2]);
plot2d(x(:,1), x(:,4), style=[3]);
plot2d(x(:,1), x(:,5), style=[4]);
plot2d(x(:,1), x(:,6), style=[5]);
xtitle('input signals [rad]');
xgrid(1);
legends(['ux(da)';'uy(de)';'uz(dr)';'throttle_left';'throttle_right'],[1 2 3 4 5], 1)

subplot(222);

plot2d(x(:,1), x(:,17), style=[1]);
plot2d(x(:,1), x(:,18), style=[2]);
xtitle('Euler angles [rad]');
xgrid(1);
legends(['phi';'thetat'],[1 2], 1)

subplot(223);

plot2d(x(:,1), x(:,33), style=[1]);
plot2d(x(:,1), x(:,34), style=[2]);
plot2d(x(:,1), x(:,35), style=[3]);
xtitle('specific forces [g]');
xgrid(1);
legends(['fx';'fy';'fz'],[1 2 3], 1)

xset("window", 2)

subplot(221);

plot2d(x(:,1), x(:,40), style=[1]);
plot2d(x(:,1), x(:,43), style=[2]);
xtitle('Fuel flow [lbs/hr]');
xgrid(1);
legends(['left';'right'],[1 2 ], 1)

subplot(222);

plot2d(x(:,1), x(:,41), style=[1]);
plot2d(x(:,1), x(:,44), style=[2]);
plot2d(x(:,1), x(:,42), style=[3]);
plot2d(x(:,1), x(:,45), style=[4]);
xtitle('N1 & N2');
xgrid(1);
legends(['N1left';'N1right';'N2left';'N2right' ],[1 2 3 4], 1)

subplot(223);

plot2d(x(:,1), x(:,10), style=[1]);
plot2d(x(:,1), x(:,46), style=[2]);
plot2d(x(:,1), x(:,47), style=[3]);
xtitle('Gear & flaps');
xgrid(1);
legends(['gear set';'gear';'flaps'],[1 2 3], 1)
