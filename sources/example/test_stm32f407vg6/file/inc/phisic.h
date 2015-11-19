#ifndef PHISIC_H_INCLUDED
#define PHISIC_H_INCLUDED


#define LED_GREEN (1 << 12) /* port D, pin 12 */
#define LED_ORANGE (1 << 13) /* port D, pin 13 */
#define LED_RED (1 << 14) /* port D, pin 14 */
#define LED_BLUE (1 << 15) /* port D, pin 15 */


// Initialize oscillator
//------------------------------------------------------
void Oscillator_Init(void);
// Initialization GPIO
//------------------------------------------------------
void Port_Init(void);



#endif // PHISIC_H_INCLUDED
