//Author: Sebastian Roman (Programming Lead)
//Co Author: 3229 Programming

#include "LEDS.h"
#include "Debug.h"


LEDS::LEDS(){
    
    BlinkLEDDriver = new frc::Spark(BlinkinLEDDriver_PWM);
}

LEDS::~LEDS(){

    delete BlinkLEDDriver;
}

void LEDS::ChangeLEDColors(double SetColor){

    BlinkLEDDriver->Set(SetColor);
}