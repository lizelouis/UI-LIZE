#ifndef _DATA_SAVE_LIB_H
#define _DATA_SAVE_LIB_H

#include "makos_kernel_includes.h"

#define STM32_FLASH_SAVE_ADDR  0X08070000

typedef enum
{
	UINT32,
	FLOAT
}datatype_TypeDef;

typedef	struct
{
	dnode_t		dnd;
	datatype_TypeDef datatype;
	uint32_t * p_uint32_t;
	float * p_float;
}flash_list_t, *p_flash_list;

void	flash_list_init();
void	flash_list_add(datatype_TypeDef datatype, void * p_data);
void 	data_read();
void 	data_save();


#endif