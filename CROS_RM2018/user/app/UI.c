#include "UI.h"
#include "keyboard.h"
#include "oled.h"
#include "UI_lib.h"
#include "data_save.h"

/*
ʹ��˵����
	����ҳ�����ͣ�
		FUNC(��ҳ���µ�ѡ��Ϊִ��ĳһ�Զ��庯��������������Զ��庯��)
		DIG(��ҳ���µ�ѡ��Ϊ�޸���Ӧ�Ĳ���)
		SHOW(��ҳ����û��ѡ�Ϊ����ִ��ĳһ�Զ��庯������������ʾһЩ���߻��߹۲�����仯)
	ÿ��ҳ��Ĵ������������¾���ʾ����
*/

Page_TypeDef main_page;
Page_TypeDef param_set_page;
Page_TypeDef param_set2_page;
Page_TypeDef data_Show_page;

int test1 = 1;
float test2 = 2;
int test3 = 1;
float test4 = 2;

void param_set(void);
void param_set2(void);
void OLED_data_save(void);
void data_show_callback(void);
void data_show(void);

void page_init()
{	
	//��ҳ��
	PAGE_SET_MAIN(main_page,FUNC,4);
	PAGE_FUNC(main_page,0,"param_set1",param_set);
	PAGE_FUNC(main_page,1,"param_set2",param_set2);
	PAGE_FUNC(main_page,2,"save_data",OLED_data_save);
	PAGE_FUNC(main_page,3,"show_data",data_show);
	//�����޸�ҳ��1
	PAGE_SET(param_set_page,DIG,2);
	PAGE_PARAM(param_set_page,0,"steer_PID_P",test1,UINT32);//��һ����ʾ��������
	PAGE_PARAM(param_set_page,1,"steer_PID_D",test2,FLOAT);//�ڶ�����ʾ��������
	//�����޸�ҳ��2
	PAGE_SET(param_set2_page,DIG,2);	
	PAGE_PARAM(param_set2_page,0,"PID_P",test3,UINT32);
	PAGE_PARAM(param_set2_page,1,"PID_D",test4,FLOAT);
	//������ʾҳ��
	PAGE_SET(data_Show_page,SHOW,NULL);	
	PAGE_SHOW(data_Show_page,data_show_callback);

}

void OS_menu(void)//�û����õĺ��������UI��ʼ����������һҳ
{
	page_init();
	UI_show(&main_page);
}

//**************��UI���е��õĺ���,�û��������ã�ע�ⲻͬҳ����ν�*****************
void param_set(void)
{
	UI_show(&param_set_page);
}

void param_set2(void)
{
	UI_show(&param_set2_page);
}

void OLED_data_save()
{
	OLED_ShowString(45,3, "save ok",1);
	task_delay_ms(500);
	data_save();
	OLED_Clear();
}

void data_show(void)
{
	UI_show(&data_Show_page);
}

U32 speed_test = 0;
U32 add_times = 0;
void data_show_callback(void)
{
	add_times++;
	if(add_times == 10)
	{
		speed_test++;	
		add_times = 0;
	}

	OLED_ShowString(32,3, "speed:",1);
	OLED_ShowNum(64,3,speed_test,3,8,1);
	if(speed_test == 200)
		speed_test = 0;
}
