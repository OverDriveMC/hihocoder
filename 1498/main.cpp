#include <iostream>

using namespace std;

int main(){
    int64_t n;
    int64_t q;
    cin >> n >> q;
    int64_t m = 1;
    int64_t r = 0;
    while(n > 2*m*q){
        m = m << 1;
        r++;
    }
    int64_t t = q*r + n/m;
    if (n % m != 0)
        t += 1;
    cout << t;

    return 0;
}

