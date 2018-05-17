//数据结构：顺序表练习，实现增删查改，以及排序等操作
#pragma once

#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>

typedef int DataType;
#define N 10

typedef struct Seqlist
{
	DataType _data[10];
	size_t _size;
}Seqlist;

void SeqlistInit(Seqlist *pSeq);//初始化静态顺序表
void SeqlistInsert(Seqlist *pSeq, size_t pos, DataType data);//插入
void SeqlistErase(Seqlist *pSeq, size_t pos);//按下表删除元素
void SeqlistPushFront(Seqlist *pSeq, DataType data);//在顺序表最前面插入元素
void SeqlistPushBack(Seqlist *pSeq, DataType data);//在顺序表最后面插入元素
void SeqlistPopFront(Seqlist *pSeq);//删除顺序表最前元素
void SeqlistPopBack(Seqlist *pSeq);//删除顺序表最后元素
int SeqlistFind(Seqlist *pSeq, DataType data);//查找指定元素
void SeqlistModify(Seqlist *pSeq, size_t pos, DataType data);//修改指定元素
void SeqlistRemove(Seqlist *pSeq, DataType data);//按数据删除元素
void SeqlistRemoveAll(Seqlist *pSeq, DataType data);//按数据删除所有该数据元素

void SeqlistBubbleSort(Seqlist *pSeq);//顺序表冒泡排序
void SeqlistSelectSort(Seqlist *pSeq);//顺序表选择排序
void SeqlistBinarySearch(Seqlist *pSeq, DataType data);//顺序表的二分查找

void SeqlistPrint(Seqlist *pSeq);//顺序表的打印
void TestSeqList();//测试用例

//动态分配部分
typedef struct V_Seqlist
{
	DataType *array;
	size_t _size;
	size_t capicity;
}V_Seqlist;

void V_SeqlistInit(V_Seqlist *pSeq,size_t capicity);//动态表初始化化
void V_SeqlistPushBack(V_Seqlist *pSeq, DataType data);//在最后添加元素
void V_SeqlistDestroy(V_Seqlist *pSeq);//销毁动态表

//顺序表基本功能函数实现部分
void SeqlistInit(Seqlist *pSeq)
{
	memset(pSeq->_data, 0, sizeof(pSeq->_data));
	pSeq->_size = 0;
}

void SeqlistInsert(Seqlist *pSeq, size_t pos, DataType data)
{
	assert(pSeq);
	int end = pSeq->_size;
	if (pSeq->_size == N)
	{
		printf("The list is full!\n");
		return;
	}
	while (end > pos)
	{
		pSeq->_data[end] = pSeq->_data[end - 1];
		end--;
	}
	pSeq->_data[pos] = data;
	pSeq->_size++;
}

void SeqlistErase(Seqlist *pSeq, size_t pos)
{
	assert(pSeq);
	assert(pos < pSeq->_size);
	int index = pos;
	if (0 == pSeq->_size)
	{
		printf("The list is empty!");
		return;
	}
	while (index < pSeq->_size - 1)
	{
		pSeq->_data[index] = pSeq->_data[index + 1];
		index++;
	}
	pSeq->_size--;
}

void SeqlistPushFront(Seqlist *pSeq, DataType data)
{
	assert(pSeq);
	SeqlistInsert(pSeq, 0, data);
}

void SeqlistPushBack(Seqlist *pSeq, DataType data)
{
	assert(pSeq);
	SeqlistInsert(pSeq, pSeq->_size, data);
}

void SeqlistPopFront(Seqlist *pSeq)
{
	assert(pSeq);
	SeqlistErase(pSeq, 0);
}

void SeqlistPopBack(Seqlist *pSeq)
{
	assert(pSeq);
	SeqlistErase(pSeq, pSeq->_size - 1);
}

int SeqlistFind(Seqlist *pSeq, DataType data)
{
	assert(pSeq);
	int i = 0;
	for (i = 0; i < pSeq->_size; i++)
	{
		if (pSeq->_data[i] == data)
		{
			return i;
		}
	}
	return -1;
}

void SeqlistModify(Seqlist *pSeq, size_t pos, DataType data)
{
	assert(pSeq);
	assert(pos < pSeq->_size);
	pSeq->_data[pos] = data;
}

void SeqlistRemove(Seqlist *pSeq, DataType data)
{
	assert(pSeq);
	int pos = SeqlistFind(pSeq, data);
	SeqlistErase(pSeq, pos);
}

void SeqlistRemoveAll(Seqlist *pSeq, DataType data)
{
	assert(pSeq);
	int count = 0;
	int index1 = SeqlistFind(pSeq, data) + 1;
	int index2 = index1 - 1;
	if (SeqlistFind(pSeq, data) == -1)
	{
		return;
	}
	else
	{
		count++;
	}
	while (index1 < pSeq->_size)
	{
		if (pSeq->_data[index1] == data)
		{
			index1++;
			count++;
		}
		else
		{
			pSeq->_data[index2] = pSeq->_data[index1];
			index1++, index2++;
		}
	}
	pSeq->_size -= count;
}

void SeqlistPrint(Seqlist *pSeq)
{
	assert(pSeq);
	int i = 0;
	for (; i < pSeq->_size; i++)
	{
		printf("%d ", pSeq->_data[i]);
	}
	printf("\n");
}

void SeqlistBubbleSort(Seqlist *pSeq)
{
	assert(pSeq);
	int i = 0, j = 0;
	int flag = 0;
	for (i = 0; i < pSeq->_size - 1; i++)
	{
		flag = 0;
		for (j = 0; j < pSeq->_size - i - 1; j++)
		{
			if (pSeq->_data[j] > pSeq->_data[j + 1])//交换
			{
				pSeq->_data[j] ^= pSeq->_data[j + 1];
				pSeq->_data[j + 1] ^= pSeq->_data[j];
				pSeq->_data[j] ^= pSeq->_data[j + 1];
				flag++;
			}
		}
		if (0 == flag)//flag未变，顺序表有序，直接退出排序
		{
			break;
		}
	}
}

void SeqlistSelectSort(Seqlist *pSeq)
{
	assert(pSeq);
	int i = 0, j = 0;
	int min= 0;
	for (i = 0; i < pSeq->_size; i++)
	{
		int tmp;
		min = i;
		for (j = i + 1; j < pSeq->_size; j++)
		{
			if (pSeq->_data[j] < pSeq->_data[min])
			{
				min = j;//找出最小值下标
			}
		}
		if (min == i)//min就是i，不进行调换，跳过，进行下一循环
		{
			continue;
		}
		pSeq->_data[i] ^= pSeq->_data[min];
		pSeq->_data[min] ^= pSeq->_data[i];
		pSeq->_data[i] ^= pSeq->_data[min];
	}
}

void SeqlistBinarySearch(Seqlist *pSeq, DataType data)
{
	assert(pSeq);
	int start = 0, end = pSeq->_size - 1;
	while (start <= end)
	{
		if (data < pSeq->_data[(start + end) / 2])
		{
			end = (start + end) / 2 - 1;
		}
		else if (data > pSeq->_data[(start + end) / 2])
		{
			start = (start + end) / 2 + 1;
		}
		else
		{
			printf("Pos: %d.\n", (start + end) / 2);
			return;
		}
	}
	printf("Data doesn't exist!\n");
	return;
}

void V_SeqlistInit(V_Seqlist *pSeq, size_t capicity)
{
	pSeq->capicity = capicity;
	pSeq->array = (DataType*)melloc(pSeq->capicity * sizeof(DataType));
}

void V_SeqlistPushBack(V_Seqlist *pSeq, DataType data)
{
	if (pSeq->_size == pSeq->capicity)
	{
		pSeq->array = (DataType*)relloc(pSeq->capicity * 2 * sizeof(DataType));
		pSeq->capicity *= 2;
	}
	pSeq->array[pSeq->_size] = data;
	pSeq->_size++;
}

void V_SeqlistDestroy(V_Seqlist *pSeq)
{
	free(pSeq->array);
	pSeq->array = NULL;
	pSeq->capicity = 0;
}

void TestSeqList()
{
	Seqlist s;
	int i = 0;
	int random;
	srand((unsigned)time(0));
	SeqlistInit(&s);
	for (i = 1; i <= N; i++)
	{
		//SeqlistPushFront(&s, i);
		SeqlistPushFront(&s, rand() % 10 + 1);
	}
	//SeqlistPushFront(&s, 2);
	//SeqlistPushFront(&s, 2);
	//SeqlistPushFront(&s, 3);
	//SeqlistPushFront(&s, 1);
	//SeqlistPushFront(&s, 2);
	SeqlistBubbleSort(&s);
	//SeqlistSelectSort(&s);
	SeqlistPrint(&s);
	SeqlistBinarySearch(&s, 4);
	SeqlistBinarySearch(&s, 11);
	SeqlistRemoveAll(&s, 2);
	SeqlistPrint(&s);
}