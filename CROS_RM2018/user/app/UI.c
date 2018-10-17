#include "UI.h"
#include "keyboard.h"
#include "oled.h"
#include "UI_lib.h"
#include "data_save.h"

/*
使用说明：
	三种页面类型：
		FUNC(该页面下的选项为执行某一自定义函数，需自行添加自定义函数)
		DIG(该页面下的选项为修改相应的参数)
		SHOW(该页面下没有选项，为反复执行某一自定义函数，常用来显示一些曲线或者观察变量变化)
	每种页面的创建及设置以下均有示例。
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
	//主页面
	PAGE_SET_MAIN(main_page,FUNC,4);
	PAGE_FUNC(main_page,0,"param_set1",param_set);
	PAGE_FUNC(main_page,1,"param_set2",param_set2);
	PAGE_FUNC(main_page,2,"save_data",OLED_data_save);
	PAGE_FUNC(main_page,3,"show_data",data_show);
	//参数修改页面1
	PAGE_SET(param_set_page,DIG,2);
	PAGE_PARAM(param_set_page,0,"steer_PID_P",test1,UINT32);//第一行显示参数设置
	PAGE_PARAM(param_set_page,1,"steer_PID_D",test2,FLOAT);//第二行显示参数设置
	//参数修改页面2
	PAGE_SET(param_set2_page,DIG,2);	
	PAGE_PARAM(param_set2_page,0,"PID_P",test3,UINT32);
	PAGE_PARAM(param_set2_page,1,"PID_D",test4,FLOAT);
	//变量显示页面
	PAGE_SET(data_Show_page,SHOW,NULL);	
	PAGE_SHOW(data_Show_page,data_show_callback);

}

void OS_menu(void)//用户调用的函数，完成UI初始化，开启第一页
{
	page_init();
	UI_show(&main_page);
}

//**************由UI自行调用的函数,用户自行设置，注意不同页面的衔接*****************
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
