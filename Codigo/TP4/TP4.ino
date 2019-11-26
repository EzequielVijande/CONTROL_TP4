#include "Motor.h"
#include "PID_v1.h"
#define HALF_ADC_MEAS 512 

#define KP 3.6 // Valor de Osc 3.2 con KD y KI en 0
#define KI 0
#define KD 0

void setSpeedMotor(int s);
double setpoint=307; //setpoint del sistema
double in=0;//medicion de la salida del sistmea - la realimentacion 
double out=0;//entrada a la planta
AF_DCMotor motor(4);
PID myPID(&in, &out, &setpoint,KP,KI,KD, DIRECT);

void setup() {
 // Serial.begin(9600);
 myPID.SetMode(AUTOMATIC);//turn the PID on
 myPID.SetOutputLimits(-255,255);
 myPID.SetSampleTime(10);//10ms de sampleo
}

void loop() {
  in = analogRead(0);
  //Serial.println(in);
  myPID.Compute();
  setSpeedMotor(out);
  //Serial.println(out);
  
}




void setSpeedMotor(int s){
  if(s>255){
    s=255;
  }else if(s<-255){
    s=-255;
  }
  
  if(s<0){
    motor.setSpeed(-s);
    motor.run(FORWARD);    
  }else if(s<256){
    motor.setSpeed(s);
    motor.run(BACKWARD);    
  }
}
