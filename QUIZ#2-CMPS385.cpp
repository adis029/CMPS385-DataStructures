/*
Aditya Singh
CMPS 385 - QUIZ#2
To Do Manager using a class and a simple menu


*/


#include <iostream>
#include <string>
#include <limits>

using namespace std;


//

class Task {
private:
    int id;
    string description;
    bool done;

public:
    //Constructor
    Task() {
        id = 0;
        description = "";
        done = false;
    }

    // intialized constructor
    Task(int _id, const string& _description, bool _done = false) {
        id = _id;
        description = _description;
        done = _done;
    }

    // Getters
    int getId()
        const {
        return id;
    }

    string getDescription()
        const {
        return description;
    }

    bool isDone()
        const {
        return done;
    }

    // Setters
    void setId(int _id)
    {
        id = _id;
    }

    void setDescription(const string& _description)
    {
        description = _description;
    }

    void setDone(bool _done)
    {
        done = _done;
    }

    // I used method toggle to change value of done to opposite
    //based on whether true or false if needed

    //display is simply and used in 
    void toggle()
    {
        done = !done;
    }

    void display() const {
        cout << "ID: " << id << "| \"" << description << "\"| Status: ";
        if (done) {
            cout << "Done";
        }
        else {
            cout << "Pending";
        }
        cout << '\n';
    }
};



int main() {
    Task tasks[50];
    int n = 0, nextId = 1001;

    cout << "******** Welcome to To Do Manager ********" <<endl;
    while (true) {
        cout << "1. Add Task\n";
        cout << "2. Toggle task by ID\n";
        cout << "3. List the pending tasks\n";
        cout << "0. If you wish to exit\n";
        int choice;
        cout << "Please input choice: ";
        cin >> choice;
        //Simply checks whether number is equal to an int
        //then asks for input again
        if (!cin) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "please INPUT A NUMBER that is 1,2,3,OR 0\n";
            continue;
        }
        if (choice == 0) { cout << "Goodbye!\n"; break; }

        //Add TASKS
        if (choice == 1) {
            if (n >= 50) { cout << "Task list full.\n";
            continue; }
            cout << "Enter description: ";
            string description; getline(cin >> ws, description);
            tasks[n].setId(nextId);
            tasks[n].setDescription(description);
            tasks[n].setDone(false);
            cout << "Task added!ID: " << nextId << '\n';
            ++n; ++nextId;
        }
        //TOGGLE TASK BY ID
        else if (choice == 2) {
            cout << "Enter Task ID: ";
            int id; 
            if (!(cin >> id)) return 0;
            bool found = false;
            for (int i = 0; i < n; ++i) {
                if (tasks[i].getId() == id) { tasks[i].toggle(); cout << "Toggled task is" << id << ".\n"; found = true;
                break; }
            }
            if (!found) cout << "Task not found.\n";
        }
        //SEE PENDING TAKS displays any which may be pending still

        else if (choice == 3) {
            bool any = false;
            for (int i = 0; i < n; ++i) {
                if (!tasks[i].isDone()) {
                    cout << "ID: " << tasks[i].getId() << " | \"" << tasks[i].getDescription() << "\" | Status: Pending\n";
                    any = true;
                }
            }
            if (!any)
                cout << "No pending tasks.\n";
        }
    }
    return 0;
}
