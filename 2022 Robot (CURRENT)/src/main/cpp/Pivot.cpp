#include "Pivot.h"


Pivot::Pivot()
{

    m_pivotMotor = new ctre::phoenix::motorcontrol::can::WPI_TalonSRX(kPivotMotorID);
    m_pivotPID = new frc2::PIDController(kP,kI,kD);

    //pivot encoder 

    m_pivotMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 10); //ctre mag encoder 
    m_pivotMotor->SetSensorPhase(true);

    m_pivotMotor->ClearStickyFaults();


}

Pivot::~Pivot()
{;
    delete m_pivotMotor;
    delete m_pivotPID;
   \
}


void Pivot::Turn(double setPower) //make sure to implement before competitions! 
{
    //limits pivot turn range
    if (std::abs(GetAngle()) < kMAX_RANGE.to<double>()){
     
        m_pivotMotor->Set(std::clamp(-setPower,-kMAX_PIVOT_POWER,kMAX_PIVOT_POWER));
    }else{
        //prevent locking of the pivot
        m_pivotMotor->Set(std::clamp(setPower,-kMAX_PIVOT_CORRECT_POWER,kMAX_PIVOT_CORRECT_POWER));
    }
}


/**
 * ratio of angle:encoder is 73.17:1
 * GetDistance() start: 0, left 90: -1.23, right 90: 1.23
 * Note: around 180 degrees the encoder jumps from 2.x to -2.x (or opposite) 
 * and then original 0 becomes -1
 * @return double, angle of the pivot from starting position (when power cycle/restart robot code)
 */
double Pivot::GetAngle()
{

    debugCons("PIVOT POSITION: " << m_pivotMotor->GetSelectedSensorPosition());

    
}
