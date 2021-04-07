#ifndef __LIST_H
#define	__LIST_H

#include "FreeRTOS.h"

/*�ڵ�ṹ�嶨��*/
struct xLIST_ITEM
{
	TickType_t xItemValue;						/*����ֵ�����ڰ����ڵ���˳������*/
	struct xLIST_ITEM * pxNext;				/*ָ��������һ���ڵ�*/
	struct xLIST_ITEM * pxPrevious;		/*ָ������ǰһ���ڵ�*/
	void * pvOwner;										/*ָ��ӵ�иýڵ���ں˶���ͨ����TCB*/
	void * pvContainer;								/*ָ��ýڵ����ڵ�����*/
};
typedef struct xLIST_ITEM ListItem_t;

/*MINI�ڵ�ṹ�嶨�壬��Ϊ˫������Ľ�β	
��Ϊ˫����������β�����ģ�ͷ����β��β����ͷ*/
typedef struct xMINI_LIST_ITEM
{
	TickType_t xItemValue;							/*����ֵ�����ڰ����ڵ�����������*/
	struct xLIST_ITEM *  pxNext;        /* ָ��������һ���ڵ� */
	struct xLIST_ITEM *  pxPrevious;    /* ָ������ǰһ���ڵ� */
}	MiniListItem_t;

/*����ṹ�嶨��*/
typedef struct xLIST
{
	UBase_Type_t uxNmberOfItems;	/*����ڵ������	unsigned long*/
	ListItem_t * pxIndex;					/*����ڵ�����ָ��*/
	MiniListItem_t xListEnd;			/*�������һ���ڵ�*/
}	List_t;



void vListInitialiseItem(ListItem_t * const pxItem);
void vListInitialise(List_t * const pxList);
void vListInsertEnd(List_t * const pxList, ListItem_t * const pxNewListItem);
void vListInsert(List_t * const pxList, ListItem_t * const pxNewListItem);

#endif	/*__LIST_H*/
