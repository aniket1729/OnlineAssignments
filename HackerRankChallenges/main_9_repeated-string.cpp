/*
 * https://www.hackerrank.com/challenges/jumping-on-the-clouds
 */

#include <bits/stdc++.h>

using namespace std;

// Complete the repeatedString function below.
long repeatedString(string s, long n) {
    long substr_repeat;
    long extra_substr_len;
    long count_in_substr;
    long total_count;
    long i;

    //Base conditions
    if ( n == 0 || s.length() == 0 ) return 0;
    
    //Initialize
    substr_repeat = n / s.length();
    extra_substr_len = n % s.length();
    count_in_substr = 0;
    total_count = 0;

    for ( i = 0 ; i < s.length() ; i++ ) {
        if ( s[i] == 'a' ) {
            //Counting in Sub String
            count_in_substr++;

            //Accounting in Extra String
            if ( i < extra_substr_len )    total_count++;
        }

        if( substr_repeat == 0 && i >= extra_substr_len )    break;
    }

    //Accounting in Repeated Sub String
    total_count += (substr_repeat*count_in_substr);

    return total_count;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    long n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    long result = repeatedString(s, n);

    fout << result << "\n";

    fout.close();

    return 0;
}
