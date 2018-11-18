#include <bits/stdc++.h>
using namespace std;
char op[] = "LURD";
int main () {
    for (int i = 0; i < 50000; ++i)
        printf("%c", op[rand() % 4]);
    return 0;
}
