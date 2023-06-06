#include <iostream>
#include <string>

using namespace std;

string affine_encrypt(const string &plain_text, int a, int b)
{
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string encrypted_text = "";

    for (char ch : plain_text)
    {
        if (isalpha(ch))
        {
            int index = alphabet.find(toupper(ch));
            int encrypted_index = (a * index + b) % 26;
            char encrypted_char = alphabet[encrypted_index];
            encrypted_text += encrypted_char;
        }
        else
        {
            encrypted_text += ch;
        }
    }

    return encrypted_text;
}

string affine_decrypt(const string &cipher_text, int a, int b)
{
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string decrypted_text = "";
    int a_inverse = 0;

    for (int i = 0; i < 26; i++)
    {
        if ((a * i) % 26 == 1)
        {
            a_inverse = i;
            break;
        }
    }

    for (char ch : cipher_text)
    {
        if (isalpha(ch))
        {
            int index = alphabet.find(toupper(ch));
            int decrypted_index = (a_inverse * (index - b + 26)) % 26;
            char decrypted_char = alphabet[decrypted_index];
            decrypted_text += decrypted_char;
        }
        else
        {
            decrypted_text += ch;
        }
    }

    return decrypted_text;
}

int main()
{
    string plaintext;
    int a_key, b_key;

    cout << "Enter the plain text: ";
    getline(cin, plaintext);

    cout << "Enter the multiplicative value (a): ";
    cin >> a_key;

    cout << "Enter the additive value (b): ";
    cin >> b_key;

    string encrypted_text = affine_encrypt(plaintext, a_key, b_key);
    cout << "Encrypted text: " << encrypted_text << endl;

    string decrypted_text = affine_decrypt(encrypted_text, a_key, b_key);
    cout << "Decrypted text: " << decrypted_text << endl;

    return 0;
}