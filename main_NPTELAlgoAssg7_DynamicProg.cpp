/*
 * Best Segement from sequence of N dropping upto K elements
 *
 * https://onlinecourses.nptel.ac.in/noc19_cs11/progassignment?name=121
 *
 * Design and Analysis of Algorithms
 * Week 7 Programming Assignment
*/

#include <iostream>
using namespace std;

#define MAX(x,y) ((x) > (y) ? (x) : (y))

#define DEBUG 0

/*
 * Best[n][k] => max sum of n elements dropping k elements from it
 *
 *
 *
 * Best[n][k] = MAX FROM "k drops in previous segment + current element" OR "k-1 drops in previous segment & drop current element as kth drop"
 * Best[n][k] = max( Best[n-1][k] + ele[n] , Best[n-1][k-1])    <<<< Inductive Formula
 *
 * Best[n][0] = Best[n-1][0] + ele[n]    <<<< Boundary Case
 *
 * Best[0][0] = 0    <<<< Base Case
 *
 *
 *
 * Computing Best[ ][0 ... k] will require Best[ ][0 ... (k-1)]    <<<< Directed Graph
 *
*/
int get_best_segment_sum(int elements[], int& N, int& K) {
    if( K < 0 )    K = 0;
    if( K > N )    K = N;    /* Limiting K drops within N */

    int* pre_best = new int[K+1];
    int* cur_best = new int[K+1];
    int* temp_best = NULL;
    int max_best = 0;
    int max_flag = 0;
    int i, j;

    for( j = 0 ; j <= K ; j++ )
        pre_best[j] = 0;    /* Base Case */

#if DEBUG
    cout << "N= " << N << " K= " << K << endl;
    cout << "Elements    ";
    for( i = 0 ; i < N ; i++ ) {
        cout << (i+1) << " ";
    }
    cout << endl;
    cout << "            ";
    for( i = 0 ; i < N ; i++ ) {
        cout << elements[i] << " ";
    }
    cout << endl;
#endif


    for( i = 0 ; i < N ; i++ ) {

        cur_best[0] = pre_best[0] + elements[i];    /* Boundary Case */

        for( j = 1 ; j <= K ; j++ ) {
            cur_best[j] = MAX( (pre_best[j] + elements[i]) , pre_best[j-1] );    /* Inductive Formula */
        }

        if( max_flag ) {
            max_best = MAX( max_best , cur_best[K] );
        } else {
            max_flag = 1;
            max_best = cur_best[K];
        }

#if DEBUG
        cout << "Elements " << (i+1) << ": ";
        for( j = 0 ; j <= K ; j++ ) {
            cout << cur_best[j] << " ";
        }
        cout << endl << " max= " << max_best << endl;
#endif

        temp_best = pre_best;
        pre_best = cur_best;
        cur_best = temp_best;
    }

    delete[] pre_best;
    delete[] cur_best;
    return max_best;
}

int main(int argc, char** argv) {
    int N, K;
    int i;
    int* elements = NULL;

    cin >> N >> K;
    elements = new int[N];
    for( i = 0 ; i < N ; i++ )
        cin >> elements[i];

    if( N > 0 )
        cout << get_best_segment_sum(elements, N, K) << endl;
    else
        cout << endl;

    delete[] elements;
    return 0;
}
