#include "Feeder.h"

//Polycoord Feeder
Feeder::Feeder()
{
    m_feederMotor = new ctre::phoenix::motorcontrol::can::WPI_TalonSRX(kfeederMotorID);
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


