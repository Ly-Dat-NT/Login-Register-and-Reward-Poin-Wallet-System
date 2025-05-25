#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <conio.h>

using namespace std;

class User {
private:
    string username;
    string password;
    string email;

public:
    User(string username = "", string password = "", string email = "") {
        this->username = username;
        this->password = password;
        this->email = email;
    }

    string getUsername() const { return username; }
    string getPassword() const { return password; }
    string getEmail() const { return email; }

    void setPassword(string newPassword) { password = newPassword; }

    static bool checkEmailFormat(const string& email) {
        regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
        return regex_match(email, pattern);
    }

    static bool isPasswordSecure(const string& password) {
        if (password.length() < 8) return false;
        bool hasLower = false, hasUpper = false, hasDigit = false;
        for (char ch : password) {
            if (islower(ch)) hasLower = true;
            else if (isupper(ch)) hasUpper = true;
            else if (isdigit(ch)) hasDigit = true;
        }
        return hasLower && hasUpper && hasDigit;
    }

    static string getHiddenPassword() {
        string password;
        char ch;
        while ((ch = _getch()) != '\r') {
            if (ch == '\b') {
                if (!password.empty()) {
                    password.pop_back();
                    cout << "\b \b";
                }
            } else {
                password += ch;
                cout << '*';
            }
        }
        cout << endl;
        return password;
    }

    static void registerUser(vector<User>& users) {
        string email, username, password;
        cout << "Enter Email: ";
        cin >> email;

        if (!checkEmailFormat(email)) {
            cout << "Invalid email format!\n";
            return;
        }

        cout << "Enter Username: ";
        cin >> username;

        for (const auto& user : users) {
            if (user.getUsername() == username) {
                cout << "Username already exists!\n";
                return;
            }
        }

        cout << "Enter Password (at least 8 characters, includes upper/lowercase and number): ";
        password = getHiddenPassword();

        if (!isPasswordSecure(password)) {
            cout << "Password not secure enough!\n";
            return;
        }

        users.emplace_back(username, password, email);
        cout << "Registration successful!\n";
    }

    static User loginUser(const vector<User>& users) {
        string username, password;
        cout << "Enter Username: ";
        cin >> username;

        cout << "Enter Password: ";
        password = getHiddenPassword();

        for (const auto& user : users) {
            if (user.getUsername() == username && user.getPassword() == password) {
                cout << "Login successful!\n";
                return user;
            }
        }

        cout << "Invalid credentials!\n";
        return User();  // trả về user rỗng
    }

    static void changePassword(vector<User>& users) {
        string username, oldPassword, newPassword;

        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Old Password: ";
        oldPassword = getHiddenPassword();

        for (auto& user : users) {
            if (user.getUsername() == username && user.getPassword() == oldPassword) {
                cout << "Enter New Password: ";
                newPassword = getHiddenPassword();

                if (!isPasswordSecure(newPassword)) {
                    cout << "New password not secure enough!\n";
                    return;
                }

                user.setPassword(newPassword);
                cout << "Password updated successfully!\n";
                return;
            }
        }

        cout << "Username or password incorrect.\n";
    }
};

int main() {
    vector<User> users;
    int choice;

    while (true) {
        cout << "\n--- MENU ---\n";
        cout << "1. Register\n2. Login\n3. Change Password\n4. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice) {
            case 1:
                User::registerUser(users);
                break;
            case 2:
                User::loginUser(users);
                break;
            case 3:
                User::changePassword(users);
                break;
            case 4:
                return 0;
            default:
                cout << "Invalid option!\n";
        }
    }
}