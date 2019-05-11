#include<stdio.h>
#include<stdlib.h>
#include"first.h"
#include<math.h>


int main(int argc, char** argv)
{
	if (argc!=6)
        {
		printf("error");
        	printf("Input correct # of args\n");
        	return 0;
        }
        FILE* traceFile = fopen(argv[5],"r"); // trace1.txt
        if (traceFile==NULL)
        {
		printf("error");
                return 0;
        }
	int cacheSize = atoi(argv[1]);
	// if cache size is not 2^n, error
	if (checkPwrOfTwo(cacheSize)!=0)
	{
		printf("Error, not a power of 2\n");
		return 0; 
	}
	int assoc = getAssoc(argv[2]); // need method to read assoc better 
	/*	if (assoc == -1)
	{
		printf("Direct associativity\n"); // direct assoc
	}
	if (assoc == -2)
	{
		printf("Fully associative\n"); // fully assoc
	}
	if (assoc == -3)
	{
		printf("Invalid associativity\n"); // invalid assoc
	}
	else 
	{
		printf("Associativity is %d\n",assoc); // n-assoc
	}
*/
	int blockSize = atoi(argv[4]);
	//printf("block size is : %d\n",blockSize);
	//printf("assoc is: %d\n",assoc);
	// if blockSize != 2^n, error
	if (checkPwrOfTwo(blockSize)!=0)
	{
                printf("Error, not a power of 2\n");
                return 0;
        }
	
	//end of argument setup, now build cache
	cache* myCache = createCache(cacheSize, blockSize, assoc);
	
//	printf("Cache created\n");
	//myCache->assoc=assoc;
	myCache->prefetch=0;
	char* random = (char*)malloc(sizeof(char)*500);
	char op;
	unsigned long long int address;
	while( fscanf(traceFile,"%s %c %llx",random,&op,&address) == 3)
	{
		// search cache, return 1 if found, 0 if not 
		int loc = searchCache(myCache, address);
		//printf("Loc is: %d\n", loc);
		if (loc!=-1) //hit; hit is location in cache[setIndex][location]
		{
		// whether R or W, if it's a hit, you want to move it to the front of the cache's set array
			if (op=='R') // hit-read
			{
				myCache->hits++;
				myCache = moveToFrontOfCache(myCache, address, loc);	
			}
			else if (op=='W') // hit-write
			{
				myCache->hits++;
				myCache->writes++;
				// insert into cache
				myCache = moveToFrontOfCache(myCache, address,loc);
			}
		}		
		else if (loc == -1) //miss
		{
		// if it's a miss, insert it to the 0th index of the array's set index
			if (op=='R') // read-miss
			{
				myCache->reads++;
				myCache->misses++;
				myCache = insertCache(myCache, address, loc);
			}
			else if (op=='W') // write-miss
			{
				myCache->misses++;
				myCache->reads++;
				myCache->writes++;
				myCache = insertCache(myCache, address,loc);
			}
		}
		//printCache(myCache);
		//printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		
	}

	//printf("no-prefetch\n");
	//printf("Memory reads: %d\n", myCache->reads);
	//printf("Memory writes: %d\n", myCache->writes);
	//printf("Cache hits: %d\n", myCache->hits);
	//printf("Cache misses: %d\n", myCache->misses);
	
	// now do prefetch
        FILE* traceFilePF = fopen(argv[5],"r"); // need new file pointer for prefetch
	//printf("assoc is: %d\n", assoc);
	cache* myCachePF = createCache(cacheSize, blockSize, assoc);
       	//myCachePF->assoc=assoc;
        //printf("myCachePF->assoc is %d\n",myCachePF->assoc);
	myCachePF->prefetch=1;
	
	//printf("FSCANF initial return: %d\n",  fscanf(traceFile,"%s %c %llx",random,&op,&address));
	while( fscanf(traceFilePF,"%s",random))
	{
		if(strcmp(random, "#eof") == 0) break;
		char ass[20];;
		fscanf(traceFilePF, " %c %s", &op, ass);
		address = strtoull(ass, NULL, 16);

		int loc = searchCache(myCachePF, address);
                //printf("Loc is: %d\n", loc);
                if (loc!=-1) //hit; hit is location in cache[setIndex][location]
                {
			if (op=='R') // hit-read
                        {
                                myCachePF->hits++;
                                //printf("prefetch hits++ %d\n",myCachePF->hits);
				myCachePF = moveToFrontOfCache(myCachePF, address, loc);
                        }
                        else if (op=='W') // hit-write
                        {
                                myCachePF->hits++;
                                myCachePF->writes++;
                                myCachePF = moveToFrontOfCache(myCachePF, address,loc);
                       	}
		}
		else if (loc == -1) //miss
                {
			if (op=='R') // read-miss
                        {
                                myCachePF->reads++;
                                myCachePF->misses++;
                                myCachePF = insertCache(myCachePF, address, loc);
                        }
                        else if (op=='W') // write-miss
                        {
                                myCachePF->misses++;
                                myCachePF->reads++;
                                myCachePF->writes++;
                                myCachePF = insertCache(myCachePF, address,loc);
                        }
		}
		//printCache(myCachePF);
                //printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	}
	printf("no-prefetch\n");
        printf("Memory reads: %d\n", myCache->reads);
        printf("Memory writes: %d\n", myCache->writes);
        printf("Cache hits: %d\n", myCache->hits);
        printf("Cache misses: %d\n", myCache->misses);
	//printCache(myCache);
	printf("with-prefetch\n");
        printf("Memory reads: %d\n", myCachePF->reads);
        printf("Memory writes: %d\n", myCachePF->writes);
        printf("Cache hits: %d\n", myCachePF->hits);
        printf("Cache misses: %d\n", myCachePF->misses);
	//printCache(myCachePF);
	fclose(traceFile);
	fclose(traceFilePF);
	freeCache(myCache);
	freeCache(myCachePF);
	free(random);
	return 0;

}
cache* moveToFrontOfCache (cache* myCache, unsigned long long int address, int loc)
{
	//printf("Moving to front of cache...\n");
	//use temp to hold block you want to move
	//shift "everything to the left of the location of block you wanna move" one to the right 
	//
	unsigned long long int setIndex = getSetIndex(myCache, address);
	unsigned long long int temp = myCache->blocks[setIndex][loc].tag;
	int i = 0;
	for (i=loc; i>0; i--)
	{
		myCache->blocks[setIndex][i].tag=myCache->blocks[setIndex][i-1].tag;
	}
	myCache->blocks[setIndex][0].tag=temp;
	
	return myCache;
}

cache* insertCache (cache* myCache, unsigned long long int address, int loc)
{
	unsigned long long int setIndex = getSetIndex(myCache, address);
        unsigned long long int tagIndex = getTagIndex(myCache, address);

	if (myCache->prefetch==0) 
	{
		// move everything to the right and add to front of cache 
		//printf("Inserting into cache (no prefetch)...\n");
		
		myCache = shiftBlocks(myCache,tagIndex, setIndex, loc);
		myCache->blocks[setIndex][0].tag = tagIndex;
	}
	else if (myCache->prefetch==1)
	{
		// move everything 2x to the right and then the neighbor (+ blocksize)
		//printf("Inserting into cache (and neighbor bc prefetch)...\n");
		
		// inserting original block
		myCache = shiftBlocks(myCache, tagIndex, setIndex, loc);
		myCache->blocks[setIndex][0].tag = tagIndex;
		//printf("regular tagIndex is %llx\n",tagIndex);
		//printf("regular address is %llx\n",address);
		// inserting adjacent block 
		// 	must update address + tag index
		address = address + myCache->blockSize;
		//printf("Prefetching neighbor address which is: %llx\n",address);
		tagIndex = getTagIndex(myCache, address);
		setIndex = getSetIndex(myCache, address);
		//printf("prefetched address is: %llx\n",address);
		//printf("prefetched tagIndex is: %llx\n",tagIndex);
		loc=searchCache(myCache, address);
		
		if (loc==-1) // miss
		{
			myCache->reads++;
			shiftBlocks(myCache, tagIndex, setIndex, loc);
		}
		else //hit
		{
			//moveToFrontOfCache(myCache, address, loc);
			//donothing
		}
		
		//myCache = shiftBlocks(myCache, tagIndex, setIndex, loc);
		//myCache->blocks[setIndex][0].tag = tagIndex;
	}
	return myCache;
}

cache* shiftBlocks (cache* myCache, unsigned long long int tagIndex, unsigned long long int setIndex, int loc)
{
	int i;
	//printf("loc is : %d\n",loc);
	if (loc==-1) // miss, just add to last index
	{
		loc = myCache->assoc;
	}
	for (i=loc-1; i>0; i--) // normal case: hit, 
	{
		myCache->blocks[setIndex][i].tag=myCache->blocks[setIndex][i-1].tag;
	}
	myCache->blocks[setIndex][0].tag = tagIndex;
	return myCache;
		
}

cache* createCache (int cacheSize, int blockSize, int blocksPerSet) {
	//assoc = blocksPerSet

	cache* myCache = (cache*)malloc(sizeof(cache));

	myCache->reads=0;
	myCache->writes=0;
	myCache->hits=0;
	myCache->misses=0;
	myCache->cacheSize=cacheSize;
	myCache->blockSize=blockSize; 

	//printf("Blocks per set is %d\n",blocksPerSet);	
	//check associativity + set numSets, assoc, and blocksPerSet(n)
	if (blocksPerSet == -1) // direct associative
	{
		myCache->numSets = cacheSize / blockSize;
		//printf("Direct assoc, numSets: %d\n", myCache->numSets);
		myCache->assoc = 1;
		blocksPerSet = 1;
	}
	if (blocksPerSet == -2) // fully associative 
	{
		myCache->numSets = 1; // only 1 set for fully assoc
 		//printf("Fully assoc, numSets: %d\n", myCache->numSets);

		blocksPerSet = cacheSize / blockSize;
		myCache->assoc = blocksPerSet; // set assoc to n-way
	}
	else
	{
		myCache->numSets = cacheSize / (blockSize*blocksPerSet);
		//printf("N-way assoc, numSets: %d\n", myCache->numSets);
		myCache->assoc = blocksPerSet;
		//myCache->assoc = 3;
	}
	
	// now build cache
	int i;
	int k;
	int mallocRows = sizeof(block*) * (myCache->numSets);
	myCache->blocks=(block**)malloc(mallocRows);
	//printf("Rows: %d Colls; %d\n", myCache->numSets, blocksPerSet);	

	//cache is 2d array 
	for (i=0; i<myCache->numSets; i++) // iterate through all sets (top to bottom)
	{
		int mallocCols = sizeof(block) * blocksPerSet;
		myCache->blocks[i] = (block*)malloc(mallocCols);
		
		for (k=0; k<blocksPerSet; k++) // iterate through all blocks in set (left to right)
		{
			//array array of ints that hold addresses
			//printf("0	");			
			myCache->blocks[i][k].tag = 0;
			//myCache->blocks[i][k].valid = 0;
		}
		//printf("\n");
	}
	return myCache;
}

void printCache(cache* myCache)
{
	int i = 0;
	int k = 0;
	for (i=0; i<myCache->numSets; i++)
	{
		for (k=0; k<myCache->assoc; k++)
		{
			printf("%llx	", myCache->blocks[i][k].tag);
		}
		printf("\n");
	}
}
void printBinaryAddress(unsigned n) 
{ 
    unsigned i; 
    printf("Address is: ");
    for (i = 1 << 31; i > 0; i = i / 2) 
    {
	(n & i)? printf("1"): printf("0");
    }
    printf("\n");
} 
unsigned long long int getTagIndex(cache* myCache, unsigned long long int address)
{
        int numOffsetBits = (int) Log2(myCache->blockSize); // little b = log2(bigB)
        int numSetIndexBits = (int) Log2( myCache->numSets); 
	//printBinaryAddress(address);
        unsigned long long int tagIndex = (address >> (numSetIndexBits + numOffsetBits));
        //printf("tagIndex is: %lld\n", tagIndex);	
	return tagIndex;
}

unsigned long long int getSetIndex(cache* myCache, unsigned long long int address)
{
	int numOffsetBits = (int) Log2(myCache->blockSize); // little b = log2(bigB)
        int numSetIndexBits  = (int) Log2( myCache->numSets);
	unsigned long long int setIndex = (address >> numOffsetBits) & ((1 << numSetIndexBits)-1);
		// what i'm doing here:
		// [tag][set bits][offset bits]
		// address >> numOffsetBits will delete [offset bits]
		// [tag][set bits]
		// 1 << numSetIndexBits == 100 (where the # of zeros = # set index bits)
		// 1 << numSetIndexBits - 1 == 011 (leftmost digit becomes 0,, everything after becomes a 1)
        	// now when you & with [tag][setbits], you only have [setbits]
	return setIndex;
}
int searchCache (cache* myCache, unsigned long long int address)
{
	unsigned long long int setIndex = getSetIndex(myCache, address);
	unsigned long long int tagIndex = getTagIndex(myCache, address);
	//printf("setIndex is: %lld\n", setIndex);
	//printf("tagIndex is: %lld\n", tagIndex);

	int i=0;	
	//printf("association is: %d\n", myCache->assoc);
	for (i = 0; i<myCache->assoc; i++)
	{
		//printf("Currently @ tag: %lld\n",myCache->blocks[setIndex][i].tag);
		if(myCache->blocks[setIndex][i].tag == tagIndex)
		{
			//printf("Returning i (%d)\n",i);
			return i;
		}
	}
	return -1;
}

void freeCache (cache* myCache)
{
	int i;
	for(i=0; i < myCache->numSets; i++)
	{
        	free(myCache->blocks[i]);
    	}
    	free(myCache->blocks);
    	free(myCache);
    	return;
}
