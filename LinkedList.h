//数据结构：顺序表中链表练习，实现增删查改，以及排序等操作

//SSListNode* BuySSListNode(DataType x);
//void SSListPrint(SSListNode* pHead);
//void SSListDestory(SSListNode** ppHead);
//
//void SSListPushBack(SSListNode** ppHead, DataType x);
//void SSListPopBack(SSListNode** ppHead);
//void SSListPushFront(SSListNode** ppHead, DataType x);
//SSListNode* SSListFind(SSListNode* pHead, DataType x);
//void SSListInsest(SSListNode** ppHead, SSListNode* pos, DataType x);
//void SSListErase(SSListNode** ppHead, SSListNode* pos);

#pragma once

#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef int DataType;

typedef struct SListNode
{
	DataType _data;
	struct SListNode* _pNext;
}SListNode;

SListNode *BuySListNode(DataType data);//申请空间
void SListDestory(SListNode** ppHead);//销毁链表
void SListPrint(SListNode* pHead);//打印链表

void SListPushBack(SListNode** ppHead, DataType data);//尾插链表
void SListPopBack(SListNode* pHead);//删除尾链
void SListPushFront(SListNode** ppHead, DataType data);//头插链表
SListNode* SListFind(SListNode* pHead, DataType data);// 查找链表
void SListInsert(SListNode** ppHead, SListNode* pos, DataType data);//指定位置插入链表
void SListErase(SListNode** ppHead, SListNode* pos);//删除指定链表

//链表练习
void PrintHelp(SListNode* pHead);//1.从尾打印链表
void PrintFromTail(SListNode* pHead);
void DeleteNodeNotTail(SListNode* pHead);//2.删除一个非尾节点（不能遍历）
void SListInsert1(SListNode* pos, DataType data);//3.无头链表一个节点前插入链表（不能遍历）
SListNode* JosephCircle(SListNode* s, size_t circle_num);//4.单链实现约瑟夫环
void SListBubbleSort(SListNode* pHead);//5.逆置链表
void SListBubbleSort(SListNode* pHead);//6.冒泡排序
SListNode* SListUnion(SListNode* pHead1, SListNode* pHead2);//7.合并两个有序链表，并且链表仍有序
SListNode* FindMiddleNode(SListNode* pHead);//8.查找链表的中间结点
SListNode* FindLastKNode(SListNode* pHead, size_t k);//9.查找倒数第K个结点
void* DeleteLastKNode(SListNode* pHead, size_t k);//10.删除倒数第K个结点
//11.链表带环问题
SListNode* JudgeCycle(SListNode* pHead);//判断是否带环
size_t GetCycleLenth(SListNode* meet);//求环长度
SListNode* GetCycleEntrance(SListNode* pHead, SListNode* meet);//求环入口
SListNode* JudgeCross(SListNode* pHead1, SListNode* pHead2);//12.判断链表是否相交（不带环）
SListNode* JudgeCrossCycle(SListNode* pHead1, SListNode* pHead2);//13.判断链表是否相交（可以带环）

SListNode* BuySListNode(DataType data)
{
	SListNode *NewSList = (SListNode*)malloc(sizeof(SListNode));
	NewSList->_data = data;
	NewSList->_pNext = NULL;
	return NewSList;
}

void SListDestory(SListNode** ppHead)
{
	SListNode* prev = *ppHead;
	while (*ppHead)
	{
		(*ppHead) = (*ppHead)->_pNext;
		free(prev);
		prev = (*ppHead);
	}
}

void SListPrint(SListNode* pHead)
{
	SListNode* cur = pHead;
	while (cur)
	{
		printf("%d->", cur->_data);
		cur = cur->_pNext;
	}
	printf("NULL\n");
}

void SListPushBack(SListNode** ppHead, DataType data)
{
	SListNode* Head = *ppHead;
	if ((*ppHead) == NULL)
	{
		(*ppHead) = BuySListNode(data);
		return;
	}
	while ((*ppHead)->_pNext != NULL)
	{
		(*ppHead) = (*ppHead)->_pNext;
	}
	(*ppHead)->_pNext = BuySListNode(data);
	*ppHead = Head;
}

void SListPopBack(SListNode* pHead)
{
	assert(pHead);
	SListNode* cur = pHead;
	SListNode* prev = pHead;
	if (cur->_pNext == NULL)
	{
		free(cur);
		return;
	}
	while (cur->_pNext != NULL)
	{
		prev = cur;
		cur = cur->_pNext;
	}
	prev->_pNext = NULL;
	free(cur);
}

void SListPushFront(SListNode** ppHead, DataType data)
{
	SListNode* NewSList;
	if ((*ppHead) == NULL)
	{
		SListPushBack(ppHead, data);
	}
	NewSList = BuySListNode(data);
	NewSList->_pNext = (*ppHead);
	(*ppHead) = NewSList;
}

SListNode* SListFind(SListNode* pHead, DataType data)
{
	assert(pHead);
	SListNode* cur = pHead;
	while (cur)
	{
		if (cur->_data == data)
		{
			return cur;
		}
		else
		{
			cur = cur->_pNext;
		}
	}
	return NULL;
}

void SListInsert(SListNode** ppHead, SListNode* pos, DataType data)
{
	SListNode* cur = (*ppHead);
	if (pos == (*ppHead))
	{
		SListPushFront(ppHead, data);
		return;
	}
	while (cur->_pNext != pos)
	{
		cur = cur->_pNext;
	}
	cur->_pNext = BuySListNode(data);
	cur->_pNext->_pNext = pos;
}

void SListErase(SListNode** ppHead, SListNode* pos)
{
	assert(ppHead && (*ppHead));
	assert(pos);
	SListNode* cur = (*ppHead);
	if (cur == pos)
	{
		(*ppHead) = (*ppHead)->_pNext;
		free(cur);
		return;
	}
	while (cur->_pNext != pos)
	{
		cur = cur->_pNext;
	}
	cur->_pNext = pos->_pNext;
	free(pos);
}



//链表练习
//1.从尾打印链表
void PrintFromTail(SListNode* pHead)
{
	PrintHelp(pHead);
	printf("\n");
}

void PrintHelp(SListNode* pHead)//从尾打印链表，辅助函数
{
	assert(pHead);
	if (pHead->_pNext != NULL)
	{
		PrintHelp(pHead->_pNext);
	}
	printf("%d ", pHead->_data);//递归打印
}

//2.删除一个非尾节点（不能遍历）
void DeleteNodeNotTail(SListNode* pos)
{
	assert(pos);
	SListNode* cur = pos;
	SListNode* next = pos->_pNext;
	if (cur->_pNext == NULL)
	{
		printf("The node is tail.\n");
		return;
	}
	cur->_data = next->_data;//把下一节点的数据前移，问题转为删除后一个节点
	if (next->_pNext != NULL)
	{
		cur->_pNext = next->_pNext;
	}
	else
	{
		cur->_pNext = NULL;
	}
	free(next);
}

//3.无头链表一个节点前插入链表（不能遍历）
void SListInsert1(SListNode* pos, DataType data)
{
	SListNode* cur = pos;
	SListNode* next = BuySListNode(cur->_data);
	next->_pNext = cur->_pNext;
	next->_data = cur->_data;
	cur->_pNext = next;
	cur->_data = data;
}

//4.单链实现约瑟夫环
SListNode* JosephCircle(SListNode* pHead, size_t circle_num)
{
	assert(pHead);
	SListNode* cur = pHead;
	SListNode* next = NULL;
	while (cur->_pNext)
	{
		cur = cur->_pNext;//链表成环
	}
	cur->_pNext = pHead;
	cur = cur->_pNext;
	while (cur->_pNext != cur)
	{
		size_t count = circle_num;
		while (--count)
		{
			cur = cur->_pNext;//找到每次要删除的节点
		}
		next = cur->_pNext;
		cur->_data = next->_data;
		cur->_pNext = next->_pNext;
		free(next);
	}
	return cur;
}

//5.逆置链表
void ReverseSList(SListNode** ppHead)
{
	assert(*ppHead);
	SListNode* cur = (*ppHead);
	SListNode* new_head = NULL;
	SListNode* next;
	while (cur)
	{
		next = cur->_pNext;
		cur->_pNext = new_head;
		new_head = cur;
		cur = next;
	}
	(*ppHead) = new_head;
}

//6.链表的冒泡排序
void SListBubbleSort(SListNode* pHead)
{
	assert(pHead);
	SListNode* cur = pHead;
	SListNode* end = NULL;
	while (end != pHead)
	{
		while (cur->_pNext != end)
		{
			if (cur->_data > cur->_pNext->_data)
			{
				cur->_data ^= cur->_pNext->_data;
				cur->_pNext->_data ^= cur->_data;
				cur->_data ^= cur->_pNext->_data;
			}
			cur = cur->_pNext;
		}
		end = cur;
		cur = pHead;
	}
}

//7.双链表合并，合并后依旧有序（归并排序思想）
SListNode* SListUnion(SListNode* pHead1, SListNode* pHead2)
{
	SListNode* new_head = NULL, *cur = NULL;
	if (pHead1 == NULL && pHead2 == NULL)
	{
		return NULL;
	}
	if (pHead1 == NULL)
	{
		return pHead2;
	}
	if(pHead2 == NULL)
	{
		return pHead1;
	}
	if (pHead1->_data <= pHead2->_data)
	{
		new_head = pHead1;
		pHead1 = pHead1->_pNext;
	}
	else
	{
		new_head = pHead2;
		pHead2 = pHead2->_pNext;
	}
	cur = new_head;
	while (pHead1 && pHead2)
	{
		if (pHead1->_data <= pHead2->_data)
		{
			cur->_pNext = pHead1;
			pHead1 = pHead1->_pNext;
		}
		else
		{
			cur->_pNext = pHead2;
			pHead2 = pHead2->_pNext;
		}
		cur = cur->_pNext;
	}
	if (pHead1 == NULL)
	{
		cur->_pNext = pHead2;
	}
	else
	{
		cur->_pNext = pHead1;
	}
	return new_head;
}

//8.查找链表的中间结点（思路：快慢指针法）
SListNode* FindMiddleNode(SListNode* pHead)
{
	assert(pHead);
	SListNode* fast = pHead;
	SListNode* cur = pHead;
	while (fast && fast->_pNext != NULL)
	{
		fast = fast->_pNext;
		if (fast->_pNext != NULL)
		{
			fast = fast->_pNext;
			cur = cur->_pNext;
		}
	}
	return cur;
}

//9.查找链表倒数第K个结点
SListNode* FindLastKNode(SListNode* pHead, size_t k)
{
	assert(pHead);
	SListNode* cur = pHead;
	SListNode* end = pHead;
	while (k--)
	{
		if (end == NULL)
		{
			return NULL;
		}
		end = end->_pNext;
	}
	while (end)
	{
		end = end->_pNext;
		cur = cur->_pNext;
	}
	return cur;
}

//10.删除倒数第K个节点
void* DeleteLastKNode(SListNode** ppHead, size_t k)
{
	SListErase(ppHead, FindLastKNode((*ppHead), k));
}

//11.判断链表是否带环，带环求环长度和入口点
SListNode* JudgeCycle(SListNode* pHead)//判断是否带环
{
	assert(pHead);
	SListNode* fast = pHead;
	SListNode* slow = pHead;
	while (fast)
	{
		slow = slow->_pNext;
		fast = fast->_pNext;
		if (fast != NULL)
		{
			fast = fast->_pNext;
		}
		if (fast == slow)
		{
			return slow;
		}
	}
	return NULL;
}

size_t GetCycleLenth(SListNode* meet)//求环长度
{
	SListNode* cur = meet;
	size_t count = 1;
	while (cur->_pNext != meet)
	{
		cur = cur->_pNext;
		count++;
	}
	return count;
}

SListNode* GetCycleEntrance(SListNode* pHead, SListNode* meet)//求环的入口点
{
	while (pHead != meet)
	{
		pHead = pHead->_pNext;
		meet = meet->_pNext;
	}
	return meet;
}

//12.判断链表是否相交（假设不带环）
SListNode* JudgeCross(SListNode* pHead1, SListNode* pHead2)
{
	//两种思路：
	//1.找到两个尾指针，若相同，相交，再长的链表先走相差的步数，两者同时走找交点
	//2.同样的找尾指针，若相同，说明相交，将尾连任意表的头构成环，转换成求环入口问题
	//这里只实现第一种
	assert(pHead1 && pHead2);
	SListNode* cur1 = pHead1;
	SListNode* cur2 = pHead2;
	SListNode* plong = NULL;
	SListNode* pshort = NULL;
	int count = 0;
	int count1 = 1, count2 = 1;
	while (cur1->_pNext != NULL)//均走到尾，若尾指针相同，说明相交
	{
		cur1 = cur1->_pNext;
		count1++;
	}
	while (cur2->_pNext != NULL)
	{
		cur2 = cur2->_pNext;
		count2++;
	}
	if (cur1 != cur2)
	{
		return NULL;
	}
	count = abs(count1 - count2);
	if (count1 > count2)
	{
		plong = pHead1;
		pshort = pHead2;
	}
	else
	{
		plong = pHead2;
		pshort = pHead1;
	}
	while (count--)
	{
		plong = plong->_pNext;
	}
	while (plong != pshort)
	{
		plong = plong->_pNext;
		pshort = pshort->_pNext;
	}
	return plong;
}

//13.判断链表是否相交（设链表可以带环）
SListNode* JudgeCrossCycle(SListNode* pHead1, SListNode* pHead2)
{
	SListNode* cur1 = JudgeCycle(pHead1);
	SListNode* cur2 = JudgeCycle(pHead2);
	SListNode* traversal = NULL;
	if (cur1 == NULL && cur2 == NULL)//情况1：都不带环
	{
		return JudgeCross(pHead1, pHead2);
	}
	if (cur1 == NULL || cur2 == NULL)//情况2：一个有环一个无环，不可能相交
	{
		return NULL;
	}
	//至此两个链均带环，考虑三种情况
	//先取出环入口
	cur1 = GetCycleEntrance(pHead1, cur1);
	cur2 = GetCycleEntrance(pHead1, cur2);
	traversal = cur1->_pNext;
	//情况3：相交且环入口相同
	if (cur1 == cur2)
	{
		return cur1;
	}
	//情况4：带环相交入口不同
	//情况5：带环不相交
	while (1)
	{
		traversal = traversal->_pNext;
		if (traversal == cur2)//该种情况为情况4，打印两个地址返回其中一个指针
		{
			printf("#%p\n#%p\n", cur1, cur2);
			return cur1;
		}
		if (traversal == cur1)//带环不想交，返回空
		{
			return NULL;
		}
	}
}