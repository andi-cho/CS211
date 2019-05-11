#include<stdio.h>
#include<stdlib.h>
typedef struct _BSTNode{
	struct _BSTNode* left;
	struct _BSTNode* right;
	int data;
}BSTNode;

BSTNode* insert(BSTNode*, int);
void inOrder(BSTNode*);
void freeBST(BSTNode*);

int main(int argc, char** argv) 
{
	if (argc<2)
	{
		printf("Inproper number of arguments\n");
		return 0;
	}
	FILE* myFile = fopen(argv[1],"r");
	if (myFile==NULL)
	{
		printf("error\n");
		fclose(myFile);
		return 0;
	}
	BSTNode* root = NULL;
	int myInt;
	char myChar;
	while( fscanf(myFile,"%c%d",&myChar,&myInt) != EOF) 
	{
		if (myChar=='i')
		{
		//	printf("Inserting %d into tree\n",myInt);
			// insert into tree
			root=insert(root, myInt);
		}
	}
	//printf("in main, root is %d\n",root->data);
	inOrder(root);
	printf("\n");
	freeBST(root);
	fclose(myFile);
	return 0;
}

BSTNode* insert(BSTNode* root, int myInt)
{
	if (root==NULL) // empty tree
	{
		BSTNode* temp = (BSTNode*) malloc(1*sizeof(BSTNode));
        	temp->data = myInt;
       		temp->right = NULL;
        	temp->left = NULL;
		root=temp;
	//	printf("root is null\n");
	//	printf("Root is now: %d\n",root->data);
		return temp; 
	}
	// not an empty tree, check left or right subtree
	if (myInt==root->data) // if equal, don't do anything
	{
		return root;
	}
	if (myInt>root->data)
	{
		root->right = insert(root->right,myInt);
	}
	else if (myInt<root->data)
	{
		root->left = insert(root->left,myInt);
	}
//	printf("At the end of insert method, root is now %d\n",root->data);
	return root;
}

void inOrder(BSTNode* root)
{
	if (root==NULL)
	{
		return;
	}
	// print binary tree in-order traversal
	inOrder(root->left);
       	printf("%d\t",root->data);
       	inOrder(root->right);
	
}

void freeBST(BSTNode* root)
{
	if (root==NULL)
	{
		return;
	}
	freeBST(root->left);
	freeBST(root->right);
	free(root);
}
