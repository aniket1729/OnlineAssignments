/*
 * https://www.hackerrank.com/challenges/new-year-chaos
 */

#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the minimumBribes function below.
void minimumBribes(vector<int> q) {
  vector<int> bribes(q.size(), 0);
  int s_pos = 0, e_pos = q.size()-1;
  int choatic = 0;
  int sum_bribes = 0;

  for (int i = s_pos ; i <=  e_pos ; ) {
      if( i == q[i]-1 )
      {
          s_pos++;
          i++;
          continue;
      }
      
      //Pushing Max at end
      for (int j = s_pos; j+1 <= e_pos ; j++) {
        if ( q[j] > q[j+1])
        {
            bribes[ q[j]-1 ]++;
            if( bribes[ q[j]-1 ] > 2 )
            {                
                choatic = 1;
                cout << "Too chaotic" << endl;
                return;
            }
            sum_bribes++;

            auto temp = q[j];
            q[j] = q[j+1];
            q[j+1] = temp;            
        }
    }
    e_pos--;
  }

  if (choatic)
    cout << "Too chaotic" << endl;
  else
    cout << sum_bribes << endl;

}

int main()
{
    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string q_temp_temp;
        getline(cin, q_temp_temp);

        vector<string> q_temp = split_string(q_temp_temp);

        vector<int> q(n);

        for (int i = 0; i < n; i++) {
            int q_item = stoi(q_temp[i]);

            q[i] = q_item;
        }

        minimumBribes(q);
    }

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
