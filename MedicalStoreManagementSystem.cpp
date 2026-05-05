#include <iostream>
using namespace std;

//Base Class
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

    // Virtual Function (Abstraction)
    virtual void display() = 0;
};

// Tablet Class
class Tablet : public Medicine {
public:
    void display() {
        cout << "[Tablet] " << id << " " << name << " " << price << " " << quantity << endl;
    }
};

// Syrup Class
class Syrup : public Medicine {
public:
    void display() {
        cout << "[Syrup] " << id << " " << name << " " << price << " " << quantity << endl;
    }
};

//Medical Store System
class MedicalStore {
    Medicine* m[100];
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

        if(q <= 0 || p <= 0) {
            cout << "Invalid input!\n";
            return;
        }

        m[count] = new Tablet();
        m[count]->setData(id, n, p, q);
        count++;

        cout << "Tablet Added!\n";
    }

    void addSyrup() {
        int id, q;
        float p;
        string n;

        cout << "Enter ID Name Price Qty: ";
        cin >> id >> n >> p >> q;

        if(q <= 0 || p <= 0) {
            cout << "Invalid input!\n";
            return;
        }

        m[count] = new Syrup();
        m[count]->setData(id, n, p, q);
        count++;

        cout << "Syrup Added!\n";
    }

    void viewAll() {
        if(count == 0) {
            cout << "No medicines available!\n";
            return;
        }

        cout << "\n--- Medicine List ---\n";
        for(int i = 0; i < count; i++) {
            cout << i << ". ";
            m[i]->display();   // polymorphism
        }
    }

    void search() {
        int id;
        bool found = false;

        cout << "Enter ID: ";
        cin >> id;

        cout << "\n--- Search Result ---\n";

        for(int i = 0; i < count; i++) {
            if(m[i]->getId() == id) {
                m[i]->display();   // polymorphism
                found = true;
            }
        }

        if(!found)
            cout << "Medicine not found!\n";
    }

    void billing() {
        int id, qty, choice;
        bool found = false;

        cout << "Enter ID: ";
        cin >> id;

        cout << "\nAvailable Medicines:\n";

        for(int i = 0; i < count; i++) {
            if(m[i]->getId() == id) {
                cout << i << ". ";
                m[i]->display();
                found = true;
            }
        }

        if(!found) {
            cout << "Medicine not found!\n";
            return;
        }

        cout << "Select index: ";
        cin >> choice;

        if(choice < 0 || choice >= count || m[choice]->getId() != id) {
            cout << "Invalid selection!\n";
            return;
        }

        cout << "Enter Quantity: ";
        cin >> qty;

        if(qty <= 0) {
            cout << "Invalid quantity!\n";
            return;
        }

        if(qty > m[choice]->getQty()) {
            cout << "Not enough stock!\n";
            return;
        }

        float total = m[choice]->getPrice() * qty;

        cout << "\n--- BILL ---\n";
        m[choice]->display();
        cout << "Qty: " << qty << endl;
        cout << "Total: " << total << endl;

        m[choice]->reduceStock(qty);
        cout << "Stock updated!\n";
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

        if(ch < 1 || ch > 6) {
            cout << "Invalid choice!\n";
            continue;
        }

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
