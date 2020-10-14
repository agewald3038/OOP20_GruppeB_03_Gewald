#include <iostream>
#include<string>
#include<vector>


using namespace std;


struct transaction
{
    enum tr_enum { //would also work with bool, but it's not as fancy
        einzahlen,
        auszahlen
    };
    tr_enum tr_type;
    double value;
    transaction(tr_enum c_type, double c_value) : tr_type(c_type), value(c_value)
    {

    }
};

class Konto
{
    string name;
    double balance;
    vector<transaction> log;
public:
    void kontoeroeffnung(string name, double balance = 0)
    {
        if (balance>=0)
        {
            this->name = name;
            this->balance = balance;
            cout << "Konto von " << name << " wurde eroeffnet." << endl;
            log.insert(log.end(), transaction(transaction::einzahlen, balance));
        }
        else
        {
            cout << "Kein negativer Betrag bei Kontoeroeffnung!" << endl;
        }
    }

    void einzahlen(double value)
    {
        if (value<0)
        {
            cout << "Nur positive Zahlen bitte." << endl;
            value *= -1;
        }
        balance += value;
        log.insert(log.end(), transaction(transaction::einzahlen, value));
    }
    void auszahlen(double value)
    {
        if (value<0)
        {
            value *= -1;
        }
        if (value > balance)
        {
            cout << "Nicht genug Geld am Konto!" << endl;
            return;
        }
        balance -= value;
        log.insert(log.end(), transaction(transaction::auszahlen, value));
    }
};


int main()
{
    Konto bla;
    bla.kontoeroeffnung("Alexander", 50);
}