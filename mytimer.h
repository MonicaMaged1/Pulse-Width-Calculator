#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"

void Init_Timer0A(void);
uint32_t calculateTime(void);
void Init_GPIOF_Timers(void);


