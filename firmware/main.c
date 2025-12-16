#include <xc.h>
#define _XTAL_FREQ 4000000  // set same clock in Proteus PIC properties

// CONFIG
#pragma config FOSC = HS, WDTE = OFF, PWRTE = OFF, BOREN = ON, LVP = OFF, CPD = OFF, WRT = OFF, CP = OFF

// user threshold (adjust after calibration)
#define THRESHOLD_ADC 512

void adc_init() {
    ADCON1 = 0b10001110; // AN0 analog, others digital, Vref=Vdd
    ADCON0 = 0b01000001; // ADON=1, Channel = 0 (AN0)
}

unsigned int adc_read_ch0() {
    ADCON0 &= 0b11000111;        // clear CHS bits
    ADCON0 |= (0 << 3);         // select channel 0 (AN0)
    __delay_us(5);              // acquisition time
    ADCON0bits.GO = 1;
    while (ADCON0bits.GO);      // wait for conversion
    return ((ADRESH << 8) | ADRESL);
}

void main(void) {
    TRISA = 0xFF;  // RA0 ADC input
    TRISB = 0x00;  // RB0 output
    PORTB = 0x00;

    adc_init();

    while (1) {
        unsigned int v = adc_read_ch0();
        if (v > THRESHOLD_ADC) PORTBbits.RB0 = 1;
        else PORTBbits.RB0 = 0;
        __delay_ms(50);
    }
}


