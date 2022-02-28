#include "Limelight.h"

Limelight::Limelight(){
    
}

Limelight::~Limelight(){

}

void Limelight::LightOff(){
    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 1);
    debugCons("LimelighOFf\n")
}

void Limelight::LightOn(){
    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 3);
    debugCons("LimelightOn\n")
}
