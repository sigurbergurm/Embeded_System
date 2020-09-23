#include <Arduino.h>
#include <analog_in.h>
#include <PWM_out.h>
#include <digital_in.h>
#include <digital_out.h>
#include <debounce.h>

class stateMachine{

    public:
        stateMachine();
        stateMachine(bool LED);
        void updateState(char stepOrBack);
        void stop();
        void restart();
        
        //Operations of each state
        void operationToDo();
        

    private:
        int state;             //Initilization = 1, Operational = 3                   
        int analogReadValue;
        int ledIntensity;
        bool ledUsed;
        char serRead;
        
        Analog_in lightInput;    //Analog input á A5 (5)
        Digital_in buttonInput; //Button input on pin 12 (PB4) with ISR set on true. (0, false);
        PWM_out ledTimer;
};