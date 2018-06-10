BinaryTreeNode* Convert(BinaryTreeNode* pRootOfTree)
{
	BinaryTreeNode* pLastNode = NULL;
	ConvertNode(pRootOfTree, &pLastNode);
	while (pLastNode != NULL && pLastNode->_left != NULL)
	{
		pLastNode = pLastNode->_left;
	}
	return pLastNode;
}

//左指向前一个节点，右指向后一个节点
void ConvertNode(BinaryTreeNode* pNode, BinaryTreeNode** pLastNode)
{
	if (pNode == NULL)
	{
		return;
	}
	
	BinaryTreeNode* pCur = pNode;
	
	if (pCur->_left != NULL)
	{
		ConvertNode(pCur->_left, pLastNode);
	}
	//中序遍历，所以所有操作都在中序遍历的位置进行操作
	
	pCur->_left = pLastNode;//树中的节点要链上链表，当前节点的左指针指向链表最后一个节点
	
	//链表里的前一个节点的右节点指向当前节点，后一个就是pCur
	if (pLastNode->_right != NULL)
	{
		(*pLastNode)->_right = pCur;
	}
	
	*pLastNode = pCur;//链上了，链表中最后一个节点变成了pCur
	//操作结束
	
	if (pCur->_right != NULL)
	{
		ConvertNode(pCur->_right, pLastNode);
	}
}