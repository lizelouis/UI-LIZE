#include "data_save_lib.h"
#include "UI.h"
#include "data_save.h"

/*
ʹ��˵����
	֧���������ͣ�
		float,U32
	��datasave_set()�������Ҫ��������ݼ�����(�˲�������data_save(),data_read())
	data_read(),data_save()�ֱ����ڶ�ȡ�뱣��
	�����ַΪ�� STM32_FLASH_SAVE_ADDR  0X08070000(����data_save_lib.h���޸�)
*/

void datasave_set()
{
	flash_list_init();
	flash_list_add(UINT32, &test1);
	flash_list_add(FLOAT, &test2);
	flash_list_add(UINT32, &test3);
	flash_list_add(FLOAT, &test4);
}

