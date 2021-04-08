#ifndef __LIST_H
#define	__LIST_H

#include "FreeRTOS.h"

/*--------------------------------------------------------------------------------*/
/*节点结构体定义*/
struct xLIST_ITEM
{
	TickType_t xItemValue;						/*辅助值，用于帮助节点做顺序排列*/
	struct xLIST_ITEM * pxNext;				/*指向链表下一个节点*/
	struct xLIST_ITEM * pxPrevious;		/*指向链表前一个节点*/
	void * pvOwner;										/*指向拥有该节点的内核对象，通常是TCB*/
	void * pvContainer;								/*指向该节点所在的链表*/
};
typedef struct xLIST_ITEM ListItem_t;

/*MINI节点结构体定义，作为双线链表的结尾	
因为双线链表是首尾相连的，头即是尾，尾即是头*/
typedef struct xMINI_LIST_ITEM
{
	TickType_t xItemValue;							/*辅助值，用于帮助节点做升序排列*/
	struct xLIST_ITEM *  pxNext;        /* 指向链表下一个节点 */
	struct xLIST_ITEM *  pxPrevious;    /* 指向链表前一个节点 */
}	MiniListItem_t;

/*链表结构体定义*/
typedef struct xLIST
{
	UBase_Type_t uxNmberOfItems;	/*链表节点计数器	unsigned long*/
	ListItem_t * pxIndex;					/*链表节点索引指针*/
	MiniListItem_t xListEnd;			/*链表最后一个节点*/
}	List_t;

/*--------------------------------------------------------------------------------*/

/*节点带参宏函数*/
/*初始化节点的拥有者*/
#define	listSET_LIST_TIEM_OWNER(pxListItem, pxOwner)\
				((pxListItem)->pvOwner = (void *) (pxOwner))

/*获取节点拥有者*/
#define	listGET_LIST_TIEM_OWNER(pxListItem)\
				((pxListItem)->pvOwner)

/*初始化节点排序辅助值*/
#define	listSET_LIST_TIEM_VALUE(pxListItem, xValue)\
				((pxListItem)->xItemValue = (xValue))			

/*获取节点排序辅助值*/
#define	listGET_LIST_TIEM_VALUE(pxListItem)\
				((pxListItem)->xItemValue)

/*获取链表根节点的节点计数器的值*/
#define	listGET_ITEM_VALUE_OF_HEAD_ENTRY(pxList)\
				(((pxList)->xListEnd).pxNext->xItemValue)

/*获取链表的入口节点*/
#define	listGET_HEAD_ENTRY(pxList)\
				(((pxList)->xListEnd).pxNext)

/*获取节点的下一个节点*/
#define	listGET_NEXT(pxListItem)\
				((pxListItem)->pxNext)
				
/*获取链表的最后一个节点*/
#define	listGET_END_MARKER(pxList)\
				((ListItem_t const *) (&((pxList)->xListEnd))
					
/*判断链表是否为空*/
#define	listLIST_IS_EMPTY(pxList)\
				((BaseType_t) ((pxList)->uxNumberOfItems == (UBaseType_t)))

/*获取链表的节点数*/
#define	listCURRENT_LIST_LENGTH(pxList)\
				((pxList)->uxNumberOfItems)
				
/*获取链表第一个节点的OWNER,即TCB*/
#define	listGET_OWNER_OF_NEXT_ENTRY(pxTCB, pxList) \
{	\
	List_t * const pxConstList = (pxList);	\
	/*节点索引指向链表第一个节点*/	\
	(pxConstList)->pxIndex = (pxConstList)->pxIndex->pxNext;	\
	/*判断节点索引是否指向了第一个节点，若指向了根节点则再向后索引*/	\
	if((void *) (pxConstList)->pxIndex == (void *) &((pxConstList)->xListEnd))	\
	{	\
		(pxConstList)->pxIndex = (pxConstList)->pxIndex->pxNext;	\
	}	\
	/*获取节点的OWNER，即TCB*/	\
	(pxTCB) = (pxConstList)->pxIndex->OwpvOwnerner;	\
}

/*--------------------------------------------------------------------------------*/

void vListInitialiseItem(ListItem_t * const pxItem);
void vListInitialise(List_t * const pxList);
void vListInsertEnd(List_t * const pxList, ListItem_t * const pxNewListItem);
void vListInsert(List_t * const pxList, ListItem_t * const pxNewListItem);
UBase_Type_t uxListRemove(ListItem_t * const pxItemToRemove);


#endif	/*__LIST_H*/
