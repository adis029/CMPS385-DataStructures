/*
Aditya Singh
9/22/2025
Cmps 385-Quiz3
*/

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

//this is the abstract Base Class
//Parent class that has all the items including
//the food and electronics
class Item {
private:
    string name;
    double price;

protected:
    //A protected constructor that only the child can call upon.
    Item(string itemName, double itemPrice) :
         name(itemName), price(itemPrice) {}
    string getBaseName() const { return name; }
    double getBasePrice() const { return price; }

public:
    virtual ~Item() {}
    //must be overriden in child classes
    virtual void display() const = 0;
    virtual double getPrice() const = 0;
    virtual void receiptEntry() const = 0;
    //getter method that searches items by name
    string getName()
    const { return name; }
};

//This is a child class of item
class FoodItem : public Item {
    string expirationDate;
public:
    FoodItem(string itemName, double itemPrice, string expiration)
        : Item(itemName, itemPrice), expirationDate(expiration) {
    }
    void display() const override {
        cout << "Name: " << getBaseName()
            << " Price:$" << fixed << setprecision(2) << getBasePrice()
            << " Exp: " << expirationDate << "\n";
    }
    double getPrice() const override { return getBasePrice(); }
    void receiptEntry() const override {
        cout << getBaseName() << " $ " << fixed << setprecision(2) << getBasePrice();
    }
};

// electronic item is a child class of item
class ElectronicItem : public Item {
    int warrantyMonths;
public:
    ElectronicItem(string itemName, double itemPrice, int warranty)
        : Item(itemName, itemPrice), warrantyMonths(warranty) {
    }
    void display() const override {
        cout << "Name: " << getBaseName()
            << " | Price: $" << fixed << setprecision(2) << getBasePrice()
            << " | Warranty: " << warrantyMonths << " months\n";
    }
    double getPrice() const override { return getBasePrice(); }
    void receiptEntry() const override {
        cout << getBaseName() << " $ " << fixed << setprecision(2) << getBasePrice();
    }
};

int main() {
    // Arrays holds purchased items and store inventory
    Item* store[50];  int storeInventory = 0;
    Item* cart[20];   int totalPurchase = 0;

    cout << "******** Welcome to QuickMart POS *********\n";
    int choice;

  

    do {
        cout << "please chooose 0-4\n ";
        cout << "1.Add item to this store\n";
        cout << "2.Display available items\n";
        cout << "3.By items by name\n";
        cout << "4.View receipts\n";
        cout << "0.exit\n";

        cin >> choice;

        if (choice == 1) { 
            //add items to store
            if (storeInventory >= 50)
            {
                cout << "storage is full (50 items max)";
                continue;
            }

            string itemType, itemName; double itemPrice;
            cout << "Enter item type either the food or electronic. ";
            cin >> itemType;
            cout << "Enter item name: ";
            getline(cin >> ws, itemName);
            cout << "Enter price: ";
            cin >> itemPrice;

            if (itemType == "Food" || itemType == "food") {
                string expirationDate;
                cout << "Enter expiration date: ";
                cin >> expirationDate;
                store[storeInventory++] = new FoodItem(itemName, itemPrice, expirationDate);
            }
            else {
                int warrantyMonth;
                cout << "Enter warranty in months: "; cin >> warrantyMonth;
                store[storeInventory++] = new ElectronicItem(itemName, itemPrice, warrantyMonth);
            }
            cout << "Item added successfully!\n";
        }
        else if (choice == 2) {
            // display items in store
            for (int i = 0; i < storeInventory; i++) store[i]->display();
        }
        else if (choice == 3) {
            // purchase item by name
            string purchaseName;
            cout << "Enter name of item to purchase: ";
            getline(cin >> ws, purchaseName);
            bool found = false;
            for (int i = 0; i < storeInventory; i++) {
                if (store[i]->getName() == purchaseName) {
                    if (totalPurchase>=20)
                    {
                        cout << "Purchase List is full maximum is 20";
                            found = true;
                            break;
                    }
                    cart[totalPurchase++] = store[i];
                    cout << "Purchased " << store[i]->getName()
                        << " for " << store[i]->getPrice() << "$ dollars\n";
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Item not found.\n";
        }
        else if (choice == 4) {
            //show the total receipt
            cout << "******** Receipt ******** \n";
            double total = 0;
            for (int i = 0; i < totalPurchase; i++) {
                cout << i + 1 << ". "; cart[i]->receiptEntry();
                cout << "\n";
                total += cart[i]->getPrice();
            }
            cout << "Total Receipt:$" << total << "\n";
        }
        else if (choice == 0) {

            cout << "Thank you for shopping at QuickMart!\n";
            for (int i = 0; i < storeInventory; i++) delete store[i];
            return 0;
        }
    } while (true); 
}
