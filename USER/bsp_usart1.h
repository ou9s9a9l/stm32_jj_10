#ifndef __USART1_H
#define	__USART1_H


#include "stm32f10x.h"
#include <stdio.h>



/**************************USART参数定义********************************/
#define             macUSART_BAUD_RATE                       9600

#define             macUSARTx                                USART1
#define             macUSART_APBxClock_FUN                   RCC_APB2PeriphClockCmd
#define             macUSART_CLK                             RCC_APB2Periph_USART1
#define             macUSART_GPIO_APBxClock_FUN              RCC_APB2PeriphClockCmd
#define             macUSART_GPIO_CLK                        RCC_APB2Periph_GPIOA     
#define             macUSART_TX_PORT                         GPIOB   
#define             macUSART_TX_PIN                          GPIO_Pin_9
#define             macUSART_RX_PORT                         GPIOB 
#define             macUSART_RX_PIN                          GPIO_Pin_10
#define             macUSART_IRQ                             USART1_IRQn
#define             macUSART_INT_FUN                         USART1_IRQHandler

#define             mac1USART_BAUD_RATE                       115200

#define             mac1USARTx                                USART2
#define             mac1USART_APBxClock_FUN                   RCC_APB1PeriphClockCmd
#define             mac1USART_CLK                             RCC_APB1Periph_USART2   																												 
#define             mac1USART_GPIO_APBxClock_FUN              RCC_APB2PeriphClockCmd
#define             mac1USART_GPIO_CLK                        (RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO)    
#define             mac1USART_TX_PORT                         GPIOA   
#define             mac1USART_TX_PIN                          GPIO_Pin_2
#define             mac1USART_RX_PORT                         GPIOA 
#define             mac1USART_RX_PIN                          GPIO_Pin_3
#define             mac1USART_IRQ                             USART2_IRQn
#define             mac1USART_INT_FUN                         USART1_IRQHandler


void                USARTx_Config                           ( void );
void                USART1x_Config                           ( void );



#endif /* __USART1_H */
