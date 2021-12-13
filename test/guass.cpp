#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define FOR(i, s, n) for (auto i = s; i != n; i++)
#define FORR(i, s, n) for (auto i = n; i != s; i--)
#define MOD 1000000007
#include <bits/stdc++.h>
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
using namespace std;

vector<vector<double>> A;
vector<double> B;

// solve A[equations][variables]*x[] = B[]
int guass(vector<vector<double>> &A, vector<double> &B, vector<double> &sol)
{
    /**
     * returns : 0 if no solution
     *           1 if unique solution
     *           2 if infinite solutions
    */

    int n = A.size();
    int m = A[0].size();
    // number of equations > number of variables
    if (m > n)
        return 2;

    // reduce for each variable using one equation
    for (int i = 0; i < m; i++)
    {
        int idx = i;
        for (int j = i + 1; j < n; j++)
            if (abs(A[j][i]) > abs(A[idx][i]))
                idx = j;
        swap(A[idx], A[i]);

        // Number of equation redues since this equation can be obtained from other equations.
        if (A[i][i] == 0)
            return 2;
        // transform remaining equations to have ith co-eff as 0
        for (int j = i + 1; j < n; j++)
        {
            // change co-effiecient of all terms of equation
            double ch = A[j][i] / A[i][i];
            for (int k = i; k < m; k++)
            {
                A[j][k] -= ch * A[i][k];
            }
            B[j] -= ch * B[i];
        }
    }

    sol.resize(m);
    // find unique solution
    for (int i = m - 1; i >= 0; i--)
    {
        double temp = B[i];
        for (int j = i + 1; j < m; j++)
            temp -= A[i][j] * sol[j];
        sol[i] = temp / A[i][i];
    }

    // check for consistency
    for (int i = m; i < n; i++)
    {
        if (B[i] - A[i][m - 1] * sol[m - 1] > 1e6)
            return 0;
    }
    return 1;
}

int main(int argc, char **argv)
{

    // n - variables and m equations
    int n, m;
    cin >> n >> m;

    assert(n <= m);

    A.resize(m);
    B.resize(m);
    for (int i = 0; i < m; i++)
        A[i].resize(n);
    for (int i = 0; i < n; i++)
    {
        // input A[i][j] .... = B[i]
        for (int j = 0; j < m; j++)
        {
            cin >> A[i][j];
        }
        cin >> B[i];
    }

    vector<double> X;
    guass(A, B, X);
    for (auto x : X)
        cout << x << " ";
}