#include "Camera.h"
#include "cameraserver/CameraServer.h"


Camera::Camera()
{
    /*
    static cs::UsbCamera camera = frc::CameraServer::StartAutomaticCapture();
    camera.SetResolution(352,240);
    camera.SetFPS(FPS);
    camera.SetWhiteBalanceAuto();
    camera.SetExposureAuto();
    camera.SetBrightness(BRIGHTNESS);
  */
 
    frc::CameraServer::StartAutomaticCapture(0);

    
}