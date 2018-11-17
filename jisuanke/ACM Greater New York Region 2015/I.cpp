/*
 * @Samaritan_infi
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

#define PII pair<int, int>
#define fi first
#define se second
#define mp make_pair

bool cmp (int a, int b) {
    return a > b;
}
int arr[200], brr[200];

set <string> pq;
string last;
/// > return true
bool check_ (string a, string b) {
    if (a.length() > b.length()) return true;
    for (int i = 0; i < a.length(); ++i) {
        if (a[i] > b[i]) return true;
        else if (a[i] < b[i]) return false;
    }
    return true;
}
vector<PII> pp;
bool check (string a) {
    pp.clear();
    int siz = 1;
    for (int i = 1; i < a.length(); ++i) {
        if (a[i] == a[i-1]) {
            siz++;
        } else {
            pp.push_back(mp(a[i-1]-'0', siz));
            siz = 1;
        }
    }
    pp.push_back(mp(a[a.length()-1]-'0', siz));

    if (pp.size() == 3) {
        if (pp[0].fi == 5 && pp[0].se == 2 && pp[1].fi == 6 && pp[1].se >= 2 && pp[2].fi == 7 && pp[2].se == 4)
            return true;
        return false;
    } else if (pp.size() == 4) {
        if (pp[0].fi == 1 && pp[0].se == 1 && pp[1].fi == 2 && pp[1].se == 1 && pp[2].fi == 3 && pp[2].se >= 2
            && pp[3].fi == 4 && pp[3].se == 4)
            return true;
        return false;
    } else
        return false;
}

int cal (int n) {
//    cout << n << " ";
    for (int i = n + 1; i <= 100; ++i) arr[i] = 0;
    memset(brr, 0, sizeof brr);
    for (int i = 1; i <= n; ++i)
        brr[n-i+1] = arr[i];
    int carry, sum;
    for (int j = 1; j <= n; j++) {
        sum = brr[j]+arr[j];
        carry = sum/10;
        arr[j] = sum%10;
        arr[j+1] += carry;
    }
    if (arr[n+1]) n++, arr[n] = 1;

//    cout << "origin : ";
//    for (int i = n ; i >= 1; i--) {
//        printf("%d", arr[i]);
//    }puts("");

    sort(arr + 1, arr+n+1, cmp);
    for (int i = n; i >= 1; i--) {
        if (! arr[i]) n--;
        else break;
    }
    string str = "";
    for (int i = n; i >= 1; --i) str += (arr[i] + '0');
    //cout << str << endl;
    //if (dizeng && check(str, last) == false) dizeng = false, cout << last << "\n" << str << endl;
    if (check(str)) return -2;
    if (pq.count(str)) return -1;
    last = str;
    pq.insert(str);
    return n;
}

char crr[200];
int main () {
    //freopen("in.txt", "r", stdin);
    int _ = 1;
    int kase; scanf("%d", &kase); while (kase--) {
//        cout << "start " << _++ << endl;
        int n; int m, p;
        pq.clear();
        scanf("%d %d %s", &n, &m, crr);
        int q = p;
        memset(arr, 0, sizeof arr);
        int len = strlen(crr);
        for (int i = 1; i <= len; ++i) {
            arr[i] = crr[len-i] - '0';
        }
        sort (arr + 1, arr + 1 + len, cmp);

        //while (arr[len] == 0) len--;
        //for (int i = 1; i <= len; ++i) printf("%d", arr[i]); puts("");
        bool flag = false;
        last = "";
        //cout << len << endl;
        string str = "";
        for (int i = len; i >= 1; --i) str += (arr[i] + '0');
        pq.insert(str);
        last = str;
        if (check(last)) {
            printf("%d %c %d\n", n, 'C', 1);
            continue;
        }
        for (int i = 2; i <= m; ++i) {
            //cout << i << " ";
            len = cal(len);

            if (len == -1) {
                printf("%d %c %d\n", n, 'R', i);
                flag = true;
                break;
            } else if (len == -2) {
                printf("%d %c %d\n", n, 'C', i);
                flag = true;
                break;
            }
        }
        if (flag) continue;
        printf("%d ", n);
        cout << last << endl;

    }
    return 0;
}
/*
1 R 10
2 C 20
3 666677888
4 C 8
5 R 11
6 1111123
7 R 29
8 R 9
*/
