#include "list.h"
#include <stdlib.h>

/*�ڵ��ʼ��*/
void vListInitialiseItem(ListItem_t * const pxItem)
{
	/* ��ʼ���ýڵ����ڵ�����Ϊ�գ���ʾ�ڵ㻹û�в����κ����� */
	pxItem->pvContainer = NULL;
}

/*�������ڵ��ʼ��*/
void vListInitialise(List_t * const pxList)
{
	/*����������ָ��ָ�����һ���ڵ�*/
	pxList->pxIndex = (ListItem_t *) &(pxList->xListEnd);
	
	/*���������һ�����ĸ�������ֵ����Ϊ���ȷ���ýڵ�������������ڵ�*/
	pxList->xListEnd.xItemValue = portMAX_DELAY;
	
	/*�����һ���ڵ��pxNext��pxPreviousָ���ָ��ڵ���������ʾ����Ϊ��*/
	pxList->xListEnd.pxNext = (ListItem_t *) &(pxList->xListEnd);
	pxList->xListEnd.pxPrevious =	(ListItem_t *) &(pxList->xListEnd);
	
	/*��ʼ����������������ֵΪ0����ʾ����Ϊ��*/
	pxList->uxNmberOfItems = (UBase_Type_t) 0U;
}

/*���ڵ���뵽������β��*/
void vListInsertEnd(List_t * const pxList, ListItem_t * const pxNewListItem)
{
	ListItem_t * const TempIndex = pxList->pxIndex;
	
	pxNewListItem->pxNext = TempIndex;
	pxNewListItem->pxPrevious	=	TempIndex->pxPrevious;
	TempIndex->pxPrevious->pxNext	=	pxNewListItem;
	TempIndex->pxPrevious	=	pxNewListItem;
	
	/*��ס�ýڵ����ڵ�����*/
	pxNewListItem->pvContainer	=	(void *) pxList;
	
	/*������������ ++*/
	(pxList->uxNmberOfItems)++;
}

/*���ڵ㰴���������в��뵽����*/
void vListInsert(List_t * const pxList, ListItem_t * const pxNewListItem)
{
	ListItem_t * pxIterator;
	
	/*��ȡ�ڵ��������ֵ*/
	const TickType_t xValueOfInsertion = pxNewListItem->xItemValue;
	
	/*Ѱ�ҽڵ�Ҫ�����λ��*/
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
	
	/*�����������У����ڵ����*/
	pxNewListItem->pxNext	=	pxIterator->pxNext;
	pxNewListItem->pxNext->pxPrevious	=	pxNewListItem;
	pxNewListItem->pxPrevious	=	pxIterator;
	pxIterator->pxNext	=	pxNewListItem;
	
	/*��ס�ýڵ����ڵ�����*/
	pxNewListItem->pvContainer	=	(void *)pxList;
	
	/*������������ ++*/
	(pxList->uxNmberOfItems)++;
}