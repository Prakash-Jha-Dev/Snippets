/// Name: CountInversion
/// Description: Merge Sort based approach to count pairs(i,j) such that i<j and a[i]>a[j]
/// Detail: Merge Sort, Maths, Inversion Count
/// Guarantee: } // CountInversion

long long count_inversion(vector<int>&arr, int st, int end)
{
    if(end - st <= 1) return 0;
    long long inv = 0;
    int m = (st + end)/2;
    inv += count_inversion(arr, st, m);
    inv += count_inversion(arr, m, end);
    int j=0,it=st,bt=m;
    vector< int >temp(end - st);
    while(it < m && bt < end)
    {
        if(arr[it] < arr[bt])
        {
            inv += (bt - m);
            temp[j++] = arr[it++];
        }
        else
        {
            temp[j++] = arr[bt++];
        }
    }
    while(it < m) temp[j++] = arr[it++], inv += (bt - m);;
    while(bt < end) temp[j++] = arr[bt++];
    for(j=0; j< temp.size(); j++) arr[st+j] = temp[j];
    return inv;
} // CountInversion