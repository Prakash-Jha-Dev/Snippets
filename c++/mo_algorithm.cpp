/// Name: MoAlgorithm
/// Description: Offline algorithm to store queries and then process them in specific order on an array
/// Detail: Offline Algorthm, Range Query, Mo's Algo
/// Guarantee: } // MoAlgorithm

// NOTE : A tree can be converted in array when queries are on subtree, using euler tour

// N : Input array size
// Q : Number of queries
int N, Q;

// to store answer of each Query
vector< long long > answers;
// current answer, updated as per move in mo's algo
long long current_answer;
// NOTE: required count array to solve the sample problem i.e. freq of element in given subsegment
#define MAX_ELEMNENT = 100;
vector< long long >cnt(MAX_ELEMNENT);

// size to determine in which block a query lie. Normally 2*sqrt(N) is good
int BLOCK_SIZE;
// Input array
vector< int >arr;
// struct to store query info
struct Query_Struct
{
    int l,r,idx;
}
// container to store all queries for offline processing
vector<Query_Struct>queries; 
inline bool mo_cmp(const Query_Struct &x,const Query_Struct &y)
{
    int block_x = x.l / BLOCK_SIZE;
    int block_y = y.l / BLOCK_SIZE;
    if (block_x != block_y)
        return block_x < block_y;
    return x.r < y.r;
}

// function to simulate how answer changes when adding a value
// NOTE: this should be changed to do the required when adding a pos from some array
// as per sample ques, arr[pos] = x and hence work is done on freq[x] as per ques
inline void add(int x)
{
    current_answer -= cnt[x] * cnt[x] * x;
    cnt[x]++;
    current_answer += cnt[x] * cnt[x] * x;
}

// function to simulate how answer changes when removing a value
// NOTE: this should be changed to do the required when removing a pos from some array
// as per sample ques, arr[pos] = x and hence work is done on freq[x] as per ques
inline void remove(int x)
{
    current_answer -= cnt[x] * cnt[x] * x;
    cnt[x]--;
    current_answer += cnt[x] * cnt[x] * x;
}

void MoAlgorithm()
{
    cin >> N >> Q;
    BLOCK_SIZE = 2*sqrt(N);

    // initialize current_answer
    current_answer = 0;

    // resize array to fit new size
    arr.resize(N);
    queries.resize(Q);
    answers.resize(Q);

    // Read input array
    for (int i = 0; i < N; i++)
        cin >> arr[i];

    // Read input queries, which are 0-indexed. Store each query's
    // original position. We will use it when printing answer.
    for (int i = 0; i < Q; i++)
    {
        cin >> queries[i].l >> queries[i].r;
        queries[i].idx = i;
    }

    sort(queries.begin(), queries.end(), mo_cmp);

    int mo_left = 0, mo_right = -1;

    for (int i = 0; i < Q; i++)
    {
        // [left, right] is what query we must answer now.
        int left = queries[i].l;
        int right = queries[i].r;

        // Usual part of applying Mo's algorithm: moving mo_left
        // and mo_right.
        while (mo_right < right)
        {
            mo_right++;
            add(arr[mo_right]);
        }
        while (mo_right > right)
        {
            remove(arr[mo_right]);
            mo_right--;
        }

        while (mo_left < left)
        {
            remove(arr[mo_left]);
            mo_left++;
        }
        while (mo_left > left)
        {
            mo_left--;
            add(arr[mo_left]);
        }

        answers[queries[i].idx] = current_answer;
    }
} // MoAlgorithm