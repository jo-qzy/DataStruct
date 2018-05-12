//栈面试题
//1.两个栈实现一个队列
void QuequePush_Stack(Stack* s1, STDataType data);
STDataType QuequePop_Stack(Stack* s1, Stack* s2);
void TestTwoStackToQueque();

void QuequePush_Stack(Stack* s1, STDataType data)
{
	StackPush(s1, data);
}

STDataType QuequePop_Stack(Stack* s1, Stack* s2)
{
	STDataType ret;
	if (StackEmpty(s1) == 0 && StackEmpty(s2) == 0)
	{
		assert(0);
	}
	if (StackEmpty(s2) != 0)
	{
		ret = StackTop(s2);
		StackPop(s2);
		return ret;
	}
	while (StackEmpty(s1) != 1)
	{
		StackPush(s2, StackTop(s1));
		StackPop(s1);
	}
	ret = StackTop(s1);//要取的元素为s1的栈底元素
	StackPop(s1);
	return ret;
}

void TestTwoStackToQueque()//测试用例
{
	Stack* s1 = StackInit();
	Stack* s2 = StackInit();
	int i = 0;
	for (i; i<5; i++)
	{
		QuequePush_Stack(s1, i);
	}
	printf("%d\n", QuequePop_Stack(s1, s2));
	printf("%d\n", QuequePop_Stack(s1, s2));
}

//2.实现栈的出栈入栈，且可以给出其中的最小值
typedef struct MinStack
{
	Stack* _st;
	Stack* _min;
}MinStack;

MinStack* MinStackInit();
void MinStackPush(MinStack* ms, STDataType data);
void MinStackPop(MinStack* ms);
STDataType MinStackTop(MinStack* ms);
STDataType MinStackMin(MinStack* ms);

//缺点：当重复入最小值的时候，入100个最小值，最小值得栈也会入100个最小值

MinStack* MinStackInit()
{
	MinStack* ms;
	ms = (MinStack*)malloc(sizeof(MinStack));
	ms->_st = StackInit();
	ms->_min = StackInit();
	return ms;
}

void MinStackPush(MinStack* ms, STDataType data)
{
	assert(ms);
	StackPush(ms->_st, data);
	if (StackEmpty(ms->_min) == 0)
	{
		StackPush(ms->_min, data);
	}
	else if ((data == StackTop(ms->_min)) || (data < StackTop(ms->_min)))
	{
		StackPush(ms->_min, data);
	}
}

void MinStackPop(MinStack* ms)
{
	assert(ms);
	if (StackEmpty(ms->_st) == 0)
	{
		assert(0);
	}
	if (StackTop(ms->_st) == StackTop(ms->_min))
	{
		StackPop(ms->_min);
	}
	StackPop(ms->_st);
}

STDataType MinStackTop(MinStack* ms)
{
	assert(ms);
	return StackTop(ms->_st);
}

STDataType MinStackMin(MinStack* ms)
{
	assert(ms);
	return StackTop(ms->_min);
}

void TestMinStack()//测试用例
{
	MinStack* ms = MinStackInit();
	MinStackPush(ms, 4);
	printf("%d\n", MinStackMin(ms));
	MinStackPush(ms, 3);
	printf("%d\n", MinStackMin(ms));
	MinStackPush(ms, 5);
	MinStackPush(ms, 6);
	MinStackPush(ms, 2);
	MinStackPush(ms, 8);
	printf("%d\n", MinStackMin(ms));
	MinStackPop(ms);
	MinStackPop(ms);
	MinStackPop(ms);
	printf("%d\n", MinStackMin(ms));
}

//3.一个数组实现共享栈
typedef struct UnionStack
{
	STDataType* _array;
	size_t _top1;
	size_t _top2;
	size_t	_capacity;
}UStack;

UStack* UStackInit();
void UStackPush(UStack* us, size_t flag, STDataType data);
void UStackPop(UStack* us, size_t flag);
STDataType UStackTop(UStack* us, size_t flag);
size_t UStackSize(UStack* us, size_t flag);
int UStackEmpty(UStack* us, size_t flag);

UStack* UStackInit()
{
	UStack* new_ustack = (UStack*)malloc(sizeof(UStack));
	new_ustack->_capacity = size;
	new_ustack->_array = (STDataType*)malloc(sizeof(STDataType) * new_ustack->_capacity);
	new_ustack->_top1 = 0;
	new_ustack->_top2 = 0;
	return new_ustack;
}

void UStackPush(UStack* us, size_t flag, STDataType data)
{
	assert(us);
	//栈选择检查，防御性编程
	if ((flag != 1) && (flag != 2))
	{
		printf("选择栈错误！\n");
		assert(0);
	}
	//压栈前容量检查，容量不够重新申请
	if ((us->_top1 == us->_capacity / 2 - 1) || (us->_top2 == us->_capacity / 2 - 1))
	{
		us->_capacity *= 2;
		STDataType* new_us = (STDataType*)malloc(sizeof(STDataType) * us->_capacity);
		memcpy(new_us, us->_array, sizeof(STDataType) * us->_top1);
		memcpy(new_us + us->_capacity / 2, us->_array + us->_capacity / 4, sizeof(STDataType) * us->_top2);
		free(us->_array);
		us->_array = new_us;
	}
	//选择栈进行操作
	if (flag == 1)
	{
		*(us->_array + us->_top1) = data;
		us->_top1++;
	}
	else if (flag == 2)
	{
		*(us->_array + us->_capacity / 2 + us->_top2) = data;
		us->_top2++;
	}
}

void UStackPop(UStack* us, size_t flag)
{
	assert(us);
	if ((flag != 1) && (flag != 2))
	{
		printf("选择栈错误！\n");
		assert(0);
	}
	if (flag == 1)
	{
		us->_top1--;
	}
	else if (flag == 2)
	{
		us->_top2--;
	}
}

STDataType UStackTop(UStack* us, size_t flag)
{
	assert(us);
	if ((flag != 1) && (flag != 2))
	{
		printf("选择栈错误！\n");
		assert(0);
	}
	if (flag == 1)
	{
		return *(us->_array + us->_top1 - 1);
	}
	else if (flag == 2)
	{
		return *(us->_array + us->_capacity / 2 + us->_top2 - 1);
	}
}

size_t UStackSize(UStack* us, size_t flag)
{
	assert(us);
	if ((flag != 1) && (flag != 2))
	{
		printf("选择栈错误！\n");
		assert(0);
	}
	if (flag == 1)
	{
		return *(us->_array + us->_top1 - 1);
	}
	else if (flag == 2)
	{
		return *(us->_array + us->_capacity / 2 + us->_top2 - 1);
	}
}

int UStackEmpty(UStack* us, size_t flag)
{
	assert(us);
	if ((flag != 1) && (flag != 2))
	{
		printf("选择栈错误！\n");
		assert(0);
	}
	if (flag == 1)
	{
		if (us->_top1 == 0)
		{
			return 0;
		}
	}
	else if (flag == 2)
	{
		if (us->_top2 == 0)
		{
			return 0;
		}
	}
	return 1;
}

void TestUnionStack()
{
	UStack* us = UStackInit();
	UStackPush(us, 1, 4);
	UStackPush(us, 1, 3);
	UStackPush(us, 1, 2);
	UStackPush(us, 1, 1);
	UStackPush(us, 2, 1);
	UStackPush(us, 2, 2);
	UStackPush(us, 2, 3);
	UStackPush(us, 2, 4);
	printf("%d\n", UStackTop(us, 1));
	printf("%d\n", UStackTop(us, 2));
	UStackPop(us, 1);
	UStackPop(us, 2);
	printf("%d\n", UStackTop(us, 1));
	printf("%d\n", UStackTop(us, 2));
	printf("栈1容量：%d\n", UStackSize(us, 1));
	printf("栈2容量：%d\n", UStackSize(us, 2));
}

//4.判断入栈序列是否合法
void JudgeSeqLegal(const STDataType dst[], const STDataType src[], size_t _size)
{
	Stack* s = StackInit();
	size_t src_index = 0;
	size_t dst_index = 0;
	while (dst_index != _size)
	{
		if (dst[dst_index] == src[src_index])
		{
			dst_index++, src_index++;
		}
		else
		{
			if (StackTop(s) == dst[dst_index] && StackEmpty(s))
			{
				StackPop(s);
				dst_index++;
			}
			else
			{
				StackPush(s, src[src_index]);
				src_index++;
			}
		}
		if (StackEmpty(s) != 0 && src_index == _size && StackTop(s) != dst[dst_index])
		{
			printf("序列不合法\n");
			return;
		}
	}
	printf("序列合法\n");
}

void TestJudgeSeqLegal()
{
	int arr[5] = { 1,2,3,4,5 };
	int arr2[5] = { 1,5,3,2,4 };
	JudgeSeqLegal(arr2, arr, 5);
}