#pragma once

#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef int DataType;

typedef struct SListNode
{
	DataType _data;
	struct SListNode* _pNext;
}SListNode;

SListNode *BuySListNode(DataType data);//申请空间
void SListDestory(SListNode** ppHead);//销毁链表
void SListPrint(SListNode* pHead);//打印链表

void SListPushBack(SListNode** ppHead, DataType data);//尾插链表
void SListPopBack(SListNode* pHead);//删除尾链
void SListPushFront(SListNode** ppHead, DataType data);//头插链表
SListNode* SListFind(SListNode* pHead, DataType data);// 查找链表
void SListInsert(SListNode** ppHead, SListNode* pos, DataType data);//指定位置插入链表
void SListErase(SListNode** ppHead, SListNode* pos);//删除指定链表

SListNode* BuySListNode(DataType data)
{
	SListNode *NewSList = (SListNode*)malloc(sizeof(SListNode));
	NewSList->_data = data;
	NewSList->_pNext = NULL;
	return NewSList;
}

void SListDestory(SListNode** ppHead)
{
	SListNode* prev = *ppHead;
	while (*ppHead)
	{
		(*ppHead) = (*ppHead)->_pNext;
		free(prev);
		prev = (*ppHead);
	}
}

void SListPrint(SListNode* pHead)
{
	SListNode* cur = pHead;
	while (cur)
	{
		printf("%d->", cur->_data);
		cur = cur->_pNext;
	}
	printf("NULL\n");
}

void SListPushBack(SListNode** ppHead, DataType data)
{
	SListNode* Head = *ppHead;
	if ((*ppHead) == NULL)
	{
		(*ppHead) = BuySListNode(data);
		return;
	}
	while ((*ppHead)->_pNext != NULL)
	{
		(*ppHead) = (*ppHead)->_pNext;
	}
	(*ppHead)->_pNext = BuySListNode(data);
	*ppHead = Head;
}

void SListPopBack(SListNode* pHead)
{
	assert(pHead);
	SListNode* cur = pHead;
	SListNode* prev = pHead;
	if (cur->_pNext == NULL)
	{
		free(cur);
		return;
	}
	while (cur->_pNext != NULL)
	{
		prev = cur;
		cur = cur->_pNext;
	}
	prev->_pNext = NULL;
	free(cur);
}

void SListPushFront(SListNode** ppHead, DataType data)
{
	SListNode* NewSList;
	if ((*ppHead) == NULL)
	{
		SListPushBack(ppHead, data);
	}
	NewSList = BuySListNode(data);
	NewSList->_pNext = (*ppHead);
	(*ppHead) = NewSList;
}

SListNode* SListFind(SListNode* pHead, DataType data)
{
	assert(pHead);
	SListNode* cur = pHead;
	while (cur)
	{
		if (cur->_data == data)
		{
			return cur;
		}
		else
		{
			cur = cur->_pNext;
		}
	}
	return NULL;
}

void SListInsert(SListNode** ppHead, SListNode* pos, DataType data)
{
	SListNode* cur = (*ppHead);
	if (pos == (*ppHead))
	{
		SListPushFront(ppHead, data);
		return;
	}
	while (cur->_pNext != pos)
	{
		cur = cur->_pNext;
	}
	cur->_pNext = BuySListNode(data);
	cur->_pNext->_pNext = pos;
}

void SListErase(SListNode** ppHead, SListNode* pos)
{
	assert(ppHead && (*ppHead));
	assert(pos);
	SListNode* cur = (*ppHead);
	if (cur == pos)
	{
		(*ppHead) = (*ppHead)->_pNext;
		free(cur);
		return;
	}
	while (cur->_pNext != pos)
	{
		cur = cur->_pNext;
	}
	cur->_pNext = pos->_pNext;
	free(pos);
}