#include <iostream>

using namespace std;

int extended_euclidean_algorithm(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }

    int x1, y1;
    int gcd = extended_euclidean_algorithm(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

int find_modular_inverse(int a, int m)
{
    int x, y;
    int gcd = extended_euclidean_algorithm(a, m, x, y);
    if (gcd != 1)
    {
        throw runtime_error("Inverse does not exist.");
    }
    return (x + m) % m;
}

int main()
{
    int a, m;

    cout << "Enter a number to find inverse: ";
    cin >> a;

    cout << "Enter the number whose modulus is to be found: ";
    cin >> m;

    int inverse;
    try
    {
        inverse = find_modular_inverse(a, m);
        cout << "Modular inverse of " << a << " mod " << m << " is: " << inverse << endl;
    }
    catch (const exception &e)
    {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
