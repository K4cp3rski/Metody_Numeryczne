#include <iostream>
#include <vector>
#include <cmath>
#include <matplot/matplot.h>

using namespace std;
// Temat zajęć: Dokładność numeryczna

double find_epsilon()
{
    double epsilon = 1;
    while (1 + epsilon != 1)
    {
        epsilon /= 2;
    }
    return epsilon*2;
}

void ex_2(vector<double> &X, vector<double> &N)
{
    using namespace matplot;
    for (auto & del_x: X)
    {
        for (auto &num: N) {
            double summed = 0;
            vector<double> diff;
            vector<double> x = linspace(1, num, num);
            for (auto &i: x) {
                summed += del_x;
                double real = i * del_x;
                double diff_unit = real - summed;
                diff.push_back(diff_unit);
                cout << "Real: " << real << ", Summed: " << summed << endl;
            }
            stem(x, diff);
            show();
        }
    }
}

void ex_3(int n)
{
    vector<double> X;
    X.push_back(1);
    X.push_back(1.0/3.0);
    for (int i=2; i < n;i++) {
        double x_prev = X[i-2];
        double x_now = X[i-1];
        double x = 13.0/3.0 * x_now - 4.0/3.0 * x_prev;
        X.push_back(x);
    }
    vector<double> X_diff;
    using namespace matplot;
    vector<int> vec_n (n);
    iota(vec_n.begin(), vec_n.end(), 0);
    for (auto & n : vec_n)
    {
        double x_act = pow(1.0/3.0, n);
        double diff = X[n] - x_act;
        X_diff.push_back(diff);
    }

//    for (auto & x : X_diff) cout << n << endl;

    stem(vec_n, X_diff);
    show();
}

void ex_4(int num) {
//    Linspace definition
    vector<int> N(num);
    iota(N.begin(), N.end(), 0);

//    Series definition
    vector<double> a_n;
    vector<double> b_n;
    vector<double> c_n;
    vector<double> d_n;

//    Limit, as stated in excercise body
    double lim_a_n = 1;
    double lim_b_n = exp(1.0);
    double lim_c_n = sqrt(2);
    double lim_d_n = 1;

//  Distance from limit
    vector<double> a_n_diff;
    vector<double> b_n_diff;
    vector<double> c_n_diff;
    vector<double> d_n_diff;

//    Start values
    c_n.push_back(2);
    d_n.push_back(0);
    d_n.push_back(2);

//    Ciąg a_n
    for (auto &n: N) {
        double a = (float) (n + 1) / (float) n;
        a_n.push_back(a);
        a_n_diff.push_back(a - lim_a_n);
    }

//    Ciąg b_n
    for (auto &n: N) {
        double b = pow(1 + 1.0 / (float) n, n);
        b_n.push_back(b);
        b_n_diff.push_back(b - lim_b_n);
    }

//    Ciąg c_n
    for (auto &n: N) {
        if (n == 0) {
            c_n_diff.push_back(c_n[n] - lim_c_n);
            continue;
        }
        double c = (1.0 / (float) (2.0)) * c_n[n - 1] + 1.0 / (float) c_n[n - 1];
        c_n.push_back(c);
        c_n_diff.push_back(c - lim_c_n);
    }

//    Ciąg d_n
    for (auto &n: N) {
        if (n < 2) {
            d_n_diff.push_back(d_n[n] - lim_d_n);
            continue;
        }
        double d_n_1 = d_n[n - 2];
        double d_n_curr = d_n[n - 1];
        double d = (d_n_1 * d_n_curr + 1) / (d_n_1 + d_n_curr);
        d_n.push_back(d);
        d_n_diff.push_back(d - lim_d_n);
    }

    using namespace matplot;
    vector<vector<double>> Y = {a_n_diff, b_n_diff, c_n_diff, d_n_diff};
    stem(N, Y, "--o");
    auto l = legend("a_n", "b_n", "c_n", "d_n");
    l->location(legend::general_alignment::topright);
    l->num_rows(2);
    title("Szybkość zbieżności do granicy ciągów a_n - d_n");
    xlabel("N");
    ylabel("x_n - lim x_n");
    show();
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    cout << find_epsilon() << endl;
    cout << (1 + find_epsilon() == 1) << endl;
    vector<double> N = {10, 100, 1000, 100000, 1000000};
    vector<double> X = {0.1, 0.125};
    ex_2(X, N);
    ex_3(30);
    ex_4(100);

    return 0;
}
