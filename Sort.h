#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>



void InsertSort(int* arr, size_t size);//插入排序
void ShellSort(int* arr, size_t size);//希尔排序
void SelectSort(int* arr, size_t size);//选择排序
void BubbleSort(int* arr, size_t size);//冒泡排序
void QuickSort(int* arr, int left, int right);//快速排序
static int PartSort1(int* arr, int left, int right);//左右指针法
static int PartSort2(int* arr, int left, int right);//挖坑法
static int PartSort3(int* arr, int left, int right);//右指针法

void MergeSort(int* arr, int size);//归并排序
static void PartMergeSort(int* arr, int left, int right, int* tmp);//部分归并

static void Swap(int* x1, int* x2);
static void ResetArr(int* arr);
static void PrintArr(int* arr, size_t size);

void TestSort();//测试用例

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

static int PartSort1(int* arr, int left, int right)
{
	assert(arr && left < right);
	int key = arr[right];
	int head = left;
	int tail = right;
	while (head < tail)
	{
		//左边找比Key大的数，右边找比Key小得数，交换
		while (head < tail && *(arr + head) <= key)
		{
			head++;
		}
		while (head < tail && *(arr + tail) >= key)
		{
			tail--;
		}
		Swap(arr + head, arr + tail);
	}
	Swap(arr + head, arr + right);
	return head;
}

static int PartSort2(int* arr, int left, int right)
{
	assert(arr && left < right);
	int key = arr[right];
	int head = left;
	int tail = right;
	while (head < tail)
	{
		//挖坑，将Key值得位置当作坑，左右两边找，左边找到大的数就把数放到坑里，拿走的数的位置成为新的坑
		//右边开始找小的数，找到放在右边的坑里，拿走数的位置成为新的坑，循环直至左右指针相遇
		while (head < tail && arr[head] <= key)
		{
			head++;
		}
		arr[tail] = arr[head];
		while (head < tail && arr[tail] >= key)
		{
			tail--;
		}
		arr[head] = arr[tail];
	}
	arr[head] = key;
	return head;
}

static int PartSort3(int* arr, int left, int right)
{
	assert(arr && left < right);
	int key = arr[right];
	int fast = left;
	int slow = left - 1;
	//一个快指针一个慢指针，快指针始终前进，慢指针只有在当前数小于Key才走
	//当慢指针++后不等于快指针，则交换两数的位置
	while (fast < right)
	{
		if (arr[fast] <= key && ++slow != fast)
		{
				Swap(arr + fast, arr + slow);
		}
		fast++;
	}
	slow++;
	Swap(arr + slow, arr + right);
	return slow;
}

void QuickSort(int* arr, int left, int right)
{
	assert(arr);
	int div = PartSort3(arr, left, right);
	if (left < div - 1)
	{
		//递归进行区间划分
		QuickSort(arr, left, div - 1);
	}
	if (right > div + 1)
	{
		QuickSort(arr, div + 1, right);
	}
}

void MergeSort(int* arr, int size)
{
	//归并需要临时空间
	int* tmp = (int*)malloc(sizeof(int) * size);
	PartMergeSort(arr, 0, size - 1, tmp);
	free(tmp);
}

static void PartMergeSort(int* arr, int left, int right, int* tmp)
{
	if (left >= right)
	{
		return;
	}
	int mid = (left + right) / 2;//取中间数分成两部分递归进行归并
	PartMergeSort(arr, left, mid, tmp);
	PartMergeSort(arr, mid + 1, right, tmp);

	int begin1 = left, end1 = mid;
	int begin2 = mid + 1, end2 = right;
	int index = left;
	while (begin1 <= end1 && begin2 <= end2)
	{
		//从原数组中取数据，将其归并到临时空间中
		if (arr[begin1] <= arr[begin2])
		{
			tmp[index++] = arr[begin1++];
		}
		else
		{
			tmp[index++] = arr[begin2++];
		}
	}
	//由于两部分必定有一部分还没拷完，所以把剩下部分继续排在临时数组后面
	if (begin1 <= end1)
	{
		memcpy(tmp + index, arr + begin1, sizeof(int) * (end1 - begin1 + 1));
	}
	else
	{
		memcpy(tmp + index, arr + begin2, sizeof(int) * (end2 - begin2 + 1));
	}
	//将临时空间的数据放回原数组
	memcpy(arr + left, tmp + left, sizeof(int) * (right - left + 1));
}

static void Swap(int* x1, int* x2)
{
	if (x1 == x2)
	{
		return;
	}
	*x1 ^= *x2;
	*x2 ^= *x1;
	*x1 ^= *x2;
}

static void ResetArr(int* arr)
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
	*(arr + 9) = 5;
}

static void PrintArr(int* arr, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		printf("%d ", *(arr + i));
	}
	printf("\n");
}

void TestSort()
{
	int arr[10] = { 6,4,3,7,9,1,5,2,8,5 };
	PrintArr(arr, 10);
	
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

	QuickSort(arr, 0, 9);
	PrintArr(arr, 10);
	ResetArr(arr);

	MergeSort(arr, 10);
	PrintArr(arr, 10);
}