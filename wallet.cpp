class Wallet {
    private:
        double balance;
        string walletID;
        vector<Transaction> history;
    
    public:
        Wallet(const string& id) : balance(0.0), walletID(id) {}
    
        double getBalance() const {
            return balance;
        }
    
        void deposit(double amount) {
            balance += amount;
        }
    
        bool withdraw(double amount) {
            if (balance >= amount) {
                balance -= amount;
                return true;
            }
            return false;
        }
    
        string getID() const {
            return walletID;
        }
    
        void addTransaction(const Transaction& tx) {
            history.push_back(tx);
        }
    
        void showHistory() const {
            cout << "Lịch sử giao dịch của ví [" << walletID << "]:\n";
            for (const auto& tx : history) {
                cout << "- Từ: " << tx.from << ", Đến: " << tx.to
                     << ", Số tiền: " << tx.amount << ", Trạng thái: " << tx.status << "\n";
            }
        }
    };
    
    class Account {
    private:
        string username;
        Wallet wallet;
    
    public:
        Account(const string& uname, const string& walletID)
            : username(uname), wallet(walletID) {
            cout << " Tài khoản \"" << username << "\" đã được tạo.\n";
        }
    
        string getUsername() const {
            return username;
        }
    
        Wallet& getWallet() {
            return wallet;
        }
    };
    
    string generateOTP() {
        srand((unsigned)time(0)); 
        int otp = rand() % 900000 + 100000; 
        return to_string(otp);
    }