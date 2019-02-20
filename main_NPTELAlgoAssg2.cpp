/* 
 * The Siruseri Singing Championship
 *
 * https://onlinecourses.nptel.ac.in/noc19_cs11/progassignment?name=99
 *
 * Design and Analysis of Algorithms
 * Week 2 Programming Assignment
*/

#include <iostream>
using namespace std;

struct Singer {
    int m_iSeq;
    int m_iLowVocal;
    int m_iUpVocal;
    int m_iScore;
};

int compare_ascending_lowvocal(const Singer* pSinger1, const Singer* pSinger2) {
    return ( pSinger1->m_iLowVocal < pSinger2->m_iLowVocal );
}

int compare_ascending_sequence(const Singer* pSinger1, const Singer* pSinger2) {
    return ( pSinger1->m_iSeq < pSinger2->m_iSeq );
}

void swap_singer(Singer& singer1, Singer& singer2) {
    Singer temp = singer1;
    singer1 = singer2;
    singer2 = temp;
}

void quick_sort(Singer *arr_singers, int left, int right, int (*compare_asc_func)(const Singer*, const Singer*)) {
    Singer *pPivot;
    int afterL, afterH;

    /* at least 2 numbers to sort */
    if (left < right) {
        pPivot = &arr_singers[left];

        afterL = afterH = left+1;

        for( ; afterH <= right ; afterH++ ) {
            if( compare_asc_func(&arr_singers[afterH], pPivot) ) {
                /* swap afterL & afterH elements */
                if( afterL != afterH ) swap_singer(arr_singers[afterL], arr_singers[afterH]);
                afterL++;
            }
        }

        if( left != afterL-1 ) swap_singer(arr_singers[left], arr_singers[afterL-1]);

        quick_sort(arr_singers, left, afterL-2, compare_asc_func);
        quick_sort(arr_singers, afterL, right, compare_asc_func);

    }
}

void calculate_score(Singer *arr_singers, int size) {
    int i = 0;
    for ( i = 0 ; i < size ; i++ ) {
	arr_singers[i].m_iScore = (size-i-1)*2;
    }
}

void print_result(Singer *arr_singers, int size) {
    int i = 0;
    for ( i = 0 ; i < size ; i++ ) {
        cout << arr_singers[i].m_iScore << " ";
    }
    cout << endl;
}

void print_score(Singer *arr_singers, int size) {
    int i = 0;
    cout << "==== Scores ====" << endl;
    for ( i = 0 ; i < size ; i++ ) {
        cout << arr_singers[i].m_iScore << " ";
    }
    cout << endl << endl;
}

void print_singers(Singer *arr_singers, int size) {
    int i = 0;
    cout << "==== Singers ====" << endl;
    for ( i = 0 ; i < size ; i++ ) {
        cout << "[" << arr_singers[i].m_iSeq << " " << arr_singers[i].m_iLowVocal << " " << arr_singers[i].m_iUpVocal << " " << arr_singers[i].m_iScore << "] , ";
    }
    cout << endl << endl;
}

int main(void)
{
    Singer *arrSingers = NULL;
    int singer_count = 0;
    int i;

    cin >> singer_count;
    if ( singer_count <= 0 ) return -1;

    arrSingers = new Singer[singer_count];
    for( i = 0 ; i < singer_count ; i++ ) {
        cin >> arrSingers[i].m_iLowVocal >> arrSingers[i].m_iUpVocal;
        arrSingers[i].m_iSeq = i;
        arrSingers[i].m_iScore = 0;
    }
//    print_singers(arrSingers, singer_count);
//    print_score(arrSingers, singer_count);

    quick_sort(arrSingers, 0, singer_count-1, compare_ascending_lowvocal);
    calculate_score(arrSingers, singer_count);
//    print_singers(arrSingers, singer_count);

    quick_sort(arrSingers, 0, singer_count-1, compare_ascending_sequence);
//    print_singers(arrSingers, singer_count);
//    print_score(arrSingers, singer_count);
    
    print_result(arrSingers, singer_count);

    delete[] arrSingers;
    return 0;
}
