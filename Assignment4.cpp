/*
CMPS 385 - Assignment4
Aditya Singh
Program:Recursive Grade Analyzer
*/

#include <iostream>
using namespace std;

//Function declarations- prototypes so the main() knows the functions exist
void displayGrades(int grades[], int size, int index = 0);
int sumGrades(int grades[], int size, int index = 0);
int countFailing(int grades[], int size, int index = 0);
int findMax(int grades[], int size, int index = 0, int currentMax = -1);

int grades[100];
int gradeCount = 0;

//Recursively displays the grade all one by one
//Index starts at 0 and increases until it equals the maximum of 100
void displayGrades(int grades[], int size, int index) {
    if (index == size) {
        cout << endl;
        return;
    }
    cout << grades[index] << " ";
    displayGrades(grades, size, index + 1);
}

int sumGrades(int grades[], int size, int index) {
    if (index == size)
        return 0;   //Base Case: return 0 if we have checked all grades

    // recursive step : take the current grade and add sum of the rest
    return grades[index] + sumGrades(grades, size, index + 1);
}

int countFailing(int grades[], int size, int index) {
    // Base case: if we've reached the end of the array
    if (index == size)
        return 0;

    int fail;
    if (grades[index] < 60) {
        fail = 1;  // this grade means that it is failing
    }
    else {
        fail = 0;  // this grade means that it is passing
    }

    // add the current fail whether 1 or 0 to the recursive result of the rest
    return fail + countFailing(grades, size, index + 1);
}

int findMax(int grades[], int size, int index, int currentMax) {
    //Base case: return the largest found so far when you reach the end of array
    if (index == size)
        return currentMax;

    //If current grade is bigger than currentMax update the currentMax
    if (grades[index] > currentMax)
        currentMax = grades[index];

    //Recursive step: check the next grade with the updated currentMax
    return findMax(grades, size, index + 1, currentMax);
}

int main() {
    int choice;

    cout << "******** Welcome to Recursive Grade Analyzer ********\n";

    while (true) {
        cout << "Please choose one of the following operations:\n";
        cout << "1. Enter Grades\n";
        cout << "2. Display Grades\n";
        //STEPS 3-5 uses recursive steps
        cout << "3. Calculate Average Grade\n";
        cout << "4. Count Failing Grades \n";
        cout << "5. Find Highest Grade \n";
        cout << "6. Exit\n";
        cout << "Please select a Choice! : ";
        cin >> choice;

        //if input isn't a number this makes it so the user has to reinput
        if (!cin) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Please type in a valid number from 1-6 \n";
            continue;
        }

        if (choice == 1) {
            cout << "How many grades do you want to enter. \n";
            cin >> gradeCount;

            if (gradeCount > 100 || gradeCount <= 0) {
                cout << "Invalid number of grades, (must be between 1-100).\n";
                gradeCount = 0;
                continue;
            }

            for (int i = 0; i < gradeCount; i++) {
                cout << "Enter grade #" << (i + 1) << ": ";
                cin >> grades[i];
            }
            cout << "Grades successfully saved!\n";
        }
        else if (choice == 2) {
            if (gradeCount == 0) {
                cout << "No grades entered yet.\n";
            }
            else {
                cout << "Grades entered:\n";
                displayGrades(grades, gradeCount);
            }
        }
        else if (choice == 3) {
            if (gradeCount == 0) {
                cout << "No grades to calculate average.\n";
            }
            else {
                double avg = (double)sumGrades(grades, gradeCount) / gradeCount;
                cout << "The average grade is: " << avg << endl;
            }
        }
        else if (choice == 4) {
            if (gradeCount == 0) {
                cout << "No grades to analyze.\n";
            }
            else {
                cout << "Number of failing grades: " << countFailing(grades, gradeCount) << endl;
            }
        }
        else if (choice == 5) {
            if (gradeCount == 0) {
                cout << "No grades to find highest.\n";
            }
            else {
                cout << "Highest grade: " << findMax(grades, gradeCount) << endl;
            }
        }
        else if (choice == 6) {
            cout << "Thank you for using Recursive Grade Analyzer!\n";
            break;
        }
        else {
            cout << "Invalid choice. Please select between 1-6.\n";
        }
    }
    return 0;
}
