/// Name: FenwickTree
/// Description: Implementation of Binary Index Tree
/// Detail: Data Structure, BIT, Range Query
/// Guarantee: } // FenwickTree

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
} // FenwickTree