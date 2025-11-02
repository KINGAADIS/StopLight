#include <xc.h>
#include <p18f4620.h>
#include "Interrupt.h"

// External variables declared in main program
extern char INT0_Flag;           // Flag for INT0 interrupt occurrence
extern char INT1_Flag;           // Flag for INT1 interrupt occurrence  
extern char INT2_Flag;           // Flag for INT2 interrupt occurrence
extern char EW_PED_SW;           // East-West pedestrian switch 
extern char NS_PED_SW;           // North-South pedestrian switch 
extern char MODE;                // Current mode: 1=Day mode, 0=Night mode
extern char Flashing_Request;    // Flag to request flashing lights 

// ========== Initialize Interrupt System ==========
void init_INTERRUPT()
{
    // Clear all interrupt flags to start fresh
    INTCONbits.INT0IF = 0;       // Clear INT0 interrupt flag
    INTCON3bits.INT1IF = 0;      // Clear INT1 interrupt flag
    INTCON3bits.INT2IF = 0;      // Clear INT2 interrupt flag
    
    // Set interrupt edge detection to rising edge (0?1 transition)
    INTCON2bits.INTEDG0 = 1;     // INT0 triggers on rising edge 
    INTCON2bits.INTEDG1 = 1;     // INT1 triggers on rising edge
    INTCON2bits.INTEDG2 = 1;     // INT2 triggers on rising edge
    
    // Enable individual interrupt
    INTCONbits.INT0IE = 1;       // Enable INT0 (NS pedestrian button)
    INTCON3bits.INT1IE = 1;      // Enable INT1 (EW pedestrian button)
    INTCON3bits.INT2IE = 1;      // Enable INT2 (flashing request button)
    
    // Enable global interrupts (master switch)
    INTCONbits.GIE = 1;          // Global Interrupt Enable - turn on interrupts
}

// ========== High Priority Interrupt Service Routine ==========
// This function is called automatically whenever any enabled interrupt occurs
void interrupt high_priority chkisr()
{
    // Check which interrupt occurred and call appropriate handler
    
    if (INTCONbits.INT0IF == 1)  // INT0 occur
    {
        INT0_ISR();              // Handle NS pedestrian request
    }
    
    if (INTCON3bits.INT1IF == 1) // Did INT1 occur? (EW pedestrian button)
    {
        INT1_ISR();              // Handle EW pedestrian request
    }
    
    if (INTCON3bits.INT2IF == 1) // Did INT2 occur
    {
        INT2_ISR();              // Handle flashing/emergency request
    }	
}

// ========== INT0 ISR: North-South Pedestrian Button ==========
// Called when NS pedestrian button is pressed (rising edge on RB0/INT0)
void INT0_ISR()
{
    INTCONbits.INT0IF = 0;       // Clear the interrupt flag (acknowledge interrupt)
    
    // Only allow pedestrian requests in Day mode (MODE == 1)
    if (MODE == 1)               // If currently in Day mode
    {
        NS_PED_SW = 1;           // Set flag: NS pedestrian crossing requested
    }
    else                         // If in Night mode
    {
        NS_PED_SW = 0;           // Ignore request: pedestrian features disabled at night
    }
}

// ========== INT1 ISR: East-West Pedestrian Button ==========
// Called when EW pedestrian button is pressed (rising edge on RB1/INT1)
void INT1_ISR()
{
    INTCON3bits.INT1IF = 0;      // Clear the interrupt flag (acknowledge interrupt)
    
    // Only allow pedestrian requests in Day mode (MODE == 1)
    if (MODE == 1)               // If currently in Day mode
    {
        EW_PED_SW = 1;           // Set flag: EW pedestrian crossing requested
    }
    else                         // If in Night mode
    {
        EW_PED_SW = 0;           // Ignore request: pedestrian features disabled at night
    }
}

// ========== INT2 ISR: Flashing Request ==========
// Called when flashing button is pressed (rising edge on RB2/INT2)
void INT2_ISR()
{
    INTCON3bits.INT2IF = 0;      // Clear the interrupt flag 
    Flashing_Request = 1;        // Set flag: enter flashing mode 
                                 
}