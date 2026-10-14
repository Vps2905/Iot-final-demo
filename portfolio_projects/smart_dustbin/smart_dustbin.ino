// ESP32 Arduino core 3.x. Public reconstruction; pin map must be verified on the bench.
#include <Arduino.h>
#include "bin_control.h"
constexpr int TRIG=18,ECHO=19,PERSON=27,SERVO_PIN=13,FULL_LED=25;
BinControl control;
uint32_t last_sample=0,last_log=0;
float distance_cm=NAN;
float readDistance(){
    digitalWrite(TRIG,LOW);delayMicroseconds(2);digitalWrite(TRIG,HIGH);delayMicroseconds(10);digitalWrite(TRIG,LOW);
    unsigned long echo=pulseIn(ECHO,HIGH,25000);return echo?echo*.0343f/2.f:NAN;
}
void setServo(bool open){
    // 500–2500 us servo pulse range. Confirm the actual servo's safe range before mounting.
    uint32_t pulse=open?2000:1000;ledcWrite(SERVO_PIN,uint32_t(pulse*16383ULL/20000));
}
void setup(){
    Serial.begin(115200);pinMode(TRIG,OUTPUT);pinMode(ECHO,INPUT);pinMode(PERSON,INPUT_PULLUP);pinMode(FULL_LED,OUTPUT);
    if(!ledcAttach(SERVO_PIN,50,14)){Serial.println("{\"error\":\"servo_pwm_initialization_failed\"}");while(true){delay(1000);}}setServo(false);
}
void loop(){
    uint32_t now=millis();if(uint32_t(now-last_sample)>=100){last_sample=now;distance_cm=readDistance();}
    auto out=control.tick(now,digitalRead(PERSON)==LOW,distance_cm);setServo(out.lid_open);digitalWrite(FULL_LED,out.full);
    if(uint32_t(now-last_log)>=1000){last_log=now;Serial.printf("{\"device\":\"bin-demo\",\"fill_percent\":%d,\"lid_open\":%s,\"full\":%s}\n",out.fill_percent,out.lid_open?"true":"false",out.full?"true":"false");}
}
