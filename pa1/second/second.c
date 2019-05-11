#include<stdio.h>
#include<stdlib.h>
// creating node for ll
typedef struct _node 
{
	int data;
	struct _node *next;
}node;

int findDuplicate(node**, int);
void deleteNode(node**,int);
void insertNode(node**, int, int);
void printList(node*);
void printUnique(node*);
void freeNodes(node*);

int emptyLL=1;

int main(int argc, char** argv) {
	if (argc!=2) // error check
        {
                printf("Inproper number of arguments \n");
               	return 0;
        }
	char* f = argv[1];
        FILE* myFile = fopen(f, "r"); // open file
        if (myFile==NULL) // error check: if file doesn't exist
        {
                printf("error\n");
		fclose(myFile);
                return 0;// positive exit indicates error
        }
	char myChar;
	int myInt=-1;
//	int emptyLL = 1;
	node* front=NULL;
	int duplicateFound=0;
	//int insertCalled=0;
	// need to make scanner ignore white space as character!!!
	while (fscanf(myFile, " %c %d",&myChar,&myInt ) != EOF) {
		if (emptyLL==0) // if the list is NOT empty (has contents)
		{
		//	printf("List is NOT empty\n");
			if (myChar=='i')
			{
		//		insertCalled=1;
				insertNode(&front, myInt, emptyLL);
			}
			if (myChar=='d')
			{
				duplicateFound = findDuplicate(&front,myInt);
				if (duplicateFound==1)
				{
					deleteNode(&front, myInt);
		//			printf("Empty list is: %d\n", emptyLL);
				}

				// else, silenty ignore request
			}
		}
		else if (emptyLL==1) // if LL is empty
		{
		//	printf("List is empty\n");
			if (myChar=='i') // insert in order
			{
		//		insertCalled=1;
				insertNode(&front, myInt, emptyLL);
				emptyLL=0;
			}
			else if (myChar=='d') // delete existing val and replace
			{
				//myChar is 'd' but list is empty, so doing nothing
			}	 
		}
	//	printList(front);
	}
//	printList(front);
	if (front==NULL)
	{
		printf("0\n");
		freeNodes(front);
		fclose(myFile);
		return 0;
	}

	printUnique(front);
/*	if (feof(myFile))
	{
		//freeNodes(front);
		front = NULL;
		freeNodes(front);
	}
*/
	fclose(myFile);
	freeNodes(front);
	return 0;
}

void freeNodes (node* front)
{
	node* temp;
	while (front!=NULL)
	{
		temp = front;
		front = front->next;
		free(temp);
	}
	return;
}
void deleteNode(node** front, int myInt)
{
	// delete node
	node* ptr = *front;
	node* prev = NULL;
	while (ptr!=NULL)
	{
		if (ptr->data==myInt)
		{
			if (ptr==*front)
			{
	//			printf("deleting front...\n");
				*front = ptr->next;
				free(ptr);
				if (ptr->next==NULL)
				{
					//free(ptr);
					emptyLL=1;
				}
			}
			else
			{
				prev->next=ptr->next;
				free(ptr);
			}
			return;
		}
		prev = ptr;
		ptr = ptr->next;
	}
	return;
}

void insertNode(node** front, int myInt, int emptyLL)
{
	node* temp = (node*) malloc(1*sizeof(node));
	temp->data = myInt;
	temp->next = NULL;
	//if empty linked list, just make it the front
	if (emptyLL==1)
	{
		*front=temp;
		return;
	}
	//if linked list is filled, traverse list to find duplicate 
	node* ptr = *front;
	node* prev = NULL;
	while (ptr!=NULL)
	{
		if (ptr->data == myInt)
		{
			prev = ptr;
			ptr = ptr->next;
			prev->next = temp;
			temp->next = ptr;

			//prev->next = temp;
			//temp->next = ptr;
			return;
		}
		if (ptr->data > myInt)
		{
			if (prev==NULL) // ex: linked list is: 2,3,4 + inserting 1
			{
				*front=temp;
				temp->next=ptr;
				return;
			}
			prev->next = temp;
			temp->next = ptr;
			return;
		}
		if (ptr->data < myInt && ptr->next==NULL)
		{
			ptr->next = temp;
			return;
		} // else if ptr.data < myInt, cont. to traverse list
		prev = ptr;
		ptr = ptr->next;
	}	
	return;
}

int findDuplicate(node** front, int myInt)
{
	int duplicateFound=0;
	node* ptr = *front;
	while (ptr!=NULL)
	{
		if (ptr->data==myInt)
		{
			duplicateFound=1;
			return duplicateFound;
		}
		ptr=ptr->next;
	}	
	return duplicateFound;
}

void printList(node* front)
{
	int i=0;
	node* ptr=front;
	while( ptr!=NULL )
	{
		i++;
		ptr=ptr->next;
	}
	ptr = front;
	while(ptr!=NULL)
	{
		printf("%d\t",ptr->data);
		ptr=ptr->next;
	}
	printf("\n");
	return;
}

void printUnique(node* front)
{
	int i = 0;
	node* ptr = front;
	node* prev = NULL;
	while (ptr!=NULL)
	{
		i++;
		ptr=ptr->next;
	}
	
	if (i==0)
	{
	//	printf("nothing in list\n");
	//	printf("0\n");
		return;
	}
	printf("%d\n", i);
	ptr=front;

	while (ptr!=NULL)
	{
		while (prev!=NULL && prev->data==ptr->data)
		{
			prev=ptr;
			if (ptr->next==NULL)
			{
				printf("\n");
				return;
			}
			else
			{
				ptr=ptr->next;
			}
		}
		printf("%d\t",ptr->data);
		prev=ptr;
		ptr=ptr->next;
	}
	printf("\n");	
	return;
}
