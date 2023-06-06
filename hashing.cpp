#include <iostream>
#include <random>
#include <string>
using namespace std;

int customHash(string &msg)
{
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(0, 65535);
    generator.seed(hash<string>{}(msg));
    return distribution(generator);
}

int main()
{
    string msg;
    cout << "Enter the msg: ";
    cin >> msg;

    int hashValue = customHash(msg);

    cout << "Original msg: " << msg << endl;
    cout << "Hash value: " << hashValue << endl;

    string receivedmsg;
    cout << "Enter the received msg: ";
    cin >> receivedmsg;

    int receivedHashValue = customHash(receivedmsg);

    cout << "Received msg: " << receivedmsg << endl;
    cout << "Received Hash value: " << receivedHashValue << endl;

    if (receivedHashValue == hashValue)
    {
        cout << "Integrity: The msg has not been modified." << endl;
    }
    else
    {
        cout << "Integrity: The msg has been modified." << endl;
    }

    return 0;
}