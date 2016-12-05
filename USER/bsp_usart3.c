/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * �ļ���  ��usart3.c
 * ����    ����printf�����ض���USART3�������Ϳ�����printf��������Ƭ��������
 *           ��ӡ��PC�ϵĳ����ն˻򴮿ڵ������֡�         
 * ʵ��ƽ̨��Ұ��STM32������
 * Ӳ�����ӣ�---------------------
 *          | 									  |
 *          | PB10  - USART3(Tx)   |
 *          | PB11  - USART3(Rx)   |
 *          |                     |
 *           ---------------------
 * ��汾  ��ST3.5.0
 *
 * ����    ��wildfire team 
 * ��̳    ��http://www.amobbs.com/forum-1008-1.html
 * �Ա�    ��http://firestm32.taobao.com
**********************************************************************************/
#include "bsp_usart3.h"
#include <stdarg.h>


/// ����USART3�����ж�
static void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    /* Configure the NVIC Preemption Priority Bits */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

    /* Enable the USARTy Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = macUSART_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/*
 * ��������USARTx_Config
 * ����  ��USART3 GPIO ����,����ģʽ����
 * ����  ����
 * ���  : ��
 * ����  ���ⲿ����
 */
void USARTx_Config3(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* config USART3 clock */
	macUSART_APBxClock_FUN(macUSART_CLK, ENABLE);
	macUSART_GPIO_APBxClock_FUN(macUSART_GPIO_CLK, ENABLE);

	/* USART3 GPIO config */
   /* Configure USART3 Tx (PB.10) as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = macUSART_TX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_Init(macUSART_TX_PORT, &GPIO_InitStructure);
	    
  /* Configure USART3 Rx (PB.11) as input floating */
  GPIO_InitStructure.GPIO_Pin = macUSART_RX_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_Init(macUSART_RX_PORT, &GPIO_InitStructure);
	  
	/* USART3 mode config */
	USART_InitStructure.USART_BaudRate = macUSART_BAUD_RATE;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(macUSARTx, &USART_InitStructure); 
	
	/*	�����ж����ȼ� */
	NVIC_Configuration();
	/* ʹ�ܴ���2�����ж� */
	USART_ITConfig(macUSARTx, USART_IT_RXNE, ENABLE);

	USART_Cmd(macUSARTx, ENABLE);
	USART_ClearFlag(macUSARTx, USART_FLAG_TC);
}

/*****************  ����һ���ַ� **********************/

/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
