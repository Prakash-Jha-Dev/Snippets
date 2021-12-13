#include <bits/stdc++.h>
using namespace std;

// structure of node in arr
typedef struct A_node
{
    int val;
    bool lazy_rem;
    int lazy_val;

    friend ostream &operator<<(ostream &out, A_node &x)
    {
        out << "Value : " << x.val << "\n";
        out << "Is pending update to child : " << x.lazy_rem << "\n";
        out << "Pending Value : " << x.lazy_val << "\n";
        cout << "\n";
    }
} anode;

vector<int> val;   // to store the initial values on which seg tree is built
vector<anode> arr; // to store the segment tree

// to build a segment tree with values from val vector
void build(int idx, int st, int ed)
{
    if (st == ed)
    {
        arr[idx].val = val[st];
        arr[idx].lazy_rem = false;
        return;
    }
    int mid = (st + ed) >> 1;
    build(idx << 1, st, mid);
    build(idx << 1 | 1, mid + 1, ed);

    // seg tree to give sum of values
    arr[idx].val = arr[idx << 1].val + arr[idx << 1 | 1].val;
    arr[idx].lazy_rem = false;
}

// to push updates to child before accessing them
void propogate_lazy(int idx, int st, int ed)
{
    // if not leaf, push the updates
    if (st != ed)
    {
        // if values are pending to be pushed to childs
        if (arr[idx].lazy_rem)
        {
            int mid = (st + ed) >> 1;
            // since all child the value x, sum becomes x*n
            arr[idx << 1].val = arr[idx].lazy_val * (mid - st + 1);
            arr[idx << 1].lazy_rem = true;

            arr[idx << 1 | 1].val = arr[idx].lazy_val * (ed - mid);
            arr[idx << 1 | 1].lazy_rem = true;

            arr[idx].lazy_rem = false;
        }
    }
    else
    {
        arr[idx].lazy_rem = false;
    }
}

// to query segment in range [l...r]
// for given tree, sum of values of vertices lying in range
int query(int idx, int st, int ed, int l, int r)
{
    // if current section lies completely in range, return the value directly
    if (l <= st && ed <= r)
        return arr[idx].val;
    propogate_lazy(idx, st, ed);
    int mid = (st + ed) >> 1;
    if (mid >= r)
        return query(idx << 1, st, mid, l, r);
    if (mid < l)
        return query(idx << 1 | 1, mid + 1, ed, l, r);
    return query(idx << 1, st, mid, l, mid) + query(idx << 1 | 1, mid + 1, ed, mid + 1, r);
}

// to update the value of vertexes in range [l...r]
void update(int idx, int st, int ed, int l, int r, int val)
{
    // placing it before new update, in case updates cannot be merged (often they can be merged tho.)
    propogate_lazy(idx, st, ed);
    if (l <= st && ed <= r)
    {
        arr[idx].val = val * (r - l + 1);
        arr[idx].lazy_rem = true;
        arr[idx].lazy_val = val;
        return;
    }
    int mid = (st + ed) >> 1;
    if (mid >= r)
        update(idx << 1, st, mid, l, r, val);
    else if (mid < l)
        update(idx << 1 | 1, mid + 1, ed, l, r, val);
    else
    {
        update(idx << 1, st, mid, l, mid, val);
        update(idx << 1 | 1, mid + 1, ed, mid + 1, r, val);
    }
    arr[idx].val = arr[idx << 1].val + arr[idx << 1 | 1].val;
}

int main()
{
    int n;
    cin >> n;

    val.resize(n);
    for (int i = 0; i < n; i++)
        cin >> val[i];

    arr.resize(4*n);
    build(1, 0, n - 1);

    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++)
            cout << query(1, 0, n - 1, i, j) << " : " << i << " " << j << "\n";
    cout << "\n";

    update(1, 0, n - 1, 3, 6, 10);

    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++)
            cout << query(1, 0, n - 1, i, j) << " : " << i << " " << j << "\n";
    cout << "done\n";
}

// 10
// 1 2 3 4 5 6 7 8 9 10
