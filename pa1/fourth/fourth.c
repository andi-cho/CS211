#include<stdio.h>
#include<stdlib.h>

//int** multiplyMatrices(int**, int**, int, int);
void freeMatrices(int**,int);

int main(int argc, char** argv) 
{
	if (argc!=2)
	{
		printf("Inproper number of arguments\n");
		return 1;
	}
	FILE* myFile = fopen(argv[1],"r"); // open file
	if (myFile==NULL) 
	{
		printf("No such file \n");
		exit(1);
	}
	
	int rowA;
	int colA;
	//int rowB;
	//int colB;
	fscanf(myFile,"%d",&rowA); // read row A
	fscanf(myFile,"%d",&colA); // read col A
	//printf("row A is: %d\n",rowA);
        //printf("col A is: %d\n",colA);
	// make 2D array, alot space for rowA and colA
	int i;
	int k;
	int temp;
 	int **matrixA = (int**) malloc(rowA*sizeof(int*));
	for(i=0;i<rowA;i++){
		matrixA[i] = (int*)malloc(colA*sizeof(int));
	}
	//	printf("\n");

	for (i=0; i<rowA; i++)
	{
		for (k=0; k<colA; k++)
		{
			fscanf(myFile,"%d",&temp);	
          //              printf("matrixA[%d][%d]: %d\t",i,k,temp);
			matrixA[i][k]=temp;
		}
	//	printf("\n");
	}
//	printf("matrixA[0][0] is: %d\n",matrixA[0][0]);	
	int rowB;
	int colB;
	fscanf(myFile,"%d",&rowB);
	fscanf(myFile,"%d",&colB);
//	printf("row B is: %d\n", rowB);
//	printf("col B is: %d\n", colB);
	
	int **matrixB = (int**) malloc(rowB*sizeof(int*));
        for(i=0;i<rowB;i++){
                matrixB[i] = (int*)malloc(colB*sizeof(int));
        }

	for (i=0; i<rowB; i++)
	{
		for (k=0;k<colB;k++)
		{
			fscanf(myFile,"%d",&temp);
			matrixB[i][k]=temp;
//			printf("%d\t",temp);
		}
//		printf("\n");
	}

	if (colA != rowB) // matrix multiplication not possible
	{	
		printf("bad-matrices\n");
		freeMatrices(matrixA, rowA);
       		freeMatrices(matrixB, rowB);
		fclose(myFile);
		return(0); 
	}
	// build result matrix
	int rowC=rowA;
	int colC=colB;
//	printf("rowC is %d\n",rowC);
//	printf("colC is %d\n",colC);
	
	int **matrixC = (int**) malloc(rowC*sizeof(int*));
        for(i=0;i<rowC;i++){
                matrixC[i] = (int*)malloc(colC*sizeof(int));
        }

	for(i=0;i<rowC;i++)
	{
		for(k=0;k<colC;k++)
		{
			matrixC[i][k]=0;
//			printf("%d\t",matrixC[i][k]);
		}
//		printf("\n");
	}
	int j;
	for (i=0;i<rowA;i++)
	{
		for (k=0;k<colB; k++)
		{
			for (j=0;j<colA;j++)
			{
				matrixC[i][k]+=matrixA[i][j]*matrixB[j][k];
			}
		}
	}
	for (i=0;i<rowC;i++)
	{
		for (k=0;k<colC;k++)
		{
			printf("%d\t",matrixC[i][k]);
		}
		printf("\n");

	}
	freeMatrices(matrixA, rowA);
	freeMatrices(matrixB, rowB);
	freeMatrices(matrixC, rowC);
	fclose(myFile);
	return 0;
}

void freeMatrices(int** matrixA,int rowA)
{
	int i;
	for (i=0; i<rowA; i++)
	{
		free(matrixA[i]);
		//ptr=matrixA[i];
		//free(ptr);	
	}
	free(matrixA);
	return;
}
//int** multiplyMatrices(int** matrixA, int** matrixB, int rowC, int colC)
//{
//	int i,k;
//	printf("matrixA[0][0] is: %d\n", matrixA[0][0]);
//	for (i=0; i<rowC;i++)
//	{
//		for (k=0;k<colC;k++)
//		{
//			int temp 
//			matrixC[i][k]=
//		}
//		printf("\n");
//	}
//	return 0;
//}
