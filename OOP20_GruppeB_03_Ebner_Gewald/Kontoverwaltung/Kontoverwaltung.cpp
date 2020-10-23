#include <iostream>
#include<string>
#include<vector>
#include <iomanip>
#include<fstream>

using namespace std;
/* 
Authors: Sabine Ebner & Alexander Gewald
Aufgabennummer 3.1
*/

int id_count = 0;

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
    int kontonr;
    vector<transaction> log;
    bool open;
public:
    
    Konto(string name="Unbekannt", double balance=0) : name(name), balance(balance), open(true)
    {
        kontonr = id_count;
        id_count++;
        transaction temp(transaction::einzahlen, balance);
        log.push_back(temp);
    }

    Konto(const Konto& other)
    {
        this->name = other.name;
        kontonr = id_count;
        id_count++;
        balance = 0;
        open = true;
        transaction temp(transaction::einzahlen, balance);
        log.push_back(temp);
    }

    void einzahlen(double value)
    {
        if (!open)
        {
            cout << "Konto wurde geschlossen - keine Transaktinen mehr möglich." << endl;
            return;
        }
        if (value<0)
        {
            value *= -1;
        }
        balance += value;
        log.insert(log.end(), transaction(transaction::einzahlen, value));
    }

    void abheben(double value)
    {
        if (!open)
        {
            cout << "Konto wurde geschlossen - keine Transaktinen mehr möglich." << endl;
            return;
        }
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
        cout << "Liste der Transaktionen von " << name <<":" << endl;
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
    //write the current Account to a file in the format it can also be read out again.
    void writetofile(string file_name=0) //every textfile is for one account
    {
        if (file_name.empty()) //if no file_name was passed, read it in from console
        {
            cout << "Name of File:" << endl;
            getline(cin, file_name);
        }
        ofstream file;
        file.open(file_name, ios_base::out);
        file << name << endl << balance << endl;
        for (int i = (int)log.size()-1; i > -1; i--)
        {
            if (log[i].tr_type==transaction::einzahlen)
            {
                file << setprecision(2) << fixed << log[i].value << endl;
            }
            else if (log[i].tr_type==transaction::auszahlen)
            {
                file << setprecision(2) << fixed << log[i].value * -1 << endl;
            }
        }
    }

    void schliessen()
    {
        if (balance==0)
        {
            open = false;
        }
        else
        {
            cout << "Kontostand muss 0 sein." << endl;
        }
    }

    void ueberweisen(Konto& other, double value)
    {
        if (!open)
        {
            cout << "Konto wurde bereits geschlossen - keine Transaktionen mehr möglich." << endl;
            return;
        }
        this->abheben(value);
        other.einzahlen(value);
        cout << "Ueberweisung von " << name << " im Wert von " << value << " an " << other.name << endl;;
    }

    double kontostand()
    {
        return balance;
    }

    void addentry(double value)
    {
        if (value < 0)
        {
            log.push_back(transaction(transaction::auszahlen, value));
        }
        else
        {
            log.push_back(transaction(transaction::einzahlen, value));
        }
    }
};

//As its own function, because this creates a new account --> can't use method of an object that doesn't exist yet
Konto readfromfile(const char* file_name) //open a new account from file
{
    ifstream file(file_name);
    if (file.is_open())
    {
        string name; //temporary places for reading out of file
        getline(file, name);
        string balance;
        getline(file, balance);
        Konto temp(name, atof(balance.c_str()));
        string str;
        double val;
        while (getline(file, str))
        {
            temp.addentry(atof(str.c_str()));
        }
        file.close();
        return temp;
    }
    else
    {
        cout << "File could not be opened. Closing Programm." << endl;
        exit(0);
    }
}

int main()
{
    Konto alex("Alex",25);
    Konto sabsi("Sabsi",10.5);
    sabsi.kontoauszug();
    alex.einzahlen(25.36);
    alex.einzahlen(20);
    alex.abheben(10);
    alex.kontoauszug();
    //Bonus:
    alex.writetofile("test.txt");
    Konto alexf = readfromfile("test.txt");
    alexf.kontoauszug();
    //Aufgabe 4:
    Konto sabsi2(sabsi);
    sabsi2.kontoauszug();
    alex.ueberweisen(sabsi2, 10);
    sabsi2.kontoauszug();
}


