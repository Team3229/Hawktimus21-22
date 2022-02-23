#include "Shooter.h"

Shooter::Shooter()
{
    //hood likely removal, change when it is set to be removed (comment out hood functions and move to the end)
    //in case to be used in the future as a reference (code worked fine but not good enough for mechanical needs)
    //m_hoodServo = new frc::Servo(kHoodServoID);

    m_flyWheelLead = new rev::CANSparkMax(kFlyLeadFWID,rev::CANSparkMax::MotorType::kBrushless);
    m_flyWheelFollow = new rev::CANSparkMax(kFlyFollowFWID,rev::CANSparkMax::MotorType::kBrushless);
    m_flyWheelPID = new frc2::PIDController(kP,kI,kD);

    m_feeder = new ctre::phoenix::motorcontrol::can::WPI_TalonSRX(kFeederID);

    //m_hoodServo->SetBounds(2.0,1.8,1.5,1.2,1.0);
    // Test values with lower maximum:
    //m_hoodServo->SetBounds(1.6,1.4,1.1,0.8,0.6);

    m_flyWheelLead->RestoreFactoryDefaults();
    m_flyWheelFollow->RestoreFactoryDefaults();
    m_feeder->ClearStickyFaults();
}

Shooter::~Shooter()
{
    delete m_flyWheelLead;
    delete m_flyWheelFollow;
    delete m_flyWheelPID;
    delete m_feeder;
}

bool Shooter::adjustFWSpeed(double rpm)
{
    double FWSpeed = m_flyWheelLead->GetEncoder().GetVelocity(); //gets current rpm
    double FWOutput = m_flyWheelPID->Calculate(FWSpeed,rpm); //calculate power needed to set to rpm
    m_lastOutput = FWOutput; 
    //debug
    debug(FWOutputDebug = FWOutput); 
    debug(FWSpeedDebug = FWSpeed);
    
    m_flyWheelLead->Set(FWOutput);
    if (std::abs(FWSpeed - rpm) > kRPM_ERR_RANGE){
        debugDashNum("FWSpeed correct",0);
        return false;
    }
    debugDashNum("FWSpeed correct",1);
    return true;
}

/**
 * Maintain the state of last registered FW Speed and Hood position
 */
void Shooter::maintainState()
{
    m_flyWheelLead->Set(m_lastOutput);
    m_flyWheelFollow->Set((m_lastOutput)*-1);
    //m_hoodServo->SetPosition(m_lastHoodPos); //hood
}

//stop shooter
void Shooter::stopShooter()
{
    m_flyWheelLead->StopMotor();
    m_flyWheelFollow->StopMotor();
}

//feeder, feeding shooter
void Shooter::feedShooter()
{
    m_feeder->Set(FEEDER_FORWARD_POWER);
}
void Shooter::reverseFeed()
{
    m_feeder->Set(FEEDER_REVERSE_POWER);
}
void Shooter::stopFeed()
{
    m_feeder->StopMotor();
}

/**
 * Shooter Debugging
 */ 
void Shooter::shooterDash()
{
    //debugDashNum("(S) Hood Last Position", m_lastHoodPos);
    //debugDashNum("(S) Hood Current Position",m_hoodServo->GetPosition());
    debugDashNum("(S) FW output", FWOutputDebug);
    debugDashNum("(S) current FWrpm",FWSpeedDebug);
    debugDashNum("(S) calculated RPM",FWSetRPMDebug);
    //debugDashNum("(S) calculated Hood Pos", hoodSetPosDebug);
}

void Shooter::runShooter() {
    m_flyWheelLead->Set(SHOOTER_POWER);
    m_flyWheelFollow->Set((SHOOTER_POWER)*-1);
}


/*** Start of Hood code **/
/*
void Shooter::maintainHood() {
    m_hoodServo->SetPosition(m_lastHoodPos);
}
*/

/**
 * Calculate hood position
 * @param dist, distance units from the target
 * @return double, calculated position for hood
 */ 
/*
double Shooter::calcHoodPos(units::inch_t dist)
{
    double hoodSetPos = dist.to<double>() * kHOOD_ANGLE_RATIO;
    debug(hoodSetPosDebug = hoodSetPos);
    return hoodSetPos;
}
*/

/**
 * Adjust hood angle incrementally
 * adding incrementalValue to the current position
 * @param incrementalValue, value to increase the current position by
 */ 
/*
void Shooter::incrementalHood(double incrementalValue)
{
    // false is down
    m_lastHoodPos += incrementalValue;
    adjustHood(m_lastHoodPos);
}
*/

/**
 * Adjust hood angle with set position
 * @param pos, set position
 * @return true if the hood is in correct position
 */
/*
bool Shooter::adjustHood(double pos)
{
    double correctPos = std::clamp(pos,0.0,kMAX_HOOD_POS);
    m_lastHoodPos = correctPos;
    m_hoodServo->SetPosition(correctPos);
    if ((std::abs(m_hoodServo->GetPosition() - correctPos) > kHOOD_ERR_RANGE))
    {
        debugDashNum("Hood correct",0);
        return false;
    }
    debugDashNum("Hood correct",1);
    return true;
}
*/