#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define FOR(i, s, n) for (auto i = s; i != n; i++)
#define FORR(i, s, n) for (auto i = n; i != s; i--)
#define MOD 1000000007
#include <bits/stdc++.h>
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
using namespace std;

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

int main(int argc, char **argv)
{
	vector<point> arr;
	arr.push_back({1, 1});
	arr.push_back({1, 5});
	arr.push_back({5, 5});
	arr.push_back({5, 1});
	arr.push_back({3, 3});

	AndrewHull(arr);
	FOR(i, 0, (int)arr.size())
		cout << arr[i].x << " " << arr[i].y << "\n";
}