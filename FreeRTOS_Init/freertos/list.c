#include "list.h"
#include <stdlib.h>

/*节点初始化*/
void vListInitialiseItem(ListItem_t * const pxItem)
{
	/* 初始化该节点所在的链表为空，表示节点还没有插入任何链表 */
	pxItem->pvContainer = NULL;
}

/*链表根节点初始化*/
void vListInitialise(List_t * const pxList)
{
	/*将链表索引指针指向最后一个节点*/
	pxList->pxIndex = (ListItem_t *) &(pxList->xListEnd);
	
	/*将链表最后一个结点的辅助排序值设置为最大，确保该节点就是链表的最后节点*/
	pxList->xListEnd.xItemValue = portMAX_DELAY;
	
	/*将最后一个节点的pxNext和pxPrevious指针均指向节点自身，表示链表为空*/
	pxList->xListEnd.pxNext = (ListItem_t *) &(pxList->xListEnd);
	pxList->xListEnd.pxPrevious =	(ListItem_t *) &(pxList->xListEnd);
	
	/*初始化链表结点计数器的值为0，表示链表为空*/
	pxList->uxNmberOfItems = (UBase_Type_t) 0U;
}

/*将节点插入到链表的尾部*/
void vListInsertEnd(List_t * const pxList, ListItem_t * const pxNewListItem)
{
	ListItem_t * const TempIndex = pxList->pxIndex;
	
	pxNewListItem->pxNext = TempIndex;
	pxNewListItem->pxPrevious	=	TempIndex->pxPrevious;
	TempIndex->pxPrevious->pxNext	=	pxNewListItem;
	TempIndex->pxPrevious	=	pxNewListItem;
	
	/*记住该节点所在的链表*/
	pxNewListItem->pvContainer	=	(void *) pxList;
	
	/*链表结点计数器 ++*/
	(pxList->uxNmberOfItems)++;
}

/*将节点按照升序排列插入到链表*/
void vListInsert(List_t * const pxList, ListItem_t * const pxNewListItem)
{
	ListItem_t * pxIterator;
	
	/*获取节点的排序辅助值*/
	const TickType_t xValueOfInsertion = pxNewListItem->xItemValue;
	
	/*寻找节点要插入的位置*/
	if(xValueOfInsertion == portMAX_DELAY)
	{
		pxIterator = pxList->xListEnd.pxPrevious;
	}
	else
	{
		for(pxIterator = (ListItem_t *) &(pxList->xListEnd);
					pxIterator->pxNext->xItemValue <= xValueOfInsertion;
					pxIterator	=	pxIterator->pxNext)
		{
		}
	}
	
	/*根据升序排列，将节点插入*/
	pxNewListItem->pxNext	=	pxIterator->pxNext;
	pxNewListItem->pxNext->pxPrevious	=	pxNewListItem;
	pxNewListItem->pxPrevious	=	pxIterator;
	pxIterator->pxNext	=	pxNewListItem;
	
	/*记住该节点所在的链表*/
	pxNewListItem->pvContainer	=	(void *)pxList;
	
	/*链表结点计数器 ++*/
	(pxList->uxNmberOfItems)++;
}
