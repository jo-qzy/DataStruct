#pragma once 

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

typedef int BTreeDataType;

typedef struct BinaryTreeNode
{
	struct BinaryTreeNode* _left;
	struct BinaryTreeNode* _right;
	BTreeDataType _data;
}BTNode;

#include "queue.h"
#include "stack.h"

BTNode* BuyBTNode(BTreeDataType x);//申请空间
BTNode* CreateBTree(BTreeDataType* a, size_t* pIndex, BTreeDataType invalid);//创建二叉树
void BTreePrevOrder(BTNode* root);//递归前序遍历
void BTreeInOrder(BTNode* root);//递归中序遍历
void BTreePostOrder(BTNode* root);//递归后序遍历

size_t BTreeSize(BTNode* root);//树节点个数
size_t BTreeLeafSize(BTNode* root);//树叶子节点个数
size_t BTreeKLevelSize(BTNode* root, size_t k);//第k层节点个数
size_t BTreeDepth(BTNode* root);//求树深度
BTNode* BTreeFind(BTNode* root, BTreeDataType x);//寻找指定节点
void BTreeLevelOrder(BTNode* root);//层序遍历
// 判断完全二叉树 
int IsCompleteBTree(BTNode* root);
int IsCompleteBTree1(BTNode* root); // flag的方式判断 
								   // 非递归遍历 
void BTreePrevOrderNonR(BTNode* root);
void BTreeInOrderNonR(BTNode* root);
void BTreePostOrderNonR(BTNode* root);

//面试题
void BTreeMirror(BTNode* root);
BTNode* BTreeFindLchild(BTNode* root, BTreeDataType x);

BTNode* BuyBTNode(BTreeDataType x)
{
	BTNode* new_node = (BTNode*)malloc(sizeof(BTNode));
	new_node->_data = x;
	new_node->_left = NULL;
	new_node->_right = NULL;
	return new_node;
}

BTNode* CreateBTree(BTreeDataType* a, size_t* pIndex, BTreeDataType invalid)
{
	BTNode* root = NULL;
	if (*(a + *pIndex) != invalid)
	{
		root = BuyBTNode(*(a + *pIndex));
		(*pIndex)++;
		root->_left = CreateBTree(a, pIndex, invalid);
		(*pIndex)++;
		root->_right = CreateBTree(a, pIndex, invalid);
	}
	return root;
}

void BTreePrevOrder(BTNode* root)
{
	if (root == NULL)
	{
		return;
	}
	printf("%d ", root->_data);
	BTreePrevOrder(root->_left);
	BTreePrevOrder(root->_right);
}

void BTreeInOrder(BTNode* root)
{
	if (root == NULL)
	{
		return;
	}
	BTreeInOrder(root->_left);
	printf("%d ", root->_data);
	BTreeInOrder(root->_right);
}

void BTreePostOrder(BTNode* root)
{
	if (root == NULL)
	{
		return;
	}
	BTreePostOrder(root->_left);
	BTreePostOrder(root->_right);
	printf("%d ", root->_data);
}

size_t BTreeSize(BTNode* root)
{
	if (root == NULL)
	{
		return 0;
	}
	//当前节点加左树和右树节点
	return 1 + BTreeSize(root->_left) + BTreeSize(root->_right);
}

size_t BTreeLeafSize(BTNode* root)
{
	static int count = 0;
	if (root == NULL)//不判空出错
	{
		return 0;
	}
	else if (root->_left == NULL && root->_right == NULL)
	{
		return 1;
	}
	return BTreeLeafSize(root->_left) + BTreeLeafSize(root->_right);
}

size_t BTreeKLevelSize(BTNode* root, size_t k)
{
	if (root == NULL)
	{
		return 0;
	}
	if (k == 1)
	{
		return 1;
	}
	//求第k层节点相当于求
	//左树第k-1层节点加右树第k-1层节点
	return BTreeKLevelSize(root->_left, k - 1) + BTreeKLevelSize(root->_right, k - 1);
}

size_t BTreeDepth(BTNode* root)
{
	if (root == NULL)
	{
		return 0;
	}
	size_t left = BTreeDepth(root->_left);
	size_t right = BTreeDepth(root->_right);
	return 1 + (left < right ? right : left);//返回左树右树中较大的深度加当前层
}

BTNode* BTreeFind(BTNode* root, BTreeDataType x)
{
	if (root == NULL)
	{
		return NULL;
	}
	if (root->_data == x)
	{
		return root;
	}
	BTNode* left = BTreeFind(root->_left, x);
	//左右判空，若有一个不为空，说明找到，返回该地址至上层
	if (left != NULL)
	{
		return left;
	}
	return BTreeFind(root->_right, x);//返回右，无论是否为空
}

void BTreeLevelOrder(BTNode* root)
{
	if (root == NULL)
	{
		return;
	}
	Queue* q = QueueInit();
	QueuePush(q, root);
	while (QueueEmpty(q))
	{
		BTNode* cur = QueueFront(q);//涉及队列的使用需要用我写的队列配合使用
		QueuePop(q);
		printf("%d ", cur->_data);
		if (cur->_left != NULL)
		{
			QueuePush(q, cur->_left);
		}
		if (cur->_right != NULL)
		{
			QueuePush(q, cur->_right);
		}
		
	}
	printf("\n");
	QueueDestroy(q);
}

int IsCompleteBTree(BTNode* root)
{
	if (root == NULL)
	{
		return 1;
	}
	Queue* q = QueueInit();
	QueuePush(q, root);
	while (QueueEmpty(q))
	{
		BTNode* cur = QueueFront(q);
		if (QueueFront(q) == NULL)
		{
			QueuePop(q);
			break;
		}
		if (cur != NULL)
		{
			QueuePush(q, cur->_left);
			QueuePush(q, cur->_right);
			QueuePop(q);
		}
	}
	while (QueueEmpty(q))
	{
		BTNode* cur = QueueFront(q);
		QueuePop(q);
		if (cur != NULL)
		{
			return 0;
		}
	}
	QueueDestroy(q);
	return 1;
}

int IsCompleteBTree1(BTNode* root)
{
	if (root == NULL)
	{
		return 1;
	}
	Queue* q = QueueInit();
	QueuePush(q, root);
	int flag = 0;
	while (QueueEmpty(q))
	{
		BTNode* cur = QueueFront(q);
		QueuePop(q);
		if (cur != NULL && flag == 1)
		{
			return 0;
		}
		if (cur == NULL)
		{
			flag = 1;
		}
		else
		{
			QueuePush(q, cur->_left);
			QueuePush(q, cur->_right);
		}
	}
	QueueDestroy(q);
	return 1;
}

void BTreePrevOrderNonR(BTNode* root)
{
	if (root == NULL)
	{
		return;
	}
	Stack* s = StackInit();
	BTNode* cur = root;
	while (cur || (StackEmpty(s) != 0))
	{
		while (cur)
		{
			printf("%d ", cur->_data);
			StackPush(s, cur);
			cur = cur->_left;
		}
		BTNode* front = StackTop(s);
		StackPop(s);
		cur = front->_right;
	}
	StackDestroy(s);
	printf("\n");
}

void BTreeInOrderNonR(BTNode* root)
{
	if (root == NULL)
	{
		return;
	}
	Stack* s = StackInit();
	BTNode* cur = root;
	while (cur || (StackEmpty(s) != 0))
	{
		while (cur)
		{
			StackPush(s, cur);
			cur = cur->_left;
		}
		BTNode* front = StackTop(s);
		StackPop(s);
		printf("%d ", front->_data);
		cur = front->_right;
	}
	StackDestroy(s);
	printf("\n");
}

void BTreePostOrderNonR(BTNode* root)
{
	if (root == NULL)
	{
		return;
	}
	Stack* s = StackInit();
	BTNode* cur = root;
	BTNode* last = NULL;//最后一个访问的节点
	while (cur || (StackEmpty(s) != 0))
	{
		while (cur)
		{
			StackPush(s, cur);
			cur = cur->_left;
		}
		BTNode* front = StackTop(s);
		if ((front->_right == NULL) || (front->_right == last))
		{
			printf("%d ", front->_data);
			StackPop(s);
			last = front;
		}
		else
		{
			cur = front->_right;
		}
	}
	printf("\n");
}

void BTreeMirror(BTNode* root)
{
	if (root == NULL)
	{
		return;
	}
	if (root->_left == root->_right)
	{
		return;
	}
	BTNode* tmp = root->_left;
	root->_left = root->_right;
	root->_right = tmp;
	BTreeMirror(root->_left);
	BTreeMirror(root->_right);
}

void BTreeMirrorNoR(BTNode* root)
{
	if (root == NULL)
	{
		return;
	}
	Stack* s = StackInit();
	BTNode* cur = root;
	StackPush(s, cur);
	while ((cur != NULL) || (StackEmpty(s) != 0))
	{
		while (cur)
		{
			BTNode* tmp = cur->_left;
			cur->_left = cur->_right;
			cur->_right = tmp;
			StackPush(s, cur);
			cur = cur->_right;
		}
		BTNode* front = StackTop(s);
		StackPop(s);
		cur = front->_left;
	}
}

BTNode* BTreeFindFather(BTNode* root, BTreeDataType x)
{
	if (root == NULL)
	{
		return NULL;
	}
	if (((root->_left != NULL) && (root->_left->_data == x)) || ((root->_right != NULL) && (root->_right->_data == x)))
	{
		return root;
	}
	BTNode* left = BTreeFindFather(root->_left, x);
	if (left != NULL)
	{
		return left;
	}
	return BTreeFindFather(root->_right, x);
}

BTNode* TreeFindLChild(BTNode* root,BTreeDataType x)
{
	BTNode* cur = BTreeFind(root, x);
	if (cur != NULL)
	{
		return cur->_left;
	}
	return cur;
}

BTNode* TreeFindRChild(BTNode* root, BTreeDataType x)
{
	BTNode* cur = BTreeFind(root, x);
	if (cur != NULL)
	{
		return cur->_right;
	}
	return cur;
}

size_t BTreeDistance(BTNode* root, BTNode* dst)//求节点深度
{
	if (root == NULL)
	{
		return 0;
	}
	if (root == dst)
	{
		return 1;
	}
	size_t left = BTreeDistance(root->_left, dst);
	size_t right = BTreeDistance(root->_right, dst);
	if (left != 0 || right != 0)
	{
		return 1 + (left < right ? right : left);
	}
	return 0;
}

BTNode* BTreeFindSameFather(BTNode* root, BTNode* n1, BTNode* n2)
{
	size_t k1 = BTreeDistance(root, n1), k2 = BTreeDistance(root, n2);
	if (k2 < k1)
	{
		BTNode* tmp = n1;
		k1 = k1 ^ k2;
		k2 = k1 ^ k2;
		k1 = k1 ^ k2;
		n1 = n2;
		n2 = tmp;
	}
	n1 = BTreeFindFather(root, n1->_data);
	k1--;
	while (k2 != k1)
	{
		n2 = BTreeFindFather(root, n2->_data);
		k2--;
	}
	while (n1 != n2)
	{
		n1 = BTreeFindFather(root, n1->_data);
		n2 = BTreeFindFather(root, n2->_data);
	}
	return n1;
}

void TestBinaryTree()
{
	int a[] = { 1, 2, 3, '#', '#', 4 , '#', '#', 5, 6, '#', '#', '#' };
	size_t index = 0;
	BTNode* tree = CreateBTree(a, &index, '#');
	printf("BTreePrevOrder:");
	BTreePrevOrder(tree);
	printf("\n");
	printf("BTreePrevOrderNonR:");
	BTreePrevOrderNonR(tree);
	printf("BTreeInOrder:");
	BTreeInOrder(tree);
	printf("\n");
	printf("BTreeInOrderNonR:");
	BTreeInOrderNonR(tree);
	printf("BTreePostOrder:");
	BTreePostOrder(tree);
	printf("\n");
	printf("BTreePostOrderNonR:");
	BTreePostOrderNonR(tree);

	printf("BTreeSize:%d\n", BTreeSize(tree));
	printf("BTreeLeafSize:%d\n", BTreeLeafSize(tree));
	printf("BTreeKLevelSize:%d\n", BTreeKLevelSize(tree, 2));
	printf("BTreeDepth:%d\n", BTreeDepth(tree));
	printf("Node 6:%#p\n", tree->_right->_left);
	printf("BTreeFind:%#p\n", BTreeFind(tree, 6));
	BTreeLevelOrder(tree);
	printf("IsCompleteBTree:%d\n", IsCompleteBTree(tree));
	printf("IsCompleteBTree:%d\n", IsCompleteBTree1(tree));

	BTreeMirror(tree);
	printf("BTreePrevOrder:");
	BTreePrevOrder(tree);
	printf("\n");
	BTreeMirrorNoR(tree);
	printf("BTreePrevOrderNor:");
	BTreePrevOrder(tree);
	printf("\n");

	printf("BTreeFindFather:%p  %p\n", BTreeFindFather(tree, 5), BTreeFind(tree, 1));
	printf("BTreeDistance:%d\n", BTreeDistance(tree, BTreeFind(tree, 4)));
	printf("BTreeDistance:%d\n", BTreeDistance(tree, BTreeFind(tree, 5)));
	printf("BTreeDistance:%d\n", BTreeDistance(tree, BTreeFind(tree, 4)));
	printf("BTreeDistance:%d\n", BTreeDistance(tree, BTreeFind(tree, 5)));
	printf("BTreeFindSameFather:%p %p\n", BTreeFindSameFather(tree, BTreeFind(tree, 4), BTreeFind(tree, 5)), tree);
}