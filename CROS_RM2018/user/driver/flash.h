#ifndef _FLASH_H
#define _FLASH_H

#include "stm32f4xx.h"


//�û������Լ�����Ҫ����
#define STM32_FLASH_SIZE 512 	 //��ѡSTM32��FLASH������С(��λΪK)

//FLASH��ʼ��ַ
#define STM32_FLASH_BASE 0x08000000 	//STM32 FLASH����ʼ��ַ
 
vu16 STM32_FLASH_ReadHalfWord(u32 faddr);
void STM32_FLASH_Read32(u32 ReadAddr,u32 *pBuffer,u32 NumToRead);
void STM32_FLASH_Write(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite);		//��ָ����ַ��ʼд��ָ�����ȵ�����
void STM32_FLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead);   		//��ָ����ַ��ʼ����ָ�����ȵ�����
void STM32_FLASH_Write32_NoCheck(u32 WriteAddr,u32 *pBuffer,u32 NumToWrite);					   

#endif
