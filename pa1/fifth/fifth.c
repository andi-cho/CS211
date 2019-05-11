#include<stdio.h>
#include<stdlib.h>
//void findVowels(char*);
int main(int argc, char** argv) 
{
	if (argc<=1)
	{
		printf("Inproper number of arguments\n");
		return 0;
	}
	
	int i,k;
	char temp;
	for (i=1;i<argc;i++)
	{
		for (k=0; argv[i][k]!='\0'; k++)
		{
			temp = argv[i][k];
			if (temp=='a' || temp=='e' || temp=='i' || temp=='o' || temp=='u' || temp=='A' || temp=='E' || temp=='I' || temp=='O' || temp=='U')
			{
				printf("%c",temp);
			}
		}
	}
	printf("\n");
	return 0;
}
