/**
 * @Samaritan
 */
//#include <bits/stdc++.h>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <iostream>
#include <cmath>
#include <stack>
using namespace std;
typedef long long LL;

const int N = 1e2 + 5;
const int M = 1e4 + 5;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;

string str;
ios::sync_with_stdio(false);
getline(cin, str);

void split (string s, vector <string> & arr, string c) {
    string::size_type pos_l = 0, pos_r = 0;
    pos_r = s.find(c);
    while (string::npos != pos_r) {
        arr.emplace_back(s.substr(pos_l, pos_r - pos_l));
        pos_l = pos_r + c.size();
        pos_r = s.find(c, pos_l);
    }
    if (pos_l != s.size())
        arr.emplace_back(s.substr(pos_l));

    for (string str : arr)
        cout << str << endl;
}


char arr[N][20];
int main () {
    stack <double> num;
    int cnt = 0;
    while (~ scanf("%s", arr[cnt++])) {
    }

    for (int i = cnt - 2; i >= 0; --i) {
        if (arr[i][0] >= '0' && arr[i][0] <= '9') {
            num.push(atof(arr[i]));
            //cout << arr[i] << endl;
        } else {
            // op.push(arr[0]);
            double a = num.top(); num.pop();
            double b = num.top(); num.pop();
            char now_op = arr[i][0];
            //cout << a << " " << b << " " << now_op << endl;
            switch (now_op) {
                case '+':
                    a += b;
                    break;
                case '-':
                    a -= b;
                    break;
                case '*':
                    a *= b;
                    break;
                case '/':
                    a /= b;
                    break;
            }
            num.push(a);
        }
    }
    printf("%f\n", num.top());
    return 0;
}
