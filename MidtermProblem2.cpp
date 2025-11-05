// MidtermProblem2 Airport taxi Queue System

#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

struct Taxi {
    int id;
    string driver;
    string model;
    string plate;
};

const int max_Queue = 100;


 // front index points to current front element if its not empty
// rear index points to current of last element if its not empty
// all indexes use the %(mod) of max_qeueue to make sure index
// wraps back to start of array when it reaches end

Taxi queue[max_Queue];
int frontIndex = 0;
int rearIndex = -1;
int countQueue = 0;



//isEMPTY-  true when no taxis are waiting
//isFULL - true when the queue reached its maximum cpacity and cannot add any more(100)


bool isEmpty()
{
    return countQueue == 0;
}
bool isFull()
{
    return countQueue == max_Queue;
}


// adds taxi to the back and advances the rear Index with wrap around to the next spot
//countQueue only tracks how many items there are total(counting the queue)
void enqueue(const Taxi& t) {
    if (isFull()) {
        cout << "Our queue is full cannot make a queue now.\n";
        return;
    }
    rearIndex = (rearIndex + 1) % max_Queue;
    queue[rearIndex] = t;
    countQueue++;
    cout << "Taxi has been added to queue\n";
}

// removes the front taxi and copies it out, then advances the front index to next spot
// next it doesnt shift because we have wraps with %

bool dequeue(Taxi& out) {
    if (isEmpty()) {
        cout << "There are no taxis to dispatch now.\n";
        return false;
    }
    out = queue[frontIndex];
    frontIndex = (frontIndex + 1) % max_Queue;
    countQueue--;
    return true;
}

//helper functions which return the taxis object either the only currently at the front
// or the one rear the most recently added of the queue
Taxi frontTaxi()
{
    return queue[frontIndex];
}
Taxi rearTaxi()
{
    return queue[rearIndex];
}


//prints taxis waiting from front to back using the module indexing of max_queue
void viewWaiting() {
    if (isEmpty()) {
        cout << "No taxis are waiting at this moment\n";
        return;
    }
    cout << "===== Waiting taxis front to back =====\n";
    cout << "|ID| Driver| Model |Plate|\n";
    for (int i = 0; i < countQueue; ++i) {
        int idx = (frontIndex + i) % max_Queue;
        cout << queue[idx].id << " " << queue[idx].driver << " "
            << queue[idx].model << " " << queue[idx].plate << "\n";
    }
}
//prints front means next to dispatch and the rear which means most recently added taxi
void viewSummary()
{
    cout << "===== Queue Summary =====;";
    cout << "All Total taxis waiting: " << countQueue << "\n";
    if (!isEmpty()) {
        cout << "Front taxi:  ID: " << queue[frontIndex].id << " - " << queue[frontIndex].driver << "\n";
        cout << "Rear  taxi: ID :  " << queue[rearIndex].id << " - " << queue[rearIndex].driver << "\n";
    }
    cout << "==========\n";
}

void saveToFile() {
    ofstream out("taxis.txt");
    if (!out)
    {
        cout << "Could not open the taxi.txt file for adding.\n"; return;
    }

    out << "ID,Driver,Model,Plate\n";
    for (int i = 0; i < countQueue; ++i) {
        int idx = (frontIndex + i) % max_Queue;
        out << queue[idx].id << "," << queue[idx].driver << ","
            << queue[idx].model << "," << queue[idx].plate << "\n";
    }
    out.close();
    cout << "Taxi queue saved to taxi.txt \n";
}


int main() {
    cout << "===== Welcome to airport taxi Queue Systems =====\n";
    while (true) {
        cout << "\nPlease choose one of the following operations 1-5"
            << "Please enter choice below : \n"
            << "1. Add Taxi to Queue\n"
            << "2. View Waiting Taxis\n"
            << "3. Dispatch Next Taxi\n"
            << "4. View Queue Summary\n"
            << "5. Exit\n";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice." << endl;
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush newline

        if (choice == 1) {
            Taxi t;

            cout << "Enter Taxi's ID: ";
            cin >> t.id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter Driver's Name: ";
            getline(cin, t.driver);

            cout << "Enter Car's Model: ";
            getline(cin, t.model);

            cout << "Enter License's Plate: ";
            getline(cin, t.plate);

            enqueue(t);
        }

        else if (choice == 2) {
            viewWaiting();
        }
        else if (choice == 3) {
            Taxi t;
            if (dequeue(t)) {
                cout << "Taxi has been dispatched now:\n"
                    << "Taxi ID: " << t.id << ",Taxi Driver: " << t.driver
                    << ", Car: " << t.model << ",Taxi Plate: " << t.plate << "\n";
            }
        }
        else if (choice == 4) {
            viewSummary();
        }
        else if (choice == 5) {
            saveToFile();
            break;
        }
        else {
            cout << "Invalid Choice.\n";
        }
    }
    return 0;
}
