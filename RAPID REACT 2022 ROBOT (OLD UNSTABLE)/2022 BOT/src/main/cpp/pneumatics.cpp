#include "climb/pneumatics.h"

Climb::Climb() {
  m_crabclaws= new frc::DoubleSolenoid(FORWARD_ID, REVERSE_ID);

  m_crabclaws->ClearAllPCMStickyFaults();
  // Start pos
  m_crabclaws->Set(frc::DoubleSolenoid::Value::kReverse);
}

Climb::~Climb() {
  delete m_crabclaws;
}

void Climb::ToggleClimb() {
  // Run the climber pneumatics, acts as a toggle
  if (m_crabclaws->Get() == frc::DoubleSolenoid::Value::kReverse) {
    m_crabclaws->Set(frc::DoubleSolenoid::Value::kForward);
  } else {
    m_crabclaws->Set(frc::DoubleSolenoid::Value::kReverse);
  }

  debugCons("Climber pneumatics toggled.\n");
  frc::Wait(1.0);
}