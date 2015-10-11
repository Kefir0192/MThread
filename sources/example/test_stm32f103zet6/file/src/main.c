#include "globalincludefile.h"
#include "main.h"
#include "phisic.h"
#include "test_thread.h"
#include <task.h>
#include <mutex.h>
#include <delay.h>



//------------------------------------------------------
// Hardware initialization
//------------------------------------------------------
void Hardware_Init(void)
{
    // Initialize oscillator
    Oscillator_Init();
    // Initialization GPIO
    Port_Init();
}

//------------------------------------------------------
// MAIN
//------------------------------------------------------
int main(void)
{
    // Hardware initialization
    Hardware_Init();

    eMutex_Create(&MutexA);

    eTask_Create(&eTask_Element[0], Thread_A, &stack_a[127], 64, &vA, 0);
    eTask_Create(&eTask_Element[1], Thread_B, &stack_b[127], 64, &vB, 0);

    eStart_Schedule();

    while(1) {


    }
}
