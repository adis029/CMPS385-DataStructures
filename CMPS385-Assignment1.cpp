/*
CMPS 385 - Data Structures (Fall 2025)
Assignment 1: Faculty Gradebook
Aditya Singh
8/25/2025
Program purpose:
Adds an automatic generated unique ID for student
updates scores for a student by ID and computes the average
and grade correlated
displays students reports by ID
displays semester reports with filtering 
list all students briefly
*/

#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;



// STRUCTS
struct Name {
    string first;
    string last;
};
struct Scores {
    double exam1;
    double exam2;
    double exam3;
    double average;
    char letter;
};
struct Student {
    int id;
    Name name;
    string semester;
    Scores scores;
};

Student gradebook[100];
int countStudents = 0;




//Necessary when using both cin and getLine 
// it is needed to discard the leftover newline
//so when user inputs it reads properly
void clearLine() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

//BELOW are 5 functions all used to make code easier to read
// and run not necessary needed

//Returns true if an ID already Exists in the gradebook 
bool idChecker(int id) {
    for (int i = 0; i < countStudents; ++i)
        if (gradebook[i].id == id) return true;
    return false;
}

//Generates random id between 10000, 99999 and re tries if
// it matches another one already created

int generateUniqueID() {
    int id;
    do {
        id = 10000 + rand() % 90000;
    } while (idChecker(id));
    return id;
}

//Searches for student index by ID number
int findIndexByID(int id) {
    for (int i = 0; i < countStudents; ++i)
        if (gradebook[i].id == id) return i;
    return -1;
}

//Prompts user for an ID correlating to a student already in the array,
//if not found prints not found

int promptAndFindStudent() {
    cout << "Enter student ID: ";
    int id;
    cin >> id;

    //Guard to make sure prompt doesn't fail if user inputs BELOW
    //something else besides numbers

    if (!cin) {
        cin.clear();
        clearLine();
        cout << "PLEASE INPUT A VALID NUMBER ID\n";
        cout << "------------------------------------";
        return -1;
    }

    int index = findIndexByID(id);
    if (index == -1) {
        cout << "Student not found.\n";
        cout << "---------------------------------------------\n";
    }
    return index;
}


//Computes averages and correlates the letter grade
void computeAverageAndLetter(Scores& s) {
    s.average = (s.exam1 + s.exam2 + s.exam3) / 3.0;
    if (s.average >= 90.0)      s.letter = 'A';
    else if (s.average >= 80.0) s.letter = 'B';
    else if (s.average >= 70.0) s.letter = 'C';
    else if (s.average >= 60.0) s.letter = 'D';
    else                        s.letter = 'F';
}




/*Generates unique ID
inputs first name and last name
generates random ID
initalizes all scores to zero and F for letter grade

*/
void addStudent() {
    if (countStudents >= 100) {
        cout << "The maximum number of students in gradebook has reached 100.\n";
        return;
    }

    Student stu;
    stu.id = generateUniqueID();
    stu.scores.exam1 = 0.0;
    stu.scores.exam2 = 0.0;
    stu.scores.exam3 = 0.0;
    stu.scores.average = 0.0;
    stu.scores.letter = 'F';

    cout << "Please input your first name: ";
    cin >> stu.name.first;
    cout << "Please input your last name: ";
    cin >> stu.name.last;

    cout << "Please input the semester: ";
    clearLine();
    getline(cin, stu.semester);

    gradebook[countStudents++] = stu;

    cout << "HELLO!  " << stu.name.first << " " << stu.name.last << " from "
        << stu.semester << "you have been added.\n";
    cout << "YOUR UNIQUE ID is " << stu.id << endl;
  
}

// Asks for ID and finds student
//inputs exam scores by user
//computes averag and letter grade
// shows the 




void updateScoresById() {
    int index = promptAndFindStudent();
    if (index == -1) return;  

    Student& stu = gradebook[index];
    cout << "Enter Exam 1 (0-100): "; 
    cin >> stu.scores.exam1;
    cout << "Enter Exam 2 (0-100): ";
    cin >> stu.scores.exam2;
    cout << "Enter Exam 3 (0-100): "; 
    cin >> stu.scores.exam3;

    computeAverageAndLetter(stu.scores);

    cout << fixed << setprecision(2);
    cout << "Scores updated for " << stu.name.first << " " << stu.name.last
        << " (ID: " << stu.id << ").\n";
    cout << "Average: " << stu.scores.average << "\n";
    cout << "Letter: " << stu.scores.letter << "\n";
}

void displayStudentById() {
    int index = promptAndFindStudent();
    if (index == -1) return;

    Student& stu = gradebook[index];
    cout << "------ Student Report ------\n";
    cout << "Name: " << stu.name.last << ", " << stu.name.first << "\n";
    cout << "ID: " << stu.id << "\n";
    cout << "Semester: " << stu.semester << "\n";
    cout << "Exam 1: " << stu.scores.exam1 << "\n";
    cout << "Exam 2: " << stu.scores.exam2 << "\n";
    cout << "Exam 3: " << stu.scores.exam3 << "\n";
    cout << fixed << setprecision(2);
    cout << "Average: " << stu.scores.average << "\n";
    cout << "Letter: " << stu.scores.letter << "\n";
    cout << "----------------------------\n";

}


void displaySemesterReport() {
    cout << "Enter semester (e.g., Fall 2025): ";
    clearLine();
    string sem; getline(cin, sem);

    int studentsFound = 0;
    double sumAvg = 0.0;
    double hi = 0, lo = 100;

    cout << "ID | Name | E1 E2 E3 | Avg | Letter\n";
    cout << "-------------------------------------------------------\n" << fixed << setprecision(2);

    for (int i = 0; i < countStudents; ++i) {
        Student& s = gradebook[i];
        if (s.semester == sem) {
            studentsFound+=1;
            sumAvg += s.scores.average;
            if (s.scores.average > hi) hi = s.scores.average;
            if (s.scores.average < lo) lo = s.scores.average;

            cout << s.id << " | "
                << s.name.last << ", " << s.name.first << " | "
                << s.scores.exam1 << " " << s.scores.exam2 << " " << s.scores.exam3 << " | "
                << s.scores.average << " | "
                << s.scores.letter << "\n";
        }
    }

    if (studentsFound == 0) {
        cout << "No records for that semester.\n";
        cout << "---------------------------------------------\n";
        return;
    }

    cout << "Students: " << studentsFound << "\n";
    cout << "Semester Average: " << (sumAvg / studentsFound) << "\n";
    cout << "Highest Average: " << hi << "\n";
    cout << "Lowest Average: " << lo << "\n";
    
}

void listAllStudents() {
    if (countStudents == 0) {
        cout << "No students added yet.\n";
        return;
    }

    cout << "ID | Name | Semester\n";
    cout << "-----------------------------------------\n";
    for (int i = 0; i < countStudents; ++i) {
        cout << gradebook[i].id << " | "
            << gradebook[i].name.last << ", " << gradebook[i].name.first << " | "
            << gradebook[i].semester << "\n";
    }
  
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    while (true) {
        cout << "----------------------- Faculty Gradebook -----------------------\n";
        cout << "Type a number to the following options please 1-6\n";
        cout << "1.Add a new student record! \n";
        cout << "2.Enter/Update scores for a student (by ID)\n";
        cout << "3.Display a report for one student (by ID)\n";
        cout << "4.Display a report for a whole semester (filter by semester)\n";
        cout << "5.List all students (brief roster)\n";
        cout << "6.Exit\n";
        cout << "Your Choice!: ";

        int choice; 
        cin >> choice;
        if (!cin || choice <1 || choice >6) {
            cin.clear();
            clearLine();
            cout << "---- CHOOSE ANOTHER NUMBER , PLEASE ONLY BETWEEN 1-6----\n";
            continue;
        }

        if (choice == 1) 
        addStudent();
        else if (choice == 2)
        updateScoresById();
        else if (choice == 3)
        displayStudentById();
        else if (choice == 4)
        displaySemesterReport();
        else if (choice == 5) 
        listAllStudents();
        else if (choice == 6) {
        cout << "Thank you for using the Faculty Gradebook!\n";
        cout << "Goodbye!\n";
        return 0;
        }
    }
}
