#include "keyboard.h"
#include "stdlib.h"


uint8_t KeyBox[Key_MAX] = {0, 1, 2, 3};
Key_msg_t  key_msg[FifoSize];             //????FIFO
volatile uint8_t      key_msg_front = 0, key_msg_rear = 0;    //??FIFO???
volatile uint8_t      key_msg_flag = 0;           //????FIFO??

void key_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; //定义结构体变量	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOD, ENABLE);
	
	
	GPIO_InitStructure.GPIO_Pin=KEY_DOWN_Pin;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;	//上拉输入
	//GPIO_InitStructure.GPIO_OType	= GPIO_OType_PP;
	//GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_NOPULL;
	GPIO_Init(KEY_DOWN_Port,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=KEY_LEFT_Pin;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;	//上拉输入
	//GPIO_InitStructure.GPIO_OType	= GPIO_OType_PP;
	//GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_NOPULL;
	GPIO_Init(KEY_LEFT_Port,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=KEY_RIGHT_Pin;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;	//上拉输入
	//GPIO_InitStructure.GPIO_OType	= GPIO_OType_PP;
	//GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_UP;
	GPIO_Init(KEY_RIGHT_Port,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=KEY_UP_Pin;	   //选择你要设置的IO口
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;//下拉输入  
	//GPIO_InitStructure.GPIO_OType	= GPIO_OType_PP;
	//GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	   //设置传输速率
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_UP;
	GPIO_Init(KEY_UP_Port,&GPIO_InitStructure);		  /* 初始化GPIO */
}

uint8_t key_get(Key_e key)
{
  uint32_t key_state;
  switch(key)
  {
    case Key_U:
    {
      key_state = K_UP;
			//printf("K_UP:%d\r\n",key_state);
    };break;
    case Key_D:
    {
      key_state = K_DOWN; 
			//printf("K_DOWN:%d\r\n",key_state);
    };break;
    case Key_Y:
    {
      key_state = K_RIGHT;  
			//printf("K_RIGHT:%d\r\n",key_state);
    };break;
    case Key_N:
    {
      key_state = K_LEFT;  
			//printf("K_LEFT:%d\r\n",key_state);
    };break;      
   
  }

  return key_state;
}

uint8_t key_check(Key_e key)
{
    if(key_get(key) == 0)
    {
        CommonDelay(10);      //??
        if( key_get(key) == 0)
        {
            return 0;
        }
    }
    return 1;
}

void SendToFifo(Key_msg_t keymsg)
{
    uint8_t temp = 0;
    if(key_msg_flag == 1)
    {
        return ;
    }
    
    key_msg[key_msg_rear].key = keymsg.key;
    key_msg[key_msg_rear].status = keymsg.status;

    key_msg_rear++;

    if(key_msg_rear >= FifoSize)
    {
        key_msg_rear = 0;                       //????
    }

    temp = key_msg_rear;
    if(temp == key_msg_front)                   //?????,??
    {
        key_msg_flag = 1;
    }
    else
    {
        key_msg_flag = 2;
    }
}

uint8_t Get_KeyFifo(Key_msg_t *keymsg)
{
    uint8_t temp;

    if(key_msg_flag == 0)               //????FIFO??,????0
    {
        return 0;
    }

    keymsg->key = key_msg[key_msg_front].key;       //?FIFO????????
    keymsg->status = key_msg[key_msg_front].status; //?FIFO?????????

    key_msg_front++;                                //FIFO?????1,???????

    if(key_msg_front >= FifoSize)          //FIFO????????0????
    {
        key_msg_front = 0;                          //??????(??????)
    }

    temp = key_msg_rear;
    if(key_msg_front == temp)                        //???????????,?????FIFO???
    {
        key_msg_flag = 0;
    }
    else
    {
        key_msg_flag = 2;
    }

    return 1;
}

void key_scan(void)
{
  Key_e num;
  uint8_t status = 0;
  Key_msg_t keymsg;
  static uint8_t keytime[Key_MAX];
 // BUZZSystem();
  for(num = (Key_e)0; num < Key_MAX; num++)   //????
  {
    status = key_get(num);
    if(status == 0)        //?????
    {
      keytime[num]++;
      if(keytime[num] < 2)     //????
      {
        continue;      //??????????
      }
      else if(keytime[num] == 2)   //??????
      {
         keymsg.key = num;
         keymsg.status = 0;
         SendToFifo(keymsg);
      }
      else if(keytime[num] < 40)
      {
        continue;
      }
      else if(keytime[num] >= 40)
      {
         keymsg.key = num;
         keymsg.status = 1;        
         SendToFifo(keymsg);
         keytime[num] = 0;//????
      }
    }
    else
    {
      if(keytime[num] >= 2)    //????????
      {
        keymsg.key = num;
        keymsg.status = 2;        
        SendToFifo(keymsg);
        keytime[num] = 0;//????
      }
    }
  }
}