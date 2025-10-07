//INCLUDES THE TXT FILES(transactions/Inventory)
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

//structure for item data
struct Item {
    string name;
    string category;
    int quantity;
    double price;
};

//structure for items transactions data
struct Transaction {
    string type;
    string itemName;
    int quantity;
    double unitPrice;
};

//function declarations
int loadInventory(Item items[]);
void saveInventory(Item items[], int count);
void saveTransaction(Transaction transaction);
void displayInventory(Item items[], int count);
void buyItem(Item items[], int count);
void returnItem(Item items[], int count);
void showProfitReport();
void addNewItem(Item items[], int& count);

// Load items from inventory.txt
int loadInventory(Item items[]) {
    ifstream fin("inventory.txt");
    if (fin.is_open()) {
        int count = 0;
        string header;
        getline(fin, header); // skip header

        while (count < 100 && fin.good()) {
            string name, category, quantityString, priceString;
            getline(fin, name, ',');
            getline(fin, category, ',');
            getline(fin, quantityString, ',');
            getline(fin, priceString, '\n');

            if (name.empty()) break;

            items[count].name = name;
            items[count].category = category;
            items[count].quantity = stoi(quantityString);
            items[count].price = stod(priceString);
            count++;
        }
        fin.close();
        return count;
    }
    return 0;
}

// Save any new inventory data
void saveInventory(Item items[], int count) {
    ofstream fout("inventory.txt");
    fout << "Name,Category,Quantity,Price\n";
    for (int i = 0; i < count; i++) {
        fout << items[i].name << "," << items[i].category << ","
            << items[i].quantity << "," << fixed << setprecision(2)
            << items[i].price << "\n";
    }
    fout.close();
}

// Record every transaction
void saveTransaction(Transaction transaction) {
    ofstream fout("transactions.txt", ios::app);
    if (fout.tellp() == 0)
        fout << "Type,ItemName,Quantity,UnitPrice\n";
    fout << transaction.type << "," << transaction.itemName << ","
        << transaction.quantity << "," << fixed << setprecision(2)
        << transaction.unitPrice << "\n";
    fout.close();
}

// show inventory
void displayInventory(Item items[], int count) {
    cout << "\n*** Inventory ***\n";
    cout << "Name\tCategory\tQuantity\tPrice\n\n";
    for (int i = 0; i < count; i++) {
        cout << items[i].name << "\t" << items[i].category << "\t"
            << items[i].quantity << "\t$" << fixed << setprecision(2)
            << items[i].price << endl;
    }
    cout << endl;
}

// Add new item
void addNewItem(Item items[], int& count) {
    if (count >= 100) {
        cout << "Inventory full!\n";
        return;
    }
    Item temp;
    cout << "Enter item name: ";
    cin >> ws;
    getline(cin, temp.name);
    while (temp.name.empty()) {
        cout << "PLEASE INPUT AGAIN! Enter item name: ";
        getline(cin, temp.name);
    }
    cout << "Enter category: ";
    getline(cin, temp.category);
    while (temp.category.empty()) {
        cout << "PLEASE INPUT AGAIN! Enter category: ";
        getline(cin, temp.category);
    }
    cout << "Enter quantity: ";
    cin >> temp.quantity;
    while (cin.fail() || temp.quantity <= 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "PLEASE INPUT AGAIN! Enter quantity: ";
        cin >> temp.quantity;
    }
    cout << "Enter price: ";
    cin >> temp.price;
    while (cin.fail() || temp.price <= 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "PLEASE INPUT AGAIN! Enter price: ";
        cin >> temp.price;
    }

    items[count] = temp;
    count++;
    cout << "Item added!\n";
}

// Buying item
void buyItem(Item items[], int count) {
    string itemName;
    int quantityInput;
    cout << "Enter item to buy: ";
    cin >> ws;
    getline(cin, itemName);
    while (itemName.empty()) {
        cout << "PLEASE INPUT AGAIN! Enter item to buy: ";
        getline(cin, itemName);
    }
    cout << "Quantity: ";
    cin >> quantityInput;
    while (cin.fail() || quantityInput <= 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "PLEASE INPUT AGAIN! Enter quantity: ";
        cin >> quantityInput;
    }
    for (int i = 0; i < count; i++) {
        if (items[i].name == itemName) {
            if (items[i].quantity < quantityInput) {
                cout << "Not enough stock!\n";
                return;
            }
            items[i].quantity -= quantityInput;
            double total = quantityInput * items[i].price;
            Transaction transaction = { "BUY", itemName, quantityInput, items[i].price };
            saveTransaction(transaction);
            cout << "Successfully purchased " << quantityInput << " x " << itemName
                << " for $" << fixed << setprecision(2) << total << endl;
            return;
        }
    }
    cout << "Item not found!\n";
}

// Return item
void returnItem(Item items[], int count) {
    string itemName;
    int quantityInput;
    cout << "Enter item to return: ";
    cin >> ws;
    getline(cin, itemName);
    while (itemName.empty()) {
        cout << "PLEASE INPUT AGAIN! Enter item to return: ";
        getline(cin, itemName);
    }
    cout << "Quantity: ";
    cin >> quantityInput;
    while (cin.fail() || quantityInput <= 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "PLEASE INPUT AGAIN! Enter quantity: ";
        cin >> quantityInput;
    }
    for (int i = 0; i < count; i++) {
        if (items[i].name == itemName) {
            items[i].quantity += quantityInput;
            Transaction transaction = { "RETURN", itemName, quantityInput, items[i].price };
            saveTransaction(transaction);
            cout << quantityInput << " x " << itemName
                << " returned and added back to inventory.\n";
            return;
        }
    }
    cout << "Item not found!\n";
}

// Profit report
void showProfitReport() {
    ifstream fin("transactions.txt");
    if (fin.is_open()) {
        string header;
        getline(fin, header);
        double revenue = 0, refunds = 0;
        string type, itemName, quantityString, priceString;
        while (getline(fin, type, ',') &&
            getline(fin, itemName, ',') &&
            getline(fin, quantityString, ',') &&
            getline(fin, priceString, '\n')) {
            if (type.empty()) continue;
            int quantity = stoi(quantityString);
            double price = stod(priceString);
            double total = quantity * price;
            if (type == "BUY") revenue += total;
            else if (type == "RETURN") refunds += total;
        }
        fin.close();
        cout << "\nProfit Report\n";
        cout << "Revenue: $" << fixed << setprecision(2) << revenue << endl;
        cout << "Refunds: $" << fixed << setprecision(2) << refunds << endl;
        cout << "Net Profit: $" << fixed << setprecision(2)
            << (revenue - refunds) << endl;
    }
    else {
        cout << "No transactions found.\n";
    }
}

int main() {
    Item items[100];
    int count = loadInventory(items);
    int choice = 0;
    cout << "******** Welcome to Store Inventory and Profit Tracker ********\n";
    while (choice != 6) {
        cout << "Choose one option:\n";
        cout << "1. Add Item\n 2. Display Inventory\n 3. Buy Item\n4. Return Item\n5. Profit Report\n6. Exit\n";
        cin >> choice;
        while (cin.fail() || choice < 1 || choice > 6) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "PLEASE INPUT AGAIN! Enter 1-6: ";
            cin >> choice;
        }
        if (choice == 1) addNewItem(items, count);
        else if (choice == 2) displayInventory(items, count);
        else if (choice == 3) buyItem(items, count);
        else if (choice == 4) returnItem(items, count);
        else if (choice == 5) showProfitReport();
        else if (choice == 6) {
            saveInventory(items, count);
            cout << "Inventory and transactions have been saved.\n";
        }
    }
    return 0;
}
