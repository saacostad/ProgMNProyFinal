// INCLUDE STANDARD LIBRARIES
#include <iostream>
#include <random>
#include <vector>
#include <string.h>

// INCLUDE HEADERS
#include "classes/constants.h"
#include "classes/ball.h"
#include "classes/world_generation.h"
 

void calculate_forces(Ball &particle);
void print_results(double time, Ball particle);

int main (int argc, char *argv[])
{
    // CHECK IF PARAMETERS INPUT IS DONE CORRECTLY
    if ( ((argc - 1) % 2) != 0  )
    {
        std::cout << "INVALID PARAMETERS INPUT, SHOULD BE \" -parameter parameter_value \". \n "
        " Example: \" source.exe -radious 10 \" " << std::endl;

        return 1;
    }

    // GENERATE THE SCENARIO DEPENDING ON THE INPUTS GIVEN IN THE CONSOLE
    generate_world(argc, argv);

    double time = 0;
    double dt = 0.01;
    double sec = 5;

    auto p = generate_ball();

    for (int i = 0; i < (sec / dt); i++)
    {
        print_results(i * dt, p);

        calculate_forces(p);
        p.calculate_vel(dt);
        p.calculate_pos(dt);

    }


    return 0;

}

void calculate_forces(Ball &particle)
{
    // Reset the forces of the particle
    particle.reset_forces();

    // All time, the particle is interacting with gravity, so one force
    // acting constantly is gravity

    particle.az = G;

    // Now lets check if the particle is interacting with any of the walls
    double delta;

    // For left wall
    delta = particle.x - particle.radio;
    if (delta < 0)
    {
        particle.ax += -K * delta; 
    }

    // For right wall
    delta = particle.x + particle.radio - WORLD_WIDTH;
    if (delta > 0)
    {
        particle.ax += -K * delta;
    }

    // For front wall
    delta = particle.y - particle.radio;
    if (delta < 0)
    {
        particle.ay += -K * delta;
    }

    // For back wall
    delta = particle.y + particle.radio - WORLD_DEPTH;
    if (delta > 0)
    {
        particle.ay += -K * delta;
    }

    // For the roof
    delta = particle.z + particle.radio - WORLD_HEIGHT;
    if (delta > 0)
    {
        particle.az += -K * delta;
    }

    // For the floor
    delta = particle.z - particle.radio;
    if (delta < 0)
    {
        particle.az += -K * delta;
    }

}

void print_results(double time, Ball particle)
{
    std::cout << time << " " 
    << particle.x << " " 
    << particle.y << " "
    << particle.z << std::endl;
}