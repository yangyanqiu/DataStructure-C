#include<stdio.h>

#define MAXSIZE 15
typedef unsigned char String[MAXSIZE+1];

void Concat(String T, String s1, String s2);
void SubString(String T, String s, int pos, int len);


int main()
{
	String t = "";
	String s1 = "ranyixu yangyan i love you"; // out of range, how to handle??
	String s2 =  "lalala~";

	Concat(t, s1, s2);

	printf("string1: %s, length:%d\n", s1, strlen(s1));
	printf("string2: %s, length:%d\n", s2, strlen(s2));
	printf("new string: %s, length:%d, sizeof:%d\n", t, strlen(t), sizeof(t));

	String t1;
	SubString(t1, s1, 15, 3);
	printf("Substring:%s\n",t1);
	
	char test[] = "abc";
	printf("strlen:%d\tsizeof:%d\n",strlen(test), sizeof(test));

	return 0;
}

void Concat(String T, String s1, String s2)
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

void SubString(String T, String s, int pos, int len)
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
