#include<stdio.h>
#include<stdlib.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef struct{
	int * base;
	int * top;
	int stacksize;
}SqStack;

//*********************The implement of stack*********************
//1. init an empty stack
void InitStack(SqStack *S);
//2. Insert a element
void Push(SqStack *S, int elem);
//3. get the top element
void GetTop(SqStack *S, int *elem);
//int GetTop(SqStack *S);
//4. delete the top element
void Pop(SqStack *S, int *elem);
//5. judge whether the stack is empty
// return 0 when is not empty, return 1 when is empty
int StackEmpty(SqStack *S);
//6. Clear the stack
void ClearStack(SqStack *S);
//7. DestroyStack
void DestroyStack(SqStack *S);

//*******************************the application of stack****************************
//1. convert decimal number to octal number
void Convertion(int number);
//2. func: Eliminate bracket 
//return true when the bracket ()[] is matched
//return false when the bracket is unmatched
void EliminateBracket(void);
//3. Line editor
void LineEditor();
//4. Maze: find one road
//....

//5. calculate the value of the expression you entered
void EvaluateExpression();

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
	//EliminateBracket();
	
	//6. line editor end of EOF
	//LineEditor();

	//7. Evaluate the value of Expression
	EvaluateExpression();

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
		//printf("Stack is full\n");
		S->base = (int *)realloc(S->base, (S->stacksize+STACKINCREMENT)*sizeof(int));
		if(!S->base) exit(-1);

		S->top = S->base + S->stacksize;
		S->stacksize += STACKINCREMENT;
	}
	*S->top++ = elem;
}

void GetTop(SqStack *S, int *elem)
{
	if(S->base == S->top) return -1;

	*elem = *(S->top-1);
}

/*
int GetTop(SqStack *S)
{
	if(S->base == S->top) -1;

	return *(S->top);
}*/

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

void ClearStack(SqStack *S)
{
	S->top = S->base;
	//if (S->top == S->base)   printf("Clear stack.\n");
}

void DestroyStack(SqStack *S)
{
	free(S->base);
	S->base = S->top = NULL;
	//printf("Destroy stack.\n");
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

void LineEditor()
{
	SqStack line;
	int top;
	char ch;

	InitStack(&line);

	ch = getchar();
	while(ch != EOF)
	{
		while(ch != EOF && ch != '\n')
		{
			switch(ch)
			{
				case '#': Pop(&line, &top);
				case '@': ClearStack(&line);
				default: Push(&line, ch);
			}
			ch = getchar();

		}

		//complete this line...
		ClearStack(&line);
		/*
		int isEmp = StackEmpty(&line);
		while(!isEmp)
	       	{
			Pop(&line, &top);
			printf("%d", top);
		}
		*/
		
		if(ch != EOF) ch = getchar();
	}
	DestroyStack(&line);
}

int IsOperator(char o)
{
	int i = o;

	if ((i-48) >= 0 && (i-48) <= 9) return 0;
	else return 1;
	
}

char ComparePriority(char prev, char next)
{
	if(prev == '+' || prev == '-')
	{
		if(next == '+' || next == '-' || next == ')' || next == '#') return '>';
		else if(next == '*' || next == '/' || next == '(') return '<';

	}else if(prev == '*' || prev == '/')
	{
		if(next == '+' || next == '-' || next == '*' || next == '/' || next == ')' || next == '#') return '>';
		else if(next == '(') return '<';
	}else if(prev == '(')
	{
		if(next == '+' || next == '-' || next == '*' || next == '/' || next == '(') return '<';
		else if(next == ')') return '=';
		else if(next == '#'){ printf("(# is illegal.\n"); exit(-1);}
	}else if(prev == ')')
	{
		if(next == '+' || next == '-' || next == '*' || next == '/' || next == ')' || next == '#') return '>';
		else if(next == '#'){ printf("((# is illegal.\n"); exit(-1);}
	}else if(prev == '#')
	{
		if(next == '+' || next == '-' || next == '*' || next == '/' || next == '(') return '<';
		else if(prev == '#') return '=';
		else if(next == '#'){ printf("(# is illegal.\n"); exit(-1);}
	}
}

int Operate(char n1, char op, char n2)
{
	int result;
	int num1 = n1, num2 = n2;
	//int num1 = (int)n1 - 48, num2 = (int)n2 - 48;

	switch(op)
	{
		case '*':
			result = num1*num2;
			break;
		case '/':
			if(num2 == 0)
			{
				printf("**/0 is illegal.\n");
				exit(-1);
			}

			result = num1/num2;
			break;
		case '-':
			result = num1 - num2;
			break;
		case '+':
			result = num1+num2;
			break;
	}

	return result;
}


void EvaluateExpression()
{
	SqStack operator,operand;
	char ch, tmp;
	int top;
	int num1, num2, result;

	InitStack(&operator);
	InitStack(&operand);
	Push(&operator, '#');

	ch = getchar();
	GetTop(&operator, &top);

	while(ch != '#' || top != '#')
	{
		//printf("char %c\t", ch);
		if (ch == ' ') ch = getchar();

		if(!IsOperator(ch))
		{
			Push(&operand, (int)ch - 48);
			ch = getchar();
			//printf("----: %c\n", ch);
			
		}else
		{
			switch(ComparePriority((char)top, ch))  //compare the prioty of operator
			{
				case '<':
					Push(&operator, ch);
					ch = getchar();
					break;
				case '=':
					Pop(&operator, &tmp);
					ch = getchar();
					break;
				case '>':
					Pop(&operand, &num2);
					Pop(&operand, &num1);
					Pop(&operator, &top);
					result = Operate(num1, top, num2);
					Push(&operand, result);
					break;
			}
		}
		GetTop(&operator, &top);
	}

	//int result;
	Pop(&operand, &result);
	printf("The result is %d\n", result);
}
