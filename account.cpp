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