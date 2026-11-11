%% DC and AC load lines in the IC-VCE plane
clear; clc; close all;

%% Given intercepts
Vdc_max = 10;              % DC line, VCE intercept (V)
Idc_max = 625.860558e-6;   % DC line, IC intercept (A)
Vac_max = 5.5558;          % AC line, VCE intercept (V)
Iac_max = 925.966667e-6;   % AC line, IC intercept (A)

%% Resistances implied by the slopes
R_dc = Vdc_max / Idc_max;  % RC + RE/alpha  (about 15.98 kOhm)
r_ac = Vac_max / Iac_max;  % RC || RL       (about 6 kOhm)

%% Q-point = intersection of the two lines
% (Vdc_max - V)/R_dc = (Vac_max - V)/r_ac
VCEQ = (R_dc*Vac_max - Vdc_max*r_ac) / (R_dc - r_ac);
ICQ  = (Vdc_max - VCEQ) / R_dc;

%% Maximum symmetric swing: VCEQ - VCEsat = ICQ*r_ac
swing = ICQ * r_ac;
VCEsat = VCEQ - swing;     % equals 2*VCEQ - Vac_max

fprintf('R_dc   = %.1f Ohm\n', R_dc);
fprintf('r_ac   = %.1f Ohm\n', r_ac);
fprintf('VCEQ   = %.4f V\n', VCEQ);
fprintf('ICQ    = %.2f uA\n', ICQ*1e6);
fprintf('VCEsat = %.4f V\n', VCEsat);
fprintf('Swing  = +/- %.3f V\n', swing);

%% Load lines (IC in mA)
vce    = linspace(0, Vdc_max, 500);
ic_dc  = (Vdc_max - vce) / R_dc * 1e3;
vce_ac = linspace(0, Vac_max, 500);
ic_ac  = (ICQ + (VCEQ - vce_ac) / r_ac) * 1e3;

blue   = [0.22 0.54 0.87];
orange = [0.85 0.35 0.19];
gray   = [0.45 0.45 0.45];

%% Plot
figure('Color','w','Position',[100 100 900 620]); hold on; grid on; box on;
plot(vce,    ic_dc, 'Color', blue,   'LineWidth', 2.5);
plot(vce_ac, ic_ac, 'Color', orange, 'LineWidth', 2.5);

% Q-point and drop lines
plot([0 VCEQ],   [ICQ ICQ]*1e3, '--', 'Color', gray);
plot([VCEQ VCEQ],[0 ICQ]*1e3,   '--', 'Color', gray);
plot(VCEQ, ICQ*1e3, 'o', 'MarkerSize', 9, 'MarkerFaceColor', gray, 'MarkerEdgeColor', gray);

% VCE(sat) marker
plot([VCEsat VCEsat], [0 1.0], '--', 'Color', gray);
text(VCEsat + 0.1, 0.05, 'V_{CE(sat)}', 'Color', gray);

% Cutoff end of the AC line
plot(Vac_max, 0, 'o', 'MarkerSize', 6, 'MarkerFaceColor', orange, 'MarkerEdgeColor', orange);
text(Vac_max, 0.05, sprintf('cutoff end, %.2f V', Vac_max), ...
     'HorizontalAlignment', 'center', 'Color', gray);

% Labels
text(VCEQ + 0.1, ICQ*1e3 + 0.07, ...
     sprintf('Q: %.2f V, %.3f mA', VCEQ, ICQ*1e3), 'FontWeight', 'bold');
text(0.6, 0.88, 'AC load line, slope -1/(R_C||R_L)', 'Color', orange, 'FontWeight', 'bold');
text(6.0, 0.30, 'DC load line, slope -1/(R_C+R_E/\alpha)', 'Color', blue, 'FontWeight', 'bold');

% Axes
xlabel('V_{CE} (V)'); ylabel('I_C (mA)');
title('DC and AC load lines');
xlim([0 10]); ylim([0 1.0]);
set(gca, 'FontSize', 12, 'XTick', 0:2:10, 'YTick', 0:0.2:1.0);

%% Swing arrows below the x-axis
ya = -0.13;
set(gca, 'Clipping', 'off');
plot([VCEsat VCEQ],  [ya ya], '-', 'Color', gray, 'Clipping', 'off');
plot([VCEQ Vac_max], [ya ya], '-', 'Color', gray, 'Clipping', 'off');
plot(VCEsat,  ya, '<', 'Color', gray, 'MarkerFaceColor', gray, 'MarkerSize', 5, 'Clipping', 'off');
plot(VCEQ,    ya, 'd', 'Color', gray, 'MarkerFaceColor', gray, 'MarkerSize', 4, 'Clipping', 'off');
plot(Vac_max, ya, '>', 'Color', gray, 'MarkerFaceColor', gray, 'MarkerSize', 5, 'Clipping', 'off');
text((VCEsat+VCEQ)/2,  ya - 0.06, sprintf('V_{CEQ} - V_{CE(sat)} = %.2f V', swing), ...
     'HorizontalAlignment', 'center', 'Clipping', 'off');
text((VCEQ+Vac_max)/2, ya - 0.06, sprintf('I_{CQ}\\cdot r_{ac} = %.2f V', swing), ...
     'HorizontalAlignment', 'center', 'Clipping', 'off');