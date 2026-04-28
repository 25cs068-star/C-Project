#include <iostream>
using namespace std;

// Base Class
class Medicine {
protected:
    int id;
    string name;
    float price;
    int quantity;

public:
    void setData(int i, string n, float p, int q) {
        id = i;
        name = n;
        price = p;
        quantity = q;
    }

    int getId() { return id; }
    float getPrice() { return price; }
    int getQty() { return quantity; }

    void reduceStock(int q) {
        quantity -= q;
    }

    virtual void display() {
        cout << id << " " << name << " " << price << " " << quantity;
    }
};

// Tablet Derived Class
class Tablet : public Medicine {
public:
    void display() {
        cout << "[Tablet] ";
        Medicine::display();
        cout << endl;
    }
};

//Syrup-Derived Class
class Syrup : public Medicine {
public:
    void display() {
        cout << "[Syrup] ";
        Medicine::display();
        cout << endl;
    }
};

// Main System Class
class MedicalStore {
    Medicine m[100];
    int type[100]; // 1 = Tablet, 2 = Syrup
    int count;

public:
    MedicalStore() {
        count = 0;
    }

    void addTablet() {
        int id, q;
        float p;
        string n;

        cout << "Enter ID Name Price Qty: ";
        cin >> id >> n >> p >> q;

        m[count].setData(id, n, p, q);
        type[count] = 1;
        count++;

        cout << "Tablet Added!\n";
    }

    void addSyrup() {
        int id, q;
        float p;
        string n;

        cout << "Enter ID Name Price Qty: ";
        cin >> id >> n >> p >> q;

        m[count].setData(id, n, p, q);
        type[count] = 2;
        count++;

        cout << "Syrup Added!\n";
    }

    void viewAll() {
        for(int i = 0; i < count; i++) {
            if(type[i] == 1)
                cout << "[Tablet] ";
            else
                cout << "[Syrup] ";

            m[i].display();
            cout << endl;
        }
    }

    void search() {
        int id;
        bool found = false;

        cout << "Enter ID: ";
        cin >> id;

        for(int i = 0; i < count; i++) {
            if(m[i].getId() == id) {
                if(type[i] == 1)
                    cout << "[Tablet] ";
                else
                    cout << "[Syrup] ";

                m[i].display();
                cout << endl;
                found = true;
            }
        }

        if(!found) cout << "Not found!\n";
    }

    void billing() {
        int id, qty, t;

        cout << "Enter ID & Qty: ";
        cin >> id >> qty;

        cout << "Type (1=Tablet, 2=Syrup): ";
        cin >> t;

        for(int i = 0; i < count; i++) {
            if(m[i].getId() == id && type[i] == t) {

                if(qty > m[i].getQty()) {
                    cout << "Not enough stock!\n";
                    return;
                }

                float total = m[i].getPrice() * qty;

                cout << "\n--- BILL ---\n";
                m[i].display();
                cout << "\nQty: " << qty;
                cout << "\nTotal: " << total << endl;

                m[i].reduceStock(qty);
                return;
            }
        }

        cout << "Medicine not found!\n";
    }
};

//Main
int main() {
    MedicalStore obj;
    int ch;

    do {
        cout << "\n===== MEDICAL STORE =====\n";
        cout << "1 Add Tablet\n2 Add Syrup\n3 View\n4 Search\n5 Billing\n6 Exit\n";
        cout << "Enter: ";
        cin >> ch;

        switch(ch) {
            case 1: obj.addTablet(); break;
            case 2: obj.addSyrup(); break;
            case 3: obj.viewAll(); break;
            case 4: obj.search(); break;
            case 5: obj.billing(); break;
        }

    } while(ch != 6);

    return 0;
}
