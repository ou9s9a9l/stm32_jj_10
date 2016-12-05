#ifndef __USART3_H
#define	__USART3_H


#include "stm32f10x.h"
#include <stdio.h>


#define             macUSART_BAUD_RATE                       9600

#define             macUSARTx                                USART3
#define             macUSART_APBxClock_FUN                   RCC_APB1PeriphClockCmd
#define             macUSART_CLK                             RCC_APB1Periph_USART3
#define             macUSART_GPIO_APBxClock_FUN              RCC_APB2PeriphClockCmd
#define             macUSART_GPIO_CLK                        (RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO)     
#define             macUSART_TX_PORT                         GPIOB   
#define             macUSART_TX_PIN                          GPIO_Pin_10
#define             macUSART_RX_PORT                         GPIOB   
#define             macUSART_RX_PIN                          GPIO_Pin_11
#define             macUSART_IRQ                             USART3_IRQn
#define             macUSART_INT_FUN                         USART3_IRQHandler


void USARTx_Config(void);
void Usart_SendStr_length( USART_TypeDef * pUSARTx, uint8_t *str,uint32_t strlen );
void Usart_SendString( USART_TypeDef * pUSARTx, uint8_t *str);


#endif /* __USART3_H */
