// SciLab plotting function for SimpleMotionLogger
// OS 1MAY2002

ssize = input("Required stacksize [Mb]: ");
stacksize(ssize*1024*1024);

logfile = xgetfile('*.log');

x=read(logfile,-1, 92);

eerste = x(1,1)/2000;
laatste = x(length(x(:,1)),1)/2000;

xset("window", 0)

//xsetech([0.,0.,0.5,0.5]);
subplot(221);

plot2d(x(:,1)/2000, x(:,9), style=[1], rect=[eerste,-5,laatste,5]);
plot2d(x(:,1)/2000, x(:,24), style=[2], rect=[eerste,-5,laatste,5]);
plot2d(x(:,1)/2000, x(:,15), style=[3], rect=[eerste,-5,laatste,5]);
plot2d(x(:,1)/2000, x(:,30), style=[4], rect=[eerste,-5,laatste,5]);
plot2d(x(:,1)/2000, x(:,51), style=[5], rect=[eerste,-5,laatste,5]);
xtitle('X acceleration and specific force');
xgrid(1);

//xsetech([0.5,0.,0.5,0.5]);
subplot(222);

plot2d(x(:,1)/2000, x(:,10), style=[1], rect=[eerste,-5,laatste,5]);
plot2d(x(:,1)/2000, x(:,25), style=[2], rect=[eerste,-5,laatste,5]);
plot2d(x(:,1)/2000, x(:,16), style=[3], rect=[eerste,-5,laatste,5]);
plot2d(x(:,1)/2000, x(:,31), style=[4], rect=[eerste,-5,laatste,5]);
plot2d(x(:,1)/2000, x(:,52), style=[5], rect=[eerste,-5,laatste,5]);
xtitle('Y acceleration and specific force');
xgrid(1);

//xsetech([0.,0.5,0.5,0.5]);
subplot(223);

plot2d(x(:,1)/2000, x(:,11), style=[1], rect=[eerste,-10,laatste,5]);
plot2d(x(:,1)/2000, x(:,26), style=[2], rect=[eerste,-10,laatste,5]);
plot2d(x(:,1)/2000, x(:,17), style=[3], rect=[eerste,-10,laatste,5]);
plot2d(x(:,1)/2000, x(:,32), style=[4], rect=[eerste,-10,laatste,5]);
plot2d(x(:,1)/2000, x(:,53), style=[5], rect=[eerste,-10,laatste,5]);
xtitle('Z acceleration and specific force');
xgrid(1);

//xsetech([0.5,0.5,0.5,0.5]);
subplot(224);

legends(['a/c acc body';'a/c specific force body';'sim acc inertial';'sim acc body derp';'sim specific force body'],[1 3 5 2 4], 4)

xset("window", 1)

//xsetech([0.,0.,0.5,0.5]);
subplot(221);

plot2d(x(:,1)/2000, x(:,6)*57.324840764, style=[1], rect=[eerste,-10,laatste,10]);
plot2d(x(:,1)/2000, x(:,21)*57.324840764, style=[2], rect=[eerste,-10,laatste,10]);
xtitle('Roll rate');
xgrid(1);

//xsetech([0.5,0.,0.5,0.5]);
subplot(222);

plot2d(x(:,1)/2000, x(:,7)*57.324840764, style=[1], rect=[eerste,-10,laatste,10]);
plot2d(x(:,1)/2000, x(:,22)*57.324840764, style=[2], rect=[eerste,-10,laatste,10]);
plot2d(x(:,1)/2000, x(:,37)*57.324840764, style=[3], rect=[eerste,-10,laatste,10]);
xtitle('Pitch rate');
xgrid(1);

//xsetech([0.,0.5,0.5,0.5]);
subplot(223);

plot2d(x(:,1)/2000, x(:,8)*57.324840764, style=[1], rect=[eerste,-10,laatste,10]);
plot2d(x(:,1)/2000, x(:,23)*57.324840764, style=[2], rect=[eerste,-10,laatste,10]);
xtitle('Yaw rate');
xgrid(1);

//xsetech([0.5,0.5,0.5,0.5]);
subplot(224);

legends(['a/c rate';'sim rate'],[1 2], 4)

xset("window", 2)

//xsetech([0.,0.,0.5,0.5]);
subplot(221);

plot2d(x(:,1)/2000, x(:,75), style=[2], rect=[eerste,-0.7,laatste,0.7]);
plot2d(x(:,1)/2000, x(:,76), style=[4], rect=[eerste,-0.7,laatste,0.7]);
plot2d(x(:,1)/2000, -(x(:,77)-2.3906), style=[6], rect=[eerste,-0.7,laatste,0.7]);
plot2d(x(:,1)/2000, x(:,39), style=[1], rect=[eerste,-0.7,laatste,0.7]);
plot2d(x(:,1)/2000, x(:,40), style=[5], rect=[eerste,-0.7,laatste,0.7]);
plot2d(x(:,1)/2000, x(:,41), style=[3], rect=[eerste,-0.7,laatste,0.7]);
xtitle('Position setpoints');
xgrid(1);

//xsetech([0.5,0.,0.5,0.5]);
subplot(222);

plot2d(x(:,1)/2000, x(:,45), style=[1], rect=[eerste,-1,laatste,1]);
plot2d(x(:,1)/2000, x(:,46), style=[5], rect=[eerste,-1,laatste,1]);
plot2d(x(:,1)/2000, x(:,47), style=[3], rect=[eerste,-1,laatste,1]);
xtitle('Velocity setpoints');
xgrid(1);

//xsetech([0.,0.5,0.5,0.5]);
subplot(223);

plot2d(x(:,1)/2000, x(:,42)*57.324840764, style=[1], rect=[eerste,-15,laatste,15]);
plot2d(x(:,1)/2000, x(:,43)*57.324840764, style=[5], rect=[eerste,-15,laatste,15]);
plot2d(x(:,1)/2000, x(:,44)*57.324840764, style=[3], rect=[eerste,-15,laatste,15]);
xtitle('Euler angle setpoints');
xgrid(1);

//xsetech([0.5,0.5,0.5,0.5]);
subplot(224);

legends(['x';'y';'z';'phi';'theta';'psi';'x_meas';'y_meas';'z_meas'],[1 5 3 1 5 3 2 4 6], 4)

xset("window", 3)

//xsetech([0.,0.,0.5,0.5]);
subplot(221);

z_offset=-2.70608;
plot2d(x(:,1)/2000, x(:,57)+z_offset, style=[1], rect=[eerste,-0.7,laatste,0.7]);
plot2d(x(:,1)/2000, x(:,58)+z_offset, style=[2], rect=[eerste,-0.7,laatste,0.7]);
plot2d(x(:,1)/2000, x(:,59)+z_offset, style=[3], rect=[eerste,-0.7,laatste,0.7]);
plot2d(x(:,1)/2000, x(:,60)+z_offset, style=[4], rect=[eerste,-0.7,laatste,0.7]);
plot2d(x(:,1)/2000, x(:,61)+z_offset, style=[5], rect=[eerste,-0.7,laatste,0.7]);
plot2d(x(:,1)/2000, x(:,62)+z_offset, style=[6], rect=[eerste,-0.7,laatste,0.7]);
xtitle('Jack setpoints');
xgrid(1);

//xsetech([0.5,0.,0.5,0.5]);
subplot(222);

plot2d(x(:,1)/2000, x(:,63), style=[1], rect=[eerste,-1,laatste,1]);
plot2d(x(:,1)/2000, x(:,64), style=[2], rect=[eerste,-1,laatste,1]);
plot2d(x(:,1)/2000, x(:,65), style=[3], rect=[eerste,-1,laatste,1]);
plot2d(x(:,1)/2000, x(:,66), style=[4], rect=[eerste,-1,laatste,1]);
plot2d(x(:,1)/2000, x(:,67), style=[5], rect=[eerste,-1,laatste,1]);
plot2d(x(:,1)/2000, x(:,68), style=[6], rect=[eerste,-1,laatste,1]);
xtitle('Jack velocity setpoints');
xgrid(1);

//xsetech([0.,0.5,0.5,0.5]);
subplot(223);

plot2d(x(:,1)/2000, x(:,69), style=[1], rect=[eerste,-10,laatste,10]);
plot2d(x(:,1)/2000, x(:,70), style=[2], rect=[eerste,-10,laatste,10]);
plot2d(x(:,1)/2000, x(:,71), style=[3], rect=[eerste,-10,laatste,10]);
plot2d(x(:,1)/2000, x(:,72), style=[4], rect=[eerste,-10,laatste,10]);
plot2d(x(:,1)/2000, x(:,73), style=[5], rect=[eerste,-10,laatste,10]);
plot2d(x(:,1)/2000, x(:,74), style=[6], rect=[eerste,-10,laatste,10]);
xtitle('Jack acceleration setpoints excl. limiting');
xgrid(1);

//xsetech([0.5,0.5,0.5,0.5]);
subplot(224);

legends(['1';'2';'3';'4';'5';'6'],[1 2 3 4 5 6], 4)

xset("window", 4)

//xsetech([0.,0.,0.5,0.5]);
subplot(121);

plot2d(x(:,1)/2000, x(:,81), style=[1], rect=[eerste,-0.01,laatste,0.01]);
plot2d(x(:,1)/2000, x(:,82), style=[2], rect=[eerste,-0.01,laatste,0.01]);
plot2d(x(:,1)/2000, x(:,83), style=[3], rect=[eerste,-0.01,laatste,0.01]);
xtitle('Motion Filter User Data 1-3');
xgrid(1);

subplot(122);
plot2d(x(:,1)/2000, x(:,84)*57.324840764, style=[4], rect=[eerste,-0.15,laatste,0.15]);
plot2d(x(:,1)/2000, x(:,85)*57.324840764, style=[5], rect=[eerste,-0.15,laatste,0.15]);
plot2d(x(:,1)/2000, x(:,86)*57.324840764, style=[6], rect=[eerste,-0.15,laatste,0.15]);
xtitle('Motion Filter User Data 4-6');

xgrid(1);

legends(['1';'2';'3';'4';'5';'6'],[1 2 3 4 5 6], 4)

//chdir('/home/simona/GLT1/scilab');

