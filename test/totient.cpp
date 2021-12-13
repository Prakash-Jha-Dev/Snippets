#pragma comment(linker,"/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define FOR(i,s,n) for(auto i = s; i != n; i++)
#define FORR(i,s,n) for(auto i = n; i != s; i--)
#define MOD 1000000007
#include <bits/stdc++.h>
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
using namespace std;

template <typename T>
T totient(T num)
{
    T ans = num;
    for (T i = 2; i*i <= num; i++)
    {
        if(num%i == 0)
        {
            ans -= ans/i;
            while(num%i == 0) num /= i;
        }
    }
    if(num > 1) ans -= ans/num;
    return ans;
} // Totient


int main(int argc, char** argv)
{
    int test = 1;
    cin >> test;
    for(int kase = 1; kase <= test; kase++)
    {
        long long x;
        cin>>x;
        cout<<"Totient of "<<x<<" :: "<<totient(x)<<"\n";
    }
}