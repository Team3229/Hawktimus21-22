#include "Pivot.h"

Pivot::Pivot()
{

    m_pivotMotor = new ctre::phoenix::motorcontrol::can::WPI_TalonSRX(kPivotMotorID);
    m_pivotPID = new frc2::PIDController(kP,kI,kD);
    m_pivotEncoder = new frc::AnalogEncoder(pivotEncID);
    m_pivotPID->SetTolerance(kNOMINAL_TX_ERROR);
    debugCons("\nEncoder Reset")   
    m_pivotEncoder->Reset();

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
    return m_pivotEncoder->GetDistance() * kENCODER_RATIO;
}
