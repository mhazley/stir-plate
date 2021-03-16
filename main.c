#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

/*
 * Super basic PWM test, run from 0 <--> 255 with 100ms delay at each step
 * To test PWM bring up
 */

int main (void) {

    uint8_t output = 0;
    uint8_t increasing = 1;

    // Set PB0 (this is OC0A) to output
    DDRB = 1<<DDB0;

    /* Enable PWM
     * TCCR0A Timer Control Register A
     *    Compare Match Output A set to 0b10 (clear 0C0A on match)
     *    Waveform Generation Mode set to 0b011 (Fast PWM)
     *    Clock Select set to no prescaling
     */
    TCCR0A = 2<<COM0A0 | 3<<WGM00;
    TCCR0B = 0<<WGM02 | 1<<CS00;

    // TODO: Read `output` from analog in
    while (1) {

        if (increasing) {
            if (++output == 255) increasing = 0;
        }
        else {
            if (--output==0) increasing = 1;
        }

        OCR0A = output;
        _delay_ms(100);

    }
}
