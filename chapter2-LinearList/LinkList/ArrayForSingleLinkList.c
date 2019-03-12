#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef struct{
	int data;
	int cur;
}component, SLinkList[MAXSIZE];

void InitSpace_SL(SLinkList space);
void MallocSpace_SL(SLinkList space);
void FreeSpace_SL(SLinkList space, int k);
void Printf_SL(SLinkList space);
int LocateSpace_SL(SLinkList space, int number);

int main()
{
	SLinkList s1;
	InitSpace_SL(s1);
	Printf_SL(s1);

	return 0;
}

void InitSpace_SL(SLinkList space)
{
	space[0].cur = 1;
	for (int i = 1; i < MAXSIZE - 1; i++)
	{
		space[i].data = i;
		space[i].cur = i+1;
	}
	space[MAXSIZE -1].cur = 0;

}

void MallocSpace_SL(SLinkList space)
{
	int i = space[0].cur; 

	return i;
}

void FreeSpace_SL(SLinkList space, int k)
{
	space[k].cur = space[0].cur;
	space[0].cur = k;
}

void Printf_SL(SLinkList space)
{
	int i = space[0].cur;

	while(space[i].cur)
	{
		printf("data%d: %d\n", i, space[i].data);
		i = space[i].cur;
	}
}

int LocateSpace_SL(SLinkList space, int number)
{
	int i = space[0].cur;

	while(i && space[i].data != number) i = space[i].cur;

	return i;
}
