#include <iostream>
#include<string>
#include<vector>
#include <iomanip>

using namespace std;
/* 
Authors: Sabine Ebner & Alexander Gewald
Aufgabennummer 3.1
*/

struct transaction
{
    enum tr_enum { //would also work with bool, but it's not as fancy
        einzahlen,
        auszahlen
    };
    tr_enum tr_type;
    double value;
    transaction(tr_enum c_type, double c_value) : tr_type(c_type), value(c_value) //constructor with initialization list. Constructor is really needed here, otherwise making new transaction entries would be a lot more complicated
    {

    }
};

class Konto
{
    string name;
    double balance;
    vector<transaction> log;
public:
    void kontoeroeffnung(string name, double balance = 0)//method, because this one has to be a method according to the task | =0 is so that if no balance is passed, it will go to 0 by default
    {
        if (balance>-1) //no negative balance allowed
        {
            this->name = name;
            this->balance = balance;
            cout << "Konto von " << name << " wurde eroeffnet." << endl;
            log.insert(log.end(), transaction(transaction::einzahlen, balance)); //constructing a new "transaction" and putting it into the vector
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
        if (value > balance) //because it isn't allowed to become negative
        {
            cout << "Nicht genug Geld am Konto!" << endl;
            return;
        }
        balance -= value;
        log.insert(log.end(), transaction(transaction::auszahlen, value));
    }

    void kontoauszug() // prints all transactions to console, from newest to oldest
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
    Konto alex;
    Konto sabsi;
    sabsi.kontoeroeffnung("Sabsi");
    sabsi.kontoauszug();
    alex.kontoeroeffnung("Alexander", 50);
    alex.einzahlen(25.36);
    alex.einzahlen(20);
    alex.abheben(10);
    alex.kontoauszug();
}