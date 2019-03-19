#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 100

typedef struct{
	int * base;
	int front;
	int rear;
}SqQueue;

void InitQueue(SqQueue * s);
int QueueLength(SqQueue s);
void EnQueue(SqQueue * s, int elem);
int DeQueue(SqQueue * s);

int main()
{
	SqQueue s;
	InitQueue(&s);

	for(int i = 0; i<99;i++)
	{
		EnQueue(&s, i);
	}
	
	printf("Queque Length: %d\n", QueueLength(s));
	printf("Delete: %d\n", DeQueue(&s));
	printf("Queque Length: %d\n", QueueLength(s));


	return 0;
}

void InitQueue(SqQueue * s)
{
	s->base = (int *)malloc(sizeof(int)*MAXSIZE);
	s->front = s->rear = 0;
}

int QueueLength(SqQueue s)
{
	return (s.rear - s.front + MAXSIZE)%MAXSIZE;
}

void EnQueue(SqQueue * s, int elem)
{
	if((s->rear+1)%MAXSIZE == s->front)
	{
		printf("Queue is full.\n");
		exit(-1);

	}
	s->base[s->rear] = elem;
	s->rear = (s->rear +1)%MAXSIZE;
}

int DeQueue(SqQueue * s)
{
	int data;

	if(s->rear == s->base)	 exit(-1);
	data = s->base[s->front];
	s->front = (s->front +1)%MAXSIZE;
	
	return data;
}
