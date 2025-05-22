#pragma once
#include <string>
#include <vector>
#include<queue>
#include<map>
using namespace std;

struct requests {
    string senderUsername;
    string recipientUsername;
    double amount;
    int day;
    int month;
    int year;
    int hour;
    int minute;
    string datetype;
};
struct transactions {
    char transactionDate[100];
    string type;
    int code = 1;
    string senderUsername;
    string recipientUsername;
    double amount;
    int day;
    int month;
    int year;
    int hour;
    int minute;
    string datetype;
};


class User {
public:
    string username;
    string email;
    string password;
    double balance;
    bool suspended;

public:
    void setUsername(string&);
    void setPassword(string&);
    void setEmail(string&);
    bool getSuspended();
    void setSuspended(User& user, bool isSuspended);
    User getUserByUsername(vector<User>& users, string& username);
    User(string, string, string, double, bool);
    User registerUser(vector<User>& users, int& nextChoice);
    User loginUser(vector<User>& users, int& nextChoice);
    void editProfile(vector<User>& users, int& nextChoice);
    bool checkEmailFormat(string);
    bool isPasswordSecure(string password);
    string getHidePassword();
    void SendMoney(queue<transactions>& allTransactions, vector<User>& users, string senderusername, queue<int>& balances, map<string, queue<transactions>>& userTransactions);
    void requestMoney(vector<User>& users, string Senderusername, queue <requests>& allRequests, map<string, queue<requests>>& userRequests);
    void ShowNotification(queue<transactions>& allTransactions, vector<User>& users, User user, queue<int>& balances, map<string, queue<transactions>>& userTransactions);
    void CheckRequests(queue<transactions>& allTransactions, vector<User>& users, string recipientusername, queue<int>& balances, queue <requests>& allRequests, map<string, queue<requests>>& userRequests, map<string, queue<transactions>>& userTransactions);
    static void viewBalance(User user);
    static void viewTransactions(string username, map<string, queue<transactions>>& userTransactions);

    // Overload < operator for sorting by usernameUser
    bool operator<(const User& other) const {
        return username < other.username;
    }
};