/// Name: PersistentSegmentTree
/// Description: Segment tree structure with persistence
/// Detail: Data Structure, Persistent, Segment Tree, Range Query
/// Guarantee: } // PersistentSegmentTree

struct Vertex
{
    Vertex *l, *r;
    int sum, mini, maxi;

    Vertex(int val) : l(nullptr), r(nullptr), sum(val), mini(val), maxi(val){};
    Vertex(Vertex *lp, Vertex *rp)
    {
        l = lp;
        r = rp;
        sum = 0;
        mini = INT_MAX;
        maxi = INT_MIN;

        if (l)
        {
            sum += l->sum;
            mini = min(mini, l->mini);
            maxi = max(maxi, l->maxi);
        }
        if (r)
        {
            sum += r->sum;
            mini = min(mini, r->mini);
            maxi = max(maxi, r->maxi);
        }
    }
};

Vertex *build(int *arr, int l, int r)
{
    if (l == r)
        return new Vertex(arr[l]);
    int mid = (l + r) >> 1;
    return new Vertex(build(arr, l, mid), build(arr, mid + 1, r));
}

int get_sum(Vertex *ptr, int beg, int end, int l, int r)
{
    if (l == beg && end == r)
        return ptr->sum;
    int mid = (beg + end) >> 1;
    if(l > mid) return get_sum(ptr->r, mid+1, end, l, r);
    if(r <= mid) return get_sum(ptr->l, beg, mid, l, r);
    return (get_sum(ptr->l, beg, mid, l, mid) + get_sum(ptr->r, mid + 1, end, mid + 1, r));
}

int get_min(Vertex *ptr, int beg, int end, int l, int r)
{
    if (l == beg && end == r)
        return ptr->mini;
    int mid = (beg + end) >> 1;
    if(l > mid) return get_min(ptr->r, mid+1, end, l, r);
    if(r <= mid) return get_min(ptr->l, beg, mid, l, r);
    return min(get_min(ptr->l, beg, mid, l, mid) , get_min(ptr->r, mid + 1, end, mid + 1, r));
}


int get_max(Vertex *ptr, int beg, int end, int l, int r)
{
    if (l == beg && end == r)
        return ptr->maxi;
    int mid = (beg + end) >> 1;
    if(l > mid) return get_max(ptr->r, mid+1, end, l, r);
    if(r <= mid) return get_max(ptr->l, beg, mid, l, r);
    return max(get_max(ptr->l, beg, mid, l, mid) , get_max(ptr->r, mid + 1, end, mid + 1, r));
}

Vertex *update(Vertex *ptr, int l, int r, int pos, int val)
{
    if (l == r && r == pos)
        return new Vertex(val);
    int mid = (l + r) >> 1;

    if (pos <= mid)
        return new Vertex(update(ptr->l, l, mid, pos, val), ptr->r);
    else
        new Vertex(ptr->l, update(ptr->r, mid + 1, r, pos, val));
} // PersistentSegmentTree