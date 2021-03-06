#include "Pivot.h"

Pivot::Pivot()
{

    m_pivotMotor = new ctre::phoenix::motorcontrol::can::WPI_TalonSRX(kPivotMotorID);
    m_pivotPID = new frc2::PIDController(kP,kI,kD);
    m_pivotEncoder = new frc::AnalogEncoder(pivotEncID);
    m_pivotPID->SetTolerance(kNOMINAL_TX_ERROR);
    m_pivotEncoder->Reset();

    
    m_pivotMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 10); //ctre mag encoder 
    m_pivotMotor->SetSensorPhase(true);
    m_pivotMotor->SetSelectedSensorPosition(0); //resets encoder to 0 and makes sure the values is zero upon startup 

    
    m_pivotMotor->ClearStickyFaults();
}
Pivot::~Pivot()
{;
    delete m_pivotMotor;
    delete m_pivotPID;
    delete m_pivotEncoder;
}


void Pivot::Turn(double setPower)
{
     if (abs(GetAngle() - MAX_PIVOT_ANGLE) > 500) {
     
        m_pivotMotor->Set(std::clamp(-setPower,-kMAX_PIVOT_POWER,kMAX_PIVOT_POWER));
    }
    else if (abs(GetAngle() - MIN_PIVOT_ANGLE > 500)) {

        m_pivotMotor->Set(std::clamp(setPower,-kMAX_PIVOT_CORRECT_POWER,kMAX_PIVOT_CORRECT_POWER));
    }
}


double Pivot::GetAngle()
{
     double pivotAngleActual = 0.0;
    
    pivotAngleActual = m_pivotMotor->GetSelectedSensorPosition();
    

    return (pivotAngleActual);
   
}


