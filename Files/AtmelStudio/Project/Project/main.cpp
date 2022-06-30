#define F_CPU 10000000UL // Quantify the CPU

#include <avr/io.h> // Library to use avr functions
#include <util/delay.h> // Library to use some delays

/*
	** FunctionName: ADC_Init
	* Description: Initialize the ADC
*/
void ADC_Init()
{
	DDRA=0x0;	// Make ADC port as input
	ADCSRA = 0x87;	// Enable ADC-fr/128 
	ADMUX = 0x40;	// AVCC-ADC channel: 0 
}
/*
	** FunctionName: ADC_Read
	* Description: Operation of convert Analog to Digital
*/
int ADC_Read(char channel) // Input of port as an input of function
{
	int Ain,AinLow; // Define 2 variable to read bytes
	ADMUX=ADMUX|(channel & 0x0f);	// Set input channel to read
	ADCSRA |= (1<<ADSC);	// Start conversion 
	while((ADCSRA&(1<<ADIF))==0);	// Monitor end of conversion interrupt-Wait until conversion finished
	_delay_us(10);  //Take 10microSeconde delay
	AinLow = (int)ADCL;		// Read lower byte
	Ain = (int)ADCH*256;		// Read higher 2 bits & multiply with weight */
	Ain = Ain + AinLow;		//Add 2 variables Ain & AinLow		
	return(Ain);		// Return digital value
}
/*
	** FunctionName: Delay
	* Description: Custom delay that working with _delay_ms for each second
*/
void Delay (double delay){
	while (delay>0){ // Wait until delay will be zero or negative
		_delay_ms(1000); // 100 miliSecond delay for each decrease of delay
		delay=delay-1; // Decrease delay on each iteration
	}
}
/*
	** FunctionName: Main
	* Description:The main program
*/
int main(void)
{
	double value1,value2; // Define 2 variables(value1 & value2) for put the result of each potentiometer
	double green1,green2,red1,red2; //Define red & green for each traffic light delay
	double totalTime; //Define variable to save the value of each period
	double yellow=2,lossTime=1; //Define variable for yellow time and also for loss time in red state of traffic light
	DDRC=0b00111111; // Convert Port C as an output port (1-3 for traffic light1 & 4-6 for traffic light2)
	PORTC=0b00001100; // First time the green light in traffic light 1 & red light in traffic light 2 is on
    while (1) // While loop for each duration of traffic light (1 iteration of each traffic light)
    {
		ADC_Init(); // Call ADC_Init function
		value1=ADC_Read(0); // Put returned value of function ADC_Read to value1 by passing 0(first input of port A)
		value2=ADC_Read(1); // Put returned value of function ADC_Read to value2 by passing 1(second input of port A)
		totalTime=( ( 10 * value1 ) / 1023 ) + 14; // Calculate totalTime from linear equation(multiply the descent of current and the value1 and after that add to minimum of the first potentiometer)
		green1=  (((totalTime-14) * value2) / 1023) + 5; // Calculate the green time of traffic light 1 (multiply the descent of current and the totalTime - minimum value and after that add to the minimum value of the second potentiometer)
		green2=totalTime-green1-4; // Calculate the green time of traffic light 2(totalTime - the green time of traffic light 1 - yellow time of traffic light 1 - yellow time of traffic light2)
		red1=totalTime-2-green1; // Calculate the red time of traffic light 1(total Time - the yellow time of traffic light 1 - the green time of traffic light 1)
		red2=green1+2; // Calculate the red time of traffic light 2(sum of the green time of traffic light 1  and the yellow time of traffic light 1 => because it same as the green+yellow time of traffic light 1)
		Delay(green1); // Take delay of green time of traffic light 1
		PORTC=0b00001010; // traffic light 1(yellow) - traffic light 2(red)
		Delay(yellow); // Take delay of yellow time of traffic light 1
		PORTC=0b00001001; // traffic light 1(red) - traffic light 2(red)
		Delay(lossTime); // Take delay of lossTime of traffic light 1
		PORTC=0b00100001; // traffic light 1(red) - traffic light 2(green)
		Delay(green2); // Take delay of green time of traffic light 2
		PORTC=0b0010001; // traffic light 1(red) - traffic light 2(yellow)
		Delay(yellow); // Take delay of yellow time of traffic light 2
		PORTC=0b0001001; // traffic light 1(red) - traffic light 2(red)
		Delay(lossTime); // Take delay of lossTime time of traffic light 2
		PORTC=0b00001100; // traffic light 1(green) - traffic light 2(red)
	}
	return 0; // Return 0 of main program function
}