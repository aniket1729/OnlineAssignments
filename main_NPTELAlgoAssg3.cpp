/*
 * Prisoner Escape
 *
 * https://onlinecourses.nptel.ac.in/noc19_cs11/progassignment?name=102
 *
 * Design and Analysis of Algorithms
 * Week 3 Programming Assignment
*/

#include <cstring>
#include <cmath>
#include <queue>
#include <iostream>
using namespace std;

struct Point {
    int m_LocX;
    int m_LocY;

    int dist(const Point& pt) {
        return sqrt( pow((m_LocX-pt.m_LocX), 2) + pow((m_LocY-pt.m_LocY), 2) );
    }
};


void print_army(Point *arr_army, int size) {
    int i = 0;
    cout << "==== Soldiers ====" << endl;
    for( i = 0 ; i < size ; i++ ) {
        cout << i << ":[" << arr_army[i].m_LocX << " " << arr_army[i].m_LocY << "] , ";
    }
    cout << endl << endl;
}

struct AdjecencyList {
    int m_NodeCount;
    int *m_arr_AdjIndex;

    AdjecencyList() {
        m_NodeCount = 0;
        m_arr_AdjIndex = NULL;
    }
    ~AdjecencyList() {
        m_NodeCount = 0;
        if( m_arr_AdjIndex ) { m_arr_AdjIndex = NULL;    delete[] m_arr_AdjIndex; }
    }

    void add_adj(int node_number) {
        if( m_arr_AdjIndex ) { m_arr_AdjIndex[m_NodeCount++] = node_number; }
    }
};
void init_adj_list(AdjecencyList *arr_adj_list, int size) {
    int i;
    for( i = 0 ; i < size ; i++ ) {
        arr_adj_list[i].m_arr_AdjIndex = new int[size];
        memset(arr_adj_list[i].m_arr_AdjIndex, 0, sizeof(int)*size);
    }
}

void print_adj_list(AdjecencyList *arr_adj_list, int size) {
    int i, j;
    cout << "==== AdjecencyList ====" << endl;
    for( i = 0 ; i < size ; i++ ) {
        cout << i << " -> [";
        for( j = 0 ; j < arr_adj_list[i].m_NodeCount ; j++ ) {
            cout << arr_adj_list[i].m_arr_AdjIndex[j] << ",";
        }
        cout << "]" << endl;
    }
}

int is_path_bet_walls(AdjecencyList *arr_adj_list, int size) {
    int ret = 0;
    int i, j, k;
    queue<int> q_bfs;
    int *p_visited = NULL;

    p_visited = new int[size];
    memset(p_visited, 0, sizeof(int)*size);


    i = size-2;    /* Node for bottom wall */
    if( arr_adj_list[i].m_NodeCount == 0 ) return 0;
    p_visited[i] = 1;
    q_bfs.push(i);

    while( !q_bfs.empty() ) {
        j = q_bfs.front();
        q_bfs.pop();
        for( i = 0 ; i < arr_adj_list[j].m_NodeCount ; i++ ) {
            k = arr_adj_list[j].m_arr_AdjIndex[i];

            if( p_visited[k] == 0 ) {
                if( k == size-1 )    { ret = 1; break; }    /* Node for top wall */
                p_visited[k] = 1;
                q_bfs.push(k);
            }
        }
    }

    delete[] p_visited;

    return ret;
}

int main() {
    int canyon_len, canyon_wid, army_count;
    int i, j;
    Point *arr_army = NULL;
    AdjecencyList *arr_adj_list = NULL;

    cin >> canyon_len >> canyon_wid >> army_count;

    arr_army = new Point[army_count];
    arr_adj_list = new AdjecencyList[army_count +2];    /* LAST 2 for canyon walls */

    for( i = 0 ; i < army_count ; i++ ) {
        cin >> arr_army[i].m_LocX >> arr_army[i].m_LocY;
    }

    init_adj_list(arr_adj_list, army_count +2);

    for( i = 0 ; i < army_count ; i++ ) {
        for( j = i+1 ; j < army_count ; j++ ) {
            if( arr_army[i].dist(arr_army[j]) <= 200 ) {    /* army range is 100 , so range of i & j overlap */
                arr_adj_list[i].add_adj(j);
                arr_adj_list[j].add_adj(i);
            }
        }

        if( arr_army[i].m_LocY <= 100 ) {    /* army i is closer to bottom wall */
            arr_adj_list[i].add_adj(army_count);
            arr_adj_list[army_count].add_adj(i);
        }
        if( canyon_wid-100 <= arr_army[i].m_LocY ) {    /* army j is closer to top wall */
            arr_adj_list[i].add_adj(army_count+1);
            arr_adj_list[army_count+1].add_adj(i);
        }
    }

//    print_army(arr_army, army_count);
//    print_adj_list(arr_adj_list, army_count +2);

    cout << is_path_bet_walls(arr_adj_list, army_count +2) << endl;    /* result output, 0: prisoner can run away, 1: no */

    delete[] arr_army;
    delete[] arr_adj_list;

    return 0;
}
