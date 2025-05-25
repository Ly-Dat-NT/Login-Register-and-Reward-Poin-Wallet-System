class Transaction {
    public:
        string from;
        string to;
        double amount;
        string status;
        Transaction(const string& f, const string& t, double a, const string& s)
            : from(f), to(t), amount(a), status(s) {}
    };