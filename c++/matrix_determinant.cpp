/// Name: MatrixDeterminant
/// Description: Determinant of a Matrix using gaussian elimination
/// Detail: Matrix, Maths, Linear Equation, Guass Elimination
/// Guarantee: } // MatrixDeterminant

vector<vector<double>> A;

double determinant(vector<vector<double>> &A)
{
    int n = A.size();
    int m = A[0].size();
    assert(n == m);

    double d = 1;
    for (int i = 0; i < m; i++)
    {
        int idx = i;
        for (int j = i + 1; j < n; j++)
            if (abs(A[j][i]) > abs(A[idx][i]))
                idx = j;
        if(idx != i)
        {
            d *= -1;
            swap(A[idx], A[i]);
        }

        // Det is equal to product of elements on primary diagonal.
        if (A[i][i] == 0)
            return 0;
        // transform remaining equations to have ith co-eff as 0
        for (int j = i + 1; j < n; j++)
        {
            // change co-effiecient of all terms of equation
            double ch = A[j][i] / A[i][i];
            for (int k = i; k < m; k++)
            {
                A[j][k] -= ch * A[i][k];
            }
        }
    }

    for (int i = m - 1; i >= 0; i--)
        d *= A[i][i];
    return d;
} // MatrixDeterminant