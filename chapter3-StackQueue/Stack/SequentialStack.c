#include<stdio.h>
#include<stdlib.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef struct{
	int * base;
	int * top;
	int stacksize;
}SqStack;

//init an empty stack
void InitStack(SqStack *S);
void Push(SqStack *S, int elem);
void GetTop(SqStack *S, int *elem);
void Pop(SqStack *S, int *elem);

int main()
{
	SqStack s1;
	int topElem;
	int popElem;	

	//1. init
	InitStack(&s1);
	//2. Push
	for(int i = 0;i<20;i++)
	{
		Push(&s1, i);
	}

	//4. Pop
	Pop(&s1, &popElem);

	//3.Get the Top element
	GetTop(&s1, &topElem);
	printf("The top elem is %d\n", topElem);

	return 0;
}

void InitStack(SqStack *S)
{
	S->base = (int *)malloc(STACK_INIT_SIZE*sizeof(int));
	if(!S->base) exit(-1);
	S->top = S->base;
	S->stacksize = STACK_INIT_SIZE;

}

void Push(SqStack *S, int elem)
{
	if ((S->top - S->base) >= S->stacksize)
	{
		printf("Stack is full\n");
		S->base = (int *)realloc(S->base, (S->stacksize+STACKINCREMENT)*sizeof(int));
		if(!S->base) exit(-1);

		S->top = S->base + S->stacksize;
		S->stacksize += STACKINCREMENT;
	}
	*S->top++ = elem;
}

void GetTop(SqStack *S, int *elem)
{
	if(S->base == S->top) exit(-1);

	*elem = *(S->top-1);
}

void Pop(SqStack *S, int * elem)
{
	if(S->base == S->top) exit(-1);

	*elem = *--S->top;
}
