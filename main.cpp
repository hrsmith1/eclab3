#include <iostream>
#include <string>
using namespace std;


class Account{
    private:
        string acctNum;
        string acctHolder;
        int balance;
    public: 
        Account();
        virtual void displayDetails();
        int deposit(int amount);
        virtual bool withdrawl(int amount);
        friend class savingsAccount;
        friend class currentAccount;
};
Account:: Account(){
}
void Account::displayDetails(){
    cout<<"Account Holder:"<<acctHolder<<endl;
    cout<<"Balance: $"<<balance<<endl;

}
int Account::deposit(int amount){
    if (amount > 0){
        balance+= amount;

    }
    else{
        cout<<"You have tired to deposit an invlaid amount"<<endl;
    }
    return balance;
}
bool Account::withdrawl(int amount){
    if (amount< balance && amount>0){
        balance -= amount;
        return true;
    }
    else return false;

}
class savingsAccount : public Account
{
private:
    float interestRate;
public:
    savingsAccount(string num, string name, int intal, float rate);
    void displayDetails();
    bool withdrawl(int amount);
    friend ostream& operator<<(ostream& COUT, savingsAccount& genacct);
    savingsAccount& operator+(Account& genacct);
};
savingsAccount::savingsAccount(string num, string name, int intal, float rate){
    acctNum = num;
    acctHolder = name;
    balance = intal;
    interestRate = rate;
}
void savingsAccount::displayDetails(){
    cout<< "Account Details for Saving Account("<<acctNum<<")"<<endl;
    Account::displayDetails();
    cout<<"Interest Rate:"<<interestRate<<"%"<<endl;
}
bool savingsAccount:: withdrawl(int amount){
        if (amount > 0 && balance - amount >= 1000){
            balance -= amount;
            return true;
        }
        else{
            cout<<"You have tired to withdraw an invalid ammount"<<endl;
            return false;
        }
}
ostream& operator<<(ostream& COUT, savingsAccount& genacct) {
    genacct.displayDetails();
    return COUT;
}
savingsAccount& savingsAccount::operator+(Account& genacct){
    if (genacct.withdrawl(300)){
        this->deposit(300);}
    return *this;
}

class currentAccount : public Account
{
public:
    currentAccount(string num, string name, int intal, int limit);
    int overdraftLim;
    void displayDetails();
    bool withdrawl(int amount);
    friend ostream& operator<<(ostream& COUT, currentAccount& genacct);
    currentAccount& operator+(Account& genacct);
};
currentAccount::currentAccount(string num, string name, int intal, int limit){
    acctNum = num;
    acctHolder = name;
    balance = intal;
    overdraftLim = limit;
}
void currentAccount::displayDetails(){
    cout<< "Account Details for Current Account("<<acctNum<<")"<<endl;
    Account::displayDetails();
    cout<<"Overdraft Limit: $"<<overdraftLim<<endl;
}
bool currentAccount::withdrawl(int amount){
    if (amount>0 && balance-amount >= -overdraftLim){
        balance -= amount;
        return true;}
    else{
        cout<<"you have tried to withdraw an invalid amount"<<endl;
        return false;
    }
}
ostream& operator<<(ostream& COUT, currentAccount& genacct){
    genacct.displayDetails();
    return COUT;
}
currentAccount& currentAccount::operator+(Account& genacct){
    if (genacct.withdrawl(300)){
        this->deposit(300);}
    
    return *this;
}
int main(){
    savingsAccount savings("S123", "John Doe", 1300, 0.02);
    currentAccount current("C456", "Jane Doe", 2300, 500);
    cout<<"prints after initalization"<<endl;
    cout<<savings<<endl<<current<<endl;
    
    savings.withdrawl(300);
    current.withdrawl(2600);
    cout<<"account prints after withdrawls"<<endl;
    cout<<savings<<endl<<current<<endl;

    savings = savings + current;
    current = current + savings;
    cout<<"transfers that don't work"<<endl;
    cout<<savings<<endl<<current<<endl;

    cout<<"account and balance prints after deposits"<<endl;
    cout<<"balence of savings is $"<<savings.deposit(500)<<endl;
    cout<<"balence of current is $"<<current.deposit(2400)<<endl;
    cout<<savings<<endl<<current<<endl;

    savings = savings + current;
    current = current + savings;
    cout<<"transfers that do work"<<endl;
    cout<<savings<<endl<<current<<endl;

    return 1;

}