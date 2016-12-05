/*
 * judge.c
 *
 * Created: 2015/11/21 10:39:39
 *  Author: xiao
 */ 

#include "define.h"

extern unsigned short rx0x12,rx0x11;
extern char rdatatemp[size_array];
extern	short signalflag;
extern	char rdata[size_array];
extern	unsigned short rdata3[300];

extern unsigned char rdatacache[cachelen+1][cachelen1];
void handle_data(unsigned char temp);
unsigned short CRC1(char* pBuf,short Len);


void add(unsigned char Data2,unsigned char Data1,volatile unsigned short Ident);

void cut(unsigned short Num);
#define DELAY 50
#define DEVIDE 9
#define ConSize 7

#define Startcharlen 10
#define SELECT 2010
#define collectlen  1
const unsigned short start1[collectlen]={0/*,625,770*/};
const unsigned short last1[collectlen]={144/*,640,820*/};
const unsigned short start12[collectlen]={0,/*975,2424,78,96*/};
const unsigned short last12[collectlen]={640,/*1515,2464,80,103*/};
unsigned short Quest_len_int(unsigned short *Par);


char rdata1[size_array]={0};


typedef struct BYTE_BIT
{
    unsigned BIT0:1;
    unsigned BIT1:1;
    unsigned BIT2:1;
    unsigned BIT3:1;
    unsigned BIT4:1;
    unsigned BIT5:1;
    unsigned BIT6:1;
    unsigned BIT7:1;
}BYTEBIT,*BYTEBIT1;


BYTEBIT  Cdata1,Cdata2;
#define FORMAT(Addr) SET_BIT8_FORMAT(Addr)
# define SET_BIT8_FORMAT(Addr)     (*((volatile BYTEBIT *)&Addr))
//#ifdef Cdata1
#define Cdat1_0   Cdata1.BIT0
#define Cdat1_1   Cdata1.BIT1
#define Cdat1_2   Cdata1.BIT2
#define Cdat1_3   Cdata1.BIT3
#define Cdat1_4   Cdata1.BIT4
#define Cdat1_5   Cdata1.BIT5
#define Cdat1_6   Cdata1.BIT6
#define Cdat1_7   Cdata1.BIT7
//#endif
//#ifdef Cdata2
#define Cdat2_0   Cdata2.BIT0
#define Cdat2_1   Cdata2.BIT1
#define Cdat2_2   Cdata2.BIT2
#define Cdat2_3   Cdata2.BIT3
#define Cdat2_4   Cdata2.BIT4
#define Cdat2_5   Cdata2.BIT5
#define Cdat2_6   Cdata2.BIT6
#define Cdat2_7   Cdata2.BIT7
	volatile unsigned char flag_12 = 0;
unsigned short rx12(void)
{
	unsigned short a,b=0,c=0,d=0,e=0,tempNum,len=0;
	for (b=0;b<cachelen;b++)
	if(rdatacache[b][0]==0)
	break;
	flag_12++;
	b--;//×??ó????
	for (a=0;a<rdatacache[b][Startcharlen];a++)
	{
		c=0;
		tempNum=rdatacache[b][a*2+Startcharlen+2];//10
		tempNum|=rdatacache[b][a*2+Startcharlen+3]<<8;
		for (d=0;d<collectlen;d++)
		 if((tempNum&0x0fff)>=start1[d]*8&&(tempNum&0x0fff)<=last1[d]*8)
				{
					if (tempNum&0x8000)
					{
						len=Quest_len_int(rdata3);
						for (e=0;e<len;e++)
						{
						
						if(((tempNum&0x0fff)+1)==rdata3[e])
						c=1;
						}
						if (c==0)
						{
							rdata3[len]=(tempNum&0x0fff)+1;
						}
					}
					else
					cut((tempNum&0x0fff)+1);
					
				}
			
	}
	for (a=0;a<cachelen1;a++)
		rdatacache[b][a]=0;
	
	return b;
}

void cut(unsigned short Num)
{
	unsigned char b,len;
		for(b=0;b<Quest_len_int(rdata3);b++)
			if(rdata3[b]==Num)
			{
				len=Quest_len_int(rdata3);
				for(;b<len;b++)rdata3[b]=rdata3[b+1];
			}
}

void Judge(void)//????????rxdata?? ??????????????????   05 51  ??????????51
{
	 unsigned short b=0,a=0,d=0;
	for (b=0;b<300;b++)
		rdata3[b]=0;
		for (d=0;d<collectlen;d++)
		for (a=start1[d]+Startcharlen;a<last1[d]+Startcharlen;a++)
		{
	
	#if SELECT==2010
		add(0,rdata[a],a); 
	#endif
	#if SELECT==2006                          //????2010
		add1(rdata1[a],rdata[a],a);	
	#endif
	#if SELECT==2009						   //????zyz
	add(rdata1[a],rdata[a],a);
	#endif
		}
	
	for(a=0;a<size_array;a++)
	{rdata1[a]=rdata[a];}
	for(a=0;a<size_array;a++)
	{rdata[a]=0;}

}

////////////////////////////////////////??////////////////////////////////////////////////////////////////////////////////
unsigned short Quest_len_int(unsigned short *Par)
{
//unsigned char b=0;
unsigned short a=0;
	for(a=0;a<size_array;a++)
	if(Par[a]==0)
		break;
return a;
}


unsigned char find(unsigned short *rdat,unsigned short source)
{
	unsigned short b=0,temp,a;
	temp=Quest_len_int(rdat);

	for (a=0;a<=temp;a++)
	{if(rdat[a]==source)return 1;}
	
	return 0;
}




/////////////////////////////////////add////////////////////
void add(unsigned char Data2,unsigned char Data1,volatile unsigned short Ident)
{
	
	volatile unsigned short dat=0;
	Cdata1=FORMAT(Data1);
	Cdata2=FORMAT(Data2);
	dat=Ident*8-Startcharlen*8+1;//4*8-1
	if(Cdat1_0>Cdat2_0&&!find(rdata3,dat+0))
	{rdata3[Quest_len_int(rdata3)]=dat+0;
	}
	
	if(Cdat1_1>Cdat2_1&&!find(rdata3,dat+1))
	{rdata3[Quest_len_int(rdata3)]=dat+1;
	//if(find(rdata2,(dat+6))&&(!find(rdata4,(dat+6))))addto4_last(dat+6);
	}
	
	if(Cdat1_2>Cdat2_2&&!find(rdata3,dat+2))
	{rdata3[Quest_len_int(rdata3)]=dat+2;
	}

	
	if(Cdat1_3>Cdat2_3&&!find(rdata3,dat+3))
	{rdata3[Quest_len_int(rdata3)]=dat+3;
	//if(find(rdata2,(dat+4))&&(!find(rdata4,(dat+4))))addto4_last(dat+4);
	}
	
	if(Cdat1_4>Cdat2_4&&!find(rdata3,dat+4))
	{rdata3[Quest_len_int(rdata3)]=dat+4;
	}
	
	if(Cdat1_5>Cdat2_5&&!find(rdata3,dat+5))
	{rdata3[Quest_len_int(rdata3)]=dat+5;
	//if(find(rdata2,(dat+2))&&(!find(rdata4,(dat+2))))addto4_last(dat+2);
	}
	
	if(Cdat1_6>Cdat2_6&&!find(rdata3,dat+6))
	{rdata3[Quest_len_int(rdata3)]=dat+6;
	}
	
	if(Cdat1_7>Cdat2_7&&!find(rdata3,dat+7))
	{rdata3[Quest_len_int(rdata3)]=dat+7;
	//if(find(rdata2,(dat+0))&&(!find(rdata4,(dat+0))))addto4_last(dat+0);
	}
	
	/*if(Cdat1_0<Cdat2_0&&Cdat1_0==0){cut((dat+0));}
	if(Cdat1_1<Cdat2_1&&Cdat1_1==0){cut((dat+1));}
	if(Cdat1_2<Cdat2_2&&Cdat1_2==0){cut((dat+2));}
	if(Cdat1_3<Cdat2_3&&Cdat1_3==0){cut((dat+3));}
	if(Cdat1_4<Cdat2_4&&Cdat1_4==0){cut((dat+4));}
	if(Cdat1_5<Cdat2_5&&Cdat1_5==0){Z//76666666
		cut((dat+6));}
	if(Cdat1_7<Cdat2_7&&Cdat1_7==0){cut((dat+7));}*/

	
 }
