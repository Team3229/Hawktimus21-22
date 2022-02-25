#ifndef CONTROLLER_INPUTS_H
#define CONTROLLER_INPUTS_H

struct cmd 
{
  // Driver 1 Controls
  double driver_rightY;
  double driver_rightX;
  double driver_leftX;
  double driver_leftY;
  int driver_AButton;
  int driver_BButton;
  int driver_XButton;
  int driver_YButton;
  bool driver_RightBumper;
  bool driver_LeftBumper;
  float driver_RightTriggerAxis;
  float driver_LeftTriggerAxis;
  int driver_POV;
  // Driver 2 Controls
  float mani_leftX;
  float mani_rightX;
  float mani_leftY;
  float mani_rightY;
  bool mani_AButton;
  bool mani_BButton;
  bool mani_XButton;
  bool mani_YButton;
  bool mani_RightBumper;
  bool mani_LeftBumper;
  float mani_RightTriggerAxis;
  float mani_LeftTriggerAxis;
  int mani_POV;
};

#endif // CONTROLLER_INPUTS_H