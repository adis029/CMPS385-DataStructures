/*
CMPS 385 Data Structures - Fall 2025
Quiz 1 - Appointment Scheduler
Aditya Singh
Program purpose:

This program is designed to allows 
users to add new appointments,
view appointments by date,
and exit the system when prompted

*/
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

struct Date {
    int day;
    int month;
    int year;
};
struct Appointment {
    int id;        // auto-generated
    string name;   // person’s name
    Date date;     // appointment date
    string purpose;// reason for visit
};

Appointment schedule[50];
int countSchedules = 0;


//Trick used after cin >> to clear any leftover newlines
// before using getline for inputs

void clearLine() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/*Prompts user for name, appointment date, and purpose
generates random ID
stores appointment in array
*/


void addAppointment() {
    if (countSchedules >= 50) {
        cout << "MAXIMUM appointments reached 50, cannot exceed this number!\n";
        cout << "---------------------------------------------\n";
        return;
    }

    Appointment info;

    info.id = 1000 + rand() % 9000;

    cout << "Please input your Name: ";
    clearLine();
    getline(cin, info.name);

    cout << "Please input your appointment date (DD MM YYYY): ";
    cin >> info.date.day >> info.date.month >> info.date.year;

    cout << "Please input your purpose of visit: ";
    clearLine();
    getline(cin, info.purpose);

    // First appointment added to the array of info
    schedule[countSchedules] = info;
    countSchedules += 1;

    cout << "YOUR APPOINTMENT HAS BEEN CREATED!\n";
    cout << "YOUR RANDOM ID IS " << info.id << "\n";
    cout << "---------------------------------------------\n";
}

//Prompts user for date and prints all apointments on that day


void viewAppointments() {
    Date d;
    cout << "Enter date (DD MM YYYY): ";
    cin >> d.day >> d.month >> d.year;

    bool apptFound = false;

    cout << "Appointments on "
        << setfill('0') << setw(2) << d.day << "/"
        << setw(2) << d.month << "/"
        << setfill(' ') << d.year << ":\n";

    for (int i = 0; i < countSchedules; ++i) {
        const Appointment& appt = schedule[i];
        if (appt.date.day == d.day && appt.date.month == d.month && appt.date.year == d.year) {
            cout << "ID: " << appt.id << " | " << appt.name << " | " << appt.purpose << "\n";
            apptFound = true;
        }
    }

    if (apptFound == false) {
        cout << "No appointments are made for this date.\n";
    }
    cout << "---------------------------------------------\n";
}

int main() {
    srand(static_cast<unsigned>(time(0)));//seeds random generator once program starts

    while (true) {
        cout << "---------- Appointment Scheduler ----------\n";
        cout << "1.Add Appointment\n";
        cout << "2.View Appointments by Date\n";
        cout << "3.Exit\n";
        cout << "Choose a choice (1-3): ";

        int choice;
        cin >> choice;


        //!cin is a trick
        //If user types in something invalid(not correlated to data type chosen)
        //will make user retype it 
        if (!cin || choice <1 || choice >3 ) {
            cin.clear();
            clearLine();
            cout << "NOT VALID PLEASE CHOOSE NUMBERS BETWEEN 1-3\n";
            continue;
        }
        if (choice == 1) {
            addAppointment();
        }
        else if (choice == 2) {
            viewAppointments();
        }
        else if (choice == 3) {
            cout << "Thank you for using the scheduler!\n";
            return 0;
        }
    }
}
