#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXSIZE 100
typedef unsigned char SString[MAXSIZE+1];

void Concat(SString T, SString s1, SString s2);
void SubSString(SString T, SString s, int pos, int len);
int Index(SString S, SString T, int pos);
int Index_KMP(SString S, SString T, int pos, int next[]);


int main()
{
	SString t = "";
	SString s1 = "ranyixu yangyan i love you"; // out of range, how to handle??
	SString s2 =  "lalala~";

	Concat(t, s1, s2);

	printf("string1: %s, length:%d\n", s1, strlen(s1));
	printf("string2: %s, length:%d\n", s2, strlen(s2));
	printf("new string: %s, length:%d, sizeof:%d\n", t, strlen(t), sizeof(t));

	SString t1;
	SubSString(t1, s1, 15, 3);
	printf("Substring:%s\n",t1);
	
	char test[] = "abc";
	printf("strlen:%d\tsizeof:%d\n",strlen(test), sizeof(test));

	SString s3 = "i and love ab abc the abaabcalove";
	SString s4 = "abaabc";
	int pos;
	pos = Index(s3, s4, 3);
	printf("S1:%s, S2:%s, pos:%d, Index:%d\n", s3, s4, 3, pos);

	int next[6];
	Get_Next(s4, next);
	//for(int i = 0; i < 6; i++) printf("next: %d\t", next[i]);
	pos = Index_KMP(s3, s4, 3, next);
	printf("S1:%s, S2:%s, pos:%d, KMP_Index:%d\n", s3, s4, 3, pos);


	return 0;
}

void Concat(SString T, SString s1, SString s2)
{
	int len1 = strlen(s1);	
	int len2 = strlen(s2);

	if(len1+len2 <= MAXSIZE)
	{
		int j = 0;
		for(int i= 0;i <= len1+len2;i++)
		{
			if(i<len1)
			{
				T[i] = s1[i];
			}else
			{
				T[i] = s2[j];
				j++;
			}
		}
	}else if(len1+len2 > MAXSIZE && len1 == MAXSIZE)
	{
		for(int i = 0; i < len1; i++) T[i] = s1[i];
	}else{
		int j = 0;
		for(int i= 0;i < MAXSIZE;i++)
		{
			if(i<len1)
			{
				T[i] = s1[i];
			}else
			{
				T[i] = s2[j];
				j++;
			}
			T[MAXSIZE] = '\0';
		}
	}
}

void SubSString(SString T, SString s, int pos, int len)
{
	int len1 = strlen(s);

	if(pos < 1 || pos > len1 || len < 0 || len > len1 - pos + 1) 
	{
		printf("out of string range.\n");
		exit(-1);
	}

	for(int i = 0; i < len; i++)
	{
		T[i] = s[i+pos-1];
	}
	T[len] = '\0';

}

int Index(SString S, SString T, int pos)
{
	int len1 = strlen(S);
	int len2 = strlen(T);

	if(len2 == 0)
	{
		printf("Substring is null.\n");
		return 0;
	}
	int i = pos -1;
	int j = 0;
	while( i < len1 && j < len2)
	{
		if(S[i] == T[j])
		{
			i++;
			j++;
		}else{
			i = i -j + 1;
			j = 0;
		}
	}

	if(j == len2) return i-len2 + 1;
	else return 0;
}

void Get_Next(SString T, int next[])
{
	int i = 0;
	next[0] = -1;
	int j = -1;
	int len = strlen(T);

	while(i<len - 1)
	{
		if(j == -1 || T[i] == T[j])
		{
			i++;
			j++;
			next[i] = j;
		}else j = next[j];
	}
}

int Index_KMP(SString S, SString T, int pos, int next[])
{

	int len1 = strlen(S);
	int len2 = strlen(T);

	if(len2 == 0)
	{
		printf("Substring is null.\n");
		return 0;
	}
	int i = pos -1;
	int j = 0;

	while(i < len1 && j < len2)
	{
		if(j == -1 || S[i] == T[j])
		{
			++i;
			++j;
		}else{
			j=next[j];
		}
	}

	if(j >= len2) return i-len2+1;

	return 0;
}
