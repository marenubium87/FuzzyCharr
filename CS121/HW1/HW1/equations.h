/* Header file for equations used in PA2 */

#define _CRT_SECURE_NO_WARNINGS

/*  Calculates the force given a mass and an acceleration via Newton's 2nd law */
double calculate_newtons_2nd_law(double mass, double acceleration);

/*  Calculates the volume of a cylinder given radius and height */
double calculate_volume_cylinder(double radius, double height);

/*  Character encoding based on directions in PA2 */
char perform_character_encoding(char plaintext_character);

/*  Calculates gravitational force between mass1 and mass2
    and separated by distance using Newton's law of gravitation  */
double calculate_gravity_force(double mass1, double mass2, double distance);

/*  Calculates vout bases on resistances and vin, given by eqn in problem statement.*/
double calculate_resistive_divider(double resistance1, double resistance2, double vin);

/*  Calculates distance btwn 2 points using the midpoint formula.
    Note here the order of variables that need to be entered into the function -
	needs to be x1 x2 y1 y2, not the perhaps more intuitive x1 y1 x2 y2  */
double calculate_distance_between_2pts(double x1, double x2, double y1, double y2);

/*  Calculates the value of the equation as defined in PA2 */
double calculate_general_equation(int a, double x, double z);