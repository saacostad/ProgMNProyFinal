// INCLUDE STANDARD LIBRARIES
#include <iostream>
#include <random>
#include <vector>
#include <array>
#include <string.h>
#include <cmath>

// INCLUDE HEADERS
#include "classes/constants.h"
#include "classes/ball.h"
#include "classes/world_generation.h"
#include "classes/vector3.h"
 

void calculate_forces(Ball &particle);
void check_collitions(Ball &p1, Ball &p2);
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
    double sec = 10;

    for (int i = 0; i < (sec / dt); i++)
    {
        for (auto &particle : particles)
        {
            calculate_forces(particle);
            particle.calculate_acc(dt);
            particle.calculate_vel(dt);
            particle.calculate_pos(dt);

            print_results(i*dt, particle);
        }

    }


    return 0;

}

void calculate_forces(Ball &particle)
{
    // Reset the forces of the particle
    particle.reset_forces();

    // All time, the particle is interacting with gravity, so one force
    // acting constantly is gravity

    if (particle.z - particle.radio > 0)
    {
        particle.fz = particle.mass * G;
    }

    // Now lets check if the particle is interacting with any of the walls
    double delta;

    // For left wall
    delta = particle.x - particle.radio;
    if (delta < 0)
    {
        particle.fx += -K * delta; 
    }

    // For right wall
    delta = particle.x + particle.radio - WORLD_WIDTH;
    if (delta > 0)
    {
        particle.fx += -K * delta;
    }

    // For front wall
    delta = particle.y - particle.radio;
    if (delta < 0)
    {
        particle.fy += -K * delta;
    }

    // For back wall
    delta = particle.y + particle.radio - WORLD_DEPTH;
    if (delta > 0)
    {
        particle.fy += -K * delta;
    }

    // For the roof
    delta = particle.z + particle.radio - WORLD_HEIGHT;
    if (delta > 0)
    {
        particle.fz += -K * delta;
    }

    // For the floor
    delta = particle.z - particle.radio;
    if (delta < 0)
    {
        particle.fz += -K * delta;
    }

    // Check for collitions with other balls
    for (auto p1 : particles)
    {
        for (auto p2 : particles)
        {   
            // if both parti les are the same, jut continue
            if (&p1 == &p2)
            {
                continue;
            } else
            {
                // Else, check if there's a collition
                check_collitions(p1, p2);
            }
        }
    }

}

// Function that checks if 2 particles are colliding with each other and calculate it's forces
void check_collitions(Ball &p1, Ball &p2)
{
    // check the distance between the center of the spheres
    double dist = std::sqrt( std::pow((p1.x - p2.x), 2) + std::pow((p1.y - p2.y), 2) + std::pow((p1.z - p2.z), 2) );

    // if the distance is less than the sum of the radios, both balls are touching
    if (dist < (p1.radio + p2.radio))
    {
        std::cout << "COLITION\n";
        Vector3 vec2_1 = { (p1.x - p2.x), (p1.y - p2.y), (p1.z - p2.z) };
        vec2_1 = vec2_1.normalize();

        double delta = p1.radio - (dist - p2.radio);
        double force = -K * delta;

        Vector3 forceP1 = force * vec2_1;
        Vector3 forceP2 = force * (-1.0 * vec2_1);

        p1.fx = forceP1.a;
        p1.fy = forceP1.b;
        p1.fz = forceP1.c;
        
        p2.fx = forceP2.a;
        p2.fy = forceP2.b;
        p2.fz = forceP2.c;
    }
}

void print_results(double time, Ball particle)
{
    std::cout << time << "  "
    << particle.x << "  " 
    << particle.y << "  "
    << particle.z << std::endl;
}