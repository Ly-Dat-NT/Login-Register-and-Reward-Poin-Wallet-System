#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cstdlib>  
#include <ctime>    
using namespace std;
int main() {
    unordered_map<string, Account> accounts;
    accounts.emplace("admin", Account("admin", "WALLET-ADMIN"));
    accounts.find("admin")->second.getWallet().deposit(1000000); 
    string command;

    while (true) {
        cout << "\n========= MENU =========\n";
        cout << "1. Tạo tài khoản\n";
        cout << "2. Nạp tiền\n";
        cout << "3. Chuyển tiền \n";
        cout << "4. Xem số dư\n";
        cout << "5. Xem lịch sử giao dịch\n";
        cout << "0. Thoát\n";
        cout << "Chọn thao tác: ";
        cin >> command;

        if (command == "1") {
            string username, walletID;
            cout << "Nhập tên tài khoản: ";
            cin >> username;
            walletID = "WALLET-" + username;

            if (accounts.find(username) != accounts.end()) {
                cout << "️ Tài khoản đã tồn tại.\n";
            } else {
                accounts.emplace(username, Account(username, walletID));
            }

        } else if (command == "2") {
            string username;
            double amount;
            cout << "Nhập tên tài khoản muốn nạp tiền: ";
            cin >> username;

            auto itUser = accounts.find(username);
            auto itAdmin = accounts.find("admin");
            if (itUser == accounts.end()) {
                cout << "️ Không tìm thấy tài khoản.\n";
                continue;
            }
            if (itAdmin == accounts.end()) {
                cout << "️ Ví tổng chưa được khởi tạo.\n";
                continue;
            }

            cout << "Nhập số tiền muốn nạp: ";
            cin >> amount;

            Wallet& adminWallet = itAdmin->second.getWallet();
            Wallet& userWallet = itUser->second.getWallet();

            if (adminWallet.withdraw(amount)) {
                userWallet.deposit(amount);
                Transaction tx("admin", username, amount, "Thành công");
                adminWallet.addTransaction(tx);
                userWallet.addTransaction(tx);
                cout << " Nạp tiền thành công.\n";
            } else {
                cout << " Ví tổng không đủ tiền để nạp.\n";
            }

        } else if (command == "3") {
            string from, to;
            double amount;
            cout << "Nhập tài khoản gửi: ";
            cin >> from;
            cout << "Nhập tài khoản nhận: ";
            cin >> to;
            auto itFrom = accounts.find(from);
            auto itTo = accounts.find(to);
            if (itFrom == accounts.end() || itTo == accounts.end()) {
                cout << "️ Tài khoản không tồn tại.\n";
                continue;
            }
            cout << "Nhập số tiền muốn chuyển: ";
            cin >> amount;                                          
            Wallet& fromWallet = itFrom->second.getWallet(); 
            Wallet& toWallet = itTo->second.getWallet();
            string otp = generateOTP();
            cout << "OTP xác thực giao dịch: " << otp << "\n";
            cout << "Nhập OTP: ";
            string userOTP;
            cin >> userOTP;
            if (userOTP != otp) {      
                cout << "OTP không đúng. Giao dịch bị hủy.\n";
                Transaction tx(from, to, amount, "Thất bại: OTP sai");
                fromWallet.addTransaction(tx);
                continue;
            }
                if (fromWallet.getBalance() >= amount) {
                if (fromWallet.withdraw(amount)) {
                    toWallet.deposit(amount);
                Transaction tx(from, to, amount, "Thành công");
                    fromWallet.addTransaction(tx);
                    toWallet.addTransaction(tx);
                cout << " Chuyển tiền thành công.\n";
                } else {
                    cout << " Không đủ số dư.\n";
                    Transaction tx(from, to, amount, "Thất bại: không đủ tiền");
                    fromWallet.addTransaction(tx);
                }
            } else {
                cout << " Số dư không đủ để chuyển tiền.\n";
                Transaction tx(from, to, amount, "Thất bại: không đủ tiền");
                fromWallet.addTransaction(tx);
            }
        } else if (command == "4") {
            string username;
            cout << "Nhập tài khoản: ";
            cin >> username;
            auto itUser = accounts.find(username);
            if (itUser != accounts.end()) {
                cout << "Số dư của " << username << ": "
                     << itUser->second.getWallet().getBalance() << "\n";
            } else {
                cout << "️ Tài khoản không tồn tại.\n";
            }
        } else if (command == "5") {
            string username;
            cout << "Nhập tài khoản: ";
            cin >> username;
            auto itUser = accounts.find(username);
            if (itUser != accounts.end()) {
                itUser->second.getWallet().showHistory();
            } else {
                cout << "️ Tài khoản không tồn tại.\n";
            }
        } else if (command == "0") {
            cout << " Tạm biệt!\n";
            break;
        } else {
            cout << " Lệnh không hợp lệ.\n";
        }
    }
    return 0;
}