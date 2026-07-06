#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

class User {
    string userName, Email, password;
    fstream file;
    bool signedUp; // Flag to indicate whether the user has signed up

public:
    User() : signedUp(false) {} // Initialize the flag in the constructor
    void SignUp();
    bool Login();
    bool isLoggedIn() const; // Function to check if the user is logged in
};

void User::SignUp() {
    cin.ignore(); // Clear the buffer

    cout << "\n--------------------- SignUp ---------------------\n";
    cout << "Enter your User Name: ";
    getline(cin, userName);
    cout << "Enter your email Address: ";
    getline(cin, Email);
    cout << "Enter your password: ";
    getline(cin, password);

    file.open("LoginData.txt", ios::out | ios::app);
    file << userName << " * " << Email << " * " << password << endl;
    file.close();

    cout << "Account created successfully!\n";
    signedUp = true; // Set the flag to indicate successful signup
}

bool User::Login() {
    if (!signedUp) {
        cout << "You need to sign up first!\n";
        return false;
    }

    cout << "\n--------------------- LOGIN ---------------------\n";
    cin.ignore(); // Clear the buffer

    cout << "Enter your user name: ";
    string inputUserName;
    getline(cin, inputUserName);
    cout << "Enter your password: ";
    string inputPassword;
    getline(cin, inputPassword);

    file.open("LoginData.txt", ios::in);
    while (file >> userName >> Email >> password) {
        if (inputUserName == userName && inputPassword == password) {
            cout << "\nAccount login successful!\n";
            file.close();
            return true;
        }
    }
    file.close();

    cout << "Username or password is incorrect!\n";
    return false;
}

bool User::isLoggedIn() const {
    return signedUp;
}

// Function prototypes
void addRecord();
void displayRecords();
void modifyRecord();
void deleteRecord();

// Student structure
struct Student {
    char name[50];
    int rollNo;
    float marks;
    char section[10];
    int semester;
};

// File name
const char fileName[] = "student_records.txt";

int main() {
    User user;
    char choice;

    do {
        cout << "\n--------------------- MENU ---------------------\n";
        cout << "1- Login\n";
        cout << "2- SignUp\n";
        cout << "3- Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                if (user.Login()) {
                    int studentChoice;
                    do {
                        // Display student management menu
                        cout << "\nStudent Record Management System\n";
                        cout << "1. Add Record\n";
                        cout << "2. Display Records\n";
                        cout << "3. Modify Record\n";
                        cout << "4. Delete Record\n";
                        cout << "5. Logout\n";
                        cout << "Enter your choice: ";
                        cin >> studentChoice;

                        // Process user's choice for student management
                        switch (studentChoice) {
                            case 1:
                                addRecord();
                                break;
                            case 2:
                                displayRecords();
                                break;
                            case 3:
                                modifyRecord();
                                break;
                            case 4:
                                deleteRecord();
                                break;
                            case 5:
                                cout << "Logging out...\n";
                                break;
                            default:
                                cout << "Invalid choice. Please enter a valid option.\n";
                        }
                    } while (studentChoice != 5);
                }
                break;
            case '2':
                user.SignUp();
                break;
            case '3':
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid selection!\n";
        }
    } while (choice != '3');

    return 0;
}

// Function to add a new record
void addRecord() {
    ofstream outFile(fileName, ios::app); // Open file in append mode

    if (!outFile) {
        cerr << "Error opening file for writing.\n";
        exit(EXIT_FAILURE);
    }

    Student newStudent;

    cout << "Enter name: ";
    cin.ignore(); // Clear the input buffer
    cin.getline(newStudent.name, sizeof(newStudent.name));

    cout << "Enter roll number: ";
    cin >> newStudent.rollNo;

    cout << "Enter marks: ";
    cin >> newStudent.marks;

    cout << "Enter section: ";
    cin >> newStudent.section;

    cout << "Enter semester: ";
    cin >> newStudent.semester;

    // Write the record to the file
    outFile << newStudent.name << ' ' << newStudent.rollNo << ' ' << newStudent.marks << ' '
            << newStudent.section << ' ' << newStudent.semester << endl;

    cout << "Record added successfully.\n";

    outFile.close();
}

// Function to display all records
void displayRecords() {
    ifstream inFile(fileName);

    if (!inFile) {
        cerr << "Error opening file for reading.\n";
        exit(EXIT_FAILURE);
    }

    Student currentStudent;

    // Read records from the file and display them
    cout << "\nStudent Records:\n";
    cout << setw(20) << "Name" << setw(15) << "Roll No" << setw(10) << "Marks" << setw(10) << "Section" << setw(10) << "Semester" << "\n";
    cout << "--------------------------------------------------------\n";

    while (inFile >> currentStudent.name >> currentStudent.rollNo >> currentStudent.marks
           >> currentStudent.section >> currentStudent.semester) {
        cout << setw(20) << currentStudent.name << setw(15) << currentStudent.rollNo << setw(10) << currentStudent.marks
             << setw(10) << currentStudent.section << setw(10) << currentStudent.semester << "\n";
    }

    inFile.close();
}

// Function to modify a record
void modifyRecord() {
    int rollNo;

    cout << "Enter the roll number of the student to modify: ";
    cin >> rollNo;

    ifstream inFile(fileName);
    ofstream outFile("temp.txt");

    if (!inFile || !outFile) {
        cerr << "Error opening file for reading or writing.\n";
        exit(EXIT_FAILURE);
    }

    Student currentStudent;
    bool found = false;

    while (inFile >> currentStudent.name >> currentStudent.rollNo >> currentStudent.marks
           >> currentStudent.section >> currentStudent.semester) {
        if (currentStudent.rollNo == rollNo) {
            cout << "Enter new details:\n";
            cout << "Enter name: ";
            cin.ignore(); // Clear the input buffer
            cin.getline(currentStudent.name, sizeof(currentStudent.name));

            cout << "Enter marks: ";
            cin >> currentStudent.marks;

            cout << "Enter section: ";
            cin >> currentStudent.section;

            cout << "Enter semester: ";
            cin >> currentStudent.semester;

            outFile << currentStudent.name << ' ' << currentStudent.rollNo << ' ' << currentStudent.marks
                    << ' ' << currentStudent.section << ' ' << currentStudent.semester << endl;

            cout << "Record modified successfully.\n";
            found = true;
        } else {
            outFile << currentStudent.name << ' ' << currentStudent.rollNo << ' ' << currentStudent.marks
                    << ' ' << currentStudent.section << ' ' << currentStudent.semester << endl;
        }
    }

    if (!found) {
        cout << "Record not found.\n";
    }

    inFile.close();
    outFile.close();

    remove(fileName);
    rename("temp.txt", fileName);
}

// Function to delete a record
void deleteRecord() {
    int rollNo;

    cout << "Enter the roll number of the student to delete: ";
    cin >> rollNo;

    ifstream inFile(fileName);
    ofstream outFile("temp.txt");

    if (!inFile || !outFile) {
        cerr << "Error opening file for reading or writing.\n";
        exit(EXIT_FAILURE);
    }

    Student currentStudent;
    bool found = false;

    while (inFile >> currentStudent.name >> currentStudent.rollNo >> currentStudent.marks
           >> currentStudent.section >> currentStudent.semester) {
        if (currentStudent.rollNo == rollNo) {
            cout << "Record deleted successfully.\n";
            found = true;
        } else {
            outFile << currentStudent.name << ' ' << currentStudent.rollNo << ' ' << currentStudent.marks
                    << ' ' << currentStudent.section << ' ' << currentStudent.semester << endl;
        }
    }

    if (!found) {
        cout << "Record not found.\n";
    }

    inFile.close();
    outFile.close();

    remove(fileName);
    rename("temp.txt", fileName);
}
