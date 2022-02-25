#include "Intake.h"

//Intake Indexer 
Intake::Intake()
{
    m_intakeMotor = new ctre::phoenix::motorcontrol::can::WPI_TalonSRX(kIntakeMotorID);
}

Intake::~Intake()
{
    delete m_intakeMotor;
}

void Intake::runIntake()
{
    m_intakeMotor->Set(INTAKE_POWER_IN);
}

void Intake::reverseIntake()
{
    m_intakeMotor->Set(INTAKE_POWER_OUT);
}

void Intake::stopIntake()
{
    m_intakeMotor->StopMotor();
}

//Feeder 
