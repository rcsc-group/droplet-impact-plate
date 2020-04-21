/* force.c
    Basilisk script to test the force calculation. We set a uniform grid with a 
    prescribed pressure across the domain which only depends on the radial 
    coordinate. We calculate the force on the bottom of the domain by 
    approximating a surface integral in cylindrical coordinates using 
    trapazoidal rule.
*/

#include "navier-stokes/centered.h"
#include "axi.h"
#include "parameters.h"

double force(); // C function for calculating the force
double pressure(double rr, double tt); // Prescribed pressure 

int gfs_output_no = 1;
int plate_output_no = 1;

FILE * force_file;

int main() {

    init_grid(1 << LEVEL);
    size(BOX_WIDTH);

    force_file = fopen("force_file.txt", "w");
    run();
}

event update_pressure(t += TIMESTEP) {
/* Updates the pressure across the domain */
    foreach() {
        p[] = exp(-(y - t));
    }
}

// event gfs_output (t += TIMESTEP) {
//     char gfs_filename[80];
//     sprintf(gfs_filename, "gfs_output_%d.gfs", gfs_output_no);
//     output_gfs(file = gfs_filename);
//     gfs_output_no++;
// }

event output_force (t += TIMESTEP) {
    /* Numeric force */
    double force_value = 0.;
    foreach_boundary(left, reduction(+:force_value)) {
        force_value += Delta * y * p[1, 0];
    }
    force_value = 2 * pi * force_value; // Integrates angularly

    /* Analytic force */
    double analytic_force = \
        2 * pi * (exp(t) - (BOX_WIDTH + 1) * exp(t - BOX_WIDTH));

    /* Prints force to file */
    fprintf(force_file, "%g, %g, %g\n", t, force_value, analytic_force);
}

event end(t = MAX_TIME) {
    fclose(force_file);
}

double pressure(double rr, double tt) {
/* Prescribed pressure across the domain as a function of the radial coordinate,
rr and the time, tt. */
    return exp(-(rr - tt));
}
