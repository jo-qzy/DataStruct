//配合Queue.h使用
//面试题
//两个队列实现一个栈
typedef struct QueueStack
{
	Queue* _q1;
	Queue* _q2;
}QueueStack;

QueueStack* Stack_QueueInit()
{
	QueueStack* new_qs = (QueueStack*)malloc(sizeof(QueueStack));
	new_qs->_q1 = QueueInit();
	new_qs->_q2 = QueueInit();
	return new_qs;
}

void StackPush_Queue(QueueStack* qs, QueueDataType data)
{
	if (QueueEmpty(qs->_q1) == 0)
	{
		QueuePush(qs->_q2, data);
	}
	else
	{
		QueuePush(qs->_q1, data);
	}
}

void StackPop_Queue(QueueStack* qs)
{
	assert(qs);
	Queue* op = NULL;
	Queue* empty = NULL;
	if (QueueEmpty(qs->_q1) == 0)
	{
		op = qs->_q2;
		empty = qs->_q1;
	}
	else
	{
		op = qs->_q1;
		empty = qs->_q2;
	}
	while (QueueSize(op) != 1)
	{
		QueueDataType tmp = QueueFront(op);
		QueuePop(op);
		QueuePush(empty, tmp);
	}
	QueuePop(op);
}

QueueDataType StackTop_Queue(QueueStack* qs)
{
	if ((QueueEmpty(qs->_q1) == 0) && (QueueEmpty(qs->_q2) == 0))
	{
		assert(0);
	}
	if (QueueEmpty(qs->_q1) == 0)
	{
		return QueueBack(qs->_q2);
	}
	else
	{
		return QueueBack(qs->_q1);
	}
}

void Test2QToS()
{
	QueueStack* qs = Stack_QueueInit();
	StackPush_Queue(qs, 1);
	StackPush_Queue(qs, 2);
	StackPush_Queue(qs, 3);
	StackPush_Queue(qs, 4);
	StackPush_Queue(qs, 5);
	printf("%d ", StackTop_Queue(qs));
	StackPop_Queue(qs);
	printf("%d ", StackTop_Queue(qs));
	StackPop_Queue(qs);
	printf("%d ", StackTop_Queue(qs));
}