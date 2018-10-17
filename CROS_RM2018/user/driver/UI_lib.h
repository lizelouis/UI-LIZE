#ifndef __UI_LIB_H
#define __UI_LIB_H	

#include "stm32f4xx.h"
#include "data_save_lib.h"

#define USE_OS	

/*
PAGE:�����õ�ҳ��
X�������õ�ҳ������
CONTENT��������ʾ���ַ���
PARAM�����޸ĵĲ���
PARAM_TYPE���������ͣ���֧�� float u32
*/
#define   PAGE_PARAM(PAGE,X,CONTENT,PARAM,PARAM_TYPE)   do{   \
   \
	PAGE.Page_content[X] = CONTENT;\
	PAGE.param[X] = &PARAM;	\
	PAGE.param_type[X] = PARAM_TYPE;\
   \
}while(0) 

/*
PAGE:�����õ�ҳ��
X�������õ�ҳ������
CONTENT��������ʾ���ַ���
FUNC: ����ѡ��ʱ���õ��Զ��庯��
*/

#define   PAGE_FUNC(PAGE,X,CONTENT,FUNC)   do{   \
   \
	PAGE.Page_content[X] = CONTENT;\
	PAGE.func[X] = FUNC;\
   \
}while(0) 

/*
PAGE:�����õ�ҳ��
FUNC: ��ҳ���в��ϵ��õĻص�����(�Զ���),����������ʾҳ��
*/

#define   PAGE_SHOW(PAGE,FUNC)   do{   \
   \
	PAGE.show_func = FUNC;\
   \
}while(0) 
/*

���ڷ�ҳ�������

PAGE:�����õ�ҳ��
TYPE:����ҳ������
LENGTH:���ø�ҳ�������
*/
#define   PAGE_SET(PAGE,TYPE,LENGTH)   do{   \
   \
	PAGE.page_type = TYPE;\
	PAGE.Page_H = LENGTH;\
   \
}while(0) 

/*

������ҳ�������

PAGE:�����õ�ҳ��
TYPE:����ҳ������
LENGTH:���ø�ҳ�������
*/

#define   PAGE_SET_MAIN(PAGE,TYPE,LENGTH)   do{   \
   \
	PAGE.page_type = TYPE;\
	PAGE.Page_H = LENGTH;\
	PAGE.is_mainmenu = 1;\
   \
}while(0) 

#define PAGE_FUNC_MAX	10//FUNC��ҳ�����֧�ֵ��Զ��庯����Ŀ
typedef	void	(*page_f_array[PAGE_FUNC_MAX])();
typedef	void	(*page_f)();

#define Page_L 15//ҳ����ַ������������
#define PARAM_MAX	10//DIG��ҳ�����֧�ֵĿ��޸ı�����Ŀ

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
