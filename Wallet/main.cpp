#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <limits>

using namespace std;

void clearScreen() {
    system("cls");
}

// CẤU TRÚC DỮ LIỆU
struct User {
    string username;
    string password;
    string role;
    string walletId;
    int balance;
    bool isTempPassword = false;
    string fullName;
    string dob;
    string phone;
};

unordered_map<string, User> users;
unordered_map<string, vector<string>> transactions;

// HÀM HỖ TRỢ
string generateRandomString(int length) {
    string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string result;
    for (int i = 0; i < length; ++i) {
        result += chars[rand() % chars.size()];
    }
    return result;
}

string generateOTP() {
    return to_string(100000 + rand() % 900000);
}

void saveUsers(const string& filename = "users.txt") {
    ofstream file(filename);
    for (const auto &pair : users) {
        const User &u = pair.second;
        file << u.username << "," << u.password << "," << u.role << ","
             << u.walletId << "," << u.balance << "," << (u.isTempPassword ? "1" : "0") << ","
             << u.fullName << "," << u.dob << "," << u.phone << "\n";
    }
}

void loadUsers(const string& filename = "users.txt") {
    users.clear();
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        User u;
        string temp;

        if (!getline(ss, u.username, ',')) continue;
        if (!getline(ss, u.password, ',')) continue;
        if (!getline(ss, u.role, ',')) continue;
        if (!getline(ss, u.walletId, ',')) continue;
        if (!getline(ss, temp, ',')) continue;
        try {
            u.balance = stoi(temp);
        } catch (...) {
            continue;
        }
        if (!getline(ss, temp, ',')) continue;
        u.isTempPassword = (temp == "1");
        if (!getline(ss, u.fullName, ',')) continue;
        if (!getline(ss, u.dob, ',')) continue;
        if (!getline(ss, u.phone, ',')) continue;

        users[u.username] = u;
    }
}

void backupUsers() {
    saveUsers("backup_users.txt");
    cout << "\nSao Luu Du Lieu Khach Hang Thanh Cong\n";
}

void saveTransactions() {
    ofstream file("transactions.txt");
    for (const auto &pair : transactions) {
        for (const auto &line : pair.second) {
            file << pair.first << "|" << line << "\n";
        }
    }
}

void loadTransactions() {
    transactions.clear();
    ifstream file("transactions.txt");
    string line;
    while (getline(file, line)) {
        size_t pos = line.find('|');
        if (pos != string::npos) {
            string walletId = line.substr(0, pos);
            string record = line.substr(pos + 1);
            transactions[walletId].push_back(record);
        }
    }
}

void viewWallet(const User &u) {
    cout << "\n[THONG TIN VI]" << endl;
    cout << "Ho Ten: " << u.fullName << endl;
    cout << "Ngay Sinh: " << u.dob << endl;
    cout << "SDT: " << u.phone << endl;
    cout << "ID Vi: " << u.walletId << endl;
    cout << "So Du: " << u.balance << " diem\n";

    cout << "Lich Su Giao Dich:\n";
    if (transactions[u.walletId].empty()) {
        cout << "Chua Co Giao Dich Nao.\n";
    } else {
        for (const string &record : transactions[u.walletId]) {
            cout << record << endl;
        }
    }
    cout << "Nhan 0 De Tro Lai:";
    int choice;
    cin >> choice;
    if(choice == 0) clearScreen();
}

bool verifyOTP(const string &otp) {
    string input;
    cout << "Nhap OTP: ";
    cin >> input;
    return input == otp;
}

//ĐỔI MẬT KHẨU
void changePassword(User &u) {
    string otp = generateOTP();
    cout << "Ma OTP cua ban la: " << otp << endl;

    if (!verifyOTP(otp)) {
        cout << "OTP khong hop le. Khong the doi mat khau.\n";
        cout << "Nhan 0 De Tro Lai:";
        int choice;
        cin >> choice;
        if(choice == 0) clearScreen();
        return;
    }

    cout << "\nNhap Mat Khau Moi: ";
    string newPass;
    cin >> newPass;
    u.password = newPass;
    u.isTempPassword = false;
    saveUsers();
    saveTransactions();
    cout << "Doi Mat Khau Thanh Cong!\n";
    cout << "Nhan 0 De Tro Lai:";
    int choice;
    cin >> choice;
    if(choice == 0) clearScreen();
}

//ĐỔI SỐ ĐIỆN THOẠI
void changePhoneNumber(User &u) {
    string otp = generateOTP();
    cout << "Ma OTP cua ban la: " << otp << endl;

    if (!verifyOTP(otp)) {
        cout << "OTP khong hop le. Khong the doi so dien thoai.\n";
        cout << "Nhan 0 de tro lai:";
        int choice;
        cin >> choice;
        if (choice == 0) clearScreen();
        return;
    }

    cout << "Nhap So Dien Thoai Moi: ";
    string newPhone;
    cin.ignore();
    getline(cin, newPhone);

    u.phone = newPhone;
    saveUsers();

    cout << "Doi So Dien Thoai Thanh Cong!\n";
    cout << "Nhan 0 de tro lai:";
    int choice;
    cin >> choice;
    if (choice == 0) clearScreen();
}

void transferPoints(User &u) {
    string targetWallet;
    int amount;

    cout << "\nNhap ID Vi Cua Nguoi Nhan: ";
    cin >> targetWallet;

    cout << "Nhap So Diem Can Chuyen: ";
    cin >> amount;

    if (u.balance < amount) {
        cout << "So Du Khong Du!\n";
        return;
    }

    for (auto &pair : users) {
        User &usr = pair.second;
        if (usr.walletId == targetWallet) {
            string otp = generateOTP();
            cout << "OTP (Tu Dong Tao): " << otp << endl;
            if (!verifyOTP(otp)) {
                cout << "OTP Khong Hop Le. Giao Dich Bi Huy\n";
                return;
            }
            u.balance -= amount;
            usr.balance += amount;

            string tx = "Da Chuyen " + to_string(amount) + " Diem toi Vi " + targetWallet;
            transactions[u.walletId].push_back(tx);
            transactions[usr.walletId].push_back("Da Nhan " + to_string(amount) + " Diem Tu Vi " + u.walletId);

            saveUsers();
            saveTransactions();
            cout << "Giao Dich Thanh Cong!\n";
            return;
        }
    }
    cout << "Khong Tim Thay Vi.\n";
    cout << "Nhan 0 De Tro Lai:";
    int choice;
    cin >> choice;
    if(choice == 0) clearScreen();
}

void userMenu(User &u) {
    if (u.isTempPassword) {
        cout << "Day La Mat Khau Tam Thoi. Vui Long Doi Mat Khau\n";
        changePassword(u);
    }

    int choice;
    do {
        clearScreen();
        cout << "\n--- GIAO DIEN NGUOI DUNG ---\n";
        cout << "1. Xem Vi\n2. Chuyen Diem\n3. Doi Mat Khau\n4. Doi So Dien Thoai\n0. Dang Xuat\nChon: ";
        cin >> choice;
        if (choice == 1) viewWallet(u); 
        else if (choice == 2) transferPoints(u);
        else if (choice == 3) changePassword(u);
        else if (choice == 4) changePhoneNumber(u);
    } while (choice != 0);
}

void createUser(bool isAdmin = false) {
    User u;
    cout << "Ten Dang Nhap: "; cin >> u.username;
    if (users.count(u.username)) {
        cout << "Ten Dang Nhap Da Ton Tai.\n";
        return;
    }
    u.walletId = generateRandomString(8);
    u.balance = 1000;
    cin.ignore();
    cout << "Nhap Ho Va Ten: "; getline(cin, u.fullName);
    cout << "Nhap Ngay Sinh (dd/mm/yyyy): "; getline(cin, u.dob);
    cout << "Nhap So Dien Thoai: "; getline(cin, u.phone);

    cout << "Nhap Mat Khau (De Trong De Tu Dong Tao): ";
    string pass;
    getline(cin, pass);
    if (pass.empty()) {
        u.password = generateRandomString(6);
        u.isTempPassword = true;
        cout << "Tao Mat Khau Tu Dong: " << u.password << endl;
    } else {
        u.password = pass;
    }
    u.role = isAdmin ? "admin" : "user";
    users[u.username] = u;
    saveUsers();
    saveTransactions();
    cout << "Da Tao Tai Khoan.\n";
    cout << "Nhan 0 De Tro Lai:";
    int choice;
    cin >> choice;
    if(choice == 0) clearScreen();
}

void adminMenu(User &admin) {
    int choice;
    do {
        clearScreen(); 
        cout << "\n--- GIAO DIEN QUAN LY ---\n";
        cout << "1. Tao Tai Khoan\n";
        cout << "2. Xem Tat Ca Vi\n";
        cout << "3. Sao Luu Du Lieu\n";
        cout << "0. Dang Xuat\n";
        cout << "Chon: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  

        switch (choice) {
            case 1:
                clearScreen();  
                createUser();   
                break;

            case 2:
                clearScreen();
                cout << "--- DANH SACH TAT CA CAC VI ---\n";
                for (const auto &pair : users) {
                    const User &u = pair.second;
                    cout << u.username << " | " << u.fullName
                         << " | Vai Tro: " << u.role
                         << " | Vi: " << u.walletId
                         << " | So Du: " << u.balance << "\n";
                }
                cout << "\nNhan 0 De Tro Lai:";
                int back;
                cin >> back;
                if (back == 0) clearScreen();
                break;

            case 3:
                clearScreen();
                backupUsers();
                cout << "\nNhan 0 De Tro Lai:";
                cin >> back;
                if (back == 0) clearScreen();
                break;

            case 0:
                clearScreen(); 
                cout << "Dang xuat khoi che do quan ly...\n";
                break;

            default:
                cout << "Lua chon khong hop le. Thu lai.\n";
                break;
        }
    } while (choice != 0);
}

void login() {
    string user, pass;
    cout << "\nTen dang nhap: "; cin >> user;
    cout << "Mat Khau: "; cin >> pass;
    if (users.count(user) && users[user].password == pass) {
        cout << "Dang Nhap Thanh Cong.\n";
        if (users[user].role == "admin") adminMenu(users[user]);
        else userMenu(users[user]);
    } else {
        cout << "Sai ten dang nhap hoac mat khau.\n";
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    loadUsers();
    loadTransactions();

    int choice;
    do {
        clearScreen();
        cout << "\n---- HE THONG DIEM THUONG ----\n";
        cout << "1. Dang nhap\n2. Dang ky\n0. Thoat\nChon: ";
        cin >> choice;
        cin.ignore();
        if (choice == 1) login();
        else if (choice == 2) createUser();
    } while (choice != 0);
    cout << "Tam biet!\n";
    return 0;
}
