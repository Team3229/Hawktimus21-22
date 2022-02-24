#include "Climb.h"

Climb::Climb() {
  // Initiate/Setup Climb System
  m_climber = new rev::CANSparkMax(mClimbID,rev::CANSparkMax::MotorType::kBrushless);
  l_climber = new rev::CANSparkMax(lClimbID,rev::CANSparkMax::MotorType::kBrushless);
  r_climber = new rev::CANSparkMax(rClimbID,rev::CANSparkMax::MotorType::kBrushless);
  m_climber->RestoreFactoryDefaults();
  l_climber->RestoreFactoryDefaults();
  r_climber->RestoreFactoryDefaults();
}

Climb::~Climb() {
  //Delete Motor Variables
  delete m_climber;
  delete l_climber;
  delete r_climber;
}

void Climb::ClimbT() {

  /*
    O  Extend to Bar  I           P  0*
    O  Retract        I  Extend   P  5* Out
    O                 I  Retract  P  5* In
    O  Extend         I           P  30* In
    O  Retract        I  Retract  P  0*
  */



  }


  // Software Cap for Climb
  // 5 degrees back, 30 degrees, forward