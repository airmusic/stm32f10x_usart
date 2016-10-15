#ifndef BSP_USART_H
#define BSP_USART_H

#include "stm32f10x.h"
#include <stdio.h>


#define MAX_LEN_UASRT2_RX_BUFF         128
#define USART2_TRANS_START_FLAG        '$'
#define USART2_TRANS_FINISH_FLAG       '#'

#define MAX_LEN_UASRT3_RX_BUFF         128
#define USART3_TRANS_START_FLAG        '$'
#define USART3_TRANS_FINISH_FLAG       '#'


void usart1_configuration(void);
static void usart1_nvic_configuration(void);
void usart2_configuration(void);
static void usart2_nvic_configuration(void);
void usart3_configuration(void);
static void usart3_nvic_configuration(void);
int fputc(int ch, FILE *f);
int fgetc(FILE *f);
void usart_printf(USART_TypeDef* USARTx, uint8_t *data, ...);
void usart_custinit(void);

void usart3_data_recv(uint8_t recv_ch);

#endif
