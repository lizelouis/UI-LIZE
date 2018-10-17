#include "keyboard.h"
#include "oled.h"
#include "UI_lib.h"

Key_msg_t         KeyStatus;
int     Cursor = 0;
int     Cursor_last = 0;
int     NowPage = 0;
int     Menustatus = 0;
uint8_t   uintForNow = 0;
float   DataInterval =0;    //???????
//double  uintArray[8] = {100, 10, 1, 0, 0.1, 0.01, 0.001, 0.0001};//???????
int     DataToChangeNum = 0;
/*
??????:
key_u:????,?????????
key_d:????,?????????

key_y:????,????????(???????????????)
key_n:????,????????????
*/
void Key_Event(void)   //????  
{
  if(Get_KeyFifo(&KeyStatus))    //?????????
  { 
    switch(KeyStatus.key)        //????
    {
    case Key_U:       if(!Menustatus)            //Menustatus?0?????? 1????
                        {
                          if(KeyStatus.status == 0)
                          {                         
                            Cursor--;//????
                            if(Cursor < 0)//????????
                              Cursor = 0;
                          }                      
                        }
                      else                      //Menustatus?1?
                      {
                       if(KeyStatus.status == 0)//????????
                       {
                         DataInterval++;        //????????
                       }
                      }
                      break;
    case Key_D:       if(!Menustatus)           //Menustatus?0?
                        {
                          if(KeyStatus.status == 0)//????????
                          {
                            Cursor++;              //????     
                          }                  
                        }
                      else                      //Menustatus?1?
                      {
                       if(KeyStatus.status == 0)
                       {
                         DataInterval--;        //????????
                       }
                      }
                      break;
    case Key_Y:       if(KeyStatus.status == 0)//??Yes???,?????????????
                      {
                       if(!Menustatus)          //Menustatus?0?
                         NowPage++;             //????
                       else                     //Menustatus?1?
                       {
                         uintForNow++;          //??????1
                         if(uintForNow == 8) uintForNow = 0;//???????
                       }
                      }
                      break;
    case Key_N:       if(KeyStatus.status == 0)//??No???
                      {
                        
                         NowPage--;             //????
                         if(Menustatus == 1)    //Menustatus?1?,??????
                           Menustatus = 0;      //Menustatus??0
                      
                      }
                       break;                  
    default:         break;
    }
  }
  return;
}


////////????
//??:object:????
void ChangeData(P_Page_TypeDef p_page, uint8_t Num,uint8_t LastPage,void * DataToChange[])
{
	uint8_t * Object = p_page->Page_content[Num];
	u32 * data_tmp_u32;
	float * data_tmp_float;
	
	if(p_page->param_type[Num] == UINT32)
		data_tmp_u32 = (float *)p_page->param[Num];
	else 
		data_tmp_float = (U32 *)p_page->param[Num]; 
	
  //********?????????????????,???????**************
  double  uintArray[8] = {100, 10, 1, 0, 0.1, 0.01, 0.001, 0.0001};//???????    
  //************************************************************************
  OLED_Clear();//??
  Menustatus = 1;
  uintForNow = 1;//???????????
  OLED_ShowString(0, 0, Object, 0);//????????
  while(1)
  {
    Key_Event();
    if(NowPage == LastPage)//?????????
    {
      Menustatus = 0;//?????????
      OLED_Clear();//??
      break;//??????
    }
		
    if(uintArray[uintForNow] != 0)//?????????0
		{
			if(p_page->param_type[Num] == UINT32)
				*data_tmp_u32 += DataInterval * uintArray[uintForNow];
			else
				*data_tmp_float += DataInterval * uintArray[uintForNow];
		}
    else if(uintArray[uintForNow] == 0 && DataInterval != 0)//????????0???????0
		{
			if(p_page->param_type[Num] == UINT32)
				*data_tmp_u32 = 0;
			else
				*data_tmp_float = 0;
		}
    
    DataInterval = 0;//????????
    
   //********??????***********
   //**???:????????(???????????????)
   //**???:?????????
		if(p_page->param_type[Num] == UINT32)
      OLED_PrintVar(0, 1, *data_tmp_u32,14,4);
    else
			OLED_PrintVar(0, 1, *data_tmp_float,14,4);	
		
    if(uintArray[uintForNow] == 0)//?????????0
    {
      OLED_ShowString(0, 2, "Clear To  0",1);//??????????
    }     
    else
    {  
      OLED_PrintVar(0, 2, uintArray[uintForNow], 14, 5);//?????????      
    }
  }
}

void show_content(u8 cursor,P_Page_TypeDef p_page)
{
	u8 y;
	u8 ** page_coment = p_page->Page_content;
           for(y = 0; y < 8; y++)
           {
             if(y == p_page->Page_H)break;//????????????
             if(Cursor < 8)
             {
              if(y == Cursor)
               {
                 OLED_ShowString(0 , y , *(page_coment + y) , 0);     //????????
               }
              else
								 OLED_ShowString(0 , y , *(page_coment + y) , 1);        //??????
							if(p_page->page_type == DIG)
							{
								if(p_page->param_type[y] == FLOAT)
									OLED_PrintVar(90, y, *((float *)(p_page->param[y])), 6, 1);
								else
									OLED_PrintVar(90, y, *((U32 *)(p_page->param[y])), 6, 1);
							}
             }
             else
             {
               if(y == 7)
               {
                 OLED_ShowString(0 , y , *(page_coment + Cursor - 7 + y) , 0);     //????????
               }
               else
								 OLED_ShowString(0 , y , *(page_coment + Cursor - 7 + y), 1);
							if(p_page->page_type == DIG)
							{
								if(p_page->param_type[Cursor - 7 + y] == FLOAT)
									OLED_PrintVar(90, y, *((float *)(p_page->param[Cursor - 7 + y])), 6, 1);
								else
									OLED_PrintVar(90, y, *((U32 *)(p_page->param[Cursor - 7 + y])), 6, 1);
							}			
             }					 
           }	
}

void UI_show(P_Page_TypeDef p_page)
{ 
  NowPage = 2;     //????2??
  Cursor = 0;    //?????0
  Menustatus = 0;
  OLED_Clear();     //??
	
  while(1)
  {
    Key_Event();//???????
    if(Cursor == p_page->Page_H)Cursor = 0;//?????????  
    if(Cursor == p_page->Page_H) Cursor = p_page->Page_H - 1;//??????
  
    if(NowPage == 1)
		{
			if(p_page->is_mainmenu != 1)
			{
				OLED_Clear();
				NowPage = 2;
				break;
			}
			else
			{
				NowPage = 2;
			}
		}    
		else if(NowPage == 3)
		{		
			if(p_page->page_type == DIG)
				ChangeData(p_page, Cursor,2, p_page->param);
			else
			{
				NowPage = 2;
				Cursor_last = Cursor;					
				OLED_Clear();	
				p_page->func[Cursor]();
				Cursor = Cursor_last;//????????,????			
			}			
		}
		if(p_page->page_type != SHOW)
			show_content(Cursor,p_page);
		else
			p_page->show_func();
		#ifdef USE_OS
			task_delay_ms(20);
		#endif
  }
		
}

