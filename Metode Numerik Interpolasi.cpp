#include <iostream>
using namespace std;

// Fungsi untuk menghitung nilai polinomial Lagrange pada titik x yang diberikan
double lagrangeInterpolation(double x[], double y[], int n, double x_target)
{
    double result = 0.0; // Hasil akhir dari interpolasi

    for (int i = 0; i < n; i++)
    {
        double term = y[i]; // Memulai dengan y[i]

        for (int j = 0; j < n; j++)
        {
            if (j != i)
            {
                term = term * (x_target - x[j]) / (x[i] - x[j]);
            }
        }

        result += term;
    }

    return result;
}

// Fungsi untuk menghitung tabel perbedaan terbagi Newton
void dividedDifferenceTable(double x[], double y[], double diff[][10], int n)
{
    for (int i = 0; i < n; i++)
    {
        diff[i][0] = y[i];
    }

    for (int j = 1; j < n; j++)
    {
        for (int i = 0; i < n - j; i++)
        {
            diff[i][j] = (diff[i + 1][j - 1] - diff[i][j - 1]) / (x[i + j] - x[i]);
        }
    }
}

// Fungsi untuk menghitung nilai polinomial Newton pada titik x yang diberikan
double newtonInterpolation(double x[], double y[], int n, double x_target)
{
    double diff[10][10]; // Tabel perbedaan terbagi
    dividedDifferenceTable(x, y, diff, n);

    double result = diff[0][0]; // Memulai dengan f[x0]
    double term = 1.0;          // Term awal

    for (int i = 1; i < n; i++)
    {
        term *= (x_target - x[i - 1]);
        result += term * diff[0][i];
    }

    return result;
}

int main()
{
    // Contoh input array x dan y
    double x[] = {5, 10, 15, 20, 25, 30, 35, 40};
    double y[] = {40, 30, 25, 40, 18, 20, 22, 15};
    int n = sizeof(x) / sizeof(x[0]);

    for (int i = 5; i < 41; i++)
    {
        // Titik yang ingin dihitung nilai polinomialnya
        double x_target = i;
        double newtonResult = newtonInterpolation(x, y, n, x_target);
        cout << "Nilai polinomial Newton pada x = " << x_target << " adalah " << newtonResult << endl;
    }

    cout << endl;

    for (int i = 5; i < 41; i++)
    {
        // Titik yang ingin dihitung nilai polinomialnya
        double x_target = i;
        double lagrangeResult = lagrangeInterpolation(x, y, n, x_target);
        cout << "Nilai polinomial pada x Lagrange = " << x_target << " adalah " << lagrangeResult << endl;
    }

    return 0;
}
