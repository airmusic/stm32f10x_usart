/********************************************************************************
  * @file    		main.c
  * @brief   		stm32f10x usart demo
  * @author  		Timon
  * @date    		20151020
  * @versions		20151021: demo debug
 *******************************************************************************/

#include "stm32f10x.h"
#include <stdio.h>
#include "bsp_systick.h"
#include "bsp_usart.h"
#include "ssp_debug.h"

int main(void)
{
	usart_custinit();
	
	systick_custinit();
	
  DEBUG_PRINTF("============== stm32f10x usart demo ==============\r\n");
	
  while(1)
  {
		delay_ms(1000); // 1000ms delay
		
//		printf("hello, stm32.\r\n");
		
  } // end while
}
