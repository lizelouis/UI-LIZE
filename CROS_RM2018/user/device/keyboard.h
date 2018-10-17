#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include "stm32f4xx.h"
#include "stdlib.h"

#define KEY_LEFT_Pin    GPIO_Pin_7    //定义K_LEFT管脚
#define KEY_DOWN_Pin    GPIO_Pin_3    //定义K_DOWN管脚
#define KEY_RIGHT_Pin   GPIO_Pin_4   //定义K_RIGHT管脚
#define KEY_UP_Pin      GPIO_Pin_4 //定义KEY_UP管脚

#define KEY_LEFT_Port 	(GPIOD) //定义端口
#define KEY_UP_Port		  (GPIOE) //定义端口
#define KEY_DOWN_Port   (GPIOB)
#define KEY_RIGHT_Port  (GPIOB)


//使用位操作定义
//#define K_UP PAin(0)
//#define K_DOWN PEin(3)
//#define K_LEFT PEin(2)
//#define K_RIGHT PEin(4)

//使用读取管脚状态库函数定义 
#define K_UP      GPIO_ReadInputDataBit(KEY_UP_Port,KEY_UP_Pin)
#define K_DOWN    GPIO_ReadInputDataBit(KEY_DOWN_Port,KEY_DOWN_Pin)
#define K_LEFT    GPIO_ReadInputDataBit(KEY_LEFT_Port,KEY_LEFT_Pin)
#define K_RIGHT   GPIO_ReadInputDataBit(KEY_RIGHT_Port,KEY_RIGHT_Pin)

#define FifoSize      10

#define  CommonDelay(s)      {}//systick_delay_ms(s)
	
typedef enum
{
    Key_U,  //?
    Key_D,  //?

    Key_Y,  //??
    Key_N,  //??

    Key_MAX,
} Key_e;  //e???????


typedef struct
{
    Key_e key;        //????
    uint8_t status;     //?0???????
} Key_msg_t;


void key_init(void);
uint8_t key_check(Key_e key);
uint8_t key_get(Key_e key);               
void key_scan(void);
uint8_t Get_KeyFifo(Key_msg_t *keymsg);

#endif
