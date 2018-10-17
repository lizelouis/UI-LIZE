#include "oled.h"
#include "tim3_4.h"
#include "time.h"
#include "keyboard.h"
#include "UI.h"
#include "task_oled.h"
#include "data_save.h"


//float a = 1.1;
//float b =2;
int a = 3;
float b = 2.2;

void	task_oled(void* param)
{
		TIM4_Init(1000,360-1);  //定时5ms
		OLED_Init();			//初始化OLED  
		key_init();
	 
		datasave_set();
	  data_read();
	
		OLED_Clear(); 
		
		OS_menu();		
	
	while(1)
	{
		task_suspend(ptcb_curr);
	}
}





