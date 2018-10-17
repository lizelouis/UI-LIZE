#include "data_save_lib.h"
#include "UI.h"
#include "data_save.h"

/*
使用说明：
	支持数据类型：
		float,U32
	在datasave_set()中添加需要储存的数据及类型(此步必先用data_save(),data_read())
	data_read(),data_save()分别用于读取与保存
	保存地址为： STM32_FLASH_SAVE_ADDR  0X08070000(可在data_save_lib.h中修改)
*/

void datasave_set()
{
	flash_list_init();
	flash_list_add(UINT32, &test1);
	flash_list_add(FLOAT, &test2);
	flash_list_add(UINT32, &test3);
	flash_list_add(FLOAT, &test4);
}

