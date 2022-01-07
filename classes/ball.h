#pragma once

class Ball
{
    public:
        
        // values of each one of the balls
        double radio, x, y, z;
        double vx, vy, vz;
        double ax, ay, az;
        double fx, fy, fz;
        double mass;

        // contructor function, sets the position and different velocities of the ball


        Ball(double r, double _x, double _y, double _z, double _vx, double _vy, double _vz, double mass)
        {
            radio = r;
            
            this->x = _x; this->y = _y; this->z = _z;
            this->vx = _vx;  this->vy = _vy; this->vz = _vz; 
            this->mass = mass;
        }

        // function that resets the forces
        void reset_forces()
        {
            this->fx = 0; this->fy = 0; this->fz = 0;
        }

        void calculate_acc(double dt)
        {
            this->ax = this->mass * fx;
            this->ay = this->mass * fy;
            this->az = this->mass * fz;
        }

        void calculate_vel(double dt)
        {
            this->vx += ax * dt;
            this->vy += ay * dt;
            this->vz += az * dt;
        }

        void calculate_pos(double dt)
        {
            this->x += vx * dt;
            this->y += vy * dt;
            this->z += vz * dt;
        }

};