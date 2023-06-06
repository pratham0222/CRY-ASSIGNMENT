#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include <unordered_map>

using namespace std;

string generate_salt(int length = 8)
{
    string salt_characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*";
    string salt;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, salt_characters.length() - 1);

    for (int i = 0; i < length; ++i)
    {
        salt += salt_characters[dist(gen)];
    }
    return salt;
}

string hash_password(const string &password, const string &salt)
{
    string salted_password = password + salt;
    hash<string> hasher;
    return to_string(hasher(salted_password));
}

bool check_password(const string &password, const string &hashed_password, const string &salt)
{
    string salted_password = password + salt;
    hash<string> hasher;
    return to_string(hasher(salted_password)) == hashed_password;
}

int main()
{
    unordered_map<string, pair<string, string>> hashed_password_file;
    string username, password;

    int num_users;
    cout << "Enter the number of users: ";
    cin >> num_users;
    cin.ignore(); 

    for (int i = 0; i < num_users; ++i)
    {
        cout << "Enter the username for User" << i + 1 << ": ";
        getline(cin, username);
        cout << "Enter the password for User" << i + 1 << ": ";
        getline(cin, password);
        string salt = generate_salt();
        string hashed_password = hash_password(password, salt);
        hashed_password_file[username] = make_pair(hashed_password, salt);
    }

    ofstream file("hashed_passwords.txt");
    if (!file.is_open())
    {
        cerr << "Unable to open file." << endl;
        return 1;
    }

    for (const auto &entry : hashed_password_file)
    {
        const string &username = entry.first;
        const string &hashed_password = entry.second.first;
        const string &salt = entry.second.second;
        file << username << ":" << hashed_password << ":" << salt << endl;
    }
    file.close();

    string login_username, login_password;
    cout << "\nEnter username: ";
    getline(cin, login_username);
    cout << "Enter password: ";
    getline(cin, login_password);

    ifstream input_file("hashed_passwords.txt");
    if (!input_file.is_open())
    {
        cerr << "Unable to open file." << endl;
        return 1;
    }

    string stored_username, stored_hashed_password, stored_salt;
    bool login_successful = false;

    while (getline(input_file, stored_username, ':') && getline(input_file, stored_hashed_password, ':') &&
           getline(input_file, stored_salt))
    {
        if (stored_username == login_username && check_password(login_password, stored_hashed_password, stored_salt))
        {
            login_successful = true;
            break;
        }
    }
    input_file.close();

    if (login_successful)
    {
        cout << "Login successful." << endl;
    }
    else
    {
        cout << "Login failed. Invalid username or password." << endl;
    }

    return 0;
}
