#pragma once
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>

typedef char* BSTreeKey;
typedef char* BSTreeValue;

typedef struct BinarySearchTree
{
	struct BinarySearchTree* _left;
	struct BinarySearchTree* _right;
	BSTreeKey _key;
	BSTreeValue _value;
}BSTree;

BSTree* CreateBSTreeNode(BSTreeKey key, BSTreeValue value);//为新节点开辟空间
bool BSTreeInsert(BSTree** root, BSTreeKey key, BSTreeValue value);
BSTree* BSTreeFind(BSTree* root, BSTreeKey key);//递归查找节点
void BSTreeInOrder(BSTree* root);//中序遍历
void BSTreeDestroy(BSTree* root);//销毁树
void TestDictionary();

BSTree* CreateBSTreeNode(BSTreeKey key, BSTreeValue value)
{
	BSTree* new_node = (BSTree*)malloc(sizeof(BSTree));
	new_node->_key = key;
	new_node->_value = value;
	new_node->_left = NULL;
	new_node->_right = NULL;
	return new_node;
}

bool BSTreeInsert(BSTree** root, BSTreeKey key, BSTreeValue value)
{
	BSTree* cur = *root;
	BSTree* prev = *root;
	if (*root == NULL)
	{
		*root = CreateBSTreeNode(key, value);
		return true;
	}
	while (cur)//寻找合适的插入位置
	{
		prev = cur;
		if (strcmp(cur->_key, key) > 0)
		{
			cur = cur->_left;
		}
		else if (strcmp(cur->_key, key) < 0)
		{
			cur = cur->_right;
		}
		else
		{
			return false;
		}
	}
	if (strcmp(prev->_key, key) > 0)
	{
		prev->_left = CreateBSTreeNode(key, value);
	}
	else
	{
		prev->_right = CreateBSTreeNode(key, value);
	}
	return true;
}

BSTree* BSTreeFind(BSTree* root, BSTreeKey key)
{
	if (root == NULL)
	{
		return NULL;
	}
	if (strcmp(root->_key, key) == 0)
	{
		return root;
	}
	if (strcmp(root->_key, key) < 0)
	{
		return BSTreeFind(root->_right, key);
	}
	else
	{
		return BSTreeFind(root->_left, key);
	}
}

void BSTreeInOrder(BSTree* root)
{
	if(root == NULL)
	{
		return;
	}
	BSTreeInOrder(root->_left);
	printf("%s ", root->_key);
	printf("%s \n", root->_value);
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

void TestDictionary()
{
	BSTree* tree = NULL;
	
	BSTree* tree_noR = NULL;
	
	char str[20] = { 0 };

	BSTreeInsert(&tree, "insert", "插入");
	BSTreeInsert(&tree, "remove", "删除");
	BSTreeInsert(&tree, "hello", "你好");
	BSTreeInsert(&tree, "zoo", "动物园");
	BSTreeInsert(&tree, "interesting", "有趣");
	BSTreeInOrder(tree);
	while (scanf("%s", str) != EOF)
	{
		BSTree* search = BSTreeFind(tree, str);
		if (search)
		{
			printf("%s\n", search->_value);
		}
		else
		{
			printf("未找到单词，请输入正确单词\n");
		}
	}
	BSTreeDestroy(tree);
}