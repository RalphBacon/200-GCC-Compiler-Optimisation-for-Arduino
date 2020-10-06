// Do not remove the include below
//#include "Arduino_Blink_Optimisation_Demo.h"

//#include <avr/iom328p.h>
#include <binary.h>

#pragma GCC optimize ("-Ofast")
/*
 * Optimisations:
 * 		-O0 no optimisations (only for debugging)
 * 		-O3 turbo speed optimisations, use with caution
 * 		-Ofast will unroll your loops, among other things
 * 		-Os size optimisation
 * 		-O2 balanced optimisation
 * 		You can try adding -fwhole-program (or -flto) in front of these
 *
 * You can limit (or change) the optimisations for parts of your sketch by:
 * 		#pragma GCC push_options (to save the current optimistations config)
 * 		[change the #pragma GCC optimisations here]
 * 		#pragma GCC pop_options (restore previous optimisation config) or
 * 		#pragma GCC reset_options (if above errors #pragma when compiled)
 *
 * Complete list of all individual optimisations here:
 * 		https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html#index-O
 *
 */

void flashLEDTwice();

//#pragma GCC optimize ("unroll-loops")
inline void flashLEDTwice() __attribute__((always_inline));

//The setup function is called once at startup of the sketch
void setup()
{
	// Set the Data Direction Register for Port B
	// First two bits not used, next bit is for pin 13, then for pin 12... final bit for pin 8

	// A "1" indicates OUTPUT, a "0" indicates INPUT
	DDRB = DDRB | B00100000; // Takes 4 bytes

	// Above is equivalent to:
	// pinMode(13, OUTPUT); // Takes 130 bytes
}

// The loop function is called in an endless loop
#pragma GCC push_options
__attribute__((optimize("unroll-loops")))
void loop()
{
	for (auto cnt = 0; cnt < 2; cnt++)
	{
		flashLEDTwice();
		flashLEDTwice();
		flashLEDTwice();
		flashLEDTwice();
		flashLEDTwice();
		flashLEDTwice();
	}
}
#pragma GCC pop_options

void flashLEDTwice() {
	// Set Port B DATA register directly
	// Set pin 13 (5th Bit) HIGH all others LOW
	PORTB = 0b00100000;
	PORTB = 0b00000000;

	PORTB = 0b00100000;
	PORTB = 0b00000000;

	// Above is equivalent to, but considerably faster than:
	// digitalWrite(13, HIGH);
	// digitalWrite(13, LOW);
	// digitalWrite(13, HIGH);
	// digitalWrite(13, LOW);
}