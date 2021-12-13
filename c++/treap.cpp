/// Name: ImplicitTreap
/// Description: Data Structure with insert,delete or perform operation on continous segment in log(n)
/// Detail: Data Structure, Binary Tree Heap, Cartesian tree, Treap
/// Guarantee: } // ImplicitTreap

// NOTE : this implementation assumes the index as key  (Implicit Treap and Not Treap)
// the sorting by (priority,key) hence results only in sorting by priority
// as merging as (left,node) or (node,right) ensured order by key i.e.(implicit key) index
#define randint(x, y) uniform_int_distribution<int>(x, y)(rng)
typedef struct node
{
    int prior, size, val, sum, lazy, rev;
    struct node *l, *r;
} node;
typedef node *pnode;

int sz(pnode t)
{
    return t ? t->size : 0;
}

void upd_sz(pnode t)
{
    if (t)
        t->size = sz(t->l) + 1 + sz(t->r);
}

void lazy(pnode t)
{
    if (!t || !t->lazy)
        return;
    t->val += t->lazy; //operation of lazy
    t->sum += t->lazy * sz(t);
    if (t->l)
        t->l->lazy += t->lazy; //propagate lazy
    if (t->r)
        t->r->lazy += t->lazy;
    t->lazy = 0;
}

void reset(pnode t)
{
    if (t)
        t->sum = t->val; //lazy already propagated
}

void combine(pnode &t, pnode l, pnode r)
{ //combine segtree ranges
    if (!l || !r)
        return void(t = l ? l : r);
    t->sum = l->sum + r->sum;
}

void reverse(pnode t)
{
    if (t && t->rev)
    {
        swap(t->l, t->r);
        if (t->l)
            t->l->rev ^= true;
        if (t->r)
            t->r->rev ^= true;
        t->rev = false;
    }
}

void operation(pnode t)
{ //operation of segtree
    if (!t)
        return;
    reset(t); //node represents single element of array
    lazy(t->l);
    lazy(t->r); //imp:propagate lazy before combining l,r
    combine(t, t->l, t);
    combine(t, t, t->r);
}

void split(pnode t, pnode &l, pnode &r, int pos, int add = 0)
{
    if (!t)
        return void(l = r = NULL);
    lazy(t);
    reverse(t);
    int curr_pos = add + sz(t->l);
    if (curr_pos <= pos)
        split(t->r, t->r, r, pos, curr_pos + 1), l = t;
    else
        split(t->l, l, t->l, pos, add), r = t;
    upd_sz(t);
    operation(t);
}

void merge(pnode &t, pnode l, pnode r)
{
    lazy(l);
    lazy(r);
    reverse(l);
    reverse(r);
    if (!l || !r)
        t = l ? l : r;
    else if (l->prior > r->prior)
        merge(l->r, l->r, r), t = l;
    else
        merge(r->l, l, r->l), t = r;
    upd_sz(t);
    operation(t);
}

pnode init(int val)
{
    pnode ret = (pnode)malloc(sizeof(node));
    ret->l = ret->r = NULL;
    ret->prior = randint(1, INT_MAX);
    ret->size = 1;
    ret->val = val;
    ret->sum = val;
    ret->lazy = 0;
    ret->rev = 0;
    return ret;
}

// 1-based index
void insert(pnode &t, int pos, int val)
{
    if (!t)
    {
        t = init(val);
        return;
    }
    pos--;
    pnode L, R, newNode = init(val);
    split(t, L, R, pos - 1);
    merge(L, L, newNode);
    merge(t, L, R);
}

void erase(pnode &t, int pos)
{
    pnode L, mid, R;
    split(t, L, mid, pos - 1);
    split(mid, t, R, 1);
    merge(t, L, R);
}

int range_query(pnode t, int l, int r)
{ //[l,r]
    pnode L, mid, R;
    split(t, L, mid, l - 1);
    split(mid, t, R, r - l); //note: r-l!!
    int ans = t->sum;
    merge(mid, L, t);
    merge(t, mid, R);
    return ans;
}

void range_update(pnode t, int l, int r, int val)
{ //[l,r]
    pnode L, mid, R;
    split(t, L, mid, l - 1);
    split(mid, t, R, r - l); //note: r-l!!
    t->lazy += val;          //lazy_update
    merge(mid, L, t);
    merge(t, mid, R);
}

void range_reverse(pnode &t, int l, int r)
{ //[l,r]
    pnode L, mid, R;
    split(t, L, mid, l - 1);
    split(mid, t, R, r - l); //note: r-l!!
    t->rev ^= true;
    merge(mid, L, t);
    merge(t, mid, R);
}

void print(pnode t, int idx = 0)
{
    if (!t)
        return;
    lazy(t);
    reverse(t);

    int curr_pos = idx + sz(t->l);
    print(t->l, idx);
    cout << t->val << " ";
    print(t->r, curr_pos + 1);
} // ImplicitTreap
