#include <iostream>
#include<string>
#include<vector>
#include <iomanip>

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
    void kontoeroeffnung(string name, double balance = 0)//method that does the job of a constructor
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
    void abheben(double value)
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

    void kontoauszug()
    {
        cout << "Liste der Transaktionen:" << endl;
        for (int i=(int)log.size() - 1; i>=0; i--)
        {
            if (log[i].tr_type==transaction::einzahlen)
            {
                cout << "Einzahlung von: " << setprecision(2) << fixed << log[i].value << " Euro" << endl;
            }
            else
            {
                cout << "Abhebung von: " << setprecision(2) << fixed <<log[i].value << " Euro" << endl;
            }
        }
    }
};


int main()
{
    Konto bla;
    bla.kontoeroeffnung("Alexander", 50);
    bla.einzahlen(25.36);
    bla.einzahlen(20);
    bla.abheben(10);
    bla.kontoauszug();
}