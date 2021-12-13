#include <bits/stdc++.h>
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
using namespace std;

vector< int >ftree;
void build(vector<int>& arr)
{
    int uidx;
    ftree.assign(arr.size(),0);
    for(int i=1; i<arr.size(); i++)
    {
        ftree[i] += arr[i];
        uidx = i+(i&(-i));
        if(uidx < arr.size()) ftree[uidx] += ftree[i];
    }
}

void update(int idx, int change)
{
    while(idx < ftree.size())
    {
        ftree[idx] += change;
        idx += (idx&(-idx));
    }
}

int get(int idx)
{
    int ans = 0;
    while(idx)
    {
        ans += ftree[idx];
        idx -= idx&(-idx);
    }
    return ans;
}

int main(int argc, char **argv)
{
    int n;
    cin >> n;
    vector<int>A(n+1);
    for (int i = 1; i <= n; i++) cin>>A[i];
    build(A);
    for(int i=1; i<=n; i++) cout<<get(i)<<" "; cout<<"\n";
    update(5,10);
    for(int i=1; i<=n; i++) cout<<get(i)-get(i-1)<<" "; cout<<"\n";
}