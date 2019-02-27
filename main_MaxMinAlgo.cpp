//Implementation of algorithm to find Minimum & Maximum number from an array
//Implementation is made effecient to take less comparison operation

//Binary doesn't take any input. Array elements (and size) fixed in code

#include <stdio.h>

const int N = 8;

void print_max_min_general(int* arr)
{
	int min = arr[0];
	int max = arr[N-1];

	int compares = 0;

	for(int i = 0 ; i < N ; ++i)
	{
		printf(" %d", arr[i]);
		compares += 2;
		if( arr[i] < min )	{ min = arr[i]; --compares; }
		else if(max < arr[i] )	{ max = arr[i]; }
	}
	printf("\n min= %d, max= %d, compares= %d\n", min, max, compares);
}

void print_max_min_short(int* arr)
{
	int min = arr[0];
	int max = arr[N-1];

	int compares = 0;
	for( int i = 0 ; i < (N+1)/2 ; ++i )
	{
		compares += 3;
		if( arr[i] < min )	min = arr[i];
		if( max < arr[N-1-i] )	max = arr[N-1-i];
		if( max < min )		{ int temp = min; min = max; max = temp; }
		
	}
	for( int i = 0 ; i < N ; ++i )
		printf(" %d", arr[i]);
	printf("\n min= %d, max= %d, compares= %d\n", min, max, compares);
}

int main()
{
	int arr1[] = {1, 2, 3, 4, 5, 6, 7, 8};
	int arr2[] = {8, 7, 6, 5, 4, 3, 2, 1};
	int arr3[] = {4, 3, 2, 1, 5, 6, 7, 8};
	int arr4[] = {4, 3, 2, 1, 8, 7, 6, 5};
	int arr5[] = {8, 7, 6, 5, 1, 2, 3, 4};
	int arr6[] = {5, 6, 7, 8, 1, 2, 3, 4};
	int arr7[] = {5, 6, 3, 4, 7, 8, 1, 2};
	int arr8[] = {5, 6, 1, 2, 7, 8, 3, 4};
	int arr9[] = {1, 1, 1, 1, 1, 1, 1, 1};
	int arr10[] = {1, 3, 5, 7, 8, 6, 4, 2};

	print_max_min_short(arr1);
	print_max_min_short(arr2);
	print_max_min_short(arr3);
	print_max_min_short(arr4);
	print_max_min_short(arr5);
	print_max_min_short(arr6);
	print_max_min_short(arr7);
	print_max_min_short(arr9);
	print_max_min_short(arr10);

	return 0;
}
