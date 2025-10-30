// Aditya Singh
// CMPS 385
// Assignment 6
// Appointment Tracker
// 10/30/2025
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <type_traits>
using namespace std;

static const int MAX_APPOINTMENTS = 100;

//This struct holds info about only one appoinment 
template <typename T1, typename T2>
struct Appointment {
    T1 id;
    string patientName;
    string appointmentType;
    int timeUntilHours;
    T2 estimatedBillAmount;
    string status;
};

/*
This changes the text to numbers 
or keeps it as a string if intended 
*/
template <typename T>
bool parseFromString(const string& text, T& result) {
    if constexpr (is_same<T, string>::value) {
        result = text;
        return true;
    }
    else if constexpr (is_same<T, int>::value) {
        try { size_t pos = 0; result = stoi(text, &pos); return pos == text.size(); }
        catch (...) { return false; }
    }
    else if constexpr (is_same<T, float>::value) {
        try { size_t pos = 0; result = stof(text, &pos); return pos == text.size(); }
        catch (...) { return false; }
    }
    else if constexpr (is_same<T, double>::value) {
        try { size_t pos = 0; result = stod(text, &pos); return pos == text.size(); }
        catch (...) { return false; }
    }
    else {
        stringstream ss(text);
        ss >> result;
        return !ss.fail() && ss.rdbuf()->in_avail() == 0;
    }
}
//This changes numbers back to their texts
template <typename T>
string convertToString(const T& value) {
    if constexpr (is_same<T, string>::value) {
        return value;
    }
    else {
        ostringstream output;
        output << value;
        return output.str();
    }
}

template <typename T1, typename T2>
int loadAppointmentsFromFile(Appointment<T1, T2> appointmentList[]);

template <typename T1, typename T2>
void saveAppointmentsToFile(Appointment<T1, T2> appointmentList[], int recordCount);

template <typename T1, typename T2>
void addNewAppointment(Appointment<T1, T2> appointmentList[], int& recordCount);

template <typename T1, typename T2>
void displayAllAppointments(Appointment<T1, T2> appointmentList[], int recordCount);

template <typename T1, typename T2>
void markAppointmentCompleted(Appointment<T1, T2> appointmentList[], int recordCount);

template <typename T1, typename T2>
void viewAppointmentSummary(Appointment<T1, T2> appointmentList[], int recordCount);

//This prompts the user for text and if failed makes them try again
static void promptTextLine(const string& prompt, string& userInput) {
    cout << prompt << endl;
    getline(cin, userInput);
    while (userInput.empty()) {
        cout << "Input cannot be empty. Please try again." << endl;
        getline(cin, userInput);
    }
}


//This asks the user for a positive whole number if rompt failed by user makes them try again 
static void promptPositiveInteger(const string& prompt, int& number) {
    string line;
    cout << prompt << endl;
    getline(cin, line);
    while (!parseFromString<int>(line, number) || number <= 0) {
       cout << "Invalid input. Please enter a positive integer." << endl;
       getline(cin, line);
    }
}

static void promptNonNegativeDouble(const string& prompt, double& number) {
    string line;
    cout << prompt << endl;
    getline(cin, line);
    while (!parseFromString<double>(line, number) || number < 0.0) {
        cout << "Invalid input. Please enter a non-negative number." << endl;
        getline(cin, line);
    }
}

//This loads the csv files and loads the appointments from it
template <typename T1, typename T2>
int loadAppointmentsFromFile(Appointment<T1, T2> appointmentList[]) {
    ifstream inputFile("appointments.txt");
    if (!inputFile.is_open()) return 0;

    string header;
    getline(inputFile, header);

    int recordCount = 0;
    string line;
    while (recordCount < MAX_APPOINTMENTS && getline(inputFile, line)) {
        if (line.empty()) continue;

        string fields[6];
        stringstream ss(line);
        for (int i = 0; i < 6; i++) {
            if (!getline(ss, fields[i], ',')) { fields[0].clear(); break; }
        }
        if (fields[0].empty()) continue;

        Appointment<T1, T2> appointment;
        if (!parseFromString<T1>(fields[0], appointment.id)) continue;
        appointment.patientName = fields[1];
        appointment.appointmentType = fields[2];
        if (!parseFromString<int>(fields[3], appointment.timeUntilHours)) continue;
        if (!parseFromString<T2>(fields[4], appointment.estimatedBillAmount)) continue;
        appointment.status = fields[5].empty() ? "Pending" : fields[5];

        appointmentList[recordCount++] = appointment;
    }

    inputFile.close();
    return recordCount;
}

//This will save all apointments when closing the program to the txt or csv file
template <typename T1, typename T2>
void saveAppointmentsToFile(Appointment<T1, T2> appointmentList[], int recordCount) {
    ofstream outputFile("appointments.txt");
    outputFile << "ID,Name,Type,Time,Bill,Status" << endl;

    for (int index = 0; index < recordCount; index++) {
        outputFile << convertToString(appointmentList[index].id)
            << "," << appointmentList[index].patientName << ","
           << appointmentList[index].appointmentType << ","
            << appointmentList[index].timeUntilHours << ","
            << static_cast<double>(appointmentList[index].estimatedBillAmount) << ","
            << appointmentList[index].status << endl;
    }

    outputFile.close();
}

//Asks the user for appointment info 
template <typename T1, typename T2>
void addNewAppointment(Appointment<T1, T2> appointmentList[], int& recordCount) {
    if (recordCount >= MAX_APPOINTMENTS) {
        cout << "The appointment list is full." << endl;
        return;
    }

    Appointment<T1, T2> appointment;

    if constexpr (is_same<T1, string>::value) {
        promptTextLine("Enter appointment ID:", appointment.id);
    }
    else {
        string line;
        cout << "Enter numeric appointment ID:" << endl;
        getline(cin, line);
        while (!parseFromString<T1>(line, appointment.id)) {
            cout << "Invalid number. Try again:" << endl;
            getline(cin, line);
        }
    }

    promptTextLine("Enter patient name:", appointment.patientName);
    promptTextLine("Enter appointment type (General, Dental, Emergency, etc.):", appointment.appointmentType);
    promptPositiveInteger("Enter time until appointment (hours):", appointment.timeUntilHours);

    double billValue = 0.0;
    promptNonNegativeDouble("Enter estimated bill amount:", billValue);
    appointment.estimatedBillAmount = static_cast<T2>(billValue);

    appointment.status = "Pending";
    appointmentList[recordCount++] = appointment;

    cout << "Appointment added successfully." << endl;
}

//Shows all appointments to the user with the ID,name,type,time,bill and status
template <typename T1, typename T2>
void displayAllAppointments(Appointment<T1, T2> appointmentList[], int recordCount) {
    cout << "ID | Name | Type | Time(h) | Bill | Status" << endl;
    for (int index = 0; index < recordCount; index++) {
        cout << convertToString(appointmentList[index].id) << " | "
            << appointmentList[index].patientName << " | "
            << appointmentList[index].appointmentType << " | "
            << appointmentList[index].timeUntilHours << " | $"
            << fixed << setprecision(2)
            << static_cast<double>(appointmentList[index].estimatedBillAmount) << " | "
            << appointmentList[index].status << endl;
    }
}
//Marks an appointment as completed otherwise 
template <typename T1, typename T2>
void markAppointmentCompleted(Appointment<T1, T2> appointmentList[], int recordCount) {
    cout << "Enter appointment ID to mark as completed:" << endl;
    string inputLine;
    getline(cin, inputLine);
    while (inputLine.empty()) {
        cout << "Input cannot be empty. Try again:" << endl;
        getline(cin, inputLine);
    }

    if constexpr (is_same<T1, string>::value) {
        for (int index = 0; index < recordCount; index++) {
            if (appointmentList[index].id == inputLine) {
                appointmentList[index].status = "Completed";
                cout << "Appointment " << appointmentList[index].id << " marked as completed." << endl;
                return;
            }
        }
    }
    else {
        T1 key{};
        if (!parseFromString<T1>(inputLine, key)) {
            cout << "Invalid numeric ID." << endl;
            return;
        }
        for (int index = 0; index < recordCount; index++) {
            if (appointmentList[index].id == key) {
                appointmentList[index].status = "Completed";
                cout << "Appointment " << convertToString(appointmentList[index].id)
                    << " marked as completed." << endl;
                return;
            }
        }
    }
    cout << "Appointment not found." << endl;
}

//Shows how many appointments there are and how much money has been made
template <typename T1, typename T2>
void viewAppointmentSummary(Appointment<T1, T2> appointmentList[], int recordCount) {
    int completedCount = 0;
    double totalEarnings = 0.0;

    for (int index = 0; index < recordCount; index++) {
        if (appointmentList[index].status == "Completed") {
            completedCount++;
            totalEarnings += static_cast<double>(appointmentList[index].estimatedBillAmount);
        }

        cout << "Total Appointments -  " << recordCount << endl;
        cout << "Completed-  " << completedCount << endl;
        cout << "Pending-  " << recordCount - completedCount << endl;
        cout << "Total Earnings -  " << fixed << setprecision(2) << totalEarnings << endl;
    }


}
int main() {
    Appointment<string, float> appointmentList[MAX_APPOINTMENTS];
    int recordCount = loadAppointmentsFromFile(appointmentList);

    cout << "Clinic Appointment Manager" << endl;

    int userChoice = 0;
    while (userChoice != 5) {
        cout << "1.Add New Appointment" << endl;
        cout << "2.Display All Appointments" << endl;
        cout << "3.Mark Appointment as Completed" << endl;
        cout << "4.View Appointment Summary" << endl;
        cout << "5.Exit" << endl;

        string line;
        getline(cin, line);
        while (!parseFromString<int>(line, userChoice)  || userChoice < 1 || userChoice > 5) {
            cout << "Invalid option! Enter a number between 1 and 5:" << endl;
            getline(cin, line);
        }

        if (userChoice == 1)
            addNewAppointment(appointmentList, recordCount);
        else if (userChoice == 2)
            displayAllAppointments(appointmentList, recordCount);
        else if (userChoice == 3)
            markAppointmentCompleted(appointmentList, recordCount);
        else if (userChoice == 4)
            viewAppointmentSummary(appointmentList, recordCount);
        else if (userChoice == 5) {
            saveAppointmentsToFile(appointmentList, recordCount);
            cout << "All data saved to appointments.txt! Now you can exit and it will be saved for next time!" << endl;
        }
    }

    return 0;
}
