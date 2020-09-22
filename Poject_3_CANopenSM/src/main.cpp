#include <Arduino.h>
#include <statemachine.h>

stateMachine StateMachine;
char serRead;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
      if(Serial.available() > 0){
        serRead = Serial.read();
       
        if(serRead == 's'){
          StateMachine.step();
        }
        if(serRead == 'b'){
          StateMachine.back();
        }
    }
}

