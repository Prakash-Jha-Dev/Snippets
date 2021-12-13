/// Name: GuassElimination
/// Description: Solution of linear equation. A[][] * X[] = B[], solve for X
/// Detail: Matrix, Maths, Linear Equation, Guass Elimination
/// Guarantee: } // GuassElimination

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
    // converts A in upper triangular matrix
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
} // GuassElimination