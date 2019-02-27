//Implementation to find second maximum in an array efficiently

#include <stdio.h>
#include <list>
using namespace std;

const int N = 8;



void print_second_largest_general(int* arr)
{
	int compares = 0;

	int max = 0;
	int max2 = 0;
	for(int i = 0 ; i < N ; ++i)
	{
		compares += 2;
		if( max < arr[i] )	{ max2 = max; max = arr[i]; --compares; }
		else if( max2 < arr[i] ) { max2 = arr[i]; }
	}
	for( int i = 0 ; i < N ; ++i )
		printf(" %d", arr[i]);
	printf(" %s(): max= %d, max2= %d, compares= %d\n", __FUNCTION__, max, max2, compares);
}

//Ref: http://stackoverflow.com/questions/3628718/find-the-2nd-largest-element-in-an-array-with-minimum-number-of-comparisons

int play_tournaments(int* winners, int* winpos, int count);

int global_compares;
list<int> losers_against_winner;
void print_second_largest_short(int* arr)
{
	global_compares = 0;
	losers_against_winner.clear();

	int* pos_arr = new int[N];
	for( int i = 0 ; i < N ; ++i ) pos_arr[i] = i;

	int max_at = play_tournaments(arr, pos_arr, N);

	delete[] pos_arr;

	int max2 = 0;
	for( int loser : losers_against_winner )
	{
		++global_compares;
		if( max2 < loser )  max2 = loser;
	}

	for( int i = 0 ; i < N ; ++i )
		printf(" %d", arr[i]);

	printf(" %s(): max= %d, max2= %d, compares= %d\n", __FUNCTION__, arr[max_at], max2, global_compares);
}

int play_tournaments(int* winners, int* winpos, int count)
{
	if( count == 2 )
	{
		++global_compares;
		if( winners[0] >= winners[1] )
		{
			losers_against_winner.push_back(winners[1]);
			return winpos[0];
		}
		else
		{
			losers_against_winner.push_back(winners[0]);
			return winpos[1];
		}
	}

	int* winners_arr = new int[(count+1)/2];
	int* winpos_arr = new int[(count+1)/2];
	for( int i = 0 ; i < (count+1)/2 ; ++i )
	{
		++global_compares;
		if( winners[i] >= winners[count-1-i] )
		{
			winners_arr[i] = winners[i];
			winpos_arr[i] = i;
		}
		else
		{
			winners_arr[i] = winners[count-1-i];
			winpos_arr[i] = count-1-i;
		}
	}
	int win_at = play_tournaments(winners_arr, winpos_arr, (count+1)/2);

	losers_against_winner.push_back(winners[count-1-win_at]);
	win_at = winpos[win_at];
	
	delete[] winners_arr;
	delete[] winpos_arr;
	return win_at;
}
int main()
{
	int arr1[] = {1, 2, 3, 4, 5, 6, 8, 7};
	int arr2[] = {8, 7, 6, 5, 4, 3, 2, 1};
	int arr3[] = {4, 3, 2, 1, 5, 6, 7, 8};
	int arr4[] = {4, 3, 2, 1, 8, 7, 6, 5};
	int arr5[] = {8, 7, 6, 5, 1, 2, 3, 4};
	int arr6[] = {5, 6, 7, 8, 1, 2, 3, 4};
	int arr7[] = {5, 6, 3, 4, 7, 8, 1, 2};
	int arr8[] = {5, 6, 1, 2, 7, 8, 3, 4};
	int arr9[] = {1, 1, 1, 1, 1, 1, 1, 1};
	int arr10[] = {1, 3, 5, 7, 8, 6, 4, 2};
	int arr11[] = {7, 3, 5, 1, 2, 6, 4, 8};
	int arr12[] = {1, 5, 2, 7, 3, 6, 4, 8};

	print_second_largest_general(arr1);
	print_second_largest_short(arr1);
	print_second_largest_general(arr2);
	print_second_largest_short(arr2);
	print_second_largest_general(arr3);
	print_second_largest_short(arr3);
	print_second_largest_general(arr4);
	print_second_largest_short(arr4);
	print_second_largest_general(arr5);
	print_second_largest_short(arr5);
	print_second_largest_general(arr6);
	print_second_largest_short(arr6);
	print_second_largest_general(arr7);
	print_second_largest_short(arr7);
	print_second_largest_general(arr8);
	print_second_largest_short(arr8);
	print_second_largest_general(arr9);
	print_second_largest_short(arr9);
	print_second_largest_general(arr10);
	print_second_largest_short(arr10);
	print_second_largest_general(arr11);
	print_second_largest_short(arr11);
	print_second_largest_general(arr12);
	print_second_largest_short(arr12);

	return 0;
}
