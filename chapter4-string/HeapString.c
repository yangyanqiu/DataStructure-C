#include<stdio.h>
#include<stdlib.h>

typedef struct{
	char * ch;
	int length;
}HString;

void InitStr(HString *S);
void StrAssign(HString *S, char * chars);
void StrInsert(HString * S, int p, HString T);
int StrLength(HString S);
int StrCompare(HString S, HString T);

int main()
{
	HString s1, s2; 
	
	InitStr(&s1);
	InitStr(&s2);
	
	StrAssign(&s1, "yangyanqiu");
	StrAssign(&s2, "abc");
	printf("string s1:%s\tlength:%d\n", s1.ch, s1.length);

	StrInsert(&s1, 1, s2);
	printf("new string s1:%s\tlength:%d\n", s1.ch, s1.length);
	
	StrAssign(&s1, "b");
	StrAssign(&s2, "aangyanqiu");
	int res = StrCompare(s1, s2);
	printf("Compare s1 and s2: %d\n", res);

	return 0;
}

void InitStr(HString *S)
{
	S->ch = NULL;
	S->length = 0;
}


void StrAssign(HString *S, char * chars)
{
	int len;

	if(S->ch) free(S->ch);

	len = strlen(chars);
		
	if(!len)
	{
		S->ch = NULL;
		S->length = 0;
	}else{
		S->ch = (char *)malloc(sizeof(char)*len);
		if(!S->ch) exit(-1);

		for(int i = 0; i < len;i++)
		{
			S->ch[i] = chars[i];
		}
		S->length = len;
	}

}

void StrInsert(HString * S, int p, HString T)
{
	if(p < 1 || p > S->length+1)
	{
		printf("Out of range.\n");
		exit(-1);
	}
	if(!T.length)
	{
		printf("insert a null string.\n");
		exit(-1);
	}

	S->ch = (char *)realloc(S->ch, (T.length+S->length)*sizeof(char));
	if(!S->ch) exit(-1);

	int j = S->length;
	for(int i = S->length+T.length-1;i > p-1; i--, j--)
	{
		S->ch[i] = S->ch[j-1];
	}

	for(int i = 0; i < T.length; i++)
	{
		S->ch[p-1+i] = T.ch[i];
		S->length++;
	}
}

int StrLength(HString S)
{
	return S.length;
}

int StrCompare(HString S, HString T)
{
	for(int i = 0; i < S.length && i < T.length; i++)
	{
		if(S.ch[i] != T.ch[i]) return S.ch[i]- T.ch[i];
	}

	return S.length - T.length;
}
