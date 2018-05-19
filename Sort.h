#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>



void InsertSort(int* arr, size_t size);
void ShellSort(int* arr, size_t size);
void SelectSort(int* arr, size_t size);
void BubbleSort(int* arr, size_t size);

void Swap(int* x1, int* x2);
void ResetArr(int* arr);
void PrintArr(int* arr, size_t size);

void InsertSort(int* arr, size_t size)
{
	assert(arr);
	for (int i = 0; i < size - 1; i++)
	{
		int end = i;//最后的有序的数的坐标
		int tmp = *(arr + i + 1);//需要插入的数
		while (end >= 0 && *(arr + end) > tmp)
		{
			*(arr + end + 1) = *(arr + end);
			end--;
		}
		*(arr + end + 1) = tmp;//1.下标为-1  2.找到插入下标
	}
}

void ShellSort(int* arr, size_t size)
{
	assert(arr);
	size_t gap = size;
	while (gap > 1)
	{
		//当gap > 1时，为预排序，让数列变得接近有序
		//gap == 1时，则为直接插入排序
		gap /= 3;
		if (gap == 0)
		{
			gap = 1;
		}
		for (size_t i = 0; i < size - gap; i++)
		{
			int end = i;
			int tmp = *(arr + i + gap);
			while (end >= 0 && *(arr + end) > tmp)
			{
				*(arr + end + gap) = *(arr + end);
				end -= gap;
			}
			*(arr + end + gap) = tmp;
		}
	}
}

void SelectSort(int* arr, size_t size)
{
	assert(arr);
	int index = 0;
	for (size_t i = 0; i < size - 1; i++)
	{
		int min = *(arr + i);
		index = i;
		//找出最小数的下标
		for (size_t j = i + 1; j < size; j++)
		{
			if (min > *(arr + j))
			{
				min = *(arr + j);
				index = j;
			}
		}
		Swap(arr + i, arr + index);
	}
}

void BubbleSort(int* arr, size_t size)
{
	assert(arr);
	while (size--)
	{
		int flag = 0;
		for (int i = 0; i < size; i++)
		{
			if (*(arr + i) > *(arr + i + 1))
			{
				flag = 1;
				Swap(arr + i, arr + i + 1);
			}
		}
		if (flag == 0)
		{
			return;
		}
	}
}

void Swap(int* x1, int* x2)
{
	if (x1 == x2)
	{
		return;
	}
	*x1 ^= *x2;
	*x2 ^= *x1;
	*x1 ^= *x2;
}

void ResetArr(int* arr)
{
	*(arr + 0) = 6;
	*(arr + 1) = 4;
	*(arr + 2) = 3;
	*(arr + 3) = 7;
	*(arr + 4) = 9;
	*(arr + 5) = 1;
	*(arr + 6) = 5;
	*(arr + 7) = 2;
	*(arr + 8) = 8;
	*(arr + 9) = 10;
}

void PrintArr(int* arr, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		printf("%d ", *(arr + i));
	}
	printf("\n");
}

void TestSort()
{
	int arr[10] = { 6,4,3,7,9,1,5,2,8,10 };
	SelectSort(arr, 10);
	PrintArr(arr, 10);
	ResetArr(arr);

	ShellSort(arr, 10);
	PrintArr(arr, 10);
	ResetArr(arr);

	InsertSort(arr, 10);
	PrintArr(arr, 10);
	ResetArr(arr);

	BubbleSort(arr, 10);
	PrintArr(arr, 10);
	ResetArr(arr);
}