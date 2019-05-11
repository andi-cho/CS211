// header file

#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
//define structs
typedef struct _block
{
        int valid;
        unsigned long long int tag;
} block;

typedef struct _cache{
    block** blocks;
    int cacheSize;
    int blockSize;
    int numSets;
    int assoc;
    int reads;
    int writes;
    int misses;
    int hits;
    int prefetch;
} cache;
//declare prototype functions
int checkPwrOfTwo(int);
cache* createCache (int,int,int);
int getAssoc(char* assocString);
int searchCache (cache*, unsigned long long int);
unsigned int Log2(unsigned int);
void printBinaryAddress(unsigned);
cache* insertCache (cache*, unsigned long long, int);
unsigned long long int getSetIndex(cache*, unsigned long long int);
unsigned long long int getTagIndex(cache*, unsigned long long int);
cache* shiftBlocks (cache*, unsigned long long int,unsigned long long int, int);
void printCache(cache*);
cache* moveToFrontOfCache(cache*, unsigned long long int, int);
void freeCache(cache*);


//start code 
int checkPwrOfTwo (int num)
{
        // check if block size + cache size is 2^n
        if(num <= 0 )
        {
		return 0;
    	}
	int boolean = num & (num-1);
	return boolean; 
}

int getAssoc(char* assocString)
{
	//tokenize string
	char* dupAssoc = malloc(sizeof(char*)*strlen(assocString)); // create new string
	strcpy(dupAssoc, assocString); // copy assocString into dupAssoc
	char* assoc;
	assoc = strtok(dupAssoc,":"); 
	assoc  = strtok(NULL, ":"); // either a # or NULL
	if (assoc==NULL)
	{
		// check if direct or fully
		// return -1 for direct
		if (strcmp(assocString, "direct")==0)
		{
			//free(dupAssoc);
			return -1;
		}
		//return -2 for fully assoc
		else if (strcmp(assocString, "fully")==0)
		{
			//free(dupAssoc);
			return -2;
		}
		//return -3 for error
		else {
			//free(dupAssoc);
			return -3; 
		}
	}
	else 
		//free(dupAssoc);
		return atoi(assoc);
}

unsigned int Log2(unsigned int x) {
        unsigned int ans = 0;
        while(x >>= 1) ans++;
        return ans;
}
