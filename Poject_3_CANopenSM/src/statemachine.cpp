#include <statemachine.h>




stateMachine::stateMachine(){
    //Initilization
    ledUsed = false;
    state = 1;
    //Initialising digital and analog pins
    stateMachine::ledTimer.init();
    stateMachine::lightInput.init();
}

void stateMachine::ledOperation(){

    // Serial.println(stateMachine::lightInput.read());
    if(ledUsed){
        //The LED is in use so do something else
        ledIntensity = map(stateMachine::lightInput.read(),400,860,0,255);
        stateMachine::ledTimer.set(ledIntensity);
    }
    else{
        stateMachine::ledTimer.set(255);
    }
    
}

// void stateMachine::blink(){
//     // this code sets up timer1 for a 1 s  @ 16Mhz system clock (mode 4)
//     TCCR1A = 0; // set entire TCCR1A register to 0
//     TCCR1B = 0; // same for TCCR1B
//     TCNT1 = 0;  //initialize counter value to 0

//     OCR1A = 16000000 / 1024 - 1;         // assign target count to compare register A (must be less than 65536)
//     TCCR1B |= (1 << WGM12);              // clear the timer on compare match A (Mode 4, CTC on OCR1A)
//     TIMSK1 |= (1 << OCIE1A);             // set interrupt on compare match A
//     TCCR1B |= (1 << CS12) | (1 << CS10); // set prescaler to 1024 and start the timer
//     sei();  //enable interrupts
// }

// ISR(TIMER1_COMPA_vect)
// {
//   // action to be done every 1 sec
//     if(ledIntensity == 255){
//         ledIntensity = 0;
//         ledTimer.set(ledIntensity);
//         Serial.println("HI");
//     }
//     else if(ledIntensity == 0)
//     {
//         ledIntensity = 255;
//         ledTimer.set(ledIntensity);
//         Serial.println("BYE");
//     }
    
// }

void stateMachine::updateState(char stepOrBack)
{
    //Goes to next state according to statemachine
    //According to the char that is sent in
    // 's' = step, 'b' = back
    if(stepOrBack == 'r')
    {
        state = 1;
    }
    switch (state)
    {
    case 1:              //Initilization state
        state = 2;
        break;
    case 2:                 //Pre Operational
        if(stepOrBack == 's')
        {
            state = 3;
        }
        break;
    case 3:                //Operatinal state
        
        if(stepOrBack == 's')
        {
            state = 3;    //For now since we are only in part 1
        }
        else if(stepOrBack == 'b')
        {
            state = 1;
        }
        break;

    default:
        Serial.print("Something went wrong state out of bounds");
        break;
    }
    Serial.print("Current state: ");
    Serial.println(state);
}

void stateMachine::stop(){
    
}


void stateMachine::restart(){
    //When writing 'r' or 'R' to console the program goes to state 'Initialization'
    // initilization();
}

void stateMachine::operationToDo(){
    //This is what initilization state is supposed to perform
    switch (state)
    {
    case 1:             //Initilization
    {  
        stateMachine();
        break;
    }
    case 2:
    { 
        while(!Serial.available());
        char serRead1 = Serial.read();
        if( serRead1 == '1')
        {
            ledUsed = true;
            
        }
        else if( serRead1 == '2')
        {
            ledUsed = false;     
        }
        updateState('s');  
    }
        break;
    case 3:             //Operational
    { 
        ledOperation();
        break;
    }
    
    default:
        break;
    }
           
}
