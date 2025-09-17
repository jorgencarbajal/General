#include <iostream>
using namespace std;

int modularExponentiation(int, int, int);

int main(int argc, char const *argv[])
{
    int a, b, m;
    cout << "Enter base (a), exponent (b), and modulus (m): ";
    cin >> a >> b >> m;
    cout << "Result: " << modularExponentiation(a, b, m) << endl;
    return 0;
}


int modularExponentiation(int a, int b, int m) {
    int result = 1; // Initialize result
    a = a % m; // Update 'a' if it is more than or equal to 'm'

    while (b > 0) {
        // If b is odd, multiply 'a' with result
        if (b % 2 == 1) {
            result = (result * a) % m;
        }
        // b must be even now
        b = b >> 1; // Divide b by 2
        result = (result * a) % m; // Multiply result by current 'a' and reduce modulo 'm'
        a = (a * a) % m; // Square 'a' and reduce modulo 'm'
    }
    return result; // Final result is (a^b) mod m
}