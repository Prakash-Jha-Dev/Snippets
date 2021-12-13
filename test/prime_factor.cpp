#pragma comment(linker,"/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define FOR(i,s,n) for(auto i = s; i != n; i++)
#define FORR(i,s,n) for(auto i = n; i != s; i--)
#define MOD 1000000007
#include <bits/stdc++.h>
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
using namespace std;


// Print function prototype
template <typename T>
void print(const T data);

void print(const __int128_t data);

void print(const __uint128_t data);

template <typename T, typename U>
void print(const pair<T, U> data);

template <typename T>
void print(const deque<T> data);

template <typename T>
void print(const stack<T> data);

template <typename T>
void print(const queue<T> data);

template <typename T>
void print(const priority_queue<T> data);

template <typename T>
void print(const vector<T> data);

template <typename T>
void print(const set<T> data);

template <typename T>
void print(const multiset<T> data);

template <typename T, typename U>
void print(const map<T, U> data);

// Print functions
template <typename T>
void print(const T data)
{
    cout << data;
}

void print(const __int128_t data)
{
    cout << "int128:: ";
    bool negative = false;
    stack<int> temp;
    if (data == 0)
        temp.push(0);
    else
    {
        __int128_t _data = data;
        if (_data < 0)
        {
            negative = true;
            _data = -data;
        }
        while (_data)
        {
            temp.push(_data % 10);
            _data /= 10;
        }
    }
    if (negative)
        cout << "-";
    while (temp.size())
    {
        cout << temp.top();
        temp.pop();
    }
}

void print(const __uint128_t data)
{
    stack<int> temp;
    if (data == 0)
        temp.push(0);
    else
    {
        __uint128_t _data = data;
        while (_data)
        {
            temp.push(_data % 10);
            _data /= 10;
        }
    }
    while (temp.size())
    {
        cout << temp.top();
        temp.pop();
    }
}

template <typename T, typename U>
void print(const pair<T, U> data)
{
    print(data.first);
    cout << " : ";
    print(data.second);
}

template <typename T>
void print(const deque<T> data)
{
    cout << "<deque>{";
    for (T val : data)
    {
        print(val);
        cout << ", ";
    }
    cout << "}";
}

template <typename T>
void print(const stack<T> data)
{
    cout << "<stack>{";
    while (!data.empty())
    {
        T val = data.top();
        data.pop();
        print(val);
        cout << ", ";
    }
    cout << "}";
}

template <typename T>
void print(const queue<T> data)
{
    cout << "<queue>{";
    while (!data.empty())
    {
        T val = data.front();
        data.pop();
        print(val);
        cout << ", ";
    }
    cout << "}";
}

template <typename T>
void print(const priority_queue<T> data)
{
    cout << "<priority_queue>{";
    while (!data.empty())
    {
        T val = data.top();
        data.pop();
        print(val);
        cout << ", ";
    }
    cout << "}";
}

template <typename T>
void print(const vector<T> data)
{
    cout << "<vector>{";
    for (T val : data)
    {
        print(val);
        cout << ", ";
    }
    cout << "}";
}

template <typename T>
void print(const set<T> data)
{
    cout << "<set>{";
    for (T val : data)
    {
        print(val);
        cout << ", ";
    }
    cout << "}";
}

template <typename T>
void print(const multiset<T> data)
{
    cout << "<multiset>{";
    for (T val : data)
    {
        print(val);
        cout << ", ";
    }
    cout << "}";
}

template <typename T, typename U>
void print(const map<T, U> data)
{
    cout << "<map>{\n";
    for (pair<T, U> val : data)
    {
        print(val);
        cout << "\n";
    }
    cout << "}";
} // PrintFunctions



template <typename T>
vector< pair<T, int> > prime_factor(T num)
{
    vector< pair<T, int> >factors;
    for (T i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
        {
            factors.push_back({i, 0});
            while (num % i == 0)
            {
                num /= i;
                factors.back().second++;
            }
        }
    }
    if (num > 1)
        factors.push_back({num, 1});
    ;
    return factors;
} // PrimeFactor


int main(int argc, char** argv)
{
    int test = 1;
    cin >> test;
    for(int kase = 1; kase <= test; kase++)
    {
        long long x;
        cin>>x;
        auto z = prime_factor(x);
        print(z);
        cout<<"\n";
    }
}