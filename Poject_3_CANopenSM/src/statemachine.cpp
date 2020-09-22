#include <statemachine.h>

PWM_out ledTimer;
int ledIntensity;

stateMachine::stateMachine(){
    //Initilization
    ledUsed = false;
    state = 1;      //state = Initilization
    cli();          //Clear flags by interrupts
}

stateMachine::stateMachine(bool LED){

    ledTimer.init();        //Initialzing the pwm timers and styff
    if(LED)
    {
        //The LED is .... so we do something other than have the LED fully lit
        ledUsed = true;
        testInput.init();
        blink();
        analogReadValue = testInput.read();
        Serial.println(analogReadValue);
        // if(analogReadValue < 1023/2){
        //     ledIntensity = 255;
        // }
        // else
        // {
        //     ledIntensity = 0;
        // }
        
    }
    else
    {
        //The LED is not in use so the default is do have the LED is fully lit
        ledUsed = false;
        ledTimer.set(255);  //Duty cycle 255 meaning it is fully lit
    }
    
}

void stateMachine::blink(){
    // this code sets up timer1 for a 1 s  @ 16Mhz system clock (mode 4)
    TCCR1A = 0; // set entire TCCR1A register to 0
    TCCR1B = 0; // same for TCCR1B
    TCNT1 = 0;  //initialize counter value to 0

    OCR1A = 16000000 / 1024 - 1;         // assign target count to compare register A (must be less than 65536)
    TCCR1B |= (1 << WGM12);              // clear the timer on compare match A (Mode 4, CTC on OCR1A)
    TIMSK1 |= (1 << OCIE1A);             // set interrupt on compare match A
    TCCR1B |= (1 << CS12) | (1 << CS10); // set prescaler to 1024 and start the timer
    sei();  //enable interrupts
}

ISR(TIMER1_COMPA_vect)
{
  // action to be done every 1 sec
    if(ledIntensity == 255){
        ledIntensity = 0;
        ledTimer.set(ledIntensity);
        Serial.println("HI");
    }
    else if(ledIntensity == 0)
    {
        ledIntensity = 255;
        ledTimer.set(ledIntensity);
        Serial.println("BYE");
    }
    
}

void stateMachine::step(){
    //Goes to next state according to statemachine
    
    switch (state)
    {
    case 1:
        operational();
        state = 2;
        break;
    
    default:
        break;
    }
    Serial.print("Current state: ");
    Serial.println(state);
}

void stateMachine::back(){
    switch (state)
    {
    case 2:
        initilization();
        state = 1;
        break;

    default:
        break;
    }
    Serial.print("Current state: ");
    Serial.println(state);
}

void stateMachine::stop(){
    
}


void stateMachine::readData(){
    //Serial.read function
    if(Serial.available() > 0){
        serRead = Serial.read();
    }
}
void stateMachine::writeData(){
    //For pre operational
    // Serial.write('Ready')
}

void stateMachine::restart(){
    //When writing 'r' or 'R' to console the program goes to state 'Initialization'
    initilization();
}

void stateMachine::initilization(){
    //This is what initilization state is supposed to perform

    stateMachine(false);       
}
void stateMachine::operational(){
    //This is what operational state is supposed to perform
    stateMachine(true);
}