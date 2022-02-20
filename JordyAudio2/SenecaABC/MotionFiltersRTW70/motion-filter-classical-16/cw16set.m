% Classical Washout Filter Values
%
% This file contains required parameters for
% a motion filter.
%
%------------------------------------------------------------
% (c) Bas Gouverneur, February 2003
%  modified Olaf Stroosma, March 2006
%------------------------------------------------------------

%------------------------------------------------------------
% General parameters
%------------------------------------------------------------
g = 9.80665;
LZDERPUGP = 1.2075;

%------------------------------------------------------------
% Reference points, relative to UGP.
% Aircraft motion is transformed from aircraft reference point
% to filter reference point before filtering.
% Simulator motion is then transformed from filter reference
% point to the motion base reference point (=UGP).
%
% Use ref_ac = (0,0,-1.2075) and ref_filt = (0,0,0) for
% behaviour of cw08 and earlier.
% Use ref_ac = (0,0,-1.2075) and ref_filt = (0,0,-1.2075) for
% doing everything in DERP.
%------------------------------------------------------------
xref_ac = 0.0;
yref_ac = 0.0;
zref_ac = -1.2075;

xref_filt = 0.0;
yref_filt = 0.0;
zref_filt = 0.0;

%------------------------------------------------------------
% Feedback parameters for synchronization with motion limiter
%------------------------------------------------------------

Kfeedbackx = 0.5;
Kfeedbackxd = 0.1;
Kfeedbackeuler = 0.2;
Kfeedbackeulerrate = 0.5;

%------------------------------------------------------------
% Controller parameters for achieving tilt coordination
% Available methods:
% 1) straight differentiation (Bas)
% 2) differentiation with rate limit compensation (Herman)
% 3) sim state feedback controller (Olaf)
%------------------------------------------------------------
tiltcoordinationmethod = 1;
Ktiltrate = 5.0; % method 2
Ktilteuler = 0.2; % method 3
Ktilteulerrate = 0.5; % method 3

%------------------------------------------------------------
% Motion Filter channel selection gains (select 0 or 1)
%------------------------------------------------------------

gainfx = 1;
gainfy = 1;
gainfz = 1;

gainfxtilt = 1;
gainfytilt = 1;

gainp = 1;
gainq = 1;
gainr = 1;

%------------------------------------------------------------
% Motion Filter Gains (k)
%------------------------------------------------------------

kfx = 0.6;
kfy = 0.6;
kfz = 0.5;

kwp = 0.6;
kwq = 0.6;
kwr = 0.6;

kf = [kfx 0 0; 0 kfy 0; 0 0 kfz];
kw = [kwp 0 0; 0 kwq 0; 0 0 kwr];

%------------------------------------------------------------
% Motion Filter 2nd order Break-Frequencies (omega_n)
% (set to zero for 1st order only)
%------------------------------------------------------------

HPomeganx     = 0.8;
HPomegany     = 1.0;
HPomeganz     = 1.0;

LPomeganx     = 2.0;
LPomegany     = 2.0;

HPomeganphi   = 1.0;
HPomegantheta = 0.8;
HPomeganpsi   = 1.0;

%------------------------------------------------------------
% Motion Filter 1st order Break-Frequencies (omega_b)
% (set to zero for 2nd order only)
%------------------------------------------------------------

HPomegabx     = 0.0;
HPomegaby     = 0.0;
HPomegabz     = 0.2;

HPomegabphi   = 0.0;
HPomegabtheta = 0.0;
HPomegabpsi   = 0.0;

%------------------------------------------------------------
% Motion Filter Damping Coefficients (zeta)
%------------------------------------------------------------

HPzetax     = 1.0;
HPzetay     = 1.0;
HPzetaz     = 1.0;

LPzetax     = 1.0;
LPzetay     = 1.0;

HPzetaphi   = 1.0;
HPzetatheta = 1.0;
HPzetapsi   = 1.0;


%------------------------------------------------------------
% Tilt coordination angular rate limit (deg/sec)
%------------------------------------------------------------

Beta_rate = 3*(pi/180);