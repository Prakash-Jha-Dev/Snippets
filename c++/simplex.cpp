/// Name: Simplex
/// Description: Finds solution to linear inequalities
/// Detail: Linear Equation, Maths
/// Guarantee: } // Simplex

// Reference: http://www.phpsimplex.com/en/simplex_method_example.htm
/*
A[][] : Input Matrix (with slack variables)
B[] : Constants of input equations i.e A[i] <= B[i]
C[] : Function to maximize
*/
class Simplex
{
public:
    int rows, cols;
    std::vector<std::vector<float>> A;
    std::vector<float> B;
    std::vector<float> C;
    float maximum;
    bool isUnbounded;

    Simplex(std::vector<std::vector<float>> a, std::vector<float> b, std::vector<float> c)
    {
        maximum = 0;
        isUnbounded = false;
        rows = a.size();
        cols = a[0].size();

        A = a;
        B = b;
        C = c;
        for (auto &x : C)
            x *= -1; // reverse the optimization co-efficient and make them positive by simplex
    }

    bool simplexAlgorithmCalculataion()
    {
        //check whether the table is optimal,if optimal no need to process further
        if (checkOptimality())
            return true;

        if (isUnbounded == true)
        {
            // NOTE : Comment cout if not required
            cout << "Error unbounded" << endl;
            return true;
        }

        //find the column which has the pivot.The least coefficient of the objective function(C array).
        int pivotColumn = findPivotColumn();
        //find the row with the pivot value.The least value item's row in the B array
        int pivotRow = findPivotRow(pivotColumn);

        //form the next table according to the pivot value
        doPivotting(pivotRow, pivotColumn);

        return false;
    }

    bool checkOptimality()
    {
        //if the table has further negative constraints,then it is not optimal
        int positveValueCount = 0;

        //check if the coefficients of the objective function are negative
        for (int i = 0; i < C.size(); i++)
            positveValueCount += (C[i] >= 0);

        //if all the constraints are positive now,the table is optimal
        return positveValueCount == C.size();
    }

    void doPivotting(int pivotRow, int pivotColumn)
    {
        float pivetValue = A[pivotRow][pivotColumn]; //gets the pivot value
        float pivotRowVals[cols];                    //the column with the pivot
        float pivotColVals[rows];                    //the row with the pivot
        float rowNew[cols];                          //the row after processing the pivot value

        maximum = maximum - (C[pivotColumn] * (B[pivotRow] / pivetValue)); //set the maximum step by step
        //get the row that has the pivot value
        for (int i = 0; i < cols; i++)
            pivotRowVals[i] = A[pivotRow][i];

        //get the column that has the pivot value
        for (int j = 0; j < rows; j++)
            pivotColVals[j] = A[j][pivotColumn];

        //set the row values that has the pivot value divided by the pivot value and put into new row
        for (int k = 0; k < cols; k++)
            rowNew[k] = pivotRowVals[k] / pivetValue;

        B[pivotRow] = B[pivotRow] / pivetValue;

        //process the other coefficients in the A array by subtracting
        for (int m = 0; m < rows; m++)
        {
            //ignore the pivot row as we already calculated that
            if (m != pivotRow)
            {
                for (int p = 0; p < cols; p++)
                {
                    A[m][p] = A[m][p] - (pivotColVals[m] * rowNew[p]);
                }
            }
        }

        //process the values of the B array
        for (int i = 0; i < B.size(); i++)
        {
            if (i != pivotRow)
            {
                B[i] = B[i] - (pivotColVals[i] * B[pivotRow]);
            }
        }
        //the least coefficient of the constraints of the objective function
        float multiplyValue = C[pivotColumn];
        //process the C array
        for (int i = 0; i < C.size(); i++)
        {
            C[i] = C[i] - (multiplyValue * rowNew[i]);
        }

        //replacing the pivot row in the new calculated A array
        for (int i = 0; i < cols; i++)
        {
            A[pivotRow][i] = rowNew[i];
        }
    }

    //find the least coefficients of constraints in the objective function's position
    int findPivotColumn()
    {
        int location = 0;

        for (int i = 1; i < C.size(); i++)
            if (C[i] < C[location])
                location = i;

        return location;
    }

    //find the row with the pivot value.The least value item's row in the B array
    int findPivotRow(int pivotColumn)
    {
        vector<float> result(rows);
        int location = -1;
        for (int i = 0; i < rows; i++)
        {
            if (A[i][pivotColumn] > 0)
            {
                result[i] = B[i] / A[i][pivotColumn];
                if (location == -1)
                    location = i;
                if (result[i] < result[location])
                    location = i;
            }
        }
        //checking the unbound condition if all the values are negative ones
        if (location == -1)
            isUnbounded = true;

        return location;
    }

    void printSolution()
    {
        for (int i = 0; i < C.size() - A.size(); i++)
        {
            int cnt = 0;
            int index = 0;
            for (int j = 0; j < rows; j++)
            {
                if (abs(A[j][i]) < 1e-6)
                    cnt++;
                else if (abs(A[j][i] - 1) < 1e-6)
                    index = j;
            }

            cout << "variable" << index + 1 << ": " << ((cnt == rows - 1) ? B[index] : 0) << endl;
        }
        cout << endl;
        cout << "maximum value: " << maximum << endl; //print the maximum values
    }

    float CalculateSimplex()
    {
        while (true)
        {
            if (simplexAlgorithmCalculataion())
                break;
        }
        return maximum;
    }
};

void inputSimplex()
{
    // n : number of equations
    // m : number of variables
    int n,m;
    cin>>n>>m;

    vector< vector< float > >A(n, vector<float>(m+n)); // extra size due to slack variable for each eq
    vector< float >B(n);
    vector< float >C(n+m); // slack variables has zero coefficient

    // Input n equations of form : Sum A_i[x] <= B_i
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            cin>>A[i][j];
        }
        A[i][m+i] = 1; //slack variable coeffcient
        cin>>B[i];
    }
    // Input the maximization function 
    // NOTE: In case of minimization, multiply everything by -1 and use as maximization
    for(int i=0; i<m; i++) cin>>C[i];

    Simplex simplex(A, B, C);
    cout << simplex.CalculateSimplex() << "\n";
    simplex.printSolution();
} // Simplex