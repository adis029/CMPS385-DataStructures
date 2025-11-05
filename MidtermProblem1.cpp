//problem 1 Warehouse Inventory Stack Tracker

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

const int stackMax = 100; // max number of boxes this stack can hold

struct Box {
    int id;
    string item;
    float weight;
    string destination;
};

//The stack storage (array) and an index pointing to the top element

Box stack[stackMax];
int topIndex = -1; // we use the index of -1 to know that its empty

//returns true if stack is empty
bool isEmpty()
{
    return topIndex == -1;
}
//returns true if stack is full
bool isFull()
{
    return topIndex == stackMax - 1;
}

//Adds one box to the tops of the stack
void addBox() {
    if (isFull()) {
        cout << "This stack is full you cannot add any other boxes." << endl;
        return;
    }

    //prompts users for fields for box instructions
    Box b;
    cout << "enter your box ID:";
    cin >> b.id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "enter your item name";
    getline(cin, b.item);

    cout << "enter the items weight in kg";
    cin >> b.weight;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "enter desinitation you are sending package to.";
    getline(cin, b.destination);

    stack[++topIndex] = b;
    cout << "This box has bee added to the new stack on top!";
}
//shows all boxes
void viewStack() {
    if (isEmpty()) {
        cout << "(No boxes in stack)\n";
        return;
    }
    cout << fixed << setprecision(1);
    for (int i = topIndex; i >= 0; --i) {
        cout << stack[i].id << " "
            << stack[i].item << " "
            << stack[i].weight << " "
            << stack[i].destination << "\n";
    }
}
//removes the top box and dispatches it
void removeTopBox() {
    if (isEmpty()) {
        cout << "The stack is empty there are no requried boxes to dispatch or remove now " << endl;
        return;
    }
    Box b = stack[topIndex--];
    cout << "This top box has been removed (dispatched)" << endl;
    cout << "ID:  " << b.id << ",Item name: " << b.item << "Desintation sent: " << b.destination << endl;
}
//shows how many boxes there are, their total weight, and info about the top boxes
void summary() {
    cout << "=============Inventory Summary=============" << endl;
    int count = topIndex + 1;
    float total = 0.0;
    for (int i = 0; i <= topIndex; ++i) total += stack[i].weight;

    cout << "Total Boxes in the Stack: " << count << "\n" << fixed << setprecision(1);
    cout << "Total Weight: " << total << " kg\n";

    if (!isEmpty())
        cout << "Top Box: ID " << stack[topIndex].id << " - " << stack[topIndex].item << "\n";
    else
        cout << "There is no Top Box\n";
    cout << "=======================================\n";
}
//Saves current stacks to inventory.txt
void saveToFile() {
    ofstream out("inventory.txt");
    if (!out) return;
    out << "ID,Item,Weight,Destination\n";
    out << fixed << setprecision(1);
    for (int i = topIndex; i >= 0; --i) {
        out << stack[i].id << ","
            << stack[i].item << ","
            << stack[i].weight << ","
            << stack[i].destination << "\n";
    }
    out.close();
}

int main() {
    cout << "===== Welcome to the Warehouse Inventory Stack Tracker =====\n";
    while (true) {
        cout << "\nPlease choose one of the following from 1-5 Please Enter Choice!";
        cout << "\n1. Add box to stack";
        cout << "\n2. view current Stack";
        cout << "\n3. Remove top box(Dispatch)";
        cout << "\n4.View Inventory summary";
        cout << "\n5. Exit\n";

        int choice;
        if (!(cin >> choice)) return 0;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1)
            addBox();
        else if (choice == 2)
            viewStack();
        else if (choice == 3)
            removeTopBox();
        else if (choice == 4)
            summary();
        else if (choice == 5)
        {
            saveToFile();
            cout << "The total inventory created today has been saved to inventory.txt file\n";
            return 0;
        }
        else {
            cout << "please choose a number betwen 1-5 NOT A VALID CHOICE" << "\n";
        }
    }
}
