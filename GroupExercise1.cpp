#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Class {
    string name = "";
    int numStudents = 0;
    int grades[100] = { 0 };
};

int main() {
    Class c;

    cout << "Enter a class name: ";
    getline(cin, c.name);

    cout << "Enter # of students in this class (1-100): ";
    cin >> c.numStudents;

    if (c.numStudents < 1)  c.numStudents = 1;
    if (c.numStudents > 100) c.numStudents = 100;

    int sum = 0;
    int minGrade = 101, maxGrade = -1;

    for (int i = 0; i < c.numStudents; i++) {
        cout << "Enter grade for student " << (i + 1) << " (0-100): ";
        cin >> c.grades[i];

        if (c.grades[i] < 0)   c.grades[i] = 0;
        if (c.grades[i] > 100) c.grades[i] = 100;

        sum += c.grades[i];
        if (c.grades[i] < minGrade) minGrade = c.grades[i];
        if (c.grades[i] > maxGrade) maxGrade = c.grades[i];
    }

    double average = (double)sum / c.numStudents;

    cout << "\n--- YOUR CLASS---" << endl;
    cout << "Class name: " << c.name << endl;
    cout << "# of students: " << c.numStudents << endl;
    cout << fixed << showpoint << setprecision(2);
    cout << "Average score: " << average << endl;
    cout << "Maximum(highest) grade: " << maxGrade << endl;
    cout << "Minimum(lowest)  grade: " << minGrade << endl;

    return 0;
}
