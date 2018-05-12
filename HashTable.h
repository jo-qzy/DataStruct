#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

typedef int HTDataType;

typedef enum Status
{
	EMPTY,
	EXIST,
	DELETE
}Status;

typedef struct HashTableNode
{
	HTDataType _data;
	Status _status;
}HTNode;

typedef struct HashTable
{
	HTNode* _table;
	size_t _size;
	size_t _capacity;
}Hash;

void HashInit(Hash* ht, size_t capacityy);//初始化

//功能辅助函数
static size_t GetPrime(Hash* ht);//STL里面的素数表，获取素数
static size_t HashFunc(HashTable* ht, HTDataType data);	//哈希函数
static void CheckCapacity(HashTable* ht);//空间检查
static void HashPrint(HashTable* ht);//打印

//基本功能函数，增删查
bool HashInsert(Hash* ht, HTDataType data);
bool HashRemove(Hash* ht, HTDataType data);
HTNode* HashFind(Hash* ht, HTDataType data);
void TestHashTable();//测试用例

void HashInit(Hash* ht, size_t capacity)
{
	assert(ht);
	ht->_size = 0;
	ht->_capacity = capacity;
	ht->_capacity = GetPrime(ht);
	ht->_table = (HTNode*)malloc(sizeof(HTNode) * ht->_capacity);
	assert(ht->_table);
	for (size_t i = 0; i < ht->_capacity; i++)
	{
		(*(ht->_table + i))._status = EMPTY;
	}
}

static size_t GetPrime(Hash* ht)
{
	const int _PrimeSize = 28;//仅可在c++下使用
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
		if (ht->_capacity < _PrimeList[index])
		{
			return _PrimeList[index];
		}
		index++;
	}
	return _PrimeList[_PrimeSize - 1];
}

static size_t HashFunc(HashTable* ht, HTDataType data)
{
	//若需要存储其他类型的数据，需要修改此函数的寻址规则
	return data % ht->_capacity;
}

static void CheckCapacity(HashTable* ht)
{
	assert(ht);
	//若空间不够，扩容
	if (ht->_size * 10 / ht->_capacity >= 7)
	{
		HashTable newht;
		HashInit(&newht, ht->_capacity);
		for (int i = 0; i < ht->_capacity; i++)
		{
			if ((*(ht->_table + i))._status == EXIST)
			{
				HashInsert(&newht, (*(ht->_table + i))._data);//赋用Insert进行重新寻址插入
			}
		}
		free(ht->_table);
		ht->_table = newht._table;
		ht->_size = newht._size;
		ht->_capacity = newht._capacity;
	}
}

bool HashInsert(Hash* ht, HTDataType data)
{
	assert(ht);
	CheckCapacity(ht);

	size_t index = HashFunc(ht, data);
	size_t i = 1;
	while ((*(ht->_table + index))._status != EMPTY)
	{
		if ((*(ht->_table + index))._status == EXIST)
		{
			if ((*(ht->_table + index))._data == data)
			{
				return false;
			}
		}
		//index++;
		//if (index == ht->_capacity)
		//{
		//	index = 0;
		//}
		index = index + i * i;//二次探测寻址
		index = index % ht->_capacity;
		i++;
	}
	(*(ht->_table + index))._data = data;
	(*(ht->_table + index))._status = EXIST;
	ht->_size++;
	return true;
}

bool HashRemove(Hash* ht, HTDataType data)
{
	HTNode* node = HashFind(ht, data);
	if (node)
	{
		node->_status = DELETE;
		return true;
	}
	return false;
}

HTNode* HashFind(Hash* ht, HTDataType data)
{
	assert(ht);
	size_t index = HashFunc(ht, data);
	size_t i = 1;
	while ((*(ht->_table + index))._status != EMPTY)
	{
		if ((*(ht->_table + index))._data == data)
		{
			if ((*(ht->_table + index))._status == EXIST)
			{
				return ht->_table + index;
			}
			else
			{
				return NULL;
			}
		}
		//index++;//线性探测寻址法
		index = index + i * i;//二次探测寻址
		index = index % ht->_capacity;
		i++;
	}
	return NULL;
}

static void HashDestroy(HashTable* ht)
{
	assert(ht);
	free(ht->_table);
	ht->_table = NULL;
	ht->_size = 0;
	ht->_capacity = 0;
}

void HashPrint(HashTable* ht)
{
	//为了测试显示用的打印函数
	for (int i = 0; i < ht->_capacity; i++)
	{
		if (i % 10 == 0 && i != 0)
		{
			printf("\n");
		}
		if ((*(ht->_table + i))._status == EXIST)
		{
			printf("%2d ", (*(ht->_table + i))._data);
		}
		else if((*(ht->_table + i))._status == DELETE)
		{
			printf(" D ");
		}
		else
		{
			printf(" N ");
		}
	}
	printf("\n");
}

void TestHashTable()
{
	Hash ht;
	HashInit(&ht, 0);
	//插入测试
	srand((unsigned)time(0));
	for (int i = 0; i < 100; i++)
	{
		HashInsert(&ht, rand() % 100);
	}
	HashPrint(&ht);
	printf("-------------------------------------------------\n");
	//删除测试
	for (int i = 0; i < 100; i++)
	{
		HashRemove(&ht, rand() % 100);
	}

	HashPrint(&ht);
	HashDestroy(&ht);
}