#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>

using namespace std;

double** createMatrix(int rows, int cols) {
    double** M = new double*[rows];
    for (int i = 0; i < rows; ++i)
        M[i] = new double[cols];
    return M;
}

void deleteMatrix(double** M, int rows) {
    for (int i = 0; i < rows; ++i)
        delete[] M[i];
    delete[] M;
}

void readMatrix(double** M, int rows, int cols) {
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            cin >> M[i][j];
}

void printMatrix(double** M, int rows, int cols) {
    cout << fixed << setprecision(2);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << M[i][j];
            if (j + 1 < cols) cout << " ";
        }
        cout << "\n";
    }
}

double** sum(double** A, double** B, int rows, int cols) {
    double** R = createMatrix(rows, cols);
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            R[i][j] = A[i][j] + B[i][j];
    return R;
}

double** sub(double** A, double** B, int rows, int cols) {
    double** R = createMatrix(rows, cols);
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            R[i][j] = A[i][j] - B[i][j];
    return R;
}

double** mul(double** A, int r1, int c1, double** B, int r2, int c2) {
    if (c1 != r2)
        throw invalid_argument("Nieprawidlowe rozmiary macierzy do mnozenia.");

    double** R = createMatrix(r1, c2);
    for (int i = 0; i < r1; ++i)
        for (int j = 0; j < c2; ++j) {
            R[i][j] = 0.0;
            for (int k = 0; k < c1; ++k)
                R[i][j] += A[i][k] * B[k][j];
        }
    return R;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string cmd;
    int r1, c1, r2, c2;

    cin >> cmd;
    cin >> r1 >> c1;
    double** A = createMatrix(r1, c1);
    readMatrix(A, r1, c1);

    cin >> r2 >> c2;
    double** B = createMatrix(r2, c2);
    readMatrix(B, r2, c2);

    try {
        double** R = nullptr;
        int rr = 0, cc = 0;

        if (cmd == "SUM") {
            if (r1 != r2 || c1 != c2)
                throw invalid_argument("Rozne rozmiary macierzy.");
            R = sum(A, B, r1, c1);
            rr = r1; cc = c1;
        } 
        else if (cmd == "SUB") {
            if (r1 != r2 || c1 != c2)
                throw invalid_argument("Rozne rozmiary macierzy.");
            R = sub(A, B, r1, c1);
            rr = r1; cc = c1;
        } 
        else if (cmd == "MUL") {
            R = mul(A, r1, c1, B, r2, c2);
            rr = r1; cc = c2;
        } 
        else {
            throw invalid_argument("Nieznane polecenie.");
        }

        printMatrix(R, rr, cc);
        deleteMatrix(R, rr);
    } 
    catch (const exception& e) {
        cout << "ERROR\n";
    }

    deleteMatrix(A, r1);
    deleteMatrix(B, r2);

    return 0;
}
