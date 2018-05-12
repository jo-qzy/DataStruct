#pragma once

#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef int STDataType;
#define size 4

typedef struct Stack
{
	STDataType* _array;
	size_t	_top;
	size_t	_capacity;
}Stack;

Stack* StackInit();
void StackPush(Stack* s, STDataType x);
void StackPop(Stack* s);
STDataType StackTop(Stack* s);
size_t StackSize(Stack* s);
int StackEmpty(Stack* s);
void StackDestroy(Stack* s);

Stack* StackInit()
{
	Stack* newstack = (Stack*)malloc(sizeof(Stack));
	newstack->_capacity = size;
	newstack->_array = (STDataType*)malloc(sizeof(STDataType) * newstack->_capacity);
	newstack->_top = 0;
	return newstack;
}

void StackPush(Stack* s, STDataType x)
{
	if (s->_top == s->_capacity - 1)
	{
		s->_capacity *= 2;
		s->_array = (STDataType*)realloc(s->_array, sizeof(STDataType) * s->_capacity);
	}
	*(s->_array + s->_top) = x;
	s->_top++;
}

void StackPop(Stack* s)
{
	if (!StackEmpty(s))
	{
		return;
	}
	s->_top--;
}

STDataType StackTop(Stack* s)
{
	return *(s->_array + s->_top - 1);
}

size_t StackSize(Stack* s)
{
	return s->_top;
}

int StackEmpty(Stack* s)
{
	if (s->_top == 0)
	{
		return 0;
	}
	return 1;
}

void StackDestroy(Stack* s)
{
	free(s->_array);
	free(s);
}