#pragma once 

#include <string.h> 
#include <random>
#include <vector>
#include <iostream>

#include "constants.h"
#include "ball.h"

// --------- EDIT FOR NEW INPUTS ------------
// array with all the correct possible inputs
std::string valid_inputs[] = {"-radious", "-wheight", "-wwidth", "-gravity", "-restitution", "-np", "-wdepth"};

// array that will store incorrect input (if there's any) to show in the console
std::vector<std::string> incorrect_inputs;

// keeps track if there's an invalid input
bool incorrect_input_boolean = false;

// array that contains all the balls
std::vector<Ball> particles;


// ------------ EDIT FOR NEW INPUTS ----------------------------
// Function that recieves a string with the parameter name and overwrites the constant with 
// the one in the input
void write_parameter(std::string param, const char* value)
{
    if (param == "-radious")
    {
        RADIOUS = std::atof(value);
    }

    if (param == "-wheight")
    {
        WORLD_HEIGHT = std::atof(value);
    }

    if (param == "-wwidth")
    {
        WORLD_WIDTH = std::atof(value);
    }

    if (param == "-gravity")
    {
        G = std::atof(value);
    }

    if (param == "-restitution")
    {
        K = std::atof(value);   
    }

    if (param == "-np")
    {
        NO_BALLS = std::atoi(value);
    }

    if (param == "-wdepth")
    {
        WORLD_DEPTH = std::atof(value);
    }
}


// GENERATES A RANDOM PLACED BALL
Ball generate_ball()
{
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    std::random_device rd;

    double x, y, z, vx, vy, vz;

    x = dist(rd) * WORLD_WIDTH;
    y = dist(rd) * WORLD_DEPTH;
    z = dist(rd) *  WORLD_HEIGHT;

    vx = dist(rd) * WORLD_WIDTH / 2;
    vy = dist(rd) * WORLD_DEPTH / 2;
    vz = dist(rd) * WORLD_HEIGHT / 2;

    return (Ball(RADIOUS, x, y, z, vx, vy, vz));
}

// Function that takes the console inputs and proccess it in order to overwrite the constants 
// and generates the world
void generate_world(int argc, char *argv[])
{
    // CHECK IF INPUT IS CORRECT
    for (int i = 1; i < argc; i += 2)
    {   
        // flag to know if the input is valid or not
        bool valid = false;

        // check if the input matches with any of the valid inputs
        for (auto par : valid_inputs)
        {
            if (par == argv[i])
            {
                valid = true;
                break;
            }
        }
        
        // if there's a match, overwrite the constant
        if (valid)
        {
            write_parameter(argv[i], argv[i + 1]);
        }
        else // if not, activate the incorrect input flag and add the string to the
        {    // array of incorrect inputs
            incorrect_input_boolean = true;
            incorrect_inputs.push_back(argv[i]);
        }
    }

    // if there are incorrect inputs, print them on the screen so the user
    // knows where's the mistake
    if (incorrect_inputs.size() > 0)
    {

        std::cout << "INVALID PARAMETERS INPUT: \n";

        for (auto inco : incorrect_inputs)
        {
            std::cout << inco << std::endl;
        }

        // and also print all the correct possible inputs
        std::cout << "TRY USING CORRECT PARAMETERS INSTEAD: \n";

        for (auto corr : valid_inputs)
        {
            std::cout << corr << std::endl;
        }

    }

    // generate all the balls to play with
    for (int i = 1; i <= NO_BALLS; i++)
    {
        particles.push_back(generate_ball());
    }

}

