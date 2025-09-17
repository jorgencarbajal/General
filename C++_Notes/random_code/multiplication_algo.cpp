#include <iostream>
using namespace std;

int multiply(int a, int b) {
    int result = 0;
    bool negative = false;

    // Handle negative numbers
    if (b < 0) {
        b = -b;
        a = -a;
    }

    for (int i = 0; i < b; ++i) {
        result += a;
    }
    return result;
}

int main() {
    int x, y;
    cout << "Enter two numbers: ";
    cin >> x >> y;
    cout << "Product: " << multiply(x, y) << endl;
    return 0;
}