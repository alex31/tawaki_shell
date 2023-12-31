#include <ch.h>
#include <hal.h>
#include <stdnoreturn.h>
#include "stdutil.h"
#include "ttyConsole.h"
#include "ramArch.h"


/*
  ° connecter C00 sur led1 
*/


static THD_WORKING_AREA(waBlinker, 512);
static noreturn void blinker (void *arg);


int main(void)
{
/*
 * System initializations.
 * - HAL initialization, this also initializes the configured device drivers
 *   and performs the board-specific initializations.
 * - Kernel initialization, the main() function becomes a thread and the
 *   RTOS is active.
 */

  halInit();
  mpuConfigureNonCachedRam();
  chSysInit();
  initHeap();

  chThdCreateStatic(waBlinker, sizeof(waBlinker), NORMALPRIO, &blinker, NULL);
  
  consoleInit();
  consoleLaunch();
  chThdSleep(TIME_INFINITE);
}


/*
#                 _      _                                 _                 
#                | |    | |                               | |                
#                | |_   | |__    _ __    ___    __ _    __| |   ___          
#                | __|  | '_ \  | '__|  / _ \  / _` |  / _` |  / __|         
#                \ |_   | | | | | |    |  __/ | (_| | | (_| |  \__ \         
#                 \__|  |_| |_| |_|     \___|  \__,_|  \__,_|  |___/         
*/
static noreturn void blinker (void *arg)
{

  (void)arg;
  chRegSetThreadName("blinker");
  while (true) {
    palToggleLine(LINE_LED1); 	
    palToggleLine(LINE_LED2); 	
    palToggleLine(LINE_LED3); 	
    palToggleLine(LINE_LED4); 	
    chThdSleepMilliseconds(500);
  }
}
