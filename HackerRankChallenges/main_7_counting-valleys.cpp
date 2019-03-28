/*
 * https://www.hackerrank.com/challenges/counting-valleys
 */

#include <bits/stdc++.h>

using namespace std;

// Complete the countingValleys function below.
int countingValleys(int n, string s) {
    int valley_count = 0;
    int from_sealevel = 0;

    for(auto step : s) {

        if( step == 'U') {
            from_sealevel++;
            if (from_sealevel == 0)    valley_count++;
        }
        else if( step == 'D') {
            from_sealevel--;
        }
    }

    return valley_count;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string s;
    getline(cin, s);

    int result = countingValleys(n, s);

    fout << result << "\n";

    fout.close();

    return 0;
}
