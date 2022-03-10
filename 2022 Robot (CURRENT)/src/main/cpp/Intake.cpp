#include "Intake.h"

//Intake Indexer 
Intake::Intake()
{
    m_intakeMotor = new ctre::phoenix::motorcontrol::can::WPI_TalonSRX(kIntakeMotorID);
    m_intakeMotor->ClearStickyFaults();

    m_intakePivot = new rev::CANSparkMax(kIntakePivotMotorID,rev::CANSparkMax::MotorType::kBrushless);

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

void Intake::runIntakePivot()
    {
        m_intakePivot->Set(INTAKE_PIVOT_POWER_IN);
    }


void Intake::reverseIntakePivot(){
        m_intakePivot->Set(INTAKE_PIVOT_POWER_OUT);
}
void Intake::stopPivot()
{

    m_intakePivot->StopMotor();
}

