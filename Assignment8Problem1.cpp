//CMPS 385 - Data Structures
// Aditya Singh
// ER management Assignment 8 -Problem 1
//Code uses memory allocation, pointers,queue logistic

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;


// Struct Patient: it represents one patient in the er that i created
// each of the pateients is a node in a linked list



struct Patient {
    string id;
    string name;
    string condition;
    int severity;
    Patient* next;
};



Patient* head = nullptr;
int totalServed = 0;

// Function Declarations

void loadPatients();
void savePatients();
void addPatient();
void displayQueue();
void servePatient();
void showSummary();




//Firstly the program loads the file of patients when it starts
int main() {
    loadPatients();

    int choice;

    do {
        cout << "\n**** **** Welcome to the Emergency Room Patient Queue Manager  **** ****\n";
        cout << "1.Add Patient\n";
        cout << "2.Display Patient queue\n";
        cout << "3.Serve Next Patient\n";
        cout << "4.View ER Summary\n";
        cout << "5.Exit\n";
        cout << "Please Choose a number 1-5! ";

        cin >> choice;
        cin.ignore();


        // Switch used based on 1-5 choices made by user
        switch (choice) {
        case 1:
            addPatient();
            break;
        case 2:
            displayQueue();
            break;
        case 3:
            servePatient();
            break;
        case 4:
            showSummary();
            break;
        case 5:
            savePatients();
            cout << "Patient queues have been saved to Patients.txt \n";
            break;
        default:
            cout << "Invalid option PLEASE Choose a number 1-5 ONLY! \n";
        }
    } while (choice != 5);

    return 0;
}


/* Function Load patients from text file and
rebuild the linked list at program startup
*/
void loadPatients() {
    ifstream file("patients.txt");

    if (!file) {
        cout << "No existing patient file found. Starting with empty queue.\n";
        return;
    }

    string id, name, condition;
    int severity;

    while (getline(file, id, ',')) {
        getline(file, name, ',');
        getline(file, condition, ',');
        file >> severity;
        file.ignore();

        Patient* newPatient = new Patient;
        newPatient->id = id;
        newPatient->name = name;
        newPatient->condition = condition;
        newPatient->severity = severity;
        newPatient->next = nullptr;


        if (head == nullptr) {
            head = newPatient;
        }
        else {
            Patient* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newPatient;
        }
    }

    file.close();
}

// Saves the current queue to patients.txt
// Format : ID,Name,Condition,Severity


void savePatients() {
    ofstream file("patients.txt");

    Patient* temp = head;

    while (temp != nullptr) {
        file << temp->id << ","
            << temp->name << ","
            << temp->condition << ","
            << temp->severity << endl;
        temp = temp->next;
    }

    file.close();
}
// Prompts user for patient info and inserts patient at the END of the queue

void addPatient() {
    Patient* newPatient = new Patient;

    cout << "Enter Patient ID: ";
    getline(cin, newPatient->id);

    cout << "Enter patient name: ";
    getline(cin, newPatient->name);

    cout << "Enter condition: ";
    getline(cin, newPatient->condition);

    cout << "Enter severity (1-5): ";
    cin >> newPatient->severity;
    cin.ignore();

    newPatient->next = nullptr;

    if (head == nullptr) {
        head = newPatient;
    }
    else {
        Patient* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newPatient;
    }

    cout << "Patient added to the queue.\n";
}

// Traverses through the linked list of patients and displays all the patients
//If none currently in queue -> directly returns no patients
void displayQueue() {
    if (head == nullptr) {
        cout << "No patients in queue.\n";
        return;
    }

    cout << "\n **** **** CURRENT QUEUE **** ****\n";
    cout << left << setw(10) << "ID"
        << setw(20) << "Name"
        << setw(20) << "Condition"
        << setw(10) << "Severity" << endl;

    Patient* temp = head;

    while (temp != nullptr) {
        cout << left << setw(10) << temp->id
            << setw(20) << temp->name
            << setw(20) << temp->condition
            << setw(10) << temp->severity << endl;
        temp = temp->next;
    }
}


//Removes the FIRST patient in the queue as a first come first serve
//Typically like real life FCFO kind of way

void servePatient() {
    if (head == nullptr) {
        cout << "No patients in queue.\n";
        return;
    }

    Patient* served = head;

    cout << "Serving Patient: "
        << served->id << " - "
        << served->name << endl;

    head = head->next;
    delete served;
    totalServed++;
}



//Involves the summary of ER statistics including patients served,patients in queue,
// and average severity of waiting patients
// IF NONE, returns No information Dated YET!
void showSummary() {
    int count = 0;
    int severitySummary = 0;

    Patient* temp = head;

    while (temp != nullptr) {
        count++;
        severitySummary += temp->severity;
        temp = temp->next;
    }

    cout << "\n **** **** EMERGENCY ROOM SUMMARY **** **** \n";
    cout << "Total patients served: " << totalServed << endl;
    cout << "Patients in queue: " << count << endl;

    if (count > 0) {
        double avg = static_cast<double>(severitySummary) / count;
        cout << fixed << setprecision(2);
        cout << "Average Severity of Waiting Patients: " << avg << endl;
    }
    else {
        cout << "Average Severity of Waiting Patients: NO information Dated! \n";
    }
}
