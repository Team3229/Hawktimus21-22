#include "Intake.h"

//Intake Indexer 
Intake::Intake()
{
    m_intakeMotor = new ctre::phoenix::motorcontrol::can::WPI_TalonSRX(kIntakeMotorID);
    m_intakeMotor->ClearStickyFaults();

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

IntakePivot::IntakePivot(){

     m_intakePivot = new ctre::phoenix::motorcontrol::can::WPI_TalonSRX(kIntakePivotMotorID);
    m_intakePivot->ClearStickyFaults();
      
      
}

IntakePivot::~IntakePivot(){

 delete m_intakePivot;
}

void IntakePivot::runIntakePivot()
    {
        m_intakePivot->Set(INTAKE_PIVOT_POWER_IN);
    }


void IntakePivot::reverseIntakePivot(){
        m_intakePivot->Set(INTAKE_PIVOT_POWER_OUT);
}
void IntakePivot::stopPivot()
{

    m_intakePivot->StopMotor();
}

