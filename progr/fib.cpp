#include <iostream>
#include <vector>
using namespace std;

int fibonacci_td(int n, vector<int>& f) {
    if (n <= 1) {
        f[n] = n;
    } else {
        f[n] = fibonacci_td(n - 1, f) + fibonacci_td(n - 2, f);
    }
    return f[n];
}

int fibonacci_bu(int n) {
    vector<int> f(n + 1, -1);
    f[0] = 0;
    f[1] = 1;
    
    for (int i = 2; i <= n; i++) {
        f[i] = f[i - 1] + f[i - 2];
    }
    return f[n];
}

int fibonacci_bu_improved(int n) {
    if (n <= 1) {
        return n;
    }
    
    int prev = 0;
    int curr = 1;
    
    for (int i = 2; i <= n; i++) {
        int next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr;
}

int fibonacci(int n, int calculation_method) {
    switch (calculation_method) {
        case 0: {
            vector<int> f(n + 1, -1);
            return fibonacci_td(n, f);
        }
        case 1:
            return fibonacci_bu(n);
        case 2:
            return fibonacci_bu_improved(n);
        default:
            cout << "Неизвестный метод вычисления: " << calculation_method << endl;
            return -1;
    }
}

int main() {
    int N = 10;
    cout << "Число Фибоначчи(" << N << "):" << endl;
    cout << "fibonacci(" << N << ", 0) = " << fibonacci(N, 0) << endl;
    cout << "fibonacci(" << N << ", 1) = " << fibonacci(N, 1) << endl;
    cout << "fibonacci(" << N << ", 2) = " << fibonacci(N, 2) << endl;
    return 0;
}
