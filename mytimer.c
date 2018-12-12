#include "mytimer.h"

int volatile diff, lastEdge, thisEdge;
int cycleCount = 0;

#define GPIO_PF0_T0CCP0 0x00050007
void Init_Timer0A()
{
  SysCtlPeripheralDisable(SYSCTL_PERIPH_TIMER0);
  SysCtlPeripheralReset(SYSCTL_PERIPH_TIMER0);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0))
  {    
  } 
  
  TimerDisable(TIMER0_BASE, TIMER_A);
  TimerClockSourceSet(TIMER0_BASE,TIMER_CLOCK_SYSTEM);
  
  
  TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR|TIMER_CFG_A_CAP_TIME_UP);
  TimerLoadSet(TIMER0_BASE,TIMER_A,0xFFFF);
  TimerControlEvent(TIMER0_BASE ,TIMER_A ,TIMER_EVENT_BOTH_EDGES);
  TimerEnable(TIMER0_BASE,TIMER_A); 
}

uint32_t calculateTime()
{
  int32_t x;
  int32_t Prev = 0;
  int32_t Curr = 0;
  TimerIntClear(TIMER0_BASE,TIMER_CAPA_EVENT);
  while(!(TimerIntStatus(TIMER0_BASE,false) & TIMER_CAPA_EVENT))
  {
    if(TimerIntStatus(TIMER0_BASE,TIMER_TIMA_TIMEOUT) == TIMER_TIMA_TIMEOUT)
        cycleCount++;
  }
  lastEdge = TimerValueGet(TIMER0_BASE,TIMER_A);
  
  TimerIntClear(TIMER0_BASE,TIMER_CAPA_EVENT);
  while(!(TimerIntStatus(TIMER0_BASE,false) & TIMER_CAPA_EVENT))
  {
    
  }
  thisEdge = TimerValueGet(TIMER0_BASE,TIMER_A);
  x = (cycleCount*0xFFFF) + thisEdge;
  diff = x - lastEdge;
  cycleCount = 0;
  return diff/16000;
  
}

void Init_GPIOF_Timers()
{
  SysCtlPeripheralDisable(SYSCTL_PERIPH_GPIOF);
  SysCtlPeripheralReset(SYSCTL_PERIPH_GPIOF); 
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)){}
  
  HWREG(GPIO_PORTF_BASE+GPIO_O_LOCK) = GPIO_LOCK_KEY;
  HWREG(GPIO_PORTF_BASE+GPIO_O_CR) |= GPIO_PIN_0;

  GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0);  
  GPIOPinTypeTimer(GPIO_PORTF_BASE,GPIO_PIN_0);

  GPIOPinConfigure(GPIO_PF0_T0CCP0);
}