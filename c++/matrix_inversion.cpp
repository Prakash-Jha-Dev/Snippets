/// Name: MatrixInversion
/// Description: Inersion of matrix using gaussian elimination
/// Detail: Matrix, Maths, Linear Equation, Guass Elimination, Inverse
/// Guarantee: } // MatrixInversion

bool invert_matrix(vector<vector<double>> &Matrix, vector<vector<double>>& InvertedMatrix)
{
    int n = Matrix.size();
    int m = Matrix[0].size();
    // only square matrices are invertible
    if (n != m)
        return 0;
    else // Initially Inverted Matrix is Identity Matrix
    {
        InvertedMatrix.clear();
        InvertedMatrix.resize(n);
        for(int i=0; i<n; i++)
        {
            InvertedMatrix[i].resize(n);
            InvertedMatrix[i][i] = 1;
        }
    }

    // convert into upper triangular matrix
    for (int i = 0; i < m; i++)
    {
        int idx = i;
        for (int j = i + 1; j < n; j++)
            if (abs(Matrix[j][i]) > abs(Matrix[idx][i]))
                idx = j;
        swap(Matrix[idx], Matrix[i]);
        swap(InvertedMatrix[idx], InvertedMatrix[i]);

        // Number of equation redues since this equation can be obtained from other equations.
        // Not a square matrix. Rank(Matrix) < n
        // NOTE: checking for Matrix[i][i] == 0
        if (abs(Matrix[i][i]) < 1e-6 ) return 0;
        // transform remaining equations to have ith co-eff as 0
        for (int j = i + 1; j < n; j++)
        {
            // change co-effiecient of all terms of equation
            double ch = Matrix[j][i] / Matrix[i][i];
            for (int k = i; k < m; k++)
            {
                Matrix[j][k] -= ch * Matrix[i][k];
            }
            for (int k = 0; k < m; k++)
            {
                InvertedMatrix[j][k] -= ch * InvertedMatrix[i][k];
            }
        }
    }

    // convert into diagonal matrix with 1 at each diagonal
    for(int i=n-1; i>=0; i--)
    {
        for(int j=i-1; j>=0; j--)
        {
            double ch = A[j][i]/A[i][i];
            // Only one element in each row is reduced as only A[i][i] is non-zero
            A[j][i] = 0;
            for(int k=0; k<n; k++)
            {
                InvertedMatrix[j][k] -= ch * InvertedMatrix[i][k];
            }
        }
        // div with A[i][i] to make diagonal element = 1 in A
        double div = A[i][i];
        A[i][i] = 1;
        for(int k=0; k<n; k++) InvertedMatrix[i][k] /= div;
    }

    return 1;
} // MatrixInversion