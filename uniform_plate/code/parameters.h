/* parameters.h
Header file for the parameters to feed into the simulations for droplet impact*/

/* Physical constants */
const double RHO_R = 0.003; // Density ratio
const double MU_R = 0.002; // Viscosity ratio
const double REYNOLDS = 1000.0; // Reynolds number
const double WEBER = 1000.0; // Weber number
const double FR = 10.1; // Froude number
const double DROP_VEL = -1.0; // Initial velocity of the droplet 
const double PLATE_VEL = -0.1; // Constant velocity of the plate
const double DROP_RADIUS = 1.0; // Radius of droplet
const double DROP_CENTRE = 2.125; // Initial centre position of droplet
const double INITIAL_PLATE_TOP = 1.0; // Initial top of plate 
const double PLATE_WIDTH = 3.0; // Width of plate (horizontal direction)
const double PLATE_THICKNESS = 0.15; // Thickness (vertical direction)

/* Computational constants */
const int MINLEVEL = 4; // Minimum refinement level 
const int MAXLEVEL = 12; // Maximum refinement level
const double BOX_WIDTH = 4.0; // Width of the computational box
