#ifndef __UI_LIB_H
#define __UI_LIB_H	

#include "stm32f4xx.h"
#include "data_save_lib.h"

#define USE_OS	

/*
PAGE:需设置的页面
X：需设置的页面行数
CONTENT：该行显示的字符串
PARAM：需修改的参数
PARAM_TYPE：参数类型，仅支持 float u32
*/
#define   PAGE_PARAM(PAGE,X,CONTENT,PARAM,PARAM_TYPE)   do{   \
   \
	PAGE.Page_content[X] = CONTENT;\
	PAGE.param[X] = &PARAM;	\
	PAGE.param_type[X] = PARAM_TYPE;\
   \
}while(0) 

/*
PAGE:需设置的页面
X：需设置的页面行数
CONTENT：该行显示的字符串
FUNC: 该行选中时调用的自定义函数
*/

#define   PAGE_FUNC(PAGE,X,CONTENT,FUNC)   do{   \
   \
	PAGE.Page_content[X] = CONTENT;\
	PAGE.func[X] = FUNC;\
   \
}while(0) 

/*
PAGE:需设置的页面
FUNC: 该页面中不断调用的回调函数(自定义),自行设置显示页面
*/

#define   PAGE_SHOW(PAGE,FUNC)   do{   \
   \
	PAGE.show_func = FUNC;\
   \
}while(0) 
/*

用于分页面的设置

PAGE:需设置的页面
TYPE:设置页面类型
LENGTH:设置该页面的行数
*/
#define   PAGE_SET(PAGE,TYPE,LENGTH)   do{   \
   \
	PAGE.page_type = TYPE;\
	PAGE.Page_H = LENGTH;\
   \
}while(0) 

/*

用于主页面的设置

PAGE:需设置的页面
TYPE:设置页面类型
LENGTH:设置该页面的行数
*/

#define   PAGE_SET_MAIN(PAGE,TYPE,LENGTH)   do{   \
   \
	PAGE.page_type = TYPE;\
	PAGE.Page_H = LENGTH;\
	PAGE.is_mainmenu = 1;\
   \
}while(0) 

#define PAGE_FUNC_MAX	10//FUNC型页面最多支持的自定义函数数目
typedef	void	(*page_f_array[PAGE_FUNC_MAX])();
typedef	void	(*page_f)();

#define Page_L 15//页面的字符串行最大行数
#define PARAM_MAX	10//DIG型页面最多支持的可修改变量数目

typedef enum
{ 
  DIG = 1,
  FUNC,
	SHOW
}Pagetype_TypeDef;

typedef struct
{
	uint8_t Page_H;
  uint8_t * Page_content[Page_L];    
	page_f_array  func;
	page_f	show_func;
	Pagetype_TypeDef page_type;
	void * param[PARAM_MAX];
	datatype_TypeDef param_type[PARAM_MAX];
	uint8_t is_mainmenu;
}Page_TypeDef,* P_Page_TypeDef;

void UI_show(P_Page_TypeDef p_page);

#endif
