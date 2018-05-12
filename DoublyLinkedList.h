#pragma once

#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef int DataType;

typedef struct DListNode
{
	DataType _data;
	struct DListNode* _prev;
	struct DListNode* _next;
}DListNode;

DListNode* BuyNewDListNode();
DListNode* DListInit();
void DListDestory(DListNode* head);
void DListPrint(DListNode* head);

void DListPushBack(DListNode* head, DataType x);
void DListPushFront(DListNode* head, DataType x);
void DListPopBack(DListNode* head);
void DListPopFront(DListNode* head);

DListNode* DListFind(DListNode* head, DataType x);
void DListInsert(DListNode* pos, DataType x);
void DListErase(DListNode* pos);


DListNode* BuyNewDListNode()
{
	DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
	return newnode;
}

DListNode* DListInit()
{
	DListNode* head = BuyNewDListNode();
	head->_next = head;
	head->_prev = head;
	return head;
}

void DListDestory(DListNode* head)
{
	DListNode* cur = head;
	DListNode* next = NULL;
	while (next != head)
	{
		next = cur->_next;
		free(cur);
		cur = next;
	}
}

void DListPrint(DListNode* head)
{
	DListNode* cur = head->_next;
	while (cur != head)
	{
		printf("%d->", cur->_data);
		cur = cur->_next;
	}
	printf("head\n");
}

void DListPushBack(DListNode* head, DataType x)
{
	DListInsert(head, x);
}

void DListPushFront(DListNode* head, DataType x)
{
	DListInsert(head->_next, x);
}

void DListPopBack(DListNode* head)
{
	DListErase(head->_prev);
}

void DListPopFront(DListNode* head)
{
	DListErase(head->_next);
}

DListNode* DListFind(DListNode* head, DataType x)
{
	assert(head);
	DListNode* cur = head->_next;
	while (cur != head)
	{
		if (cur->_data == x)
		{
			return cur;
		}
		cur = cur->_next;
	}
	return NULL;
}

void DListInsert(DListNode* pos, DataType x)
{
	DListNode* prev = pos->_prev;
	DListNode* newnode = BuyNewDListNode();
	prev->_next = newnode;
	newnode->_next = pos;
	newnode->_prev = prev;
	pos->_prev = newnode;
	newnode->_data = x;
}

void DListErase(DListNode* pos)//不判断是否删除的是头节点，删除后果自负
{
	assert(pos);
	DListNode* prev = pos->_prev;
	DListNode* next = pos->_next;
	prev->_next = next;
	next->_prev = prev;
	free(pos);
}