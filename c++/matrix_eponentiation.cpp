/// Name: MatrixExponentiation
/// Description: Logarithmic time algorihtm to compute A[][]^exp
/// Detail: Matrix, Matrix Multiplication, Matrix Power, Maths
/// Guarantee: } // MatrixExponentiation

#define matrix2D vector< vector<long long> >
matrix2D matrixMultiply(matrix2D &a, matrix2D &b)
{
    matrix2D c (a.size(), vector< long long >(b[0].size()));
    for(int i=0; i<a.size(); i++)
    {
        for(int j=0; j<b[0].size(); j++)
        {
            for(int k=0; k<a[0].size(); k++)
            {
                c[i][j] = (c[i][j] + a[i][k] * b[k][j])%MOD;
            }
        }
    }
    return c;
}

matrix2D matrixPower(matrix2D &a, long long p)
{
    matrix2D res = matrix2D (a.size(), vector<long long>(a.size()));
    for(int i=0; i<a.size(); i++) res[i][i] = 1;

    while(p)
    {
        if(p & 1) res = matrixMultiply(a, res);
        a = matrixMultiply(a,a);
        p>>=1;
    }
    return res;
} // MatrixExponentiation