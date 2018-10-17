#include "flash.h"
#include "makos_kernel_includes.h"
#include "data_save_lib.h"
#include "stm32_flash.h"

dnode_t	dhead_flash;

void	flash_list_init()
{
	dndqueue_init(&dhead_flash);
}

void	flash_list_add(datatype_TypeDef datatype, void * p_data)
{
	p_flash_list	pr;
	
	pr		= (p_flash_list)mymalloc(SRAMIN,sizeof(p_flash_list));
	pr->datatype = datatype;
	if(pr->datatype == FLOAT)
		pr->p_float = (float *)p_data;
	else
		pr->p_uint32_t = (uint32_t *)p_data;
	dndqueue_add_last(&dhead_flash, &pr->dnd);
	
}

U32 Float2U32(float data)    ///////???32?
{
  u8 * point;
  point = (u8*)(&data);
  return (((u32)point[3] << 24) | ((u32)point[2] << 16) | ((u32)point[1] << 8) | ((u32)point[0]));
}


float U322Float(u32 * data)   /////32????
{
  return (*((float *)data));
}

#define FLASH_BUFF_LENTH 20

void data_save()
{
	p_dnode curr;
	p_flash_list pr;
	curr	= dhead_flash.next;
	U32 data_save_buff[FLASH_BUFF_LENTH];
	U32 data_num = 0;
	
	while(curr != &dhead_flash)//遍历所有resolve
	{
		pr	= CONTAINER_OF(curr, flash_list_t, dnd);
		if(pr->datatype == FLOAT)
			*(data_save_buff + data_num) = Float2U32(*pr->p_float);
		else
			*(data_save_buff + data_num) = *pr->p_uint32_t;
		data_num++;
		curr	= curr->next;
	}
	
	//STM32_FLASH_Write(STM32_FLASH_SAVE_ADDR,(u16 *)data_save_buff,2*data_num);	
	Flash_EraseSector(FLASH_Sector_7);
	Flash_Write16BitDatas(STM32_FLASH_SAVE_ADDR,2*data_num,(u16 *)data_save_buff);
}

void data_read()
{
	p_dnode curr;
	p_flash_list pr;
	curr	= dhead_flash.next;
	U32 data_read_buff[FLASH_BUFF_LENTH];
	U32 data_num = 0;
	
	//STM32_FLASH_Read32(STM32_FLASH_SAVE_ADDR,data_read_buff,FLASH_BUFF_LENTH);
	Flash_Read32BitDatas(STM32_FLASH_SAVE_ADDR,FLASH_BUFF_LENTH,data_read_buff);
	
	while(curr != &dhead_flash)//遍历所有resolve
	{
		pr	= CONTAINER_OF(curr, flash_list_t, dnd);
		if(pr->datatype == FLOAT)
			*pr->p_float = U322Float((data_read_buff + data_num));
		else
			*pr->p_uint32_t = data_read_buff[data_num];
		data_num++;
		curr	= curr->next;
	}	
}