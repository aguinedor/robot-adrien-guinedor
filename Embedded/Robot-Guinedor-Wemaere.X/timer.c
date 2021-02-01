#include <xc.h>
#include "timer.h"
#include "IO.h"

// Initialisation d?un timer 32 bits

void InitTimer23(void) {
    T3CONbits.TON = 0; // Stop any 16?bit Timer3 operation
    T2CONbits.TON = 0; // Stop any 16/32? bit Timer3 operation
    T2CONbits.T32 = 1; // Enable 32?bit Timer mode
    T2CONbits.TCS = 0; // Select internal instruction cycle clock
    T2CONbits.TCKPS = 0b00; // S e l e c t 1: 1 P r e s c a l e r
    TMR3 = 0x00; // Cle a r 32?b i t Timer (msw)
    TMR2 = 0x00; // Cle a r 32?b i t Timer ( l sw )
    PR3 = 0x04C4; // Load 32?b i t p e ri o d v al u e (msw)
    PR2 = 0xB400; // Load 32?b i t p e ri o d v al u e ( l sw )
    IPC2bits.T3IP = 0x01; // Se t Timer3 I n t e r r u p t P r i o r i t y L e v el
    IFS0bits.T3IF = 0; // Cle a r Timer3 I n t e r r u p t Flag
    IEC0bits.T3IE = 1; // Enable Timer3 i n t e r r u p t
    T2CONbits.TON = 1; // S t a r t 32?b i t Timer
    /* Example code f o r Timer3 ISR */
}
// I n t e r r u p t i o n du time r 32 b i t s s u r 2?3

void __attribute__((interrupt, no_auto_psv)) _T3Interrupt(void) {
    IFS0bits . T3IF = 0; // Cle a r Timer3 I n t e r r u p t Flag
    LED_ORANGE = !LED_ORANGE;
}
// I n i t i a l i s a t i on d ?un time r 16 b i t s

void InitTimer1(void) {
    //Timer1 pour h o r o d a t e r l e s mesures ( 1ms)
    T1CONbits.TON = 0; // Di s a bl e Timer
    T1CONbits.TCKPS = 0b11; // Prescaler
    // 11 = 1: 2 5 6 p r e s c a l e v al u e
    // 10 = 1: 6 4 p r e s c a l e v al u e
    // 01 = 1: 8 p r e s c a l e v al u e
    // 00 = 1: 1 p r e s c a l e v al u e


    T1CONbits.TCS = 0; // cl o c k s o u r c e = i n t e r n a l cl o c k
    PR1 = 3125;
    IFS0bits.T1IF = 0; // Cle a r Timer I n t e r r u p t Flag
    IEC0bits.T1IE = 1; // Enable Timer i n t e r r u p t
    T1CONbits.TON = 1; // Enable Timer
}
// I n t e r r u p t i o n du time r 1

void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void) {
    IFS0bits.T1IF = 0;
    LED_BLANCHE = !LED_BLANCHE;
}
