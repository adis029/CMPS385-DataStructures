
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <type_traits>

using namespace std;

//Templated Data Types for packages
// T1 = ID type (int/string)
// T2 = Fee Type (float/double)
template <typename T1, typename T2>
struct Package {
    T1 id; 
    string name;
    string type; //standard/express/Fragile
    int etaHours;
    T2 fee;
    string status; //pending or delivered
};

//Function Declarations 
template <typename T1, typename T2>
int loadPackages(Package<T1, T2> pkgs[]);
template <typename T1, typename T2>
void savePackages(Package<T1, T2> pkgs[], int count);
template <typename T1, typename T2>
void addPackage(Package<T1, T2> pkgs[], int& count);
template <typename T1, typename T2>
void displayPackages(Package<T1, T2> pkgs[], int count);
template <typename T1, typename T2>
void markDelivered(Package<T1, T2> pkgs[], int count);
template <typename T1, typename T2>
void deliveryReport(Package<T1, T2> pkgs[], int count);

// Load packages reads the packages from the csv text files
//this skips the first header line
//fills the array up to 100
// returns how many were loaded on

template <typename T1, typename T2>
int loadPackages(Package<T1, T2> pkgs[]) {
    ifstream fin("packages.txt");
    if (!fin.is_open()) return 0;
    string header; getline(fin, header);

    int count = 0;
    while (count < 100 && fin.good()) {
        string idStr, name, type, etaStr, feeStr, status;
        if (!getline(fin, idStr, ',')) break;
        getline(fin, name, ',');
        getline(fin, type, ',');
        getline(fin, etaStr, ',');
        getline(fin, feeStr, ',');
        getline(fin, status, '\n');

        if (idStr.empty()) break;

        if constexpr (std::is_same_v<T1, std::string>) {
            pkgs[count].id = idStr;
        }
        else {
            pkgs[count].id = static_cast<T1>(stoi(idStr));
        }

        pkgs[count].name = name;
        pkgs[count].type = type;
        pkgs[count].etaHours = stoi(etaStr);
        pkgs[count].fee = (T2)stod(feeStr);
        pkgs[count].status = status.empty() ? string("Pending") : status;
        count++;
    }
    fin.close();
    return count;
}
// writes all in memory packages to packages txt which only happens on the exit
template <typename T1, typename T2>
void savePackages(Package<T1, T2> pkgs[], int count) {
    ofstream fout("packages.txt");
    fout << "ID,Name,Type,ETA,Fee,Status\n";
    for (int i = 0; i < count; i++) {
        fout << pkgs[i].id << ","
            << pkgs[i].name << ","
            << pkgs[i].type << ","
            << pkgs[i].etaHours << ","
            << fixed << setprecision(2) << (double)pkgs[i].fee << ","
            << pkgs[i].status << "\n";
    }
    fout.close();
}

//Asks the users for a new package and stores it into a memory
//Does not write the file until the user exits and validates inputs
template <typename T1, typename T2>
void addPackage(Package<T1, T2> pkgs[], int& count) {
    if (count >= 100) { cout << "List full!\n"; return; }
    Package<T1, T2> p;

    cout << "Enter package ID: ";
    if constexpr (std::is_same_v<T1, std::string>) {
        cin >> ws;
        getline(cin, p.id);
        while (p.id.empty()) {
            cout << "PLEASE INPUT AGAIN! Enter package ID: ";
            getline(cin, p.id);
        }
    }
    else {
        cin >> p.id;
        while (cin.fail()) {
            cin.clear(); cin.ignore(1000, '\n');
            cout << "PLEASE INPUT AGAIN! Enter package ID: ";
            cin >> p.id;
        }
    }
    cout << "Enter recipient name: ";
    cin >> ws;
    getline(cin, p.name);
    while (p.name.empty()) {
        cout << "PLEASE INPUT AGAIN! Enter recipient name: ";
        getline(cin, p.name);
    }
    cout << "Enter delivery type (Standard/Express/Fragile): ";
    getline(cin, p.type);
    while (p.type.empty()) {
        cout << "PLEASE INPUT AGAIN! Enter delivery type: ";
        getline(cin, p.type);
    }

    cout << "Enter delivery ETA (in hours): ";
    cin >> p.etaHours;
    while (cin.fail() || p.etaHours <= 0) {
        cin.clear(); cin.ignore(1000, '\n');
        cout << "PLEASE INPUT AGAIN! Enter delivery ETA (in hours): ";
        cin >> p.etaHours;
    }

    cout << "Enter delivery fee: ";
    double feeTemp;
    cin >> feeTemp;
    while (cin.fail() || feeTemp < 0) {
        cin.clear(); cin.ignore(1000, '\n');
        cout << "PLEASE INPUT AGAIN! Enter delivery fee: ";
        cin >> feeTemp;
    }
    p.fee = (T2)feeTemp;

    p.status = "Pending";
    pkgs[count] = p;
    count++;
    cout << "Package added!\n";
}

// shows whats currently on the file and not in memory which means
//until you exit the items wont show here

template <typename T1, typename T2>
void displayPackages(Package<T1, T2> [], int ) {
    Package<T1, T2> temp[100];
    int loaded = loadPackages(temp);

    cout << "\n Packages\n";
    cout << "ID\tName\tType\tETA\tFee\tStatus\n";
    cout << "\n";
    for (int i = 0; i < loaded; i++) {
        cout << temp[i].id << "\t"
            << temp[i].name << "\t"
            << temp[i].type << "\t"
            << temp[i].etaHours << "\t$"
            << fixed << setprecision(2) << (double)temp[i].fee << "\t"
            << temp[i].status << "\n";
    }
    cout << endl;
}
// Marks one package as delivered in memory and does not write file until exits
template <typename T1, typename T2>
void markDelivered(Package<T1, T2> pkgs[], int count) {
    T1 idIn;
    cout << "Enter package ID to mark as delivered: ";
    if constexpr (std::is_same_v<T1, std::string>) {
        cin >> ws;
        getline(cin, idIn);
        while (idIn.empty()) {
            cout << "PLEASE INPUT AGAIN! Enter package ID to mark as delivered. ";
            getline(cin, idIn);
        }
    }
    else {
       cin >> idIn;
        while (cin.fail()) {
            cin.clear(); cin.ignore(1000, '\n');
            cout << "PLEASE INPUT AGAIN! Enter package ID to mark as delivered.  ";
            cin >> idIn;
        }
    }

    for (int i = 0; i < count; i++) {
        if (pkgs[i].id == idIn) {
            pkgs[i].status = "Delivered";
            cout << "Package " << pkgs[i].id << " marked as Delivered.\n";
            return;
        }
    }
    cout << "Package was not found.\n";
}

//shows total from whats in memory and it adds up all fees of the delivered
//packages as the total revenue
template <typename T1, typename T2>
void deliveryReport(Package<T1, T2> pkgs[], int count) {
    int delivered = 0;
    double revenue = 0.0;
    for (int i = 0; i < count; i++) {
        if (pkgs[i].status == "Delivered") {
            delivered+=1;
            revenue += (double)pkgs[i].fee;
        }
    }
    int pending = count - delivered;

    cout << "\nDelivery Report\n";
    cout << "Total Packages: " << count << endl;
    cout << "Delivered: " << delivered << endl;
    cout << "Pending: " << pending << endl;
    cout << "Total Revenue: $" << fixed << setprecision(2) << revenue << endl;
}

int main() {
    Package<int, double> packages[100];
    int count = loadPackages(packages);
    int choice = 0;

    cout << "******** Welcome to Package Delivery Tracker ********\n";
    while (choice != 5) {
        cout << "Please choose one of the following \n";
        cout << "1.Add New Package\n";
        cout << "2.Display All Packages\n";
        cout << "3.Mark Package as Delivered\n";
        cout << "4.View Delivery Report\n";
        cout << "5. Exit\n ";


        cin >> choice;
        while (cin.fail() || choice < 1 || choice > 5) {
            cin.clear(); cin.ignore(1000, '\n');
            cout << "PLEASE INPUT AGAIN! Enter 1-5: ";
            cin >> choice;
        }

        if (choice == 1)
            addPackage(packages, count);
        else if (choice == 2)
            displayPackages(packages, count);
        else if (choice == 3)
            markDelivered(packages, count);
        else if (choice == 4)
            deliveryReport(packages, count);
        else if (choice == 5) {
            savePackages(packages, count);
            cout << " Your Data is saved within the packages.txt file now. \n";
        }
    }
    return 0;
}
