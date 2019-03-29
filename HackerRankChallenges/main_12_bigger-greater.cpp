/*
 * https://www.hackerrank.com/challenges/bigger-is-greater
 */

#include <bits/stdc++.h>

using namespace std;

// Complete the biggerIsGreater function below.
string biggerIsGreater(string w)
{
    int i = w.length() - 1;
    while ( i > 0 && w[i - 1] >= w[i] )    /* Bigger is already at higher position: Loop to check if Greater (higher Alphabetical order) possible */
    {
        i--;
    }

    if( i == 0 )    /* Possible biggers at higher positions: No Greater possible */
        w = "no answer";
    else            /* (i-1) is Lower than i : Yes a Greater possible*/
    {
        int j = w.length() - 1;
        while ( w[j] <= w[i-1] )    /* Looking for 1st character to be placed at right position for Greater */
        {
            j--;
        }
        char temp = w[j];           /* 1st replacement for Greater */
        w[j] = w[i-1];
        w[i-1] = temp;

        j = w.length() - 1;
        while( i < j )              /* Rest all character in alphabetical order to complete Greater */
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
