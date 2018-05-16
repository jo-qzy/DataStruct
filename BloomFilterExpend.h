#pragma once

#include "Bitmap.h"

typedef char* BloomFilterData;

typedef struct BloomFilterExpend
{
	size_t* _bit;
	size_t _range;
}BFE;

void BFEInit(BFE* bf, size_t range);
size_t BloomFilterFunc1(BloomFilterData str);//¹þÏ£º¯Êý
size_t BloomFilterFunc2(BloomFilterData str);
size_t BloomFilterFunc3(BloomFilterData str);
void BFESet(BFE* bf, BloomFilterData str);
bool BFEReset(BFE* bf, BloomFilterData str);

void BFEInit(BFE* bf, size_t range)
{
	assert(bf);
	bf->_range = range;
	bf->_bit = (size_t*)calloc(0, sizeof(size_t) * bf->_range);
	assert(bf->_bit);
}

size_t BloomFilterFunc1(BloomFilterData str)
{
	size_t seed = 131;
	register size_t hash = 0;
	while (*str)
	{
		hash = hash * seed + (*str++);
	}
	return (hash & 0x7FFFFFFF);
}

size_t BloomFilterFunc2(BloomFilterData str)
{
	register size_t hash = 0;
	size_t seed = 65599;
	while (*str)
	{
		hash = hash * seed + (*str++);
	}
	return hash;
}

size_t BloomFilterFunc3(BloomFilterData str)
{
	register size_t hash = 0;
	size_t seed = 63689;
	while (*str)
	{
		hash = hash * seed + (*str++);
	}
	return hash;
}

void BFESet(BFE* bf, BloomFilterData str)
{
	assert(bf);
	size_t index1 = BloomFilterFunc1(str) % bf->_range;
	size_t index2 = BloomFilterFunc2(str) % bf->_range;
	size_t index3 = BloomFilterFunc3(str) % bf->_range;
	(*(bf->_bit + index1))++;
	(*(bf->_bit + index1))++;
	(*(bf->_bit + index1))++;
}

bool BFEReset(BFE* bf, BloomFilterData str)
{
	assert(bf);
	size_t index1 = BloomFilterFunc1(str);
	size_t index2 = BloomFilterFunc2(str);
	size_t index3 = BloomFilterFunc3(str);
	if ((*(bf->_bit + index1)) > 0 && (*(bf->_bit + index2)) > 0 && (*(bf->_bit + index3)) > 0)
	{
		(*(bf->_bit + index1))--;
		(*(bf->_bit + index2))--;
		(*(bf->_bit + index3))--;
		return true;
	}
	return false;
}

void TestBloomFilterExpend()
{
	BFE bf;
	BFEInit(&bf, 200);
	char str1[] = "hello";
	char str2[] = "nice";
	char str3[] = "perfect";
	BFESet(&bf, str1);
	BFESet(&bf, str2);
	BFESet(&bf, str3);

}