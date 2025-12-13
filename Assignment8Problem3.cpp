//CMPS 385- Data Structures
//Aditya Singh
//Assignment 8 Problem 3

//Program uses memory allocation to create and remove
//Uses node at runtime when roads are added or system resets
//Global pointers,totation logicistics, looping through lists

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;



//Struct of Traffic Light 

// Each node represents one road and its traffic lights
// The next pointer connects its nodes in a circular manner

struct TrafficLight {

    int id;                 
    string roadName;         
    string color;             // Colors mimics real life, green,yellow,red
    TrafficLight* next;     
};

//Global poitners 

TrafficLight* first = nullptr;      //first road or light 
TrafficLight* current = nullptr;   // active light(current)

//Function declartions 

void addLight();
void displaySequence();
void advanceLight();
void resetSystem();


int main() {

    int choice;

    do {
        cout << "\n**** ****  Welcome to Smart Light Controller! **** ****\n";
        cout << "1.Add Road and Light\n";
        cout << "2.Display Light Sequence\n";
        cout << "3.Advance to Next Light\n";
        cout << "4.Reset System\n";
        cout << "5.Exit\n";
        cout << "Please Choose 1-5 ONLY!  ";

        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            addLight();
            break;
        case 2:
            displaySequence();
            break;
        case 3:
            advanceLight();
            break;
        case 4:
            resetSystem();
            break;
        case 5:
            cout << "Traffic system has been saved thanks!\n";
            break;
        default:
            cout << "Invalid option please type 1-5 ONLY !\n";
        }

    } while (choice != 5);

    return 0;
}

//ALL FUNCTIONS BELOW

//Function Addlight (adds a new road or light at end of list if list is empty
//node will point to itself


void addLight() {

    TrafficLight* newLight = new TrafficLight;

    cout << "Enter Road ID: ";
    cin >> newLight->id;
    cin.ignore();

    cout << "Enter Road Name: ";
    getline(cin, newLight->roadName);

    cout << "Enter Initial light color from (green,yellow, or red) ";
    getline(cin, newLight->color);

// First opton happens when list is empty and the node will point to itself
    if (first == nullptr) {
        first = newLight;
        current = newLight;
        newLight->next = newLight;   
    }

    //Option 2 if there is a non empty list then the program will run through and traverse
    // to the last node whose next points to the first 
    else {
        TrafficLight* temp = first;

        // Traverse to last node (whose next points to first)
        while (temp->next != first) {
            temp = temp->next;
        }

        temp->next = newLight;
        newLight->next = first;
    }

    cout << "Traffic light has been added for " << newLight->roadName;

}


//Function Display Sequence - Displays circular paths list starting from first and loops exactly once through all circles

void displaySequence() {

    if (first == nullptr) {
        cout << "No traffic lights in system.\n";
        return;
    }

    cout << "\n Trafic light sequences \n";
    cout << "[  ID|   |Road Name|           |Light|  ] \n";
    cout << "\n";

    TrafficLight* temp = first;

    do {
        cout << temp->id << "    "
            << temp->roadName << "           "
            << temp->color << endl;
        temp = temp->next;
    } while (temp != first);
}

//Function Advance light 
//Simulates light rotations as in
// the current becomes red then green then yellow

void advanceLight() {

    if (current == nullptr) {
        cout << "No traffic lights to advance.\n";
        return;
    }

    TrafficLight* temp = first;

//Set all color lights to yellow 
    do {
        temp->color = "Yellow";
        temp = temp->next;
    } while (temp != first);

    //Set all color lights to red
    current->color = "Red";

    //Set all color lights to green 
    current->next->color = "Green";

    // Display changes
    temp = first;
    do {
        cout << temp->roadName << " -> " << temp->color << endl;
        temp = temp->next;
    } while (temp != first);

    // Move current pointer forward
    current = current->next;
}

//Function Reseting system - deletes all the nodes and resets the entire system


void resetSystem() {

    if (first == nullptr) {
        cout << "System already empty.\n";
        return;
    }

    TrafficLight* temp = first->next;


    while (temp != first) {
        TrafficLight* toDelete = temp;
        temp = temp->next;
        delete toDelete;
    }

    delete first;

    first = nullptr;
    current = nullptr;

    cout << "System has now been reset Thank you for using this program. \n";
}

