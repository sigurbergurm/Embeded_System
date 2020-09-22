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
        void step();
        void back();
        void stop();
        void blink();
        void readData();
        void writeData();
        void restart();
        void initilization();
        void operational();
         

    private:
        int state;             //1 = Initilization, 2 = Operational 
        int analogReadValue;
        bool ledUsed;
        char serRead;
        Analog_in testInput;    //Analog input á A5 (5)
        Digital_in buttonInput; //Button input on pin 12 (PB4) with ISR set on true. (0, false);
        //PWM_out ledTimer;
};