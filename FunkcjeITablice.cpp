#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
using namespace std;

const int MAX = 100; // maksymalny rozmiar macierzy

void readMatrix(double A[MAX][MAX], int r, int c) {
    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j)
            cin >> A[i][j];
}

void printMatrix(double A[MAX][MAX], int r, int c) {
    cout << fixed << setprecision(2);
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            cout << A[i][j];
            if (j + 1 < c) cout << " ";
        }
        cout << "\n";
    }
}

void add(double A[MAX][MAX], double B[MAX][MAX], double R[MAX][MAX], int r, int c) {
    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j)
            R[i][j] = A[i][j] + B[i][j];
}

void multiply(double A[MAX][MAX], double B[MAX][MAX], double R[MAX][MAX],
              int r1, int c1, int r2, int c2) {
    for (int i = 0; i < r1; ++i)
        for (int j = 0; j < c2; ++j) {
            R[i][j] = 0;
            for (int k = 0; k < c1; ++k)
                R[i][j] += A[i][k] * B[k][j];
        }
}

double maxVal(double A[MAX][MAX], int r, int c) {
    double m = A[0][0];
    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j)
            if (A[i][j] > m) m = A[i][j];
    return m;
}

double minVal(double A[MAX][MAX], int r, int c) {
    double m = A[0][0];
    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j)
            if (A[i][j] < m) m = A[i][j];
    return m;
}

void transpose(double A[MAX][MAX], double R[MAX][MAX], int r, int c) {
    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j)
            R[j][i] = A[i][j];
}

bool isSymmetric(double A[MAX][MAX], int n) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (A[i][j] != A[j][i]) return false;
    return true;
}

void calibrate(double A[MAX][MAX], int r, int c, double scale, double offset) {
    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j)
            A[i][j] = scale * A[i][j] + offset;
}

double determinant(double A[MAX][MAX], int n) {
    if (n == 1) return A[0][0];
    if (n == 2) return A[0][0]*A[1][1] - A[0][1]*A[1][0];
    double det = 0.0;
    for (int p = 0; p < n; ++p) {
        double sub[MAX][MAX];
        for (int i = 1; i < n; ++i) {
            int col = 0;
            for (int j = 0; j < n; ++j)
                if (j != p)
                    sub[i-1][col++] = A[i][j];
        }
        det += pow(-1, p) * A[0][p] * determinant(sub, n-1);
    }
    return det;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string cmd;
    cin >> cmd;

    int r1, c1;
    double A[MAX][MAX], B[MAX][MAX], R[MAX][MAX];
    cin >> r1 >> c1;
    readMatrix(A, r1, c1);

    if (cmd == "ADD" || cmd == "MUL") {
        int r2, c2;
        cin >> r2 >> c2;
        readMatrix(B, r2, c2);

        if (cmd == "ADD") {
            if (r1 != r2 || c1 != c2) cout << "ERROR\n";
            else {
                add(A, B, R, r1, c1);
                printMatrix(R, r1, c1);
            }
        } else if (cmd == "MUL") {
            if (c1 != r2) cout << "ERROR\n";
            else {
                multiply(A, B, R, r1, c1, r2, c2);
                printMatrix(R, r1, c2);
            }
        }
    }
    else if (cmd == "MAX") cout << fixed << setprecision(2) << maxVal(A, r1, c1) << "\n";
    else if (cmd == "MIN") cout << fixed << setprecision(2) << minVal(A, r1, c1) << "\n";
    else if (cmd == "TRA") {
        transpose(A, R, r1, c1);
        printMatrix(R, c1, r1);
    }
    else if (cmd == "ISS") {
        if (r1 != c1) cout << "ERROR\n";
        else cout << (isSymmetric(A, r1) ? "YES\n" : "NO\n");
    }
    else if (cmd == "CAL") {
        double scale, offset;
        cin >> scale >> offset;
        calibrate(A, r1, c1, scale, offset);
        printMatrix(A, r1, c1);
    }
    else if (cmd == "DET") {
        if (r1 != c1) cout << "ERROR\n";
        else cout << fixed << setprecision(2) << determinant(A, r1) << "\n";
    }
    else cout << "ERROR\n";

    return 0;
}
