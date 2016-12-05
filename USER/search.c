/*
 * search.c
 *
 * Created: 2015/11/21 10:39:54
 *  Author: xiao
 */ 
//#include "bdn.h"
//#include "ryz.h"
//#include "stm32f10x.h"  
#include "xjc.h"
#include "bsp_spi_nrf.h"
#ifndef FLAG // 0???
#define FLAG 0
#endif
#define time 35// zm:35?  zm2:0?
#define STARTADDR 0x8006000

//#include "bdn1.h"
/*
unsigned short dat5[][12];
unsigned short dat3[][12];
unsigned short dat4[][12];
unsigned short dat2[][12];
unsigned short dat1[][8];	
unsigned short dat0[][10];*/
//#include "bdn_txt.h"

unsigned char err[DATLEN];
extern u8 status;
extern unsigned char remote_sendflag2 ;//????
extern unsigned short m_freedelay;	
extern unsigned short rdata3[300];
extern unsigned char find(unsigned short *rdat,unsigned short source);
extern u16 time2;
unsigned char flag_8 = 0;
unsigned char flag_9 = 0;
unsigned short flag1 = 0;
unsigned char Quest_len_int(unsigned short *Par);
unsigned char search(unsigned short *condition,unsigned char flag);
//unsigned char temp = 0;
void send_moni(unsigned char b,unsigned char c,unsigned char d,unsigned char e);
//unsigned short hei=0;
void show_str(unsigned char *str);
void cache_plus(unsigned char num);
void board_num(unsigned char num);

u8 test_count=0;
///////conditon
void send_to_server(unsigned char *source,unsigned short len_m)
{
	unsigned int i = 0;
	uart_sendB1(0xfd);
	uart_sendB1(len_m);
	uart_sendB1(0xfd);
	
	for(i=0;i<len_m;i++)
		uart_sendB1(source[i]);
	
}

void fac_to_server(void){
send_to_server((unsigned char *)factor[0],72);
}
void searchL(void)
{
	unsigned short temp,c,frontche;
	for(c=0;c<CON_LENGTH;c++)
	{
		if (find(rdata3,conditon[c][0]))
		{
			if(conditon[c][3] == 0)
			{
				//show_str(txt[conditon[c][1]]);//??±¨
				if(conditon[c][2] != 0)
				{
					if(conditon[c][4] != 0)
					frontche=find(rdata3,conditon[c][4]);
					else
					frontche=0;
					temp = factor[conditon[c][2]][1]+40;
					if(temp != 40&& frontche==0)//
					{
						//send_moni(1,2,3,4);
						if(conditon[c][2]==5)
						send_moni(conditon[c][1],temp,1,c);
						else if(conditon[c][2]==7)
						send_moni(conditon[c][1],temp,2,c);
						else if(conditon[c][2]==6)
						send_moni(conditon[c][1],0,1,c);
						else if(conditon[c][2]==8)
						send_moni(conditon[c][1],0,2,c);
						else
						send_moni(conditon[c][1],temp,0,c);
					}
					else/////Ã»ÓÐ¾­Â·
					{
						if(conditon[c][1]!=204&&conditon[c][1]!=214)
						{
						if(conditon[c][2]==5||conditon[c][2]==6)
						send_moni(conditon[c][1],0,1,c);
						else if (conditon[c][2]==7||conditon[c][2]==8)
						send_moni(conditon[c][1],0,2,c);
						else
						send_moni(conditon[c][1],0,0,c);
						}
					}
				
				}
				else
				send_moni(conditon[c][1],0,0,c);
				
				
				conditon[c][3]+=2;
			}
			
				
			conditon[c][3]++;
		}
		if(conditon[c][3] == 0)
		conditon[c][3] = 0;
		if(conditon[c][3]>0)
		conditon[c][3]--;
	}
	
	
}
////////////////////1£ºÊä³ö 2£º10ÖÖÊý¾ÝÀàÐÍµÄ±àºÅ 3£ºµÚ¼¸¸ö  4£º ·Ö¸ô·û
u8 read_flash(unsigned short *out,u8 pos,u8 num,u16 devide){
u16 b,count=0;
	u16 tempq[2000]={0},temp[11]={0};
	u16 start,end;

	STMFLASH_Read	(STARTADDR-0x400,temp,10);
	if(pos==0)
	start=0;
	else
	start=temp[pos-1];
	end=temp[pos];
	STMFLASH_Read	(STARTADDR+start,tempq,(end-start)/2);
	for(b=0;b<(end-start)/2;b++)
	{
		if(num==0)break;
		if(tempq[b]==devide)
		num--;
	}
	if(b>=(end-start)/2-1)
		return 1;
	else
	while(1)
	{if(tempq[b]==devide||count>20)break;
		out[count++]=tempq[b++];
	}
	return 0;
}
void read_dat0(unsigned short *RamVar,unsigned char num)
{
	char a;
	for( a = 0;a<15;a++)
	RamVar[a]=0;
read_flash(RamVar,0,num,0xfffa);
	/*for( a = 0;a<15;a++)
	{
		unsigned short b;
		b=dat0[num][a] ;
		if(b!=0)
		RamVar[a]= b ;
		else
		break;
	}*/
}

void read_dat2(unsigned short *RamVar,unsigned char num)
{
	char a;
	for( a = 0;a<15;a++)
	RamVar[a]=0;
	read_flash(RamVar,1,num,0xfffa);
	/*for( a = 0;a<15;a++)
	{
		unsigned short b;
		b=dat2[num][a] ;
		if(b!=0)
		RamVar[a]= b ;
		else
		break;
	}*/
}
u16 testnum=0;
const u8 factor_rela[8]={1,4,2,3,5,8,6,7};
volatile unsigned char result=1,result1 = 1,result2 = 1,bonum=0;
///////////////////////////////////////????
unsigned short search_single(unsigned char num)
{
	unsigned short dat[15]={0},boardnum=0,boardfx=0;

	result=1;result1=1;result2=1;
	
	{///pt
		result1 &= ( search(dat5[num][0],2)&&search(dat5[num][1],2) );
		if(result1==0){err[num]=1;return 0;}
	}

		
	
	read_dat0(dat,num);
	result &= search(dat,1);//???í
	if(result==0){err[num]=2;return 0;}
	//read_dat1(dat,num);
	//result &= search(dat,0);//????????
	//if(result==0)return 0;
	read_dat2(dat,num);
	result &= search(dat,1);//???ì
	if(result==0){err[num]=3;return 0;}
	
	//result2 &= search(dat,1);
	if(result==1&&result1==1)//success ???í
	{
		
		if((dat3[num]>140&&dat3[num]<160)||(dat3[num]>40&&dat3[num]<60)||factor[dat4[num][0]][1]==0)
		if(dat3[num]>factor[dat4[num][0]][1])
		{
			u8 factor_num=dat4[num][0],a,factor_num1=0;
			if(dat3[num]==testnum)
				err[0]=1;
			
			
			/*
			for(a=0;a<8;a++)
			if(factor_num==factor_rela[a])
				break;
			if(a%2==0)
				factor_num1=factor_rela[a+1];
			else
				factor_num1=factor_rela[a-1];
			
			if(factor[factor_num1][1]!=0&&(factor[factor_num1][1]%20==dat3[num]%20))
			*/
			for(a=1;a<9;a++)
			if(factor[a][1]%20==dat3[num]%20)
				factor_num1=a;
			if(factor_num1)
			{
				if(dat3[num]>factor[factor_num1][1])
				{factor[factor_num][1] = dat3[num]+20;
				factor[factor_num1][1] = dat3[num]+20;
				boardnum=dat3[num]+20;
				}
				else
				{factor[factor_num][1] = dat3[num]+40;
				factor[factor_num1][1] = dat3[num]+40;
				boardnum=dat3[num]+40;
				factor_num=factor_num1;}//½øÕ¾Î»²¥±¨·½Ïò
			}
			else
			{factor[dat4[num][0]][1] = dat3[num];
			boardnum=dat3[num];
			}
			//if(dat4[num][1]!=0)
			//factor[dat4[num][1]][1] = dat3[num];
			
			if(factor_num==5||factor_num==6)
			send_moni(boardnum,0,1,num);
			else if(factor_num==7||factor_num==8)
			send_moni(boardnum,0,2,num);
			else
			send_moni(boardnum,0,0,num);
			board_num(num);//
			for(a=0;a<5;a++)
			cache_plus(num);
		}
	//	if(dat3[num] == factor[dat4[num][0]][1])
		cache_plus(num);
		{err[num]=0xff;return 1;}
	}
	return 0;
}
void board_num(unsigned char num){
	//show_str(txt[dat3[num]]);//??±¨
}
void cache_plus(unsigned char num)
{
	factor[dat4[num][0]][2]++;	//success ?á??
	if(dat4[num][1]!=0)
	factor[dat4[num][1]][2]++;
}
void cache_clear(void)
{
		unsigned char a;
	unsigned short t = 0;
	t=sizeof(factor)/8;

	for(a=0;a<t;a++)
	{if(factor[a][2] == 0&&factor[a][1])//ÕÒ²»µ½factor[a][0]
	factor[a][1] = 0;
	
	}
	for(a=0;a<t;a++)
	if(factor[a][2]>0)
	factor[a][2]--;
}
///////////////////////////////////api/////////////////////////////////
unsigned short point = 0;
void show_str(unsigned char *str)
{
	if(point == 270) {point=0;}
	//LCD_ShowString(30,point+30,200,16,16,"                         ");		//??LCD ID
	//LCD_ShowString(30,point,200,16,16,str);		//??LCD ID
	point+=30;
}
// flag :1ÎªÅÐ¶ÏÓÐ 0 ÎªÅÐ¶ÏÃ»ÓÐ 2Îª»òÓÐÐÅºÅ»ú
unsigned char search(unsigned short *condition,unsigned char flag)
{
	unsigned short len=0,a;
	unsigned char result;
	len = Quest_len_int(condition);
	if(flag == 1)
	{
		result = 1;
		for(a=0;a<len;a++)
		result&=find(rdata3,condition[a]);
	}
	
	if(flag == 0)
	{	result = 0;
		for(a=0;a<len;a++)
		result|=find(rdata3,condition[a]);
		if(result == 1)result=0;else result = 1;
		if(len==0)result=1;
	}
	
	if(flag == 2)
	{result = 0;
		if(len==0)len = 1;
		for(a=0;a<len;a++)
		result|=find(rdata3,condition[a]);
	}
	return result;
	//
	//search(dat1[0]);
	//len++;
	//	 len = find(rdata3,0);
}

void read_prog(unsigned char *RamVar,unsigned char num)
{
	char a,c=0;
	for(a = 0;a<15;a++)
	RamVar[a]=0;
	
	for( a = 0;a<15;a++)
	{
		unsigned short b;
		b=s[num][a] ;
		if(b!=0)
		{RamVar[c++]= b ;
		RamVar[c++]= b>>8;}
		else
		break;
	}
}

unsigned char uart_count=0;
unsigned char uart_can=0;
void _delay_ms(__IO u32 nCount)
{
  for(; nCount != 0; nCount--);
} 
#define size_array 470
extern char rdata1[size_array];
extern unsigned char remote_sendflag1 ;//???
extern short timeflag ; // ms ¼ÆÊ±±äÁ¿ 
void send_moni(unsigned char b,unsigned char c,unsigned char d,unsigned char e)
{
	unsigned char RamVar[4][33]={0}; //?????????(Ram??)
	unsigned char send_dat[32]={0};
	short count = 0;

	unsigned char i=0,j=0,state;
	time2=0;
	test_count++;
	_delay_ms(time);
	//if(b>256){send_m_xinhao(b,0);return 0;}
	if(d==0)
	{read_prog(RamVar[0],0);
	read_prog(RamVar[1],1);
	}
	if(d==1)
	{read_prog(RamVar[0],0);
	read_prog(RamVar[1],2);
	}
	if(d==2)
	{read_prog(RamVar[0],0);
	read_prog(RamVar[1],3);
	}
	if(d==3)
	{read_prog(RamVar[0],0);
	read_prog(RamVar[1],4);
	}
	/*
	read_prog(RamVar[1],b);
	read_prog(RamVar[2],c);
	unsigned char k = 0;
	for(unsigned char i = 0;i<3;i++)
		for(unsigned char j = 0;j<30;j++)
		if(RamVar[i][j]!=0)
			RamVar[3][k++]=RamVar[i][j];*/
	
	for(i = 0;i<3;i++)
	{
		send_dat[j++] = s[0][i]; 
		send_dat[j++] = s[0][i]>>8; 
	}
	for(i = 0;i<6;i++)
	{
		if(RamVar[1][i]!=0)
		send_dat[i+6] = RamVar[1][i];
		else
		send_dat[i+6] = 0x20;
	}
	send_dat[12]=0x31;
	send_dat[13]=b;	
	send_dat[14]=c;
	
	m_freedelay=0;
	 uart_sendB1(0xff);
	 uart_sendB1(b);
	 uart_sendB1(c);
	 uart_sendB1(254-d);
	 uart_sendB1(count);
	 uart_sendB1(uart_count++);
	 uart_sendB1(e);
	 uart_sendB1(0xff);	
	if(status==SUCCESS){
state=NRF_Tx_Dat(send_dat);	
	if(state==ERROR)
			NRF_TX_Mode();}
//if(b!=0&&remote_sendflag2==0)	
	//{
	//send_to_server(rdata1,0x80);
	// remote_sendflag1=1;}
	//timeflag=0;


}
void send_m_xinhao(unsigned short xinhaodian,unsigned char num )
{
	
	short count = 0;
		unsigned char RamVar[4][33]={0}; //?????????(Ram??)
	unsigned char send_dat[32]={0};
	 unsigned char a,b;
		unsigned char i=0,j=0,state;
	for(i = 0;i<3;i++)
	{
		send_dat[j++] = s[0][i]; 
		send_dat[j++] = s[0][i]>>8; 
	}
	for(i = 0;i<6;i++)
	{
		send_dat[i+6] = 0x20;
	}
	send_dat[12]=0x32;
	send_dat[13]=0x30+xinhaodian/1000;
	send_dat[14]=0x30+xinhaodian%1000/100;
	send_dat[15]=0x30+xinhaodian%100/10;
	send_dat[16]=0x30+xinhaodian%10;
	//if(b==0)b=255;
	//if(c==0)c=255;
time2=0;
	_delay_ms(time);
m_freedelay=0;
	
	 a=xinhaodian>>8;
	 b=xinhaodian;
	 uart_sendB1(0xfe);
	 uart_sendB1(a);
	 uart_sendB1(b);
	 uart_sendB1(num);
	 uart_sendB1(count);
	 uart_sendB1(0x00);
	 uart_sendB1(0x00);
	 uart_sendB1(0xff);		
		if(status==SUCCESS){
state=NRF_Tx_Dat(send_dat);	
	if(state==ERROR)
			NRF_TX_Mode();}
	 /*unsigned char flag = send_int(send_dat);
	if(flag == 0)
	flag=send_int(send_dat);
	if(flag == 0)
	flag=send_int(send_dat);
*/
}

//01007f7f0000000000ff03
/*
02007f0f0000000000ff03
0b0000000000000000ff08
0b0102212008000000ff05
110000000002020000ff06
110000000002060000ff06
0c0045422004211008ff08
0c0104080422500000ff07
0b0000000000000000ff08
0b0102212000000000ff05
*/
//#define CAN_LENGTH 5             //

unsigned short search_single_can(unsigned char num,unsigned char *source);
unsigned char get_len_can()
{
	unsigned char t = 0;
	t=sizeof(conditon_can)/2/6;
	return t;
}
void search_can(unsigned char *source){
	unsigned char len = get_len_can();
	short a;
	for( a = 0;a<len;a++)
	{
		unsigned short board = search_single_can(a,source);
		if(conditon_can[a][5]==0&&board != 0)
		{conditon_can[a][5]=2;
			send_m_xinhao(board,a);
			
		}
		//<Buffer 11 00 00 08 40 00 00 00 00 ff 06>
		if(conditon_can[a][0]==source[0]&&conditon_can[a][1]==source[1]){
			if(board != 0 )
			conditon_can[a][5]++;
			if(conditon_can[a][5]!=0)
			conditon_can[a][5]--;
			//right
		}
		
	}
	
	//err
	
	};

	unsigned short search_single_can(unsigned char num,unsigned char *source){
	    //112d59720058000000ff06
	unsigned char pos,ana;
		if(conditon_can[num][0]!=source[0])//id
		return 0;
		if(conditon_can[num][1]!=source[2])//package num
		return 0;
	//	if(conditon_can[num][2]!=source[5])//package num
	//	return 0;
		if(source[9]!=0xff)//check num
		return 0;
		
		ana = source[ conditon_can[num][2]+2 ];
		//charnum   conditon_can[num][2] 1/2/3/4/5/6/7
		
		 pos = conditon_can[num][3];
		//posnum   conditon_can[num][3] 0/1/2/3/4/5/6/7
		ana>>=pos;
		ana&=0x01;
		if(ana == 0)
		return 0;
		else
		{
			
			return conditon_can[num][4];
		}
		
	};
	
	
	
	
	
	unsigned short get_len_dat3()
	{
		unsigned short t = 0,a=0;
		t=sizeof(dat3)/2;
		//return t;
		for(a;a<t;a++)
			if(dat3[a]==0xffff)
				break;
		return a;
	}
void set_num(u16 * temparr,u16 num){
	u8 b=0,vect=0,hori=0;
	while(temparr[b]!=0)
			{
			if(temparr[b]==0xfffa)
			{vect++;hori=0;}
			else
			dat5[num][vect][hori++]=temparr[b];
			b++;
			}
		
}
void set_num_pt(u16 * temparr,u16 * out,u8 num){
	u8 b=0,vect=0;
	for(b=0;b<num;b++)
			out[vect++]=temparr[b];
		
}
//////////////
void init_5(){///dl
			u16 temparr[20]= {0};
					u16 a=0,b=0;
	for(a=0;a<CON_LENGTH;a++)
	if(read_flash(temparr,5,a,0xfffa))//Ã»ÓÐÁË
		conditon[a][0]=0xffff;
	else
		//set num
		{set_num_pt(temparr,conditon[a],5);
		for(b=0;b<20;b++)
		temparr[b]=0;
		}
}
//////////////
void init_6(){///dl

			u16 temparr[20]= {0};
					u16 a=0,b=0;
			
	for(a=0;a<9;a++)
	if(read_flash(temparr,6,a,0xfffa))//Ã»ÓÐÁË
		factor[a][0]=0xffff;
	else
		//set num
		{
			set_num_pt(temparr,factor[a],4);//changdu
		for(b=0;b<20;b++)
		temparr[b]=0;
		}
}
void init_8(){///dl
			u16 temparr[20]= {0};
					u16 a=0,b=0;
	for(a=0;a<CON_LENGTH;a++)
	if(read_flash(temparr,8,a,0xfffa))//Ã»ÓÐÁË
		conditon_can[a][0]=0xffff;
	else
		//set num
		{set_num_pt(temparr,conditon_can[a],6);
		for(b=0;b<20;b++)
		temparr[b]=0;
		}
}
//////////////
void init_7(){///zm

			u16 temparr[20]= {0};
					u16 a=0,b=0;
			
	for(a=0;a<4;a++)
	if(read_flash(temparr,7,a,0xfffa))//Ã»ÓÐÁË
		s[a][0]=0xffff;
	else
		//set num
		{
			set_num_pt(temparr,s[a],4);//changdu
		for(b=0;b<20;b++)
		temparr[b]=0;
		}
}

void init_2(){
		u16 temparr[20]= {0};
					u16 a=0,b=0;
	for(a=0;a<DATLEN;a++)
	if(read_flash(temparr,2,a,0xfffb))//Ã»ÓÐÁË
		dat5[a][0][0]=0xffff;
	else
		//set num
		{set_num(temparr,a);
		for(b=0;b<20;b++)
		temparr[b]=0;
		}
}
void init_3(){
		u16 temparr[20]= {0};
			u16 a=0;
	for(a=0;a<DATLEN;a++)
	if(read_flash(temparr,3,a,0xfffa))//Ã»ÓÐÁË
		dat4[a][0]=0xffff;
	else
		//set num
		{dat4[a][0]=temparr[0];dat4[a][1]=temparr[1];
		temparr[0]=0;temparr[1]=0;}

}
void init_4(){
		u16 temparr[20]= {0};
	u16 a=0;
	for(a=0;a<DATLEN;a++)
	if(read_flash(temparr,4,a,0xfffa))//Ã»ÓÐÁË
		dat3[a]=0xffff;
	else
		//set num
		dat3[a]=temparr[0];
	
}
	
