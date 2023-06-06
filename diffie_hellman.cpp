#include <cmath>
#include <iostream>

using namespace std;

long long int power(long long int a, long long int b,long long int P)
{
    if (b == 1)
        return a;
    else
        return (((long long int)pow(a, b)) % P);
}

int main()
{
    long long int P, G, x, a, y, b, ka, kb;
    cout << "Enter value of P : " << endl;
    cin>>P;
    cout << "Enter value of G : " << endl;
    cin>>G;
    cout << "Enter private key a for Alice : "<< endl;
    cin>>a;
    x = power(G, a, P);
    cout << "Enter private key b for Bob : "<< endl;
    cin>>b;
    y = power(G, b, P);
    ka = power(y, a, P);
    kb = power(x, b, P);
    cout << "Secret key for the Alice is : " << ka << endl;
    cout << "Secret key for the Bob is : " << kb << endl;
    return 0;
}