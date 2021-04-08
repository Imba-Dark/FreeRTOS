#ifndef __LIST_H
#define	__LIST_H

#include "FreeRTOS.h"

/*--------------------------------------------------------------------------------*/
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

/*--------------------------------------------------------------------------------*/

/*�ڵ���κ꺯��*/
/*��ʼ���ڵ��ӵ����*/
#define	listSET_LIST_TIEM_OWNER(pxListItem, pxOwner)\
				((pxListItem)->pvOwner = (void *) (pxOwner))

/*��ȡ�ڵ�ӵ����*/
#define	listGET_LIST_TIEM_OWNER(pxListItem)\
				((pxListItem)->pvOwner)

/*��ʼ���ڵ�������ֵ*/
#define	listSET_LIST_TIEM_VALUE(pxListItem, xValue)\
				((pxListItem)->xItemValue = (xValue))			

/*��ȡ�ڵ�������ֵ*/
#define	listGET_LIST_TIEM_VALUE(pxListItem)\
				((pxListItem)->xItemValue)

/*��ȡ������ڵ�Ľڵ��������ֵ*/
#define	listGET_ITEM_VALUE_OF_HEAD_ENTRY(pxList)\
				(((pxList)->xListEnd).pxNext->xItemValue)

/*��ȡ�������ڽڵ�*/
#define	listGET_HEAD_ENTRY(pxList)\
				(((pxList)->xListEnd).pxNext)

/*��ȡ�ڵ����һ���ڵ�*/
#define	listGET_NEXT(pxListItem)\
				((pxListItem)->pxNext)
				
/*��ȡ��������һ���ڵ�*/
#define	listGET_END_MARKER(pxList)\
				((ListItem_t const *) (&((pxList)->xListEnd))
					
/*�ж������Ƿ�Ϊ��*/
#define	listLIST_IS_EMPTY(pxList)\
				((BaseType_t) ((pxList)->uxNumberOfItems == (UBaseType_t)))

/*��ȡ����Ľڵ���*/
#define	listCURRENT_LIST_LENGTH(pxList)\
				((pxList)->uxNumberOfItems)
				
/*��ȡ�����һ���ڵ��OWNER,��TCB*/
#define	listGET_OWNER_OF_NEXT_ENTRY(pxTCB, pxList) \
{	\
	List_t * const pxConstList = (pxList);	\
	/*�ڵ�����ָ�������һ���ڵ�*/	\
	(pxConstList)->pxIndex = (pxConstList)->pxIndex->pxNext;	\
	/*�жϽڵ������Ƿ�ָ���˵�һ���ڵ㣬��ָ���˸��ڵ������������*/	\
	if((void *) (pxConstList)->pxIndex == (void *) &((pxConstList)->xListEnd))	\
	{	\
		(pxConstList)->pxIndex = (pxConstList)->pxIndex->pxNext;	\
	}	\
	/*��ȡ�ڵ��OWNER����TCB*/	\
	(pxTCB) = (pxConstList)->pxIndex->OwpvOwnerner;	\
}

/*--------------------------------------------------------------------------------*/

void vListInitialiseItem(ListItem_t * const pxItem);
void vListInitialise(List_t * const pxList);
void vListInsertEnd(List_t * const pxList, ListItem_t * const pxNewListItem);
void vListInsert(List_t * const pxList, ListItem_t * const pxNewListItem);
UBase_Type_t uxListRemove(ListItem_t * const pxItemToRemove);


#endif	/*__LIST_H*/
