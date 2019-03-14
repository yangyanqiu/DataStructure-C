#include<stdio.h>
#include<stdlib.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef struct{
	int * base;
	int * top;
	int stacksize;
}SqStack;

//1. The implement of stack
//init an empty stack
void InitStack(SqStack *S);
//Insert a element
void Push(SqStack *S, int elem);
//get the top element
void GetTop(SqStack *S, int *elem);
//delete the top element
void Pop(SqStack *S, int *elem);
//judge whether the stack is empty
// return 0 when is not empty, return 1 when is empty
int StackEmpty(SqStack *S);

//2. the application of stack
//convert decimal number to octal number
void Convertion(int number);
//func: Eliminate bracket 
//return true when the bracket ()[] is matched
//return false when the bracket is unmatched
void EliminateBracket(void);

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

	//4. Convert
	Convertion(200);

	//5. bracket match
	EliminateBracket();

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

int StackEmpty(SqStack *S)
{
	if(S->top == S->base) return 1;

	return 0;
}

void Convertion(int number)
{
	SqStack octal;
	int decm = number;

	InitStack(&octal);

	while(decm)
	{
		Push(&octal, decm%8);
		decm = decm/8;
	}
	
	printf("Convert number %d to octal number:", number);
	while(!StackEmpty(&octal))
	{
		Pop(&octal, &decm);
		printf("%d", decm);
	}
	printf("\n");
	
}

void EliminateBracket(void)
{
	char bracket;
	char top;
	SqStack brack;

	InitStack(&brack);

	printf("Please enter 8 brackets with (, ), [, ]:");
	for(int i = 0; i< 8; i++)
	{
		bracket = getchar();
		if(bracket == '[' || bracket == '(')
		{
			//printf("push %c\n", bracket);
			Push(&brack, bracket);

		}else if(bracket == ']' || bracket == ')')
		{
			if(!StackEmpty(&brack))
			{
				i;
				int top1;
				Pop(&brack, &top1);
				top = (char)top1;
				if((top == '(' && bracket == ')' ) || (top == '[' && bracket == ']')){
					//printf("push %c\n", bracket);
					continue;
				}else
				{
					printf("The bracket is unmatched!\n");
					exit(-1);
				}
			}else
			{
				printf("The bracket is unmatched!\n");
				exit(-1);

			}
			

		}else
		{
			printf("You entered is not '[', ']', '(', or ')'!\n");
			exit(-1);
		}
	}
	
	if(StackEmpty(&brack))
		printf("The 8 brackets are matched!\n");
}

