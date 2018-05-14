#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

typedef struct Bitmap
{
	size_t* _bit;
	size_t _range;
}Bitmap;

void BitmapInit(Bitmap* bm, size_t range);//初始化
void BitmapSet(Bitmap* bm, size_t num);//将某个数的位置置为1
void BitmapReset(Bitmap* bm, size_t num);//将某个数的位置置为0
bool BitmapTest(Bitmap* bm, size_t num);//判断某个数是否存在
void BitmapDestroy(Bitmap* bm);//销毁位图

void TestBitmap();//测试用例

void BitmapInit(Bitmap* bm, size_t range)
{
	assert(bm);
	bm->_range = range;
	bm->_bit = (size_t*)malloc(sizeof(size_t) * ((bm->_range >> 5) + 1));
	assert(bm->_bit);
	memset(bm->_bit, 0, sizeof(size_t) * ((bm->_range >> 5) + 1));
}

void BitmapSet(Bitmap* bm, size_t num)
{
	assert(bm);
	size_t index = num / 32;
	size_t position = num % 32;
	size_t set = 1;
	(*(bm->_bit + index)) |= (set << position);
}

void BitmapReset(Bitmap* bm, size_t num)
{
	assert(bm);
	size_t index = num / 32;
	size_t position = num % 32;
	size_t set = 1;
	(*(bm->_bit + index)) &= ~(set << position);
}

bool BitmapTest(Bitmap* bm, size_t num)
{
	assert(bm);
	size_t index = num / 32;
	size_t position = num % 32;
	size_t cmp = 1;
	return ((*(bm->_bit + index)) & (cmp << position)) ? true : false;
}

void BitmapDestroy(Bitmap* bm)
{
	assert(bm);
	free(bm->_bit);
	bm->_bit = NULL;
	bm->_range = 0;
}

void TestBitmap()
{
	Bitmap bm;
	BitmapInit(&bm, 100000);
	//插入
	BitmapSet(&bm, 444);
	BitmapSet(&bm, 555);
	BitmapSet(&bm, 789);
	BitmapSet(&bm, 3);
	BitmapSet(&bm, 4567);
	printf("掺入\n%d\n", BitmapTest(&bm, 444));
	printf("%d\n", BitmapTest(&bm, 443));
	printf("%d\n", BitmapTest(&bm, 555));
	printf("%d\n", BitmapTest(&bm, 789));
	printf("%d\n", BitmapTest(&bm, 3));
	printf("%d\n", BitmapTest(&bm, 4567));
	
	//删除
	BitmapReset(&bm, 555);
	BitmapReset(&bm, 555);
	BitmapReset(&bm, 444);
	BitmapReset(&bm, 444);
	BitmapReset(&bm, 789);
	BitmapReset(&bm, 5);
	printf("删除\n%d\n", BitmapTest(&bm, 444));
	printf("%d\n", BitmapTest(&bm, 555));
	printf("%d\n", BitmapTest(&bm, 789));
	printf("%d\n", BitmapTest(&bm, 5));

	BitmapDestroy(&bm);
}