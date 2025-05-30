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

// --- HASH PASSWORD ---
string singleHash(const string &input) {
    unsigned long hash = 0;
    for (char c : input) {
        hash = (hash * 131) ^ c;  // Hash nhân-prime và XOR
    }
    return to_string(hash);
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

//TẠO MÃ OTP
string generateOTP() {
    return to_string(100000 + rand() % 900000);
}

//GHI DS NGƯỜI DÙNG RA FILE
void saveUsers(const string& filename = "users.txt") {
    ofstream file(filename);
    for (const auto &pair : users) {
        const User &u = pair.second;
        file << u.username << "," << u.password << "," << u.role << ","
             << u.walletId << "," << u.balance << "," << (u.isTempPassword ? "1" : "0") << ","
             << u.fullName << "," << u.dob << "," << u.phone << "\n";
    }
}

//ĐỌC DỮ LIỆU NGƯỜI DÙNG TỪ FILE
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

//SAO LƯU
void backupUsers() {
    saveUsers("backup_users.txt");
    cout << "\nSao Luu Du Lieu Khach Hang Thanh Cong\n";
}

//LƯU LỊCH SỬ GIAO DỊCH
void saveTransactions() {
    ofstream file("transactions.txt");
    for (const auto &pair : transactions) {
        for (const auto &line : pair.second) {
            file << pair.first << "|" << line << "\n";
        }
    }
}

//ĐỌC LỊCH SỬ GIAO DỊCH
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

//XEM VÍ
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

//XÁC MINH MÃ OTP
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
    u.password = singleHash(newPass);
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

//CHUYỂN ĐIỂM
void transferPoints(User &u) {
    string targetWallet;
    long long unsigned amount;

    cout << "\nNhap ID Vi Cua Nguoi Nhan: ";
    cin >> targetWallet;

    cout << "Nhap So Diem Can Chuyen: ";
    cin >> amount;

    if (amount < 0) {
        cout << "So Diem Phai Lon Hon 0!";
        return;
    }

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
            cout << "Giao Dich Thanh Cong!\n";
            u.balance -= amount;
            usr.balance += amount;

            string tx = "Da Chuyen " + to_string(amount) + " Diem toi Vi " + targetWallet;
            transactions[u.walletId].push_back(tx);
            transactions[usr.walletId].push_back("Da Nhan " + to_string(amount) + " Diem Tu Vi " + u.walletId);

            saveUsers();
            saveTransactions();
            return;
        }
    }
    cout << "Khong Tim Thay Vi.\n";
    cout << "Nhan 0 De Tro Lai:";
    int choice;
    cin >> choice;
    if(choice == 0) clearScreen();
}

//GIAO DIỆN NGƯỜI DÙNG
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

//TẠO TÀI KHOẢN NGƯỜI DÙNG
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
        string rawPass = generateRandomString(6);
        u.password = singleHash(rawPass);
        u.isTempPassword = true;
        cout << "Tao Mat Khau Tu Dong: " << rawPass << endl;
    } else {
        u.password = singleHash(pass);
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

//GIAO DIỆN QUẢN LÝ
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

//QUÊN MẬT KHẨU
void forgotPassword() {
    string username;
    cout << "Nhap Ten Dang Nhap: ";
    cin >> username;
    if (!users.count(username)) {
        cout << "Khong tim thay tai khoan.\n";
        cout << "Nhan 0 de tro lai:";
        int tmp;
        cin >> tmp;
        if (tmp == 0) clearScreen();
        return;
    }

    User &u = users[username];
    string otp = generateOTP();
    cout << "Ma OTP cua ban la: " << otp << endl;

    if (!verifyOTP(otp)) {
        cout << "OTP khong hop le. Khong the dat lai mat khau.\n";
        cout << "Nhan 0 de tro lai:";
        int tmp;
        cin >> tmp;
        if (tmp == 0) clearScreen();
        return;
    }

    cout << "Nhap Mat Khau Moi: ";
    string newPass;
    cin >> newPass;
    u.password = singleHash(newPass);
    u.isTempPassword = false;

    saveUsers();
    cout << "Dat lai mat khau thanh cong!\n";
    cout << "Nhan 0 de tro lai:";
    int tmp;
    cin >> tmp;
    if (tmp == 0) clearScreen();
}

//ĐĂNG NHẬP
void login() {
    string username, password;
    int choice;

    do {
        clearScreen();
        cout << "--- DANG NHAP HE THONG ---\n";
        cout << "1. Dang Nhap\n";
        cout << "2. Dang Ky\n";
        cout << "3. Quen Mat Khau\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Nhap Ten Dang Nhap: ";
            cin >> username;
            cout << "Nhap Mat Khau: ";
            cin >> password;

            if (users.count(username) && users[username].password == singleHash(password)) {
                User &u = users[username];
                if (u.role == "admin") {
                    adminMenu(u);
                } else {
                    userMenu(u);
                }
            } else {
                cout << "Dang nhap that bai.\n";
                cout << "Nhan 0 de thu lai:";
                int tmp;
                cin >> tmp;
                if (tmp == 0) clearScreen();
            }
        } else if (choice == 2) {
            clearScreen();
            createUser();
        } else if (choice == 3) {
            clearScreen();
            forgotPassword();
        }
    } while (choice != 0);
}

int main() {
    srand((unsigned)time(0));
    loadUsers();
    loadTransactions();
    login();
    return 0;
}
