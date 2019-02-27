//Implementation of Segmented Sieve Of Eratosthenes to find prime numbers within 1 to N
//Implementation is efficient way to get all primes less than N, with less time & space complexity

//Binary takes a non-zero values as input N

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <memory.h>

#include <vector>
using namespace std;
	

void simpleSieveOfEratosthenes(const int& prime_limit, vector<int>* primes_array)
{
	bool* is_prime = new bool[prime_limit+1];
	memset(is_prime, true, sizeof(bool) * (prime_limit+1));
	is_prime[0] = false;
	is_prime[1] = false;
	
	for( int i = 2 ; i*i <= prime_limit ; ++i ) {
		if( is_prime[i] ) {
			for( int j = i+i ; j <= prime_limit ; j += i )
				is_prime[j] = false;
		}
	}

	printf("[DEBUG] Simple Sieve Primes within %d\n", prime_limit);
	for( int i = 0 ; i <= prime_limit ; ++i ) {
		if( is_prime[i] ) {
			primes_array->push_back(i);
			printf("%d, ", i);
		}
	}
	printf("\n");

	delete[] is_prime;
}

int main(int argc, char** argv)
{
	if( argc == 1 ) {
		printf("[WARNING] Usage: prime_search N\n");
		return -1;
	}

	int N = atoi(argv[1]);
	int seg_size = sqrt(N);
	printf("[DEBUG] Prime search within (1, %d) using seg_size= %d\n", N, seg_size);

	vector<int> primes;

	simpleSieveOfEratosthenes(seg_size, &primes);
	int simple_sieve_primes_count = primes.size();


	int seg_begin = seg_size;
	int seg_end = seg_begin + seg_size;

	while( seg_begin < N ) {

		bool* is_prime = new bool[seg_size+1];
		memset(is_prime, true, sizeof(bool) * (seg_size+1) );
		is_prime[0] = false;

		for( int i = 0 ; i < simple_sieve_primes_count ; ++i ) {
			int prime_multiple_seg_begin = floor(seg_begin/primes[i]) * primes[i];
			if( prime_multiple_seg_begin < seg_begin )
				prime_multiple_seg_begin += primes[i];
			for( int j = prime_multiple_seg_begin; j <= seg_end ; j += primes[i] ) {
				is_prime[j-seg_begin] = false;
			}
		}

		printf("[DEBUG] Segmented Sieve Primes within (%d, %d]\n", seg_begin, seg_end);
		for( int i = 0 ; i <= seg_size ; ++i ) {
			if( is_prime[i] ) {
				primes.push_back(seg_begin+i);
				printf("%d, ", seg_begin+i);
			}
		}
		printf("\n");


		seg_begin = seg_end;
		seg_end = seg_begin + seg_size;
		if( seg_end > N ) seg_end = N;

		delete[] is_prime;
	}

	printf("[LOG] Prime numbers within (1,%d) are,\n", N);
	for( int i = 0 ; i < primes.size() ; ++i )
		printf("%d, ", primes[i]);
	printf("\n");

	return 0;
}
