/**
  ******************************************************************************
  * @file    Project/Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.0.0
  * @date    04/06/2009
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "led.h"

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
extern __IO uint32_t ret;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval : None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval : None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
	
  while (1)
  {
  }
	
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval : None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval : None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval : None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval : None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval : None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval : None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval : None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles USB Low Priority or CAN RX0 interrupts 
  *   requests.
  * @param  None
  * @retval : None
  */
/*
 * 函数名：USB_LP_CAN1_RX0_IRQHandler
 * 描述  ：USB中断和CAN接收中断服务程序，USB跟CAN公用I/O，这里只用到CAN的中断。
 * 输入  ：无
 * 输出  : 无	 
 * 调用  ：无
 */
 #define len 30
extern unsigned char cache[len][11];
unsigned short count1 = 0;
void USB_LP_CAN1_RX0_IRQHandler(void)
{
  CanRxMsg RxMessage;
	short i = 0,b=0;
  RxMessage.StdId=0x00;
  RxMessage.ExtId=0x00;
  RxMessage.IDE=0;
  RxMessage.DLC=0;
  RxMessage.FMI=0;
  RxMessage.Data[0]=0x00;
  RxMessage.Data[1]=0x00;

  CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
	{///////add function
	for(b=0;b<len-2;b++)
	if(cache[b][9]==0)break;
	
	cache[b][0]=(RxMessage.StdId)/8;
	
	for(i=0;i<8;i++)
	cache[b][i+1] = RxMessage.Data[i];
	
	cache[b][9]=0xff;//占用符号
  cache[b][10]= RxMessage.DLC;//占用符号
	}///////add function
	LED1( OFF );
  if((RxMessage.ExtId==0x1234) && (RxMessage.IDE==CAN_ID_EXT)
     && (RxMessage.DLC==2) && ((RxMessage.Data[1]|RxMessage.Data[0]<<8)==0xDECA))
  {
    ret = 1; 
  }
  else
  {
    ret = 0; 
  }
}

#include "bsp_usart1.h"


#include "define.h"
unsigned short CRC1(unsigned char* pBuf,short Len);
unsigned int m_save,m_crc;
unsigned int send_len=0;//??????
//#define count_times 6

short count_oyx = 0;


unsigned char rdatatemp[size_array];

extern char rdatacache[cachelen+1][cachelen1];
extern char rdata[size_array];
extern unsigned char rxbuffer[32];
extern unsigned char trx;//0 rx 1 tx
extern int six_second ;
short rxflag=0,succflag=0,count=0,resetflag=0,flag_oyx = 0;
void handle_data(unsigned char temp)
{
	short a=0,b=0;
	if(temp==0x01)
{succflag=1;count=0;}

	
	//if(1==count&&temp==0x14)
	//{sendcastflag=1;}
	if(1==count&&(temp==0x14||temp==0x15))
	{
		succflag=0;count=0;return;
	}
	#if SELECT==2009						   //????zyz
	if(1==count&&(temp==0x14||temp==0x11))
	{
		succflag=0;count=0;return;
	}
	#endif
	//if(1==count&&(temp==0x11||temp==0x12))LED_ON
	if (count>(size_array-10))
	{
		for (a=0;a<size_array;a++)
		rdatatemp[a]=0;
		succflag=0;
		count=0;
	}


	if(succflag)
	{
		rdatatemp[count]=temp;
		if(count>500)
		{
		count=-1;
		succflag=0;
		}
		if (rdatatemp[count]==0x03)
		{
			m_save=CRC1(rdatatemp,count-2);
			m_crc=rdatatemp[count-1];////////////12 27?
			m_crc<<=8;
			m_crc|=rdatatemp[count-2];
			
			if(m_save!=m_crc||m_crc==0)
			{
				for (a=0;a<=count;a++)
				rdatatemp[a]=0;
			}
			
			#if SELECT==2006||SELECT==2010						   //????zyz
			
			if(rdatatemp[0]==0x01)
			{
				//send_to_server(rdatatemp,count);
				for ( a=0;a<=count;a++)
				rdata[a]=rdatatemp[a];
				send_len = count;
			}
			
			#endif
			#if SELECT==2009				   //????zyz
			
			if(rdatatemp[1]==0x22)
			{
				if(rdata[0]==0)
				{for ( a=0;a<=count;a++)
					{
						rdata[a]=rdatatemp[a];
					}
				rx0x11=0;}
			}
			#endif
			
			if(rdatatemp[1]==0x12)
			{
				b=0;
				if(rdatacache[0][0]!=0)
				for (b=0;b<cachelen;b++)
				{
					if(rdatacache[b][0]==0)
					break;
				}
				if(b>=flag_oyx)
				flag_oyx=b;
				for ( a=0;a<=count;a++)
				rdatacache[b][a]=rdatatemp[a];
				
			}
			
			

			
			
			
			count=-1;
			succflag=0;
		blink();
			for (a=0;a<=count;a++)
			rdatatemp[a]=0;
		}
		//#if TEST==2
		if (rxflag==1)      				          //????
		switch(rdatatemp[count])
		{
			case 0x81: rdatatemp[count-1]=0x01;count--;rxflag=0;break;
			case 0x83: rdatatemp[count-1]=0x03;count--;rxflag=0;break;
			case 0x90: rdatatemp[count-1]=0x10;count--;rxflag=3;break;
			default:rxflag=0;break;
		}
		if (rdatatemp[count]==0x10&&rxflag!=3)
		rxflag=1;     //??????
		else rxflag=0;
		//#endif
		count++;
		//?????
	}
	// LED_OFF
}


unsigned short CRC1(unsigned char* pBuf,short Len)
{
	unsigned short CRC2 = 0;
	unsigned char R;
	short i,j,k,m;
	CRC2=0;
	if(Len<=0) return 0;
	for(i=1;i<Len;i++)    {
		R=pBuf[i];
		for(j=0;j<8;j++)
		{
			if (R>127) k=1;else k=0;
			R<<=1;
			if(CRC2>0x7fff) m=1;	else m=0;
			if (k+m==1) k=1; 	else k=0;
			CRC2<<=1;
			if (k==1) CRC2^=0x1021;
		}
	}
	return CRC2;
}
void USART1_IRQHandler(void)
{
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{ 	uint8_t ch;
	   ch = USART_ReceiveData(USART1);
		handle_data(ch);
	} 
	 
}

void USART3_IRQHandler(void)
{
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{ 	
		//USART_ClearITPendingBit(USART3,USART_IT_RXNE);
	   	uint8_t ch;
	   ch = USART_ReceiveData(USART3);
		//rdatatemp[count++]=ch;
		//if(ch==0x01)blink();
		handle_data(ch);
	} 
	 
}
/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
