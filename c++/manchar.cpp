/// Name: Manchar
/// Description: Longest Palindromic substring from each position of string
/// Detail: String, Palindrome
/// Guarantee: } // Manchar

template <class Iterator>
vector<int> manchar(Iterator first, Iterator last)
{
	// considering the symbol set is finite and represenatble in integer domain
	// covers all char, int
	// using INT_MAX as separator
	vector<int> s(1, INT_MAX);
	while (first != last)
	{
		s.push_back(*first);
		s.push_back(INT_MAX);
		first++;
	}

	vector<int> P(s.length(), 0);
	int center = 0, right = -1, radius;

	for (int i = 0; i < s.length(); i++)
	{
		if (i <= right)
			radius = min(P[2 * center - i], right - i);
		else
			radius = 0;

		while (i + radius < s.length() && i - radius >= 0 && s[i + radius] == s[i - radius])
			radius++;

		P[i] = radius;
		if (i + radius - 1 > right)
		{
			center = i;
			right = i + radius - 1;
		}
	}
	for (int i = 0; i < s.length(); i++)
	{
		if (i & 1)
			P[i] = (P[i] - 1);
		else
			P[i] = (P[i] - 1);
	}

	// returns the max size of palindrome starting at index i
	// NOTE: indexing is 1 based..
	// max_size includes dummy # values
	return P;
} // Manchar