#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int get(unsigned short, int);
int comp(unsigned short, int);
int set (unsigned short, int, int);

int main(int argc, char** argv)
{
	if (argc!=2)
	{
		return 0;
	}
	FILE* myFile = fopen(argv[1],"r"); 
	if (myFile==NULL)
	{
		return 0;
	}
	unsigned short x;
	char* command = (char*) malloc(sizeof(char*)*4); // string 
	char getstr[] = "get";
	char compstr[] = "comp";
	char setstr[] = "set";
	int n, v;
	
	fscanf(myFile, "%hu", &x);
	
	while (fscanf(myFile, "%s %d %d\n", command, &n, &v)!=EOF){
		//printf("Command is %s\n",command);
		if (strcmp(command,getstr)==0)
		{
			//printf("Calling GET...\n"); 
			printf("%d\n",get(x,n));	
		}
		else if (strcmp(command,setstr)==0)
		{
			//printf("Calling SET...\n");
         		x=set(x,n,v);
			printf("%d\n",x);
			
		}
		else if (strcmp(command,compstr)==0)
		{ 
			//printf("Calling COMP...\n");
			x = comp(x,n);
			printf("%d\n",x);
		}
		//printf("End of while loop\n");
	}
	free(command);
	fclose(myFile);
	return 0;
}

int get(unsigned short x, int n)
{
	return (x>>n)&1; 
}

int comp(unsigned short x, int n)
{
	//printf("In COMP method\n");
	int thisBit = !(get(x,n));
	return set(x,n,thisBit);
}

int set(unsigned short x, int n, int v)
{
	//printf("In SET method\n");
	// set nth bit of the number x to v
	if (v==1)
	{
		return x|(1<<n);
	}
	else// if (v==0)
		return x&~(1<<n);
}	
