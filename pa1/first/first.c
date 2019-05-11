#include<stdio.h>
#include<stdlib.h>
//final version
void sort (int*, int);
void reverse(int*, int);
int main(int argc,char** argv) {	
	
	if (argc!=2)
	{
		printf("Inproper number of arguments \n");
		return 0;
	}

	FILE* myFile;
	myFile = fopen(argv[1], "r"); // open file

	if (myFile==NULL) // error check: if file doesn't exist
	{
		printf("File does not exist\n");
		fclose(myFile);
		return 0;// positive exit indicates error
	}

	int n; // number of items in LL 	
	fscanf(myFile, "%d", &n); // scan file for number of items in array
	int *total;
	total = (int*) malloc(sizeof (int) * n);
	int i; // counter
	int evenCount=0; // keep track of number of evens
	int evenPosition=0;
	int oddCount=0; // keep track of number of odds
	int oddPosition=0; // location of oddArray position
	int *evenArray;
	int *oddArray;

	for (i = 0; i<n; i++) // count # even + # odd
	{
		fscanf(myFile, "%d", &total[i]); // insert each file numbers into array

		if (total[i]%2==0) // if a number is even, increase evenCount
		{
			evenCount=evenCount+1;
		}
		else { oddCount=oddCount+1; } // if num is odd, increase oddCount
	}
	
	evenArray = (int*) malloc(sizeof(int)*evenCount); // make even array
	oddArray = (int*) malloc(sizeof(int)*oddCount); // make odd array

	for ( i = 0; i<n; i++) // if a number is even, put it in the even array
	{
		if (total[i] %2==0) 
		{
			evenArray[evenPosition]=total[i]; // if a number is even add to evenArray 
			evenPosition=evenPosition+1; // must increment evenPosition
		}
		else { // if odd
			oddArray[oddPosition]=total[i]; // add to odd array
			oddPosition=oddPosition+1; // must increment oddPosition
		}
	}
	
	// now oddArray and evenArray are filled so sort even 	
	sort(evenArray,evenCount);
	sort(oddArray, oddCount);

	reverse(oddArray, oddCount);
	// merge evenArray + oddArray back into totalArray
	for (i=0;i<evenCount;i++)
	{
		total[i]=evenArray[i]; //copy all even numbers 
	}

	oddPosition=0; // reinitialize oddPosition to 0th index of oddArray
	
	for (i=evenCount;i<n;i++) // in total array, start where you left off
	{
		total[i]=oddArray[oddPosition]; // add odd numbers to totalArray
		oddPosition++;
	}

	for(i=0;i<n;i++)
	{
		printf("%d\t", total[i]); // print result
	}
	printf("\n");

	// free malloc'd arrays
	free(evenArray);
	free(oddArray);	
	free(total);
	fclose(myFile);
	
	return 0;
}
 	
void sort (int* array, int n)
{
	int i,k;
	int temp;
	for (i=0;i<n;i++)
	{
		for (k=0;k<n-i-1;k++)
		{
			if (array[k]>array[k+1])
			{
				temp = array[k];
				array[k] = array[k+1];
				array[k+1] = temp;
			}
		}
	}
	return;
}
void reverse(int* array, int n)
{
	int i = 0;
	for (i = 0; i<n/2; ++i) // i++ or ++i?
	{
		int temp = array[i];
		array[i]=array[n-1-i];
		array[n-1-i]=temp;
	}
	return;
}
