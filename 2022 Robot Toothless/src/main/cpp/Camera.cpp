#include "Camera.h"
#include "cameraserver/CameraServer.h"


Camera::Camera()
{
    
   static cs::UsbCamera camera = frc::CameraServer::StartAutomaticCapture();
   camera.SetResolution(256,144);
   camera.SetFPS(30);
   
}