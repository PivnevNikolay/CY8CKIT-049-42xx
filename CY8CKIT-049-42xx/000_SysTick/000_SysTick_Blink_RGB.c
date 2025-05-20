/**-----------------------------------------------------------------------
 *
 | **                                   ** |
 | ** Код написан в PSoC Creator 4.4    ** |
 *   
 * CY8CKIT-049-42xx
 *   ------------ 
 *  |            |
 *  |            |
 *  |        P0.1| ---->
 *  |        P0.2| ---->
 *  |        P0.3| ---->
 *  |            |
 *  |            |
 *  |        +5V |       | +5V
 *  |        GND | <---> | GND
 *
 *  author: PivnevNikolay 
 *  сode debugging: ScuratovaAnna
 */
/*******************************************************************************/
#include "project.h"

#define LED_ON  1u
#define LED_OFF  0u
#define pause  200

volatile uint8_t  condition = 0;
__IO uint32_t SYSTEM_MS;

uint32_t millis(void);
void system_msdelay(uint32_t delay_ms);

void SysTickISRCallback(void)
{
  SYSTEM_MS++;
}

int main(void)
{
  CyGlobalIntEnable;
  CySysTickStart();
  //CySysTickSetCallback(0, SysTickISRCallback);
  CyIntSetSysVector(CY_INT_SYSTICK_IRQN, (cyisraddress)SysTickISRCallback);
    for(;;){
      switch(condition){
      case 0:
       Pin_Red_Write(LED_ON);
       //CyDelay(pause);
       system_msdelay(pause);
       Pin_Red_Write(LED_OFF);
       //CyDelay(pause);
       system_msdelay(pause);
       condition ++;
      break;
      case 1:
       Pin_Green_Write(LED_ON);
       system_msdelay(pause);
       //CyDelay(pause);
       Pin_Green_Write(LED_OFF);
       system_msdelay(pause);
       //CyDelay(pause);
       condition ++;
      break;
      case 2:
       Pin_Blue_Write(LED_ON);
       //CyDelay(pause);
       system_msdelay(pause);
       Pin_Blue_Write(LED_OFF);
       //CyDelay(pause);
       system_msdelay(pause);
       condition = 0;
      break;
     }
   }
}
/*******************************************************************************/
uint32_t millis(void) {
  return SYSTEM_MS;
}
/*******************************************************************************/
// Задержка на указанное количество миллисекунд (мс). 1 секунда = 1'000 мс.
void system_msdelay(uint32_t delay_ms) {
  uint32_t end = millis() + delay_ms;
  while (millis() != end);
}
/******************************* End of file ***********************************/