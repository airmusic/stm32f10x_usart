/*************************************************
* @file 			  bsp_usart.c
* @brief  			USART
* @author  			Timon
* @timecreate  	20150626
* @update 			20150626: Create
*************************************************/

#include "bsp_usart.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "ssp_debug.h"


/****************************************************
* @brief: USART1 init, PA9, PA10
*****************************************************/
void usart1_configuration()
{
	GPIO_InitTypeDef gpio_initstructure;
	USART_InitTypeDef usart_initstructure;
	
	// init clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	// GPIO conf, UART1(PA9, PA10)
	// USART TX
	gpio_initstructure.GPIO_Pin = GPIO_Pin_9;
	gpio_initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_initstructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &gpio_initstructure);
	
	// USART RX
	gpio_initstructure.GPIO_Pin = GPIO_Pin_10;
	gpio_initstructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &gpio_initstructure);
	
	// USART1 param config (115200-8-N-1)
	usart_initstructure.USART_BaudRate = 115200;
	usart_initstructure.USART_WordLength = USART_WordLength_8b;
	usart_initstructure.USART_StopBits = USART_StopBits_1;
	usart_initstructure.USART_Parity = USART_Parity_No;
	usart_initstructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart_initstructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &usart_initstructure);
	
	USART_ITConfig(USART1,USART_IT_RXNE, ENABLE);
	USART_Cmd(USART1, ENABLE);
	USART_ClearFlag(USART1, USART_FLAG_TC);
	
	// USART1 nvic config
	usart1_nvic_configuration();
}

/****************************************************
* @brief  config USART1 interrupt
*****************************************************/
static void usart1_nvic_configuration(void)
{
	NVIC_InitTypeDef nvic_initstructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	nvic_initstructure.NVIC_IRQChannel = USART1_IRQn;
	nvic_initstructure.NVIC_IRQChannelPreemptionPriority = 0;
	nvic_initstructure.NVIC_IRQChannelSubPriority = 0;
	nvic_initstructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_initstructure);
}

/****************************************************
* @brief  fputc, redirect printf to USART1
*****************************************************/
int fputc(int ch, FILE *f)
{
	USART_ClearFlag(USART1, USART_FLAG_TC);
	USART_SendData(USART1, (unsigned char) ch);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET);
	return (ch);
}

/****************************************************
* @brief  fgetc, redirect scanf to USART1
*****************************************************/
int fgetc(FILE *f)
{
	while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != SET);
	return (int)USART_ReceiveData(USART1);
}

/****************************************************
* @brief: USART2 init, PA2, PA3
*****************************************************/
void usart2_configuration(void)
{
	GPIO_InitTypeDef gpio_initstructure;
	USART_InitTypeDef usart_initstructure;
	
	// clock inint
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	// GPIO config, USART3(PA2, PA3)
	// USART TX
	gpio_initstructure.GPIO_Pin = GPIO_Pin_2;
	gpio_initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_initstructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &gpio_initstructure);
	
	// USART RX
	gpio_initstructure.GPIO_Pin = GPIO_Pin_3;
	gpio_initstructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &gpio_initstructure);
	
	// USART2 param(115200-8-N-1)
	usart_initstructure.USART_BaudRate = 115200;
	usart_initstructure.USART_WordLength = USART_WordLength_8b;
	usart_initstructure.USART_StopBits = USART_StopBits_1;
	usart_initstructure.USART_Parity = USART_Parity_No;
	usart_initstructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart_initstructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2, &usart_initstructure);
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART2, ENABLE);
	USART_ClearFlag(USART2, USART_FLAG_TC);
//	USART_ClearFlag(USART2, USART_FLAG_TC);
	
	// USART2 nvic conf
	usart2_nvic_configuration();
}

/****************************************************
* @brief  USART2 interrupt conf
*****************************************************/
static void usart2_nvic_configuration(void)
{
	NVIC_InitTypeDef nvic_initstructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	nvic_initstructure.NVIC_IRQChannel = USART2_IRQn;
	nvic_initstructure.NVIC_IRQChannelPreemptionPriority = 0;
	nvic_initstructure.NVIC_IRQChannelSubPriority = 1;
	nvic_initstructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_initstructure);
}

/****************************************************
* @brief: USART3 init, PB10, PB11
*****************************************************/
void usart3_configuration(void)
{
	GPIO_InitTypeDef gpio_initstructure;
	USART_InitTypeDef usart_initstructure;
	
	// clock inint
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	
	// GPIO config, USART3(PB10, PB11)
	// USART TX
	gpio_initstructure.GPIO_Pin = GPIO_Pin_10;
	gpio_initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_initstructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &gpio_initstructure);
	
	// USART RX
	gpio_initstructure.GPIO_Pin = GPIO_Pin_11;
	gpio_initstructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &gpio_initstructure);
	
	// USART3 param(115200-8-N-1)
	usart_initstructure.USART_BaudRate = 115200;
	usart_initstructure.USART_WordLength = USART_WordLength_8b;
	usart_initstructure.USART_StopBits = USART_StopBits_1;
	usart_initstructure.USART_Parity = USART_Parity_No;
	usart_initstructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart_initstructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART3, &usart_initstructure);
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART3, ENABLE);
	USART_ClearFlag(USART3, USART_FLAG_TC);
//	USART_ClearFlag(USART3, USART_FLAG_TC);
	
	// USART3 nvic conf
	usart3_nvic_configuration();
}

/****************************************************
* @brief  USART3 interrupt conf
*****************************************************/
static void usart3_nvic_configuration(void)
{
	NVIC_InitTypeDef nvic_initstructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	nvic_initstructure.NVIC_IRQChannel = USART3_IRQn;
	nvic_initstructure.NVIC_IRQChannelPreemptionPriority = 0;
	nvic_initstructure.NVIC_IRQChannelSubPriority = 2;
	nvic_initstructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_initstructure);
}

/****************************************************
* @brief: format print, like printf, optional to choose USART no
* @param: usartx: usart no, *data, ...
*****************************************************/
void usartx_printf(USART_TypeDef* usartx, uint8_t *data, ...)
{
	const char *s;
	int d;
	char buff[16];
	va_list ap;
	va_start(ap, data);
	
	USART_ClearFlag(usartx, USART_FLAG_TC);
	while(*data != 0)
	{
		if(*data == 0x5c) // '\'
		{
			switch(*++data)
			{
				case 'r':
					USART_SendData(usartx, 0x0d);
					data++;
					break;
				case 'n':
					USART_SendData(usartx, 0x0a);
					data++;
					break;
				default:
					data++;
					break;
			}
		}
		else if(*data == '%')
		{
			switch(*++data)
			{
				case 's':
					s = va_arg(ap, const char *);
					for( ; *s; s++)
					{
						USART_SendData(usartx, *s);
						while(USART_GetFlagStatus(usartx, USART_FLAG_TC) == RESET)
							;
					}
					data++;
					break;
				case 'd':
					d = va_arg(ap, int);
					sprintf(buff, "%d", d);
					for(s = buff; *s; s++)
					{
						USART_SendData(usartx, *s);
						while(USART_GetFlagStatus(usartx, USART_FLAG_TC) == RESET)
							;
					}
					data++;
					break;
				default:
					data++;
					break;
			}
		}
		else
			USART_SendData(usartx, *data++);
		while(USART_GetFlagStatus(usartx, USART_FLAG_TC) == RESET)
			;
	}
}

/****************************************************
* @brief     USART2 data receive handler
*            with simple verify: USART2_TRANS_START_FLAG -> recv start flag, 
*                                USART2_TRANS_FINISH_FLAG -> recv finish flag
* @param     uint8_t recv_ch: recieved char
*****************************************************/
void usart2_data_recv(uint8_t recv_ch)
{
	static uint8_t recv_str[MAX_LEN_UASRT3_RX_BUFF] = {0};
	static int recv_str_index = 0;

	// filter the illegal recv start ch
	if(0 == recv_str_index && USART2_TRANS_START_FLAG != recv_ch)
	{
//		DEBUG_PRINTF("[USART3] illegal recv start ch: %c\r\n", recv_ch);
		return;
	}
	
	// recv str buff overflow (empty)
	if(recv_str_index >= MAX_LEN_UASRT2_RX_BUFF)
	{
		DEBUG_PRINTF("[USART2] recv str buff overflow (empty without recv finish flag), clean it\r\n");
		recv_str_index = 0;
		memset(recv_str, 0, sizeof(recv_str));
	}
	
	switch(recv_ch)
	{
		case USART2_TRANS_START_FLAG:
			// recv str start
			recv_str_index = 0;
			memset(recv_str, 0, sizeof(recv_str));
			recv_str[recv_str_index++] = recv_ch;
			break;
		case USART2_TRANS_FINISH_FLAG:
			// recv str finish
			recv_str[recv_str_index++] = recv_ch;
		DEBUG_PRINTF("[USART2] recv_str: %s\r\n", recv_str);
			recv_str_index = 0;
			memset(recv_str, 0, sizeof(recv_str));
			break;
		default:
			recv_str[recv_str_index++] = recv_ch;
	}
}

/****************************************************
* @brief     USART3 data receive handler
*            with simple verify: USART3_TRANS_START_FLAG -> recv start flag, 
*                                USART3_TRANS_FINISH_FLAG -> recv finish flag
* @param     uint8_t recv_ch: recieved char
*****************************************************/
void usart3_data_recv(uint8_t recv_ch)
{
	static uint8_t recv_str[MAX_LEN_UASRT3_RX_BUFF] = {0};
	static int recv_str_index = 0;

	// filter the illegal recv start ch
	if(0 == recv_str_index && USART3_TRANS_START_FLAG != recv_ch)
	{
//		DEBUG_PRINTF("[USART3] illegal recv start ch: %c\r\n", recv_ch);
		return;
	}
	
	// recv str buff overflow (empty)
	if(recv_str_index >= MAX_LEN_UASRT3_RX_BUFF)
	{
		DEBUG_PRINTF("[USART3] recv str buff overflow (empty without recv finish flag), clean it\r\n");
		recv_str_index = 0;
		memset(recv_str, 0, sizeof(recv_str));
	}
	
	switch(recv_ch)
	{
		case USART3_TRANS_START_FLAG:
			// recv str start
			recv_str_index = 0;
			memset(recv_str, 0, sizeof(recv_str));
			recv_str[recv_str_index++] = recv_ch;
			break;
		case USART3_TRANS_FINISH_FLAG:
			// recv str finish
			recv_str[recv_str_index++] = recv_ch;
		DEBUG_PRINTF("[USART3] recv_str: %s\r\n", recv_str);
			recv_str_index = 0;
			memset(recv_str, 0, sizeof(recv_str));
			break;
		default:
			recv_str[recv_str_index++] = recv_ch;
	}
}

/****************************************************
* @brief: USART init
*****************************************************/
void usart_custinit()
{
	usart1_configuration();
	DEBUG_PRINTF("USART1 initil success\r\n");
	
	DEBUG_PRINTF("usart2 configuration...\r\n");
	usart2_configuration();
	
	DEBUG_PRINTF("usart3 configuration...\r\n");
	usart3_configuration();
}
