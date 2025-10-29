#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

const int MAX_SIZE = 10;

void readMatrix(double matrix[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cin >> matrix[i][j];
        }
    }
}

void printMatrix(const double matrix[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << fixed << setprecision(2) << matrix[i][j];
            if (j < cols - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }
}

void add(const double A[MAX_SIZE][MAX_SIZE], const double B[MAX_SIZE][MAX_SIZE], double result[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
}

void multiply(const double A[MAX_SIZE][MAX_SIZE], const double B[MAX_SIZE][MAX_SIZE], double result[MAX_SIZE][MAX_SIZE], int rowsA, int colsA, int colsB) {
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < colsA; ++k) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

double maxVal(const double matrix[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    double maxVal = matrix[0][0];
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (matrix[i][j] > maxVal) {
                maxVal = matrix[i][j];
            }
        }
    }
    return maxVal;
}

double minVal(const double matrix[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    double minVal = matrix[0][0];
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (matrix[i][j] < minVal) {
                minVal = matrix[i][j];
            }
        }
    }
    return minVal;
}

void transpose(const double matrix[MAX_SIZE][MAX_SIZE], double result[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[j][i] = matrix[i][j];
        }
    }
}

bool isSymmetric(const double matrix[MAX_SIZE][MAX_SIZE], int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (matrix[i][j] != matrix[j][i]) {
                return false;
            }
        }
    }
    return true;
}

void calibrate(double matrix[MAX_SIZE][MAX_SIZE], int rows, int cols, double scale, double offset) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = scale * matrix[i][j] + offset;
        }
    }
}

double determinant(double matrix[MAX_SIZE][MAX_SIZE], int size) {
    if (size == 1) {
        return matrix[0][0];
    }
    if (size == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }

    double det = 0;
    for (int i = 0; i < size; ++i) {
        double submatrix[MAX_SIZE][MAX_SIZE];
        for (int j = 1; j < size; ++j) {
            for (int k = 0, col = 0; k < size; ++k) {
                if (k == i) continue;
                submatrix[j-1][col++] = matrix[j][k];
            }
        }
        det += (i % 2 == 0 ? 1 : -1) * matrix[0][i] * determinant(submatrix, size - 1);
    }
    return det;
}

int main() {
    double A[MAX_SIZE][MAX_SIZE], B[MAX_SIZE][MAX_SIZE], result[MAX_SIZE][MAX_SIZE];
    string command;
    int rowsA, colsA, rowsB, colsB;

    while (cin >> command) {
        if (command == "ADD") {
            cin >> rowsA >> colsA;
            readMatrix(A, rowsA, colsA);
            readMatrix(B, rowsA, colsA);
            add(A, B, result, rowsA, colsA);
            printMatrix(result, rowsA, colsA);
        }
        else if (command == "MUL") {
            cin >> rowsA >> colsA >> rowsB >> colsB;
            if (colsA != rowsB) {
                cout << "ERROR" << endl;
                continue;
            }
            readMatrix(A, rowsA, colsA);
            readMatrix(B, rowsB, colsB);
            multiply(A, B, result, rowsA, colsA, colsB);
            printMatrix(result, rowsA, colsB);
        }
        else if (command == "MAX") {
            cin >> rowsA >> colsA;
            readMatrix(A, rowsA, colsA);
            cout << fixed << setprecision(2) << maxVal(A, rowsA, colsA) << endl;
        }
        else if (command == "MIN") {
            cin >> rowsA >> colsA;
            readMatrix(A, rowsA, colsA);
            cout << fixed << setprecision(2) << minVal(A, rowsA, colsA) << endl;
        }
        else if (command == "TRA") {
            cin >> rowsA >> colsA;
            readMatrix(A, rowsA, colsA);
            transpose(A, result, rowsA, colsA);
            printMatrix(result, colsA, rowsA);
        }
        else if (command == "ISS") {
            cin >> rowsA;
            colsA = rowsA;
            readMatrix(A, rowsA, colsA);
            cout << (isSymmetric(A, rowsA) ? "YES" : "NO") << endl;
        }
        else if (command == "CAL") {
            double scale, offset;
            cin >> rowsA >> colsA >> scale >> offset;
            readMatrix(A, rowsA, colsA);
            calibrate(A, rowsA, colsA, scale, offset);
            printMatrix(A, rowsA, colsA);
        }
        else if (command == "DET") {
            cin >> rowsA;
            colsA = rowsA;
            readMatrix(A, rowsA, colsA);
            cout << fixed << setprecision(2) << determinant(A, rowsA) << endl;
        }
    }

    return 0;
}
