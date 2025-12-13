//CMPS 385- Data Structures
//Aditya Singh
//Assignment 8 Problem 2 
// Program is build using a doubly linked list implemented with a
// struct that stores both previous and next pointers
//Global pointers are used,file input and output, and saves to text file



#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;



//Each song represents one node in a double linked list
// It has pointers incorporated to both previous and next songs


struct Song {
    int id;                 
    string title;           
    string artist;          
    float duration;       
    //Pointer to previous song
    //Pointer to next song
    Song* prev;             
    Song* next;             
};


//Global Pointers


Song* first = nullptr;      
Song* last = nullptr;       
Song* current = nullptr; 


//Functions
void loadPlaylist();
void savePlaylist();
void addSong();
void displayPlaylist();
void playNext();
void playPrevious();
void removeSong();


int main() {

    // Load existing playlist from file (if it exists)
    loadPlaylist();

    int choice;

    do {
        cout << "\n**** **** Welcome to MPM (Music playlist manager) ********\n";
        cout << "1.Add Song to Playlist\n";
        cout << "2.Display Playlist\n";
        cout << "3.Play Next Song\n";
        cout << "4.Play Previous Song\n";
        cout << "5.Remove Song\n";
        cout << "6.Save and Exit\n";
        cout << "Please choose a number 1-5 PLEASE! ";

        cin >> choice;
        cin.ignore();  

        switch (choice) {
        case 1:
            addSong();
            break;
        case 2:
            displayPlaylist();
            break;
        case 3:
            playNext();
            break;
        case 4:
            playPrevious();
            break;
        case 5:
            removeSong();
            break;
        case 6:
            savePlaylist();
            cout << "playlist has been saved to text file!\n";
            break;
        default:
            cout << "Invalid option Please TYPE 1-5 ONLY !\n";
        }

    } while (choice != 6);

    return 0;
}


//Function Load playlist - loads songs from playlist.txt into a doubly linked list

void loadPlaylist() {

    ifstream file("playlist.txt");

    // If file doesn't exist
    // start with empty playlist
    if (!file) {
        return;
    }

    int id;
    string title, artist;
    float duration;

    while (file >> id) {
        file.ignore();
        getline(file, title, ',');
        getline(file, artist, ',');
        file >> duration;
        file.ignore();

        Song* newSong = new Song;
        newSong->id = id;
        newSong->title = title;
        newSong->artist = artist;
        newSong->duration = duration;
        newSong->prev = nullptr;
        newSong->next = nullptr;

 
        if (first == nullptr) {
            first = last = current = newSong;
        }
        else {
            last->next = newSong;
            newSong->prev = last;
            last = newSong;
        }
    }

    file.close();
}


//Function SavePlaylist
//Simply saves the file to a text file

void savePlaylist() {

    ofstream file("playlist.txt");

    Song* temp = first;

    while (temp != nullptr) {
        file << temp->id << ","
            << temp->title << ","
            << temp->artist << ","
            << temp->duration << endl;
        temp = temp->next;
    }

    file.close();
}

//Function Addsong
//add a song to the end of the playlist


void addSong() {

    Song* newSong = new Song;

    cout << "Enter Song ID: ";
    cin >> newSong->id;
    cin.ignore();

    cout << "Enter Title: ";
    getline(cin, newSong->title);

    cout << "Enter Artist: ";
    getline(cin, newSong->artist);

    cout << "Enter Duration (in minutes): ";
    cin >> newSong->duration;
    cin.ignore();

    newSong->prev = nullptr;
    newSong->next = nullptr;

    // Insert at last
    if (first == nullptr) {
        first = last = current = newSong;
    }
    else {
        last->next = newSong;
        newSong->prev = last;
        last = newSong;
    }

    cout << "song added to playlist! \n";
}


//Display list
//Displays all songs first to last

void displayPlaylist() {

    if (first == nullptr) {
        cout << "Playlist is empty.\n";
        return;
    }

    cout << "\n **** Your Curretn Playlist \n";
    cout << left << setw(8) << "ID"
        << setw(20) << "Title"
        << setw(20) << "Artist"
        << setw(20) << "Duration" << endl;
    Song* temp = first; 

    while (temp != nullptr) {
        cout << left << setw(8) << temp->id
            << setw(20) << temp->title
            << setw(20) << temp->artist
            << setw(20) << temp->duration << endl;
        temp = temp->next;
    }
}

//Playlist
//Moves Curretn pointers forward

void playNext() {

    if (current == nullptr) {
        cout << "Playlist is empty.\n";
        return;
    }

    if (current->next == nullptr) {
        cout << "You are at the last song.\n";
    }
    else {
        current = current->next;
        cout << "Now playing: "
            << current->title << " by "
            << current->artist << " "
            << current->duration << " minutes \n";
    }
}



//Function playPrevious - moves pointer backward 

void playPrevious() {

    if (current == nullptr) {
        cout << "Playlist is empty.\n";
        return;
    }

    if (current->prev == nullptr) {
        cout << "You are at the first song.\n";
    }
    else {
        current = current->prev;
        cout << "Now playing: "
       << current->title << " by "
       << current->artist << " ("
     << current->duration << " min)\n";
    }
}

//Remove song
//Removes a song by ID from a playlist

void removeSong() {

    if (first == nullptr) {
        cout << "Playlist is empty.\n";
        return;
    }

    int targetID;
    cout << "Enter Song ID to remove: ";
    cin >> targetID;

    Song* temp = first;

    // Search for the song
    while (temp != nullptr && temp->id != targetID) {
        temp = temp->next;
    }

    // If not found
    if (temp == nullptr) {
        cout << "Song not found.\n";
        return;
    }

    // Update current pointer if needed
    if (temp == current) {
        if (current->next != nullptr)
            current = current->next;
        else if (current->prev != nullptr)
            current = current->prev;
        else
            current = nullptr;
    }

    // Update first
    if (temp == first) {
        first = temp->next;
        if (first != nullptr)
            first->prev = nullptr;
    }
    // Update last
    else if (temp == last) {
        last = temp->prev;
        if (last != nullptr)
            last->next = nullptr;
    }
    // Middle node
    else {
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
    }

    cout << "Song '" << temp->title << "' removed from playlist.\n";
    delete temp;
}




