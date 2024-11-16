// Stream: MTechCS
// RollNo: CS2407

#include <iostream>
#include <complex>
#include <vector>

using namespace std;

// Function to print an n x n matrix
void printMatrix(vector<vector<complex<double>>> &matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to check if the matrix is unitary
bool isUnitary(vector<vector<complex<double>>> &matrix, int n)
{
    vector<vector<complex<double>>> conjugateTranspose(n, vector<complex<double>>(n));

    // Compute the conjugate transpose
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            conjugateTranspose[j][i] = conj(matrix[i][j]);
        }
    }

    // Multiply the conjugate transpose by the original matrix
    vector<vector<complex<double>>> result(n, vector<complex<double>>(n, complex<double>(0, 0)));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                result[i][j] += conjugateTranspose[i][k] * matrix[k][j];
            }
        }
    }

    // Check if the result is the identity matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j && abs(result[i][j] - complex<double>(1, 0)) > 1e-9)
            {
                return false;
            }
            if (i != j && abs(result[i][j]) > 1e-9)
            {
                return false;
            }
        }
    }

    return true;
}

int main()
{
    int n;
    cout << "Enter the size of the matrix (n x n): ";
    cin >> n;
    vector<vector<complex<double>>> matrix(n, vector<complex<double>>(n));

    cout << "Enter the elements of the matrix (real and imaginary parts):\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            double realPart, imagPart;
            cout << "Enter real part of element [" << i + 1 << "][" << j + 1 << "]: ";
            cin >> realPart;
            cout << "Enter imaginary part of element [" << i + 1 << "][" << j + 1 << "]: ";
            cin >> imagPart;
            matrix[i][j] = complex<double>(realPart, imagPart);
        }
    }

    cout << "\nInput Matrix:\n";
    printMatrix(matrix, n);

    if (isUnitary(matrix, n))
    {
        cout << "\nThe matrix is unitary.\n";
    }
    else
    {
        cout << "\nThe matrix is not unitary.\n";
    }

    return 0;
}
