#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct QNode{
	int data;;
	struct QNode * next;
}QNode, * QueuePtr;

typedef struct{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

void InitQueue(LinkQueue *Q);
void EnQueue(LinkQueue *Q, int elem);
int DeQueue(LinkQueue *Q);

//*************************Application****************************
//Envaluate the average time for people staying in Bank during a day
int BankSimulation();

int main()
{

	BankSimulation();
	
	return 0;
}

void InitQueue(LinkQueue *Q)
{
	Q->rear = Q->front = (QueuePtr)malloc(sizeof(QNode));
	if(!Q->front) exit(-1);

	Q->rear->next = Q->front->next = NULL;


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

void TotalTime(LinkQueue * q, int * totalTime)
{
	int a[] = {0, 0, 0, 0};//use to count the number of departed people
	int window = 4;//4 bank counters handle bussiness at the same time 

	while(q->rear != q->front)
	{
		int n = q->front->next->data / 5; 
		if(n < 4)//if number of person < 4, they don't need to wait.
		{
			*totalTime += 30;
			a[n] += 1;
			DeQueue(q);
			//printf("a[%d] %d\n", n, a[n]);
		}else{
			int spareTime;
			int i = n%window;
			
			spareTime = a[i]*30 + i*5 - q->front->next->data + 30; 
			*totalTime += spareTime;
			//printf("a[%d] %d, number %d, spareTime %d\n", i, a[i], n, spareTime);
			a[i] += 1;
			DeQueue(q);
		}
		printf("person %d, arrival time %d, totaltime %d\n", n, n*5, *totalTime);

	}
}
int BankSimulation()
{
	//int personNum = 0;
	int totalTime = 0;
	LinkQueue q1;

	InitQueue(&q1);
	for(int i = 0;i < 10; i++)
	{
		EnQueue(&q1, i*5);
		//personNum += 1;
	}

	TotalTime(&q1, &totalTime);
	printf("total time: %d\n", totalTime);

}
