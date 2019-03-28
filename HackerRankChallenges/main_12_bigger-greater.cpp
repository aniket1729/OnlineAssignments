/*
 * https://www.hackerrank.com/challenges/bigger-is-greater/problem
*/

#include <bits/stdc++.h>

using namespace std;

// Complete the biggerIsGreater function below.
string biggerIsGreater(string w)
{
    int i = w.length() - 1;
    while ( i > 0 && w[i - 1] >= w[i] ) /* Bigger is already at higher position */
    {
        i--;
    }

    if( i == 0 )    /* Possible bigger at higher positions */
        w = "no answer";
    else    /* (i-1) is Lower than i */
    {
        int j = w.length() - 1;
        while ( w[j] <= w[i-1] )
        {
            j--;
        }
        char temp = w[j];
        w[j] = w[i-1];
        w[i-1] = temp;

        j = w.length() - 1;
        while( i < j )
        {
            temp = w[j];
            w[j] = w[i];
            w[i] = temp;

            i++;
            j--;
        } 

    }

    return w;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int T;
    cin >> T;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int T_itr = 0; T_itr < T; T_itr++) {
        string w;
        getline(cin, w);

        string result = biggerIsGreater(w);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}
