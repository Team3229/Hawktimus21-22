//Written By: 3229 Programming Subteam

#include "Camera.h"

Camera::Camera()
{
    cs::UsbCamera camera = frc::CameraServer::GetInstance()->StartAutomaticCapture(); //camera 1
    cs::UsbCamera camera2 = frc::CameraServer::GetInstance()->StartAutomaticCapture(); //camera 2

    //camera 1 driver vision
    camera.SetResolution(352,240);
    camera.SetFPS(FPS);
    camera.SetWhiteBalanceAuto();
    camera.SetExposureAuto();
    camera.SetBrightness(BRIGHTNESS);

    //camera2 climb/or intake vision
    camera2.SetResolution(352,240);
    camera2.SetFPS(FPS);
    camera2.SetWhiteBalanceAuto();
    camera2.SetExposureAuto();
    camera2.SetBrightness(BRIGHTNESS);

    frc::CameraServer::GetInstance()->StartAutomaticCapture(0);
}

