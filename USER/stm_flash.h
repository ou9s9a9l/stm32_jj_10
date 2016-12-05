#ifndef __STMFLASH_H__
#define __STMFLASH_H__



#include "stm32f10x.h"



/************************************ STM32 �ڲ� FLASH ���� *********************************/
#define macSTM32_FLASH_SIZE 128 	 		      //��ѡSTM32��FLASH������С(��λΪK)
#define macSTM32_FLASH_WREN 1              //ʹ�� FLASH д��(0��������;1��ʹ��)



/************************************ STM32 �ڲ� FLASH �������� *********************************/
uint16_t STMFLASH_ReadHalfWord ( uint32_t faddr );		  //��������  
void     STMFLASH_WriteLenByte ( uint32_t WriteAddr, uint32_t DataToWrite, uint16_t Len );	      //ָ����ַ��ʼд��ָ�����ȵ�����
uint32_t STMFLASH_ReadLenByte  ( uint32_t ReadAddr, uint16_t Len );					                    	//ָ����ַ��ʼ��ȡָ����������
void     STMFLASH_Write        ( uint32_t WriteAddr, uint16_t * pBuffer, uint16_t NumToWrite );		//��ָ����ַ��ʼд��ָ�����ȵ�����
void     STMFLASH_Read         ( uint32_t ReadAddr, uint16_t * pBuffer, uint16_t NumToRead );   	//��ָ����ַ��ʼ����ָ�����ȵ�����
void     Test_Write            ( uint32_t WriteAddr, uint16_t WriteData );                        //����д��		



#endif

















