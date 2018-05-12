#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <assert.h>

//堆的应用
//1.TopK问题
//思路是建一个K个元素的小堆，以十万亿个元素的前十个元素当做初始堆创建
//大堆只能找出10万亿个元素里面最大的那一个，这里需要仔细思考为什么用小堆
//用小堆找到最后，堆内十个元素必定是所有元素里最大的
void GetTopK(int* a, int size, int K);//TopK问题
void AdjustDown(int* heap, int size, int parent);
void TestTopK();//测试用例

void GetTopK(int* a, int size, int K)//TopK问题
{
	int* heap = (int*)malloc(sizeof(int) * K);
	memcpy(heap, a, sizeof(int) * K);
	//建堆
	for (int i = (K - 2) / 2; i >= 0; i--)
	{
		AdjustDown(heap, K, i);
	}
	//从第K+1个元素开始读取后面的数据，比堆顶大便替换堆顶元素
	for (int i = K; i < size; i++)
	{
		if (*(a + i) > *heap)
		{
			*heap = *(a + i);
			AdjustDown(heap, K, 0);
		}
	}
	for (int i = 0; i < K; i++)
	{
		printf("%d ", *(heap + i));
	}
	printf("\n");
}

void AdjustDown(int* heap, int size, int parent)
{
	int child = parent * 2 + 1;
	while (child < size)
	{
		if (child + 1 < size)
		{
			if (*(heap + child) > *(heap + child + 1))
			{
				child += 1;
			}
		}
		if (*(heap + parent) > *(heap + child))
		{
			Swap(heap + parent, heap + child);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

void TestTopK()
{
	int arr[] = { 53,17,78,9,45,65,87,23,31 };
	GetTopK(arr, sizeof(arr) / sizeof(arr[0]), 3);
}

//2.优先级队列的实现
//实现方式：堆的另一种应用而已，本质依旧是堆，换了个名字而已
#define _SIZE 5

typedef int PQueueDataType;

typedef struct PriorityQueue
{
	int* _a;
	int _size;
	int _capacity;
}PQueue;

PQueue* PQueueInit();
void PQueuePush(PQueue* q, PQueueDataType data);
void PQueueAdjustUp(PQueue* q, int child);
void PQueueAdjustDown(PQueue* q, int parent);
void PQueuePush(PQueue* q, PQueueDataType data);
void PQueuePop(PQueue* q);
PQueueDataType PQueueTop(PQueue* q);
void PQueueDestroy(PQueue* q);

void TestPQueue();//测试用例

PQueue* PQueueInit()
{
	PQueue* q = (PQueue*)malloc(sizeof(PQueue));
	q->_capacity = _SIZE;
	q->_size = 0;
	q->_a = (PQueueDataType*)malloc(sizeof(PQueueDataType) * q->_capacity);
	return q;
}

void PQueueCheckCapacity(PQueue* q)
{
	assert(q);
	if (q->_size == q->_capacity)
	{
		q->_capacity *= 2;
		q->_a = realloc(q->_a, sizeof(PQueueDataType) * q->_capacity);
		assert(q->_a);
	}
}

void PQueueSwap(PQueueDataType* data1, PQueueDataType* data2)
{
	assert(data1 && data2);
	*(data1) ^= *(data2);
	*(data2) ^= *(data1);
	*(data1) ^= *(data2);
}

void PQueueAdjustUp(PQueue* q, int child)
{
	assert(q);
	PQueueDataType parent = (child - 1) / 2;
	while (child)
	{
		if (*(q->_a + parent) < *(q->_a + child))
		{
			PQueueSwap(q->_a + parent, q->_a + child);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
		{
			break;
		}
	}
}

void PQueueAdjustDown(PQueue* q, int parent)
{
	assert(q);
	int child = parent * 2 + 1;
	while (child < q->_size)
	{
		if (child + 1 < q->_size)
		{
			if (*(q->_a + child) < *(q->_a + child + 1))
			{
				child += 1;
			}
		}
		if (*(q->_a + parent) < *(q->_a + child))
		{
			PQueueSwap(q->_a + parent, q->_a + child);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

void PQueuePush(PQueue* q, PQueueDataType data)
{
	assert(q);
	PQueueCheckCapacity(q);
	*(q->_a + q->_size) = data;
	q->_size++;
	PQueueAdjustUp(q, q->_size - 1);
}

void PQueuePop(PQueue* q)
{
	assert(q);
	*(q->_a + 0) = *(q->_a + q->_size - 1);
	q->_size--;
	PQueueAdjustDown(q, 0);
}

PQueueDataType PQueueTop(PQueue* q)
{
	assert(q && (q->_size > 0));
	return *(q->_a + 0);
}

void PQueueDestroy(PQueue* q)
{
	assert(q);
	free(q->_a);
	free(q);
}

void TestPQueue()
{
	PQueueDataType arr[] = { 53,17,78,9,45,65,87,23,31 };
	PQueue* pq = PQueueInit();
	printf("入队列测试：");
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		PQueuePush(pq, arr[i]);
	}
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		printf("%d ", *(pq->_a + i));
	}
	printf("\n");
	printf("出队列测试:");
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		printf("%d ", PQueueTop(pq));
		PQueuePop(pq);
	}
	printf("\n");
	PQueueDestroy(pq);
}