//Author: Sebastian Roman (Programming Lead)
//Co Author: 3229 Programming

#ifndef FEEDER_H
#define FEEDER_H

#pragma once

//phoenix motor controller includes 
#include <ctre/Phoenix.h>
#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>
#include "Debug.h"

class Feeder
{
private:
    ctre::phoenix::motorcontrol::can::WPI_TalonSRX * m_feederMotor;
    
    const int kfeederMotorID = 11; 
    const double FEEDER_POWER_IN = -.8; //80 percent power
    const double FEEDER_POWER_OUT = .8;
public:
    Feeder();
    ~Feeder();

    void runFeeder();
    void reverseFeeder();

    void stopFeeder();
};

class UpperFeeder
{
    private:
    ctre::phoenix::motorcontrol::can::WPI_TalonSRX * m_upperfeederMotor;
    
    const int kupperfeederMotorID = 10; 
    const double UPPER_FEEDER_POWER_IN = -.9; // was previously at 80 percent power 
    const double UPPER_FEEDER_POWER_OUT = .9;
public:
    UpperFeeder();
    ~UpperFeeder();

    void runUpperFeeder();
    void reverseUpperFeeder();

    void stopUpperFeeder();


}; 

#endif