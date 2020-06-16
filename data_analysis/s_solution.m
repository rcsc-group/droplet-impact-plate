function [t, s, sdot, sddot] = s_solution(t_max, alpha, beta, gamma, eps)

addpath("forces");
addpath("pressures");


%% Early time limit
% Making the approximation alpha s ~ eps * (8 sqrt(3))/5 (t - s)^5/2 for
% early times, we calculate an early time limit for s and its derivatives
t0 = 1e-9; % Small time limit
options = optimoptions('fsolve','OptimalityTolerance', 1e-10);

% Solve for s0
s_fun = @(s) alpha * s - eps * (8 * sqrt(3) / 5) * (t0 - s).^(5/2);
s0 = fsolve(s_fun, 1e-10, options);

% Solve for sdot0
sdot_fun = @(sdot) alpha * sdot ...
    - eps * 4 * sqrt(3) * (1 - sdot) * (t0 - s0).^(3/2);
sdot0 = fsolve(sdot_fun, 0, options)

% Solve for sddot0
sddot_fun = @(sddot) alpha * sddot ...
    - eps * 2 * sqrt(3 * (t0 - s0)) * (3 * (1 - sdot0)^2 - 2 * sddot * (t0 - s0));
sddot0 = fsolve(sddot_fun, 0, options)

%% ODE solving
% Cantilever ODE
cant_ode = @(t, y, yp) [yp(1) - y(2); ...
    alpha * yp(2) + beta * yp(1) + gamma * y(1) ...
        - composite_force(t, y(1), yp(1), yp(2), eps) / alpha];
    
% Limits for time
tspan = [t0 t_max];

% Initial conditions for s
y0 = [s0; sdot0];
yp0 = [sdot0; sddot0];

% Use ODE15s to solve
[t, y] = ode15i(cant_ode, tspan, y0, yp0, options);

% Saves s and its derivatives
s = y(:, 1);
sdot = y(:, 2);
sddot = diff(sdot) ./ diff(t);

end