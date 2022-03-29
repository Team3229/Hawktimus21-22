#include "Camera.h"
#include "cameraserver/CameraServer.h"


Camera::Camera()
{

    frc::CameraServer::StartAutomaticCapture(0);
     //camera 1 for intake

        // Creates the CvSink and connects it to the UsbCamera
        cs::CvSink cvSink = frc::CameraServer::GetVideo();

        // Creates the CvSource and MjpegServer [2] and connects them
        cs::CvSource outputStream = frc::CameraServer::PutVideo("Blur", 640, 480);

       /*
        cs::SetCameraBrightness(BRIGHTNESS);

        cs::SetSourceFPS(FPS);

        cs::SetCameraWhiteBalanceAuto()
        
        cs::SetCameraExposureAuto();
        */

    
}