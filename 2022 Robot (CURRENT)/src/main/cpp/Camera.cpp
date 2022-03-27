#include "Camera.h"

Camera::Camera()
{
    //cs::UsbCamera camera = frc::CameraServer::GetInstance()->StartAutomaticCapture(); //camera 1

    cs::UsbCamera camera = frc::CameraServer::GetInstance()->StartAutomaticCapture();
	camera.SetResolution(352, 240); // length x height
	camera.SetFPS(FPS);
	camera.SetWhiteBalanceAuto();
	camera.SetExposureAuto();
	camera.SetBrightness(BRIGHTNESS);

	frc::CameraServer::GetInstance()->StartAutomaticCapture(0);
}