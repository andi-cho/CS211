#include<stdio.h>
#include<stdlib.h>
//linked list node definition
typedef struct _node
{
        int data;
        struct _node *next;
}node;

// prototype functions
int keyToVal (int);
void insert(int);
void hash_search(int);
void free_ht(node**);

//global variables
int size = 100;
int collisionCount=0;
int searchCount=0;
int nodeCount = 0;
node** ht; // array holding hash table, holds pointers to each list  

int main(int argc, char** argv) 
{
	ht = (node**) malloc(10000*sizeof(node*));
	if (argc!=2)
	{
		printf("Inproper number of arguments.\n");
		free_ht(ht);
		return 0;
	}
	FILE* myFile = fopen(argv[1],"r");
	if (myFile==NULL)
	{
		printf("File does not exist.\n");
		free_ht(ht);
		return 0;
	}
	char myChar;
	int myInt;
	while (fscanf(myFile,"%c%d",&myChar,&myInt) != EOF)
	{
		if (myChar=='i')
		{
			// insert
			insert(myInt);
			
		}
		else if (myChar=='s')
		{
			// search
			hash_search(myInt);
		}
	}
	printf("%d\n",collisionCount);
	printf("%d\n",searchCount);
	free_ht(ht);
	fclose(myFile);
	return 0;
}

void free_ht (node** ht) 
{
	int i;
        node* head;
        node* tmp;
        for (i=0; i<10000;i++)
        {
		for (head=ht[i]; head!=NULL; head=tmp)
		{
			tmp = head->next;
			free(head);
		}
	}
	free(ht);
	return;
}
int keyToVal(int key)
{
	key = abs(key);
	return (key%size);
}
void insert (int myInt)
{
	// basically insert into linked list
	// may call rehash if needed
	node* ptr;
	node* prev;
	node* temp = (node*) malloc (1*sizeof(node));
	temp->data = myInt;
	temp->next = NULL;
	int value = keyToVal(myInt);

	if (ht[value]==NULL) // nothing in linked list 
	{
		ht[value]=temp;
		nodeCount++;
	//	printf("Node count is: %d and size is: %d\n",nodeCount, size);
		return;
	}
	
	collisionCount++;

	ptr = ht[value];

	if (ptr->next == NULL) // one node in linked list 
	{
		if (ptr->data==myInt)
		{
		//	printf("duplicate\n");
			return;
		}
		else
		{
			ptr->next=temp;
			nodeCount++;
	          //     printf("Node count is: %d and size is: %d\n",nodeCount, size);
			return;
		}
	}

	else
	{
		while (ptr != NULL)
		{
			if (ptr->data == myInt)
			{
				// duplicate
		//		printf("duplicate\n");
				return;
			}
			prev = ptr;
			ptr = ptr->next;
		}

		// no match, add to back of list
		prev->next = temp;
		nodeCount++;
		//printf("inserted\n");
		//printf("Node count is: %d and size is: %d\n",nodeCount, size);
		return;
	}
	return;
}
void hash_search (int myInt)
{
	int value = keyToVal(abs(myInt));
	//printf("Searching...\n");
	node* ptr = ht[value];
	if (ptr == NULL)
	{
	//	printf("Does not exist!\n");
		return;
	}
	while (ptr!=NULL)
	{
		if (ptr->data == myInt)
		{
	//		printf("Found %d!\n", myInt);
			searchCount++;
			return;
		}
		ptr=ptr->next;
	}
	//printf("Does not exist!\n");
	return;
}
