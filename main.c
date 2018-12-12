#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "mytimer.h"

int main()
{
  Init_Timer0A();
  Init_GPIOF_Timers();
  printf("%d\n",calculateTime());
  
  return 0;
}
