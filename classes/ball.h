#pragma once

class Ball
{
    public:
        
        // values of each one of the balls
        double radio, x, y, z;
        double vx, vy, vz;
        double ax, ay, az;

        // contructor function, sets the position and different velocities of the ball


        Ball(double r, double _x, double _y, double _z, double _vx, double _vy, double _vz)
        {
            radio = r;
            
            x = _x; y = _y; z = _z;
            vx = _vx;  vy = _vy; vz = _vz; 
        }

        // function that resets the forces
        void reset_forces()
        {
            ax = 0; ay = 0; az = 0;
        }

        void calculate_vel(double dt)
        {
            vx += ax * dt;
            vy += ay * dt;
            vz += az * dt;
        }

        void calculate_pos(double dt)
        {
            x += vx * dt;
            y += vy * dt;
            z += vz * dt;
        }

};