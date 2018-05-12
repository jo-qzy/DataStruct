#pragma once

#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef int QueueDataType;

typedef struct QueueNode
{
	QueueDataType _data;
	struct QueueNode* _next;
}QueueNode;

typedef struct Queue
{
	QueueNode* _head;
	QueueNode* _tail;
}Queue;

Queue* QueueInit();
void QueuePush(Queue* q, QueueDataType x);
void QueuePop(Queue* q);
QueueDataType QueueFront(Queue* q);
QueueDataType QueueBack(Queue* q);
size_t QueueSize(Queue* q);
int QueueEmpty(Queue* q);
void QueueDestroy(Queue* q);

QueueNode* BuyNewNode()
{
	QueueNode* newnode = (QueueNode*)malloc(sizeof(QueueNode));
	newnode->_next = NULL;
	return newnode;
}

Queue* QueueInit()
{
	Queue* q = (Queue*)malloc(sizeof(Queue));
	q->_head = NULL;
	q->_tail = q->_head;
	return q;
}

void QueuePush(Queue* q, QueueDataType x)
{
	assert(q);
	if (q->_tail == NULL)
	{
		q->_tail = BuyNewNode();
		q->_head = q->_tail;
	}
	else
	{
		q->_tail->_next = BuyNewNode();
		q->_tail = q->_tail->_next;
	}
	q->_tail->_data = x;
	q->_tail->_next = NULL;
}

void QueuePop(Queue* q)
{
	assert(q);
	QueueNode* next = q->_head->_next;
	if (q->_head == q->_tail)
	{
		q->_tail = NULL;
	}
	if (!QueueEmpty(q))
	{
		printf("empty\n");
	}
	free(q->_head);
	q->_head = next;
}

QueueDataType QueueFront(Queue* q)
{
	assert(q);
	return q->_head->_data;
}

QueueDataType QueueBack(Queue* q)
{
	assert(q);
	return q->_tail->_data;
}

size_t QueueSize(Queue* q)
{
	assert(q);
	QueueNode* cur = q->_head;
	size_t count = 1;
	if (cur == NULL)
	{
		return 0;
	}
	while (cur != q->_tail)
	{
		cur = cur->_next;
		count++;
	}
	return count;
}

int QueueEmpty(Queue* q)
{
	if (q->_head == NULL)
	{
		return 0;
	}
	return 1;
}

void QueueDestroy(Queue* q)
{
	QueueNode* cur = q->_head;
	QueueNode* next = NULL;
	while (cur != NULL)
	{
		next = cur->_next;
		free(cur);
		cur = next;
	}
	free(q);
}

void TestQueue()//¶ÓÁÐ²âÊÔÓÃÀý
{
	Queue* q = QueueInit();
	QueuePush(q, 1);
	QueuePush(q, 2);
	QueuePush(q, 3);
	QueuePush(q, 4);
	printf("%d ", QueueSize(q));
	printf("%d ", q->_head->_data);
	QueuePop(q);
	printf("%d ", QueueSize(q));
	printf("%d ", q->_head->_data);
	printf("%d ", QueueEmpty(q));
	QueuePop(q);
	printf("%d ", QueueEmpty(q));
	QueuePop(q); 
	printf("%d ", QueueEmpty(q));
	QueuePop(q);
	printf("%d ", QueueEmpty(q));
}

