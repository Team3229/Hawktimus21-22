#include "Turret.h"

Turret::Turret()
{

    m_turretMotor = new ctre::phoenix::motorcontrol::can::WPI_TalonSRX(kTurretMotorID);
    m_turretPID = new frc2::PIDController(kP,kI,kD);
    m_turEncoder = new frc::AnalogEncoder(turretEncID);
    m_turretPID->SetTolerance(kNOMINAL_TX_ERROR);
    debugCons("\nEncoder Reset")   
    m_turEncoder->Reset();

    m_turretMotor->ClearStickyFaults();
}

Turret::~Turret()
{;
    delete m_turretMotor;
    delete m_turretPID;
    delete m_turEncoder;
}


/**
 * turn with set motor power
 * @param setpower % power set to motor
 */
void Turret::Turn(double setPower)
{
    debugDashNum("(Tur) Turret Power", setPower);
    //limits turret turn range
    //if (std::abs(GetAngle()) < kMAX_RANGE.to<double>()){
        if (std::abs(GetAngle()) < 2.46 || std::abs(GetAngle()) > -2.46){
        debugDashNum("(Tur) larger than max range",0);
        m_turretMotor->Set(std::clamp(setPower,-kMAX_TURRET_POWER,kMAX_TURRET_POWER));
    }else{
        debugDashNum("(Tur) larger than max range",1);
        //prevent locking of the turret
        m_turretMotor->Set(std::clamp(-setPower,-kMAX_TURRET_CORRECT_POWER,kMAX_TURRET_CORRECT_POWER));
    }
}

//FOR LIMELIGHT SEEKING TURNING 
void Turret::TurnLimelightRight(double setPower){

       m_turretMotor->Set(std::clamp(setPower,-kMAX_TURRET_POWER,kMAX_TURRET_POWER));
}

void Turret::TurnLimelightLeft(double setPower){

      m_turretMotor->Set(std::clamp(-setPower,-kMAX_TURRET_CORRECT_POWER,kMAX_TURRET_CORRECT_POWER));
}

/**
 * ratio of angle:encoder is 73.17:1
 * GetDistance() start: 0, left 90: -1.23, right 90: 1.23
 * Note: around 180 degrees the encoder jumps from 2.x to -2.x (or opposite) 
 * and then original 0 becomes -1
 * @return double, angle of the turret from starting position (when power cycle/restart robot code)
 */
double Turret::GetAngle()
{
    return m_turEncoder->GetDistance() * kENCODER_RATIO;
}

/**
 * Debugging Turret
 */ 
void Turret::turretDash()
{
    debugDashNum("(Tur) Turret Encoder",GetAngle());
    debugDashNum("(Tur) atSetpoint",m_turretPID->AtSetpoint());
}