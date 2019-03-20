#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct QNode{
	int data;
	struct QNode * next;
}QNode, * QueuePtr;

typedef struct{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

void InitQueue(LinkQueue *Q);
int QueueEmpty(LinkQueue Q);
int GetHead(LinkQueue Q);
int QueueLength(LinkQueue Q);
void EnQueue(LinkQueue *Q, int elem);
int DeQueue(LinkQueue *Q);
//traverse link queue from the front to the rear
void QueueTraverse(LinkQueue Q);
void DestroyQueue(LinkQueue *Q);

int main()
{
	LinkQueue q1;

	InitQueue(&q1);
	for(int i = 0;i < 6; i++)
	{
		EnQueue(&q1, i);
	}

	QueueTraverse(q1);

	printf("Head data: %d\n", GetHead(q1));
	printf("Delete data: %d\n", DeQueue(&q1));
	QueueTraverse(q1);
	printf("Queue Length: %d\n", QueueLength(q1));
	DestroyQueue(&q1);
	//QueueTraverse(q1);
	
	return 0;
}

void InitQueue(LinkQueue *Q)
{
	Q->rear = Q->front = (QueuePtr)malloc(sizeof(QNode));
	if(!Q->front) exit(-1);

	Q->rear->next = Q->front->next = NULL;


}
int QueueEmpty(LinkQueue Q)
{
	if(Q.rear == Q.front) return 1;
	else
	{
		return 0;
	}
}
int GetHead(LinkQueue Q)
{
	if(Q.rear == Q.front) exit(-1);

	return Q.front->next->data;
}
int QueueLength(LinkQueue Q)
{
	int length = 0;
	QueuePtr p = Q.front->next;
	
	while(p != NULL)
	{
		length += 1;
		p = p->next;	
	}

	return length;
}
void EnQueue(LinkQueue *Q, int elem)
{
	QueuePtr temp = (QueuePtr)malloc(sizeof(QNode));
	if(!temp) exit(-1);

	temp->data = elem;
	temp->next = NULL;
	Q->rear->next = temp;
	Q->rear = temp;
}

int DeQueue(LinkQueue *Q)
{
	int data;
	if(Q->rear == Q->front) exit(-1);

	QueuePtr p = Q->front->next;

	if(p->next == NULL) Q->rear = Q->front;
	data = p->data;

	Q->front->next = p->next;
	free(p);

	return data;
}

void QueueTraverse(LinkQueue Q)
{
	if(Q.front == Q.rear) exit(-1);
	QueuePtr p = Q.front->next;//the first node
	while(p != NULL)
	{
		printf("%d\n", p->data);
		p = p->next;
	}
}

void DestroyQueue(LinkQueue *Q)
{
	while(Q->front)
	{
		Q->rear = Q->front->next;
		free(Q->front);
		Q->front = Q->rear;
	}
}

