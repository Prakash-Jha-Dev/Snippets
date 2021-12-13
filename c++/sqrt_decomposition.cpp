/// Name: SQRTDecomposition
/// Description: Decomposes an array into several blocks of some size for efficient online range query
/// Detail: Data Structure, Range Query, Online Algorithm
/// Guarantee: } // SQRTDecomposition

// n : number of elements, q : number of queries
int n,q;
// block_size is size of each block in sqrt_decomposition and no_of_blocks is different blocks
int block_size=512, no_of_blocks=450;
// container to store element corresponding to each block
// NOTE: modify this as per question to perform operations easily
vector< vector< int > >block(no_of_blocks, vector< int >());
// input array
vector<int>arr;
 
// function to take the input and then decompose it into separate blocks
void pre()
{
	cin >> n;
	arr.resize(n);
	for(int i = 1; i<=n; i++) cin>>arr[i];

	for(int i=1;i<=n;i++)
	{
		// store the element in required block
		block[(i-1)/block_size].push_back(arr[i]);
	}
}

// function to update in range [l,r]
void update(int l, int r)
{
	int idx=(l-1)/block_size;

	// NOTE: template functions are gievn, change it as per requirement

	// update the block containing the lth element
	for(auto curr: block[idx])
	{
		if(curr <l) curr++;
		else if(curr >=l && curr<= r)
		{
			// work on these elements
		}
		else curr++;
	}

	// update the middle blocks
 	int idx2=(r-1)/block_size;
 	for(idx++; idx<idx2; idx++)
 	{
			// work on these blocks
 	}

	// update the block containing the rth element
	for(auto curr: block[idx])
	{
		if(curr <l) curr++;
		else if(curr >=l && curr<= r)
		{
			// work on these elements
		}
		else curr++;
	}
}
 
// function to get answer for range [l,r]
int get(int l, int r)
{
	int idx=(l-1)/block_size;

	// NOTE: template functions are gievn, change it as per requirement

	// get the answer from block containing the lth element
	for(auto curr: block[idx])
	{
		if(curr <l) curr++;
		else if(curr >=l && curr<= r)
		{
			// work on these elements
		}
		else curr++;
	}

	// get the answer from the middle blocks
 	int idx2=(r-1)/block_size;
 	for(idx++; idx<idx2; idx++)
 	{
 		// block[idx][y];
		// work on these block
 	}

	// get the answer from block containing the rth element
	for(auto curr: block[idx])
	{
		if(curr <l) curr++;
		else if(curr >=l && curr<= r)
		{
			// work on these elements
		}
		else curr++;
	}
}