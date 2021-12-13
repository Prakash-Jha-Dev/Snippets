/// Name: FenwickTree3D
/// Description: Implementation of Binary Index Tree in 3 dimension
/// Detail: Data Structure, BIT, Range Query
/// Guarantee: } // FenwickTree3D


// grid stores original values
// tree stores summed values i.e BIT tree
lld grid[101][101][101];
lld tree[101][101][101];

void update(lld x,lld y1, lld z1, lld val,lld n)
{
    for(;x<=n;x+=(x&(-x)))
        for(lld y=y1;y<=n;y+=(y&(-y)))
            for(lld z=z1;z<=n;z+=(z&(-z)))
                tree[x][y][z]+=val;
}

lld get(lld x, lld y1, lld z1)
{
    lld ans=0;
    for(;x>0;x-=(x&-x))
        for(lld y=y1; y>0; y-=(y&-y))
            for(lld z=z1; z>0; z-=(z&(-z)))
                ans+=tree[x][y][z];
    return ans;
}

void reset()
{
    memset(grid,0,(101)*(101)*(101)*sizeof(long long int));
    memset(tree,0,(101)*(101)*(101)*sizeof(long long int));
}

lld get_3D(int x1, int y1, int z1, int x2, int y2, int z2)
{
    return (get(x2,y2,z2)-get(x2,y2,z1-1)-get(x2,y1-1,z2)-get(x1-1,y2,z2)+get(x2,y1-1,z1-1)+get(x1-1,y1-1,z2)+get(x1-1,y2,z1-1)-get(x1-1,y1-1,z1-1));
}