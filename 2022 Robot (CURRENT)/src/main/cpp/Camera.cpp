#include "Camera.h"

Camera::Camera()
{
    cs::UsbCamera camera = frc::CameraServer::GetInstance()->StartAutomaticCapture(); //camera 1

    //camera 1 driver vision
    camera.SetResolution(352,240);
    camera.SetFPS(FPS);
    camera.SetWhiteBalanceAuto();
    camera.SetExposureAuto();
    camera.SetBrightness(BRIGHTNESS);


    frc::CameraServer::GetInstance()->StartAutomaticCapture(0);
}