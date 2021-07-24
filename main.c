#include<avr/io.h>
#include<util/delay.h>


#define HIGH 1
// PORT B Pins
uint8_t ledPin = 0;
uint8_t heatSwitch = 2;
uint8_t pushSwitch = 3;

#define OFF 0
#define ON 1



uint8_t digitalRead(volatile uint8_t* reg,uint8_t pin){
    
    return( *reg&(1<<pin) );
}

void digitalWrite(volatile uint8_t* reg,uint8_t pin,uint8_t state){
    switch (state){
        case OFF:
            *reg &= ~(1<<pin) ;
            break;
        case ON:
            *reg |= (1<<pin) ;
            break;

    }
}

void setup(){
    DDRB |= (1<<ledPin);                    /** set pin led Pin as output */ 
    DDRB &=~(1<<heatSwitch);                /** set heatSwitch as input */
    DDRB &=~(1<<pushSwitch);                /** set pushSwitch as input */
    PORTB |= (1<<heatSwitch);               /** activate PULL UP */  
    PORTB |= (1<<pushSwitch);               /** activate PULL UP */  

    digitalWrite(&PORTB,ledPin,OFF);         /** set LED to OFF */ 
    

}


int main()
{
    setup();
    while(1)
    {

        
        if(digitalRead(&PINB,heatSwitch))
        {
            digitalWrite(&PORTB,ledPin,OFF);
        }

        else
        {
            if(digitalRead(&PINB,pushSwitch)==OFF)
                digitalWrite(&PORTB,ledPin,ON);
            else
                digitalWrite(&PORTB,ledPin,OFF);
           
            
        }
    }
    return 0;
}
