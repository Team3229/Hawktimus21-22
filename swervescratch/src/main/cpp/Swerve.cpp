

#include "Swerve.h"

Swerve::Swerve()
{
    frontLeftDrive = new rev::CANSparkMax(FRONT_LEFT_DRIVE_ID,rev::CANSparkMax::MotorType::kBrushless);
    frontLeftAngle = new rev::CANSparkMax(FRONT_LEFT_ANGLE_ID,rev::CANSparkMax::MotorType::kBrushless);
    backLeftDrive = new rev::CANSparkMax(BACK_LEFT_DRIVE_ID,rev::CANSparkMax::MotorType::kBrushless);
    backLeftAngle = new rev::CANSparkMax(BACK_LEFT_ANGLE_ID,rev::CANSparkMax::MotorType::kBrushless);
    frontRightDrive = new rev::CANSparkMax(FRONT_RIGHT_DRIVE_ID,rev::CANSparkMax::MotorType::kBrushless);
    frontRightAngle = new rev::CANSparkMax(FRONT_RIGHT_ANGLE_ID,rev::CANSparkMax::MotorType::kBrushless);
    backRightDrive = new rev::CANSparkMax(BACK_RIGHT_DRIVE_ID,rev::CANSparkMax::MotorType::kBrushless);
    backRightAngle = new rev::CANSparkMax(BACK_RIGHT_ANGLE_ID,rev::CANSparkMax::MotorType::kBrushless);

    frontLeftEncoder;
    backLeftEncoder;
    frontRightEncoder;
    backRightEncoder;

    frontLeftDrive->RestoreFactoryDefaults();
    frontLeftAngle->RestoreFactoryDefaults();
    backLeftDrive->RestoreFactoryDefaults();
    backLeftAngle->RestoreFactoryDefaults();
    frontRightDrive->RestoreFactoryDefaults();
    frontRightAngle->RestoreFactoryDefaults();
    backRightDrive->RestoreFactoryDefaults();
    backRightAngle->RestoreFactoryDefaults();

    frontLeftDrive->SetClosedLoopRampRate(DRIVE_RAMP_TIME);
    frontLeftAngle->SetClosedLoopRampRate(ANGLE_RAMP_TIME);
    backLeftDrive->SetClosedLoopRampRate(DRIVE_RAMP_TIME);
    backLeftAngle->RestoreFactoryDefaults(ANGLE_RAMP_TIME);
    frontRightDrive->RestoreFactoryDefaults(DRIVE_RAMP_TIME);
    frontRightAngle->RestoreFactoryDefaults(ANGLE_RAMP_TIME);
    backRightDrive->RestoreFactoryDefaults(DRIVE_RAMP_TIME);
    backRightAngle->RestoreFactoryDefaults(ANGLE_RAMP_TIME);
}

Swerve::~Swerve()
{
    delete frontLeftDrive;
    delete frontLeftAngle;
    delete backLeftDrive;
    delete backLeftAngle;
    delete frontRightDrive;
    delete frontRightAngle;
    delete backRightDrive;
    delete backRightAngle;
}

void Swerve::Drive(double X, double Y, double Z)
{
    double a = X - Z * (L / r);
    double b = X + Z * (L / r);
    double c = Y - Z * (W / r);
    double d = Y + Z * (W / r);
    
    double d_frontLeftSpeed = sqrt((b * b) + (c * c));
    double d_backLeftSpeed = sqrt((a * a) + (c * c));
    double d_frontRightSpeed = sqrt((b * b) + (d * d));
    double d_backRightSpeed = sqrt((a * a) + (d * d));

    double d_frontLeftAngle = atan2(b, c) / M_PI;
    double d_backLeftAngle = atan2(a, c) / M_PI;
    double d_frontRightAngle = atan2(b, d) / M_PI;
    double d_backRightAngle = atan2(a, d) / M_PI;

    frontLeftDrive->Set(d_frontLeftSpeed*MAX_DRIVE_SPEED);
    backLeftDrive->Set(d_backLeftSpeed*MAX_DRIVE_SPEED);
    frontRightDrive->Set(d_frontRightSpeed*MAX_DRIVE_SPEED);
    backRightDrive->Set(d_backRightSpeed*MAX_DRIVE_SPEED);


}

void Swerve::Stop()
{

}