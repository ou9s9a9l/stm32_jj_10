#include "stm32f10x.h"                  // Device header
//#include "stm32f10x.h"
#include "bsp_TiMbase.h"
#include "bsp_spi_nrf.h"
#include "led.h"
#include "can.h" 
#include "define.h" 
#include "bsp_usart1.h"
#include "stm_flash.h"
#include "rf.h"
u8 status,i,j;	//用于判断接收/发送状态
u8 txbuf[32]={0,1,2,3};	 //发送缓冲
u8 rxbuf[32]={0};			 //接收缓冲
#define len 30
void IAP_Write_App_Bin ( uint32_t ulStartAddr, u16 * pBin_DataBuf, uint32_t ulBufLength );
void send_to_server(unsigned char *source,unsigned short len_m);
unsigned char cache[len][11]={0};
unsigned char cache1[len][11]={0};
 short timeflag = 0; // ms 计时变量 
void uart_sendB1(unsigned char data);
void blink(void);
extern u8 test_count;
typedef struct ini{
	u16 flash_cache[600];
	u16 time_flag;
	u16 vect;
	u16 receflag;
	u16 init_flag;
	u16 count;
	u16 count_old;
	u16 sect;
	u16 lengh;
}Init;
Init init = {{0},0,0,2,0,0,0};
//Init init_o = {{0},0,0,1,1};
void softinit(void)
{
	SystemInit();
	
	
	//SetSysClockTo72();
	LED_GPIO_Config();	
	//
	
	LED1( ON );	  // LED1 ON;		
	Delay(0x2fffff);
	
	#if 0
	SPI_NRF_Init();
	status = NRF_Check(); 
	
	if(status == SUCCESS)
		LED1( ON );
	else
		LED1( OFF );
	NRF_TX_Mode();
	#else
	//RFGPIOInit();
	RFInit();	 //射频模块初始化
	RFRxMode();	 //进入接收模式
	#endif
	//LED1( OFF );	  // LED1 ON;	
	//LED1( OFF );	  // LED2 ON;		
		/* USART1 配置模式为 115200 8-N-1，中断接收 */
	USARTx_Config();
	USART1x_Config();
	USARTx_Config3();
	USER_CAN_Init();	
	USER_CAN_Test();
/* 通用定时器 TIMx,x[2,3,4,5] 定时配置 */	
  TIMx_Configuration();
	/* 配置通用定时器 TIMx,x[2,3,4,5]的中断优先级 */
	TIMx_NVIC_Configuration();
	/* 通用定时器 TIMx,x[2,3,4,5] 重新开时钟，开始计时 */
	macTIM_APBxClock_FUN (macTIM_CLK, ENABLE);
	
	
}
#include "define.h"

short signalflag;
 unsigned char rdatacache[cachelen+1][cachelen1];
 char rdata[size_array];
 unsigned char remote_sendflag2=0 ;//????
unsigned char remote_sendflag1=0 ;//????
extern unsigned short send_len;//??????
 //unsigned char rdatacache[cachelen+1][cachelen1];
 unsigned short m_freedelay=0;	
short can_flag=0;

 unsigned short rdata3[300]={0};
void handle_can(void);
unsigned char rxbuffer[32];
//extern unsigned char find(unsigned short *rdat,unsigned short source);
void judge(void);
 
 void test(void)
 {
	 short t=0,a;
	 test_count=0;
	
	 if(test_count>5)
		 test_count=0;
	 cache_clear();
	 t = get_len_dat3();
	// search_single(0);
	// search_single(11);
	 for(a=0;a<t;a++)
	// if(a!=0 && a!=11)
	 search_single(a);
	  searchL();
	 
 }
  short Change(char s[],char bits[]) {
	 short i,n = 0;
	 for(i = 0; s[i]; i += 2) {
		 if(s[i] >= 'a' && s[i] <= 'f')
		 bits[n] = s[i] - 'a' + 10;
		 else bits[n] = s[i] - '0';
		 if(s[i + 1] >= 'a' && s[i + 1] <= 'f')
		 bits[n] = (bits[n] << 4) | (s[i + 1] - 'a' + 10);
		 else bits[n] = (bits[n] << 4) | (s[i + 1] - '0');
		 ++n;
	 }
	 return n;
 }
	short mainflag=0;
 u16 ledcount=0;
 u16 mainchar[15]={
0xB1,0xA3,0xB6,0xA8,0xC4,0xCF,
0xD4,0xE6,0xD1,0xF4,0x20,0x20,
0x31,0xC9,0x3D
};



//	STMFLASH_Write(0x8009000,tempnum,1);
	//STMFLASH_Read	(0x8009000,tempq,1);
void init_jlb(){
	init_2();//初始化xhj
	init_3();//初始化fx
	init_4();//初始化yy
	init_5();//初始化dl
	init_6();//初始化fxg
	init_7();//初始化zm
	init_8();//初始化qj
}
uint16_t temp[12];   //????ID?????

void Get_ChipID(void)
{
    u32 temp0,temp1,temp2;
    temp0 = *(__IO u32*)(0x1FFFF7E8);    //???????????(96?)
    temp1 = *(__IO u32*)(0x1FFFF7EC);
		temp2 = *(__IO u32*)(0x1FFFF7F0);

//ID???: 0x1FFFF7E8   0x1FFFF7EC  0x1FFFF7F0 ,??????????????????

    temp[0] = (u8)(temp0 & 0x000000FF);
    temp[1] = (u8)((temp0 & 0x0000FF00)>>8);
    temp[2] = (u8)((temp0 & 0x00FF0000)>>16);
    temp[3] = (u8)((temp0 & 0xFF000000)>>24);
    temp[4] = (u8)(temp1 & 0x000000FF);
    temp[5] = (u8)((temp1 & 0x0000FF00)>>8);
    temp[6] = (u8)((temp1 & 0x00FF0000)>>16);
    temp[7] = (u8)((temp1 & 0xFF000000)>>24);
    temp[8] = (u8)(temp2 & 0x000000FF);
    temp[9] = (u8)((temp2 & 0x0000FF00)>>8);
    temp[10] = (u8)((temp2 & 0x00FF0000)>>16);
    temp[11] = (u8)((temp2 & 0xFF000000)>>24);         
}
int main(void)
{

	//	IAP_Write_App_Bin ( 0x8007000,init.flash_cache,500 );//更新FLASH代码 
	//char shuju[]="010b000000000011840002000120000800028000800080008000800080008000800080008000800080008000800040082180420821841042008400000000008008020c0000181500000100010011115555551116565515516106000800000000000000000220000008022020000800100000000000000000000000000000000000000000000000000000000000";
	//char shuju2[]="018400000000001174000200010001800040002000200020002000000210420821841042082184104200440200400000000000cff0f010e75051f14401000300001111152111111152265505000001000000000000000000000220200008002020000821840000888aa210100a0000000000000000000000000000002100feab";
	//Change(shuju,rdata);
	//char shuju[]="012006111001001004ff08";
	//Change(shuju,cache[0]);
//	read_flash(temparr,2,0,0xfffb);
//IAP_Write_App_Bin ( 0x8005000+10+(5)*500,init.flash_cache,500 );//更新FLASH代码 
	//IAP_Write_App_Bin ( 0x8005010+(5)*500,init.flash_cache,500 );//更新FLASH代码 
	u16 temp_flash[11]={0};
		Get_ChipID();
	softinit();
	STMFLASH_Read	(0x08006000-0x400,temp_flash,10);
	if(temp_flash[9]!=0xff00)
	init.init_flag=1;
	else
	{
	init.init_flag=0;
	init_jlb();
	send_moni(0,0,0,0);
	}
//init.init_flag=1;
//send_m_xinhao(365,1);

	

	
	Delay(0xfffff);
	
	   while(1)
 {
	
	if(init.init_flag==0)
	{
		Delay(0xfff);
		if(rdata[0]==1)
		{
			if(remote_sendflag2 == 1 && send_len > 0)
				send_to_server(rdata,send_len);

			
		if(m_freedelay>=120)
		{
			send_moni(0,0,0,0);
			m_freedelay=0;
		}
		
			m_freedelay++;
			Judge();
		
			test();
		blink();
		
		//	Change(shuju2,rdata);
		}
	
		if(rdatacache[0][0]!=0)
		{
			//_delay_ms(10);
		
			//while(rx12()!=0&&rdatacache[0][10]==3);
			//test();
		}
		
	}
	//else
	{
		/*fd0bfd011000000000000000ff08
		cache1[0][0]=0xfd;
		cache1[0][1]=0xfd;
		cache1[0][2]=0xfd;
		cache1[0][3]=0xfd;
		cache1[0][4]=0xfd;
		cache1[0][5]=0xfd;
		cache1[0][6]=0xfd;
		cache1[0][7]=0xfd;
		cache1[0][8]=0xfd;
		cache1[0][9]=0xfd;
		cache1[0][10]=0xfd;*/
		if( cache[0][9]!=0 )
		{
			handle_can();
		//	rxmode();
		}
	}
		
	//sendcast();

	
 }
}
void blink(void)
{
	ledcount++;
		
			if(ledcount%2==0)
			LED1( ON );	
			else
			LED1( OFF );	
		
}
void uart_sendB1(unsigned char data)
{
	Usart_SendByte(USART2,(uint8_t) data);
	
}

void handle_can(void)
{unsigned char i,j,b; 
	//rxbuffer[30]=0;
	search_can(cache[0]);
	for(b=0;b<len-2;b++)
	if(cache[b][9]==0)break;
	if(remote_sendflag1 == 1 )
	
	{send_to_server(cache[0],11);}
	for(i=0;i<len-1;i++)
			for(j=0;j<11;j++)
			cache[i][j]=cache[i+1][j];

}
u8 head_count=0,temp_receflag=2;
u16 time4=0,time2=0,reflag=0;
void  macTIM_INT_FUN (void)
{
	if ( TIM_GetITStatus( macTIMx, TIM_IT_Update) != RESET ) 
	{	
		if(remote_sendflag1==1)
		{ //uart_sendB1(0xfc);	
			if(timeflag%2000==0)
			{ remote_sendflag1=0;
			//uart_sendB1(remote_sendflag1);
			}
		}
		else
			timeflag=0;
		timeflag++;
		if(init.init_flag==1){
			if(reflag>5)
				init.init_flag=0;
		init.time_flag++;
		if(init.time_flag==100&&init.sect==0)
		{
			init.count_old=0;
			uart_sendB1(0x53);
			init.time_flag;
		}
	
		
		if(init.time_flag==2000)
		{
			init.init_flag=1;
			init.receflag=2;
			init.time_flag=0;
			init.vect = 0;
			//init.count = 0;
			//init.sect=0;
			head_count=0;
			temp_receflag=2;
			init.count=init.count_old;
			reflag++;
			if(init.sect>0)
			{
			
				uart_sendB1(0x27);
			}
			
			//else
			//uart_sendB1(0x53);
			init.lengh=0;
		}
		}
		else
		{
			time4++;
			if(time4>60000)
			{
			LED2( OFF );	//reset
			Delay(0xfffff);
			LED2( ON );	
			time4=0;
			}
			time2++;
			if(time2>1000){
			uart_sendB1(0x31);
			uart_sendB1(remote_sendflag2);	
			uart_sendB1(remote_sendflag1);	
			time2=0;
		
		}
		
		}
		
		
		TIM_ClearITPendingBit(macTIMx , TIM_FLAG_Update);  		 
	}		 	
}
u16 temp_no=0,temp_num=2001;
u8 head[20]={0},endflag=0;
void USART2_IRQHandler(void)//internet
{
	uint8_t ch;
	
	if(USART_GetITStatus(mac1USARTx, USART_IT_RXNE) != RESET)
	{ 	
	    //ch = USART1->DR;
			ch = USART_ReceiveData(mac1USARTx);
		if(init.init_flag!=0)
	
		{
			
			if(init.vect<9999&&init.receflag==1)///开始接收数据
			{
				if(init.count%2==1)
				init.flash_cache[init.vect++]|=ch<<8;
				else
				init.flash_cache[init.vect]=ch;
			init.count++;
			init.lengh--;
			if(init.lengh==0){
			
				temp_receflag=2;
			if(init.sect>0)
			{u32 address=0x8006000+(init.sect-1)*512*2;
				u16 vect=init.vect;
				//IAP_Write_App_Bin ( address,init.flash_cache,vect );//更新FLASH代码 
			init.vect=0,init.sect++;
				if(endflag){
				uart_sendB1(0x28);
				uart_sendB1(init.count/2>>8);
				uart_sendB1(init.count/2%256);
				temp_receflag=0;
				}
					else
				uart_sendB1(0x26);
					init.count_old=init.count;
				IAP_Write_App_Bin ( address,init.flash_cache,vect ); }//下一帧
			if(init.sect==0)
			{IAP_Write_App_Bin ( 0x8005c00,init.flash_cache,512 );//更新FLASH代码 
			init.vect=0,init.sect++;init.count_old=init.count;
			uart_sendB1(0x26);}//下一帧
			init.time_flag=0;
		}
			}
			if(init.receflag==2)//包头
			{head[head_count++]=ch;
			if(head_count==6)
			{	head_count=0;
			init.lengh=head[5]*256+head[4];
		//	init.receflag=1;
			if(head[3]==0x01)
				endflag=1;
			temp_receflag=1;
			
			}
			}
			if(init.receflag==0)////////接收结束处理
				if(ch==0x06)
				{
					//IAP_Write_App_Bin ( 0x8005000+(init.sect)*500,init.flash_cache,init.vect );//更新FLASH代码 
						//STMFLASH_Write(0x8015000,init.flash_cache,init.vect);
						//STMFLASH_Read	(0x8015000,hahaha,15);
						
					uart_sendB1(0x29);//complete
					Delay(0xfffff);
					init.init_flag=0;
					init_jlb();
					send_moni(0,0,0,0);
					
				}
		}
		else
		{//////////////命令区
		if(0x34==ch)
		{
		__disable_fault_irq();   
        NVIC_SystemReset();
		}
		if(0x35==ch)
		{
		time4=0;
		}
		if(0x30==ch)
		{
		//__disable_fault_irq();   
    //    NVIC_SystemReset();
			init.init_flag=1;
			init.receflag=2;
			init.time_flag=0;
			init.vect = 0;
			init.count = 0;
			init.sect=0;
			init.lengh=0;
			endflag=0;
			temp_receflag=2;
			uart_sendB1(0x31);
			head_count=0;
			reflag=0;
		}
		if(0x32==ch)//回传can
		remote_sendflag1=!remote_sendflag1;
		if(0x31==ch)//回传usart
			remote_sendflag2=!remote_sendflag2;
		if(0x41==ch)
		fac_to_server();
		
		}
		
	}
	
	init.receflag=temp_receflag;
	 
}
static uint16_t ulBuf_Flash_App [ 1024 ];
void IAP_Write_App_Bin ( uint32_t ulStartAddr, u16 * pBin_DataBuf, uint32_t ulBufLength )
{
	uint16_t us, usCtr=0, usTemp;

	uint32_t ulAdd_Write = ulStartAddr;                                //当前写入的地址
	
	u16 * pData = pBin_DataBuf;
	
	
	for ( us = 0; us < ulBufLength; us ++ )
	{
		usTemp = ( uint16_t ) pData[0];	  
		pData += 1;                                                      //偏移2个字节
		ulBuf_Flash_App [ usCtr ++ ] = usTemp;	    
		if ( usCtr == 512 )
		{
			usCtr = 0;
			STMFLASH_Write ( ulAdd_Write, ulBuf_Flash_App, 512 );	
			ulAdd_Write += 1024;                                           //偏移2048  16=2*8.所以要乘以2.
		}
	}

	if ( usCtr ) STMFLASH_Write ( ulAdd_Write, ulBuf_Flash_App, usCtr );//将最后的一些内容字节写进去.  
	
}
