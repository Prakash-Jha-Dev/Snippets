/// Name: AndrewHull
/// Description: Finds lower and upper hull of given set of points and combine them. Time :O(nlogn)
/// Detail: Convex Hull, Geometry, Maths
/// Guarantee: } // AndrewHull

typedef struct AndrewHull
{
	double y, x;
	int idx;
} point;

bool compare(point &p1, point &p2)
{
	return (p1.y < p2.y) || (p1.y == p2.y && p1.x < p2.x);
}

bool cross(point &o, point &a, point &b)
{
	return ((a.x - o.x) * (b.y - o.y) - (b.x - o.x) * (a.y - o.y)) <= 0;
}

void AndrewHull(auto &arr)
{
	sort(arr.begin(), arr.end(), compare);
	int n = arr.size();
	vector<point> hull(2 * n);
	int k = 0;

	for (int i = 0; i < n; i++)
	{
		while (k >= 2 && cross(hull[k - 2], hull[k - 1], arr[i]))
			k--;
		hull[k++] = arr[i];
	}

	int t = k + 1;
	for (int i = n - 2; i >= 0; i--)
	{
		while (k >= t && cross(hull[k - 2], hull[k - 1], arr[i]))
			k--;
		hull[k++] = arr[i];
	}

	hull.resize(k - 1);
	arr = hull;
} // AndrewHull