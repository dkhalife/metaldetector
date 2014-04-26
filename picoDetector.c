#define		MAXTRY 50         // number of watchdog restart to calibrate loop counter

unsigned char i;
unsigned char ctr ;           // number of loops between two watchdog resets
unsigned char previous ;      // previous value of ctr
unsigned char calibr ;        // calibration value when oscillator runs free
unsigned char restarts ;      // number of watchdog restarts
unsigned char en ;            // enable flag, allows detection

/*
* main loop
*/
void main(){
	/*
	* configure GPIO as digital port
	*/
	CMCON = 7 ;
	TRISIO = 0 ;
	GPIO = 0 ;

	/*
	* power up ?
	*/
	if(STATUS.NOT_TO){
		/*
		* yes, init variables
		*/
		restarts = 0 ;
		calibr = 1 ;
	}

	/*
	* watchdog reset counter
	*/
	if(restarts < 255) restarts++ ;

	/*
	* if counter differs too much from calibration value
	*/
	if((previous ^ ctr) > calibr){
		/*
		* turn detect LED on
		*/
		GPIO.F0 = en ;

		/*
		* if not on power up
		*/
		if(STATUS.NOT_TO == 0){
			/*
			* while in calibration mode
			*/
			if(restarts < MAXTRY){
				/*
				* shift calibration value
				* and wait a little bit
				*/
				calibr <<= 1 ;
				Delay_ms(5);
			}
		}
		else{
			/*
			* turn detect LED off
			*/
			GPIO.F0 = 0 ;
		}
	}

	/*
	* save last counter
	*/
	previous = ctr ;

	/*
	* is calibration over ?
	*/
	if(restarts > MAXTRY){
		/*
		* yes, turn calibrate LED off
		* and set enable flag
		*/
		GPIO.F1 = 0 ;
		en = 1 ;
	}
	else{
		/*
		* no, turn calibrate LED on
		* and clear enable flag
		*/
		GPIO.F1 = 1 ;
		en = 0 ;
	}

	/*
	* set watchdog prescaler
	*/
	OPTION_REG = 0b11111001 ;

	/*
	* start counter, to be interrupted by watchdog
	*/
	ctr = 0 ;
	while(1){
		ctr++ ;
	}
}