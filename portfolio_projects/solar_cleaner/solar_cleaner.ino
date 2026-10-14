// ESP32 Arduino core; illustrative single-lane brush/drive control.
#include <Arduino.h>
#include "cleaner_control.h"
constexpr int DRIVE=18,BRUSH=19,FRONT_EDGE=27,REAR_EDGE=26,EMERGENCY=25;
CleanerControl control;
void setup(){Serial.begin(115200);pinMode(DRIVE,OUTPUT);pinMode(BRUSH,OUTPUT);pinMode(FRONT_EDGE,INPUT_PULLUP);pinMode(REAR_EDGE,INPUT_PULLUP);pinMode(EMERGENCY,INPUT_PULLUP);digitalWrite(DRIVE,LOW);digitalWrite(BRUSH,LOW);}
void loop(){
    bool front=digitalRead(FRONT_EDGE)==HIGH,rear=digitalRead(REAR_EDGE)==HIGH,emergency=digitalRead(EMERGENCY)==LOW;
    if(Serial.available()){
        char command=Serial.read();if(command=='s')control.start(millis(),front,rear,emergency);
        if(command=='x')control.stop();if(command=='r')control.reset(front,rear,emergency);
    }
    auto out=control.tick(millis(),front,rear,emergency);digitalWrite(DRIVE,out.drive);digitalWrite(BRUSH,out.brush);
    static uint32_t logged=0;if(uint32_t(millis()-logged)>=1000){logged=millis();Serial.printf("{\"device\":\"solar-cleaner-demo\",\"state\":%d,\"drive\":%s,\"brush\":%s}\n",int(out.state),out.drive?"true":"false",out.brush?"true":"false");}
}
