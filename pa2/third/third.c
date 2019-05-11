#include<stdio.h>
#include<stdlib.h>

int get(unsigned short, int);

int main(int argc, char** argv)
{
	if (argc<2)
        {
                return 0;
        }
        int x = atoi(argv[1]);
	
	for (int i =0; i<16; i++)
	{
		int a = get(x,i);
		int b = get (x,15-i);
		if (a==b)
		{
			continue;
		}
		else 
		{
			printf("Not-Palindrome\n");
			return 0;
		}
	} 
	printf("Is-Palindrome\n");
	return 0;
}

int get(unsigned short x, int n)
{
        return (x>>n)&1;
}

