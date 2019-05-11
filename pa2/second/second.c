#include<stdio.h>
#include<stdlib.h>

void getParity(int);
void countPairs(int);

int main(int argc, char** argv)
{
        //printf("This is second.c\n");
        if (argc<2)
	{
		return 0;
	}
	int n = atoi(argv[1]);
	//printf("C is %d\n",n);
	//printf("%d\n",getParity(n));
	//printf("%d\n",countPairs(n));	
        getParity(n);
	countPairs(n);
	return 0;
}

void getParity (int n)
{
	int numOneBits=0;
	while (n!=0)
	{
		int LSB = n&1; 
		if (LSB==1)
		{
			numOneBits++;
		}
		n=n>>1; 
	}
	if (numOneBits%2==0)
	{
		printf("Even-Parity\t");
	}
	else
	{
		printf("Odd-Parity\t");
	}
	//printf("in get parity function\n");
	// get LSB
	// if 1, increment count 
	// if count%2 = 0 return even
	// else return odd

	//while (n!=0) // stops when 0
	//{
	//	parity=!parity;
	//	n=n&(n-1); // zero out last 1 bit
	//}
	//if (parity==0) 
	//	printf("Even-Parity\t");
	//else
	//	printf("Odd-Parity\t");
}

void countPairs (int n)
{
	int onePairs = 0; // num pairs 
	int pair = 0; // boolean 
	while (n!=0)
	{
		int LSB = n&1; // LSB value 
		if (LSB == 1)
		{
			if (pair == 1) 
			{
				onePairs++;
				pair = 0;
			}
			else if (pair == 0)
			{
				pair = 1;
			}
		}
		else if (LSB==0)
		{
			pair = 0;
		}
		n=n>>1;
	}
	printf("%d\n",onePairs);
//	return onePairs; 
}
