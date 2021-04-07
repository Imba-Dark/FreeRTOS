#ifndef __LIST_H
#define	__LIST_H

#include "FreeRTOS.h"

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



void vListInitialiseItem(ListItem_t * const pxItem);
void vListInitialise(List_t * const pxList);
void vListInsertEnd(List_t * const pxList, ListItem_t * const pxNewListItem);
void vListInsert(List_t * const pxList, ListItem_t * const pxNewListItem);

#endif	/*__LIST_H*/
