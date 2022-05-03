//Author: Sebastian Roman (Programming Lead)
//Co Author: 3229 Programming

#include "Feeder.h"

//Polycoord Feeder
Feeder::Feeder()
{
    m_feederMotor = new ctre::phoenix::motorcontrol::can::WPI_TalonSRX(kfeederMotorID);
    m_feederMotor->ClearStickyFaults();
   
}   

Feeder::~Feeder()
{
    delete m_feederMotor;
}

void Feeder::runFeeder()
{
    m_feederMotor->Set(FEEDER_POWER_IN);
}

void Feeder::reverseFeeder()
{
    m_feederMotor->Set(FEEDER_POWER_OUT);
}

void Feeder::stopFeeder()
{
    m_feederMotor->StopMotor();
}

//Upper Feeder 

UpperFeeder::UpperFeeder()
{
    m_upperfeederMotor = new ctre::phoenix::motorcontrol::can::WPI_TalonSRX(kupperfeederMotorID);
    m_upperfeederMotor->ClearStickyFaults();
}

UpperFeeder::~UpperFeeder()
{
    delete m_upperfeederMotor;
}

void UpperFeeder::runUpperFeeder()
{
    m_upperfeederMotor->Set(UPPER_FEEDER_POWER_IN);
}

void UpperFeeder::reverseUpperFeeder()
{
    m_upperfeederMotor->Set(UPPER_FEEDER_POWER_OUT);
}

void UpperFeeder::stopUpperFeeder()
{
    m_upperfeederMotor->StopMotor();
}


