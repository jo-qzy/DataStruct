#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <assert.h>

typedef int HashDataType;

typedef struct HashBucketNode
{
	HashDataType _data;
	struct HashBucketNode* _next;
}HashNode;

typedef struct HashBucket
{
	HashNode** _tables;
	size_t _size;
	size_t _capacity;
}HashBucket;

void HashInit(HashBucket* hb, size_t capacity);//初始化哈希桶

static size_t HashFunc(HashBucket* hb, HashDataType data);//哈希函数
static HashNode* BuyNewHashNode(HashDataType data);//创建新链节点
static void CheckCapacity(HashBucket* hb);//检查空间，确保效率
static size_t GetPrime(HashBucket* hb);
static void HashPrint(HashBucket* hb);

bool HashInsert(HashBucket* hb, HashDataType data);//插入
HashNode* HashFind(HashBucket* hb, HashDataType data);//查找某个元素是否存在
bool HashRemove(HashBucket* hb, HashDataType data);//删除
size_t HashSize(HashBucket* hb);

void TestHashTable();//测试用例


void HashInit(HashBucket* hb, size_t capacity)
{
	assert(hb);
	hb->_capacity = capacity;
	hb->_capacity = GetPrime(hb);
	hb->_tables = (HashNode**)malloc(sizeof(HashNode*) * hb->_capacity);
	hb->_size = 0;
	for (size_t i = 0; i < hb->_capacity; i++)
	{
		*(hb->_tables + i) = NULL;
	}
}

static size_t HashFunc(HashBucket* hb, HashDataType data)
{
	assert(hb);
	return data % hb->_capacity;
}

static HashNode* BuyNewHashNode(HashDataType data)
{
	HashNode* new_node = (HashNode*)malloc(sizeof(struct HashBucketNode));
	new_node->_data = data;
	new_node->_next = NULL;
	return new_node;
}

static void CheckCapacity(HashBucket* hb)
{
	assert(hb);
	if (hb->_size == hb->_capacity)
	{
		HashBucket new_hb;
		HashNode* cur = NULL;
		HashNode* next = NULL;
		HashInit(&new_hb, hb->_capacity);
		for (size_t i = 0; i < hb->_capacity; i++)
		{
			//将原数据插入新表中
			cur = *(hb->_tables + i);
			while (cur)
			{
				//之所以可以头插是因为数据没有重复
				next = cur->_next;
				size_t index = HashFunc(&new_hb, cur->_data);
				cur->_next = *(new_hb._tables + index);
				*(new_hb._tables + index) = cur;
				cur = next;
			}
		}
		hb->_capacity = new_hb._capacity;
		free(hb->_tables);//释放旧表
		hb->_tables = new_hb._tables;//链接新表
	}
}

static size_t GetPrime(HashBucket* hb)
{
	assert(hb);
	const int _PrimeSize = 28;
	//该数据都是经过许多人测试的素数，能够满足需求，冲突较小
	static const unsigned long _PrimeList[_PrimeSize] = {
		53ul,97ul,193ul,389ul,769ul,
		1543ul,3079ul,6151ul,12289ul,
		24593ul,49157ul,98317ul,196613ul,
		393241ul,786433ul,1572869ul,3145739ul,
		6291469ul,12582917ul,25165843ul,50331653ul,
		100663319ul,201326611ul,402653189ul,805306457ul,
		1610612741ul, 3221225473ul, 4294967291ul
	};
	int index = 0;
	while (index < _PrimeSize)
	{
		if (hb->_capacity < _PrimeList[index])
		{
			return _PrimeList[index];
		}
		index++;
	}
	return _PrimeList[_PrimeSize - 1];
}

static void HashPrint(HashBucket* hb)
{
	//辅助打印函数
	assert(hb);
	HashNode* cur = NULL;
	for (size_t i = 0; i < hb->_capacity; i++)
	{
		cur = *(hb->_tables + i);
		printf("tables[%d]", i);
		while (cur)
		{
			printf("->%d", cur->_data);
			cur = cur->_next;
		}
		printf("->NULL\n");
	}
}

bool HashInsert(HashBucket* hb, HashDataType data)
{
	assert(hb);
	CheckCapacity(hb);
	size_t index = HashFunc(hb, data);
	HashNode* cur = *(hb->_tables + index);
	HashNode* prev = cur;
	if (cur == NULL)
	{
		//该位置没有任何节点，直接插入
		*(hb->_tables + index) = BuyNewHashNode(data);
	}
	else
	{
		//该位置已有节点，找寻合适位置插入
		while (cur)
		{
			//不允许头插，因为可能有数据重复
			if (cur->_data == data)
			{
				return false;
			}
			prev = cur;
			cur = cur->_next;
		}
		prev->_next = BuyNewHashNode(data);
	}
	hb->_size++;
	return true;
}

HashNode* HashFind(HashBucket* hb, HashDataType data)
{
	assert(hb);
	size_t index = HashFunc(hb, data);
	HashNode* cur = *(hb->_tables + index);
	while (cur)
	{
		if (cur->_data == data)
		{
			return cur;
		}
		cur = cur->_next;
	}
	return NULL;
}

bool HashRemove(HashBucket* hb, HashDataType data)
{
	assert(hb);
	size_t index = HashFunc(hb, data);
	HashNode* cur = *(hb->_tables + index);
	HashNode* prev = cur;
	while (cur)
	{
		if (cur->_data == data)
		{
			break;
		}
		prev = cur;
		cur = cur->_next;
	}
	if (cur == NULL)
	{
		//cur已经查到底或者该位置本就没有节点为空，未找到
		return false;
	}
	else
	{
		//找到
		if (cur == prev)
		{
			//节点为第一个结点，不能直接prev = cur，因为prev是临时变量
			*(hb->_tables + index) = cur->_next;
		}
		else
		{
			//节点不是第一个节点
			prev->_next = cur->_next;
		}
		free(cur);
		return true;
	}
}

size_t HashSize(HashBucket* hb)
{
	return hb->_size;
}

void TestHashTable()
{
	HashBucket hb;
	HashInit(&hb, 0);

	srand((unsigned)time(0));
	for (int i = 0; i < 50; i++)
	{
		HashInsert(&hb, rand() % 200);
	}
	HashPrint(&hb);
	printf("\n");

	for (int i = 0; i < 50; i++)
	{
		HashInsert(&hb, rand() % 200);
	}
	HashPrint(&hb);
	printf("\n");

	for (int i = 0; i < 200; i++)
	{
		HashRemove(&hb, rand() % 200);
	}
	HashPrint(&hb);
	
}