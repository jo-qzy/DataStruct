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

void BitmapInit(Bitmap* bm, size_t range);
void BitmapSet(Bitmap* bm, size_t num);
void BitmapReset(Bitmap* bm, size_t num);
bool BitmapTest(Bitmap* bm, size_t num);

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
	assert(bm && num < bm->_range);
	size_t index = num / 32;
	size_t position = num % 32;
	size_t set = 1;
	(*(bm->_bit + index)) |= (set << position);
}

void BitmapReset(Bitmap* bm, size_t num)
{
	assert(bm && num < bm->_range);
	size_t index = num / 32;
	size_t position = num % 32;
	size_t set = 1;
	(*(bm->_bit + index)) &= ~(set << position);
}

bool BitmapTest(Bitmap* bm, size_t num)
{
	assert(bm && num < bm->_range);
	size_t index = num / 32;
	size_t position = num % 32;
	size_t cmp = 1;
	return ((*(bm->_bit + index)) & (cmp << position)) ? true : false;
}

void TestBitmap()
{
	Bitmap bm;
	BitmapInit(&bm, 100000);
	//²åÈë
	BitmapSet(&bm, 444);
	BitmapSet(&bm, 555);
	BitmapSet(&bm, 789);
	BitmapSet(&bm, 3);
	BitmapSet(&bm, 4567);
	printf("²ôÈë\n%d\n", BitmapTest(&bm, 444));
	printf("%d\n", BitmapTest(&bm, 443));
	printf("%d\n", BitmapTest(&bm, 555));
	printf("%d\n", BitmapTest(&bm, 789));
	printf("%d\n", BitmapTest(&bm, 3));
	printf("%d\n", BitmapTest(&bm, 4567));
	
	//É¾³ý
	BitmapReset(&bm, 555);
	BitmapReset(&bm, 555);
	BitmapReset(&bm, 444);
	BitmapReset(&bm, 444);
	BitmapReset(&bm, 789);
	BitmapReset(&bm, 5);
	printf("É¾³ý\n%d\n", BitmapTest(&bm, 444));
	printf("%d\n", BitmapTest(&bm, 555));
	printf("%d\n", BitmapTest(&bm, 789));
	printf("%d\n", BitmapTest(&bm, 5));
}