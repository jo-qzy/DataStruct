#pragma once

#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>

typedef int BSTreeDataType;

typedef struct BinarySearchTree
{
	struct BinarySearchTree* _left;
	struct BinarySearchTree* _right;
	BSTreeDataType _data;
}BSTree;

BSTree* CreateBSTreeNode(BSTreeDataType data);//为新节点开辟空间
bool BSTreeInsert(BSTree** root, BSTreeDataType data);//递归插入
bool BSTreeInsertNoR(BSTree** root, BSTreeDataType data);//非递归插入
bool BSTreeRemove(BSTree** root, BSTreeDataType data);//递归法删除节点
bool BSTreeRemoveNoR(BSTree** root, BSTreeDataType data);//非递归删除
BSTree* BSTreeFind(BSTree* root, BSTreeDataType data);//递归查找节点
BSTree* BSTreeFindNoR(BSTree* root, BSTreeDataType data);//非递归查找
void BSTreeInOrder(BSTree* root);//中序遍历
void BSTreeDestroy(BSTree* root);//销毁树
void BSTreeTest();//测试用例

BSTree* CreateBSTreeNode(BSTreeDataType data)
{
	BSTree* new_node = (BSTree*)malloc(sizeof(BSTree));
	new_node->_data = data;
	new_node->_left = NULL;
	new_node->_right = NULL;
	return new_node;
}

bool BSTreeInsert(BSTree** root, BSTreeDataType data)
{
	if (*root == NULL)
	{
		*root = CreateBSTreeNode(data);
		return true;
	}
	if ((*root)->_data > data)
	{
		if ((*root)->_left != NULL)
		{
			return BSTreeInsert(&((*root)->_left), data);
		}
		else
		{
			(*root)->_left = CreateBSTreeNode(data);
			return true;
		}
	}
	else if ((*root)->_data < data)
	{
		if ((*root)->_right != NULL)
		{
			return BSTreeInsert(&((*root)->_right), data);
		}
		else
		{
			(*root)->_right = CreateBSTreeNode(data);
			return true;
		}
	}
	return false;
}

bool BSTreeInsertNoR(BSTree** root, BSTreeDataType data)
{
	BSTree* cur = *root;
	BSTree* prev = *root;
	if (*root == NULL)
	{
		*root = CreateBSTreeNode(data);
		return true;
	}
	while (cur)//寻找合适的插入位置
	{
		prev = cur;
		if (cur->_data > data)
		{
			cur = cur->_left;
		}
		else if (cur->_data < data)
		{
			cur = cur->_right;
		}
		else
		{
			return false;
		}
	}
	if (prev->_data > data)
	{
		prev->_left = CreateBSTreeNode(data);
	}
	else
	{
		prev->_right = CreateBSTreeNode(data);
	}
	return true;
}

bool BSTreeRemove(BSTree** root, BSTreeDataType data)
{
	if (*root == NULL)
	{
		return false;
	}
	else if ((*root)->_data < data)
	{
		return BSTreeRemove(&((*root)->_right), data);
	}
	else if ((*root)->_data > data)
	{
		return BSTreeRemove(&((*root)->_left), data);
	}
	if ((*root)->_left == NULL)//左为空
	{
		BSTree* tmp = *root;
		(*root) = (*root)->_right;
		free(tmp);
		return true;
	}
	else if ((*root)->_right == NULL)//右为空
	{
		BSTree* tmp = *root;
		(*root) = (*root)->_left;
		free(tmp);
		return true;
	}
	else//左右都不为空
	{
		BSTree* instead = (*root)->_left;//寻找左树中最大的节点，将其数据给要删的节点
		while (instead->_right != NULL)//将问题转化为删除左树中最大的节点
		{
			instead = instead->_right;
		}
		(*root)->_data = instead->_data;
		return BSTreeRemove(&((*root)->_left), instead->_data);
	}
}

bool BSTreeRemoveNoR(BSTree** root, BSTreeDataType data)
{
	BSTree* cur = *root;
	BSTree* parent = cur;
	while (cur)
	{
		//寻找指定节点
		if (cur->_data != data)
		{
			parent = cur;
			if (cur->_data < data)
			{
				cur = cur->_right;
			}
			else
			{
				cur = cur->_left;
			}
		}
		else
		{
			if (cur->_left == NULL)
			{
				if (cur == *root)
				{
					(*root) = cur->_right;
					free(cur);
				}
				else if (parent->_left == cur)
				{
					parent->_left = cur->_right;
				}
				else
				{
					parent->_right = cur->_right;
				}
				free(cur);
				return true;
			}
			else if (cur->_right == NULL)
			{
				if (cur == *root)
				{
					(*root) = cur->_left;
					free(cur);
				}
				else if (parent->_left == cur)
				{
					parent->_left = cur->_left;
				}
				else
				{
					parent->_right = cur->_left;
				}
				free(cur);
				return true;
			}
			else
			{
				BSTree* instead = cur->_right;
				if (instead->_left == NULL)
				{
					cur->_data = instead->_data;
					cur->_right = instead->_right;
				}
				else
				{
					while (instead->_left != NULL)
					{
						parent = instead;
						instead = instead->_left;
					}
					cur->_data = instead->_data;
					parent->_left = instead->_right;
				}
				free(instead);
				return true;
			}
		}
	}
	return false;
}

BSTree* BSTreeFind(BSTree* root, BSTreeDataType data)
{
	//递归查找
	if (root == NULL)
	{
		return NULL;
	}
	if (root->_data == data)
	{
		return root;
	}
	if (root->_data < data)
	{
		return BSTreeFind(root->_right, data);
	}
	else
	{
		return BSTreeFind(root->_left, data);
	}
}

BSTree* BSTreeFindNoR(BSTree* root, BSTreeDataType data)
{
	//非递归查找，前序遍历的非递归类似
	BSTree* cur = root;
	while (cur)
	{
		if (cur->_data < data)
		{
			cur = cur->_right;
		}
		else if (cur->_data > data)
		{
			cur = cur->_left;
		}
		else
		{
			return cur;
		}
	}
	return NULL;
}

void BSTreeInOrder(BSTree* root)
{
	if(root == NULL)
	{
		return;
	}
	BSTreeInOrder(root->_left);
	printf("%d ", root->_data);
	BSTreeInOrder(root->_right);
}

void BSTreeDestroy(BSTree* root)
{
	if (root == NULL)
	{
		return;
	}
	BSTreeDestroy(root->_left);
	BSTreeDestroy(root->_right);
	free(root);
}

void BSTreeTest()
{
	BSTree* tree = NULL;

	BSTree* tree_noR = NULL;

	BSTreeInsert(&tree, 5);
	BSTreeInsert(&tree, 4);
	BSTreeInsert(&tree, 7);
	BSTreeInsert(&tree, 9);
	BSTreeInsert(&tree, 6);
	BSTreeInsert(&tree, 8);
	BSTreeInsert(&tree, 1);
	BSTreeInsert(&tree, 2);
	printf("Find 2:%d\n", BSTreeFind(tree, 2)->_data);
	printf("%#p\n", BSTreeFind(tree, 100));
	BSTreeInOrder(tree);
	printf("\n");
	BSTreeRemove(&tree, 2);
	BSTreeRemove(&tree, 4);
	BSTreeRemove(&tree, 7);
	BSTreeRemove(&tree, 8);
	BSTreeRemove(&tree, 8);
	BSTreeRemove(&tree, 5);
	BSTreeInOrder(tree);
	printf("\n");

	printf("NoRTest:\n");
	BSTreeInsertNoR(&tree_noR, 5);
	BSTreeInsertNoR(&tree_noR, 4);
	BSTreeInsertNoR(&tree_noR, 7);
	BSTreeInsertNoR(&tree_noR, 9);
	BSTreeInsertNoR(&tree_noR, 6);
	BSTreeInsertNoR(&tree_noR, 8);
	BSTreeInsertNoR(&tree_noR, 1);
	BSTreeInsertNoR(&tree_noR, 2);
	printf("Find 2:%d\n", BSTreeFindNoR(tree_noR, 2)->_data);
	printf("%#p\n", BSTreeFindNoR(tree_noR, 100));
	BSTreeInOrder(tree_noR);
	printf("\n");
	BSTreeRemoveNoR(&tree_noR, 2);
	BSTreeRemoveNoR(&tree_noR, 4);
	BSTreeRemoveNoR(&tree_noR, 7);
	BSTreeRemoveNoR(&tree_noR, 8);
	BSTreeRemoveNoR(&tree_noR, 8);
	BSTreeRemoveNoR(&tree_noR, 5);
	BSTreeInOrder(tree_noR);
	printf("\n");

	BSTreeDestroy(tree);
	BSTreeDestroy(tree_noR);
}