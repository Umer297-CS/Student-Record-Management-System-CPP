#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

class Login {
private:
    string LoginID, Password;
public:
    Login() : LoginID(""), Password("") {}

    void setID(string id) {
        LoginID = id;
    }

    void setPW(string pw) {
        Password = pw;
    }

    string getID() {
        return LoginID;
    }

    string getPW() {
        return Password;
    }
};

void registration(Login& log) {
    system("cls");
    string id, pw;
    cout << "\tEnter Login ID: ";
    cin >> id;
    log.setID(id);

start:
    cout << "\tEnter A Strong Password (Minimum 8 characters): ";
    cin >> pw;
    if (pw.length() >= 8) {
        log.setPW(pw);
    } else {
        cout << "\tPassword must be at least 8 characters long!" << endl;
        goto start;
    }

    ofstream outfile("Login.txt", ios::app);
    if (!outfile) {
        cout << "\tError: File Can't Open!" << endl;
    } else {
        outfile << log.getID() << " : " << log.getPW() << endl << endl;
        cout << "\tUser Registered Successfully!" << endl;
    }
    outfile.close();
    cin.ignore();
    cin.get();
}

bool login(Login& log) {
    system("cls");
    string id, pw;
    cout << "\tEnter Login ID: ";
    cin >> id;

    cout << "\tEnter Password: ";
    cin >> pw;

    ifstream infile("Login.txt");
    if (!infile) {
        cout << "\tError: File Can't Open!" << endl;
        return false;
    } else {
        string line;
        while (getline(infile, line)) {
            stringstream ss(line);
            string userID, userPW;
            char delimiter;
            ss >> userID >> delimiter >> userPW;

            if (id == userID && pw == userPW) {
                infile.close();
                return true;
            }
        }
        infile.close();
        cout << "\tError: Incorrect Login ID Or Password!" << endl;
        return false;
    }
}

// Base class
class Student {
protected:
    struct StudentData {
        char name[50];
        int rollNo;
        float marks;
        char section[5];
        int semester;
    };

public:
    virtual void addRecord() = 0;
    virtual void displayRecords() = 0;
    virtual void modifyRecord() = 0;
    virtual void deleteRecord() = 0;
};

// Derived class
class StudentManager : public Student {
private:
    const char fileName[50] = "student_records.txt";

public:
    void addRecord() override {
        ofstream outFile(fileName, ios::app);

        if (!outFile) {
            cerr << "Error opening file for writing.\n";
            return;
        }

        StudentData newStudent;

        cout << "Enter name: ";
        cin.ignore();
        cin.getline(newStudent.name, sizeof(newStudent.name));

        cout << "Enter roll number: ";
        cin >> newStudent.rollNo;

        cout << "Enter marks: ";
        cin >> newStudent.marks;

        cout << "Enter section: ";
        cin >> newStudent.section;

        cout << "Enter semester: ";
        cin >> newStudent.semester;

        outFile << newStudent.name << ' ' << newStudent.rollNo << ' ' << newStudent.marks << ' '
                << newStudent.section << ' ' << newStudent.semester << endl;

        cout << "Record added successfully.\n";

        outFile.close();
        cin.ignore();
        cin.get();
    }

    void displayRecords() override {
        ifstream inFile(fileName);

        if (!inFile) {
            cerr << "Error opening file for reading.\n";
            return;
        }

        StudentData currentStudent;

        cout << "\nStudent Records:\n";
        cout << setw(20) << "Name" << setw(15) << "Roll No" << setw(10) << "Marks" << setw(10) << "Section" << setw(10) << "Semester" << "\n";
        cout << "-----------------------------------------------------------------\n";

        // Read and display each student record
        while (inFile >> currentStudent.name >> currentStudent.rollNo >> currentStudent.marks
               >> currentStudent.section >> currentStudent.semester) {
            cout << setw(20) << currentStudent.name << setw(15) << currentStudent.rollNo << setw(10) << currentStudent.marks
                 << setw(10) << currentStudent.section << setw(10) << currentStudent.semester << "\n";
        }

        inFile.close();
        cin.ignore();
        cin.get();
    }

    void modifyRecord() override {
        int rollNo;

        cout << "Enter the roll number of the student to modify: ";
        cin >> rollNo;

        ifstream inFile(fileName);
        ofstream outFile("temp.txt");

        if (!inFile || !outFile) {
            cerr << "Error opening file for reading or writing.\n";
            return;
        }

        StudentData currentStudent;
        bool found = false;

        while (inFile >> currentStudent.name >> currentStudent.rollNo >> currentStudent.marks
               >> currentStudent.section >> currentStudent.semester) {
            if (currentStudent.rollNo == rollNo) {
                cout << "Enter new details:\n";
                cout << "Enter name: ";
                cin.ignore();
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
        cin.ignore();
        cin.get();
    }

    void deleteRecord() override {
        int rollNo;

        cout << "Enter the roll number of the student to delete: ";
        cin >> rollNo;

        ifstream inFile(fileName);
        ofstream outFile("temp.txt");

        if (!inFile || !outFile) {
            cerr << "Error opening file for reading or writing.\n";
            return;
        }

        StudentData currentStudent;
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
        cin.ignore();
        cin.get();
    }
};

void displayMenu() {
    cout << "\nStudent Record Management System\n";
    cout << "1. Add Record\n";
    cout << "2. Display Records\n";
    cout << "3. Modify Record\n";
    cout << "4. Delete Record\n";
    cout << "5. Logout\n";
    cout << "Enter your choice: ";
}

int main() {
    Login log;
    StudentManager manager;

    bool loggedIn = false;
    int choice;

    while (!loggedIn) {
        system("cls");
        cout << "\tWelcome To Registration & Login Form" << endl;
        cout << "\t**" << endl;
        cout << "\t1. Register." << endl;
        cout << "\t2. Login." << endl;
        cout << "\t3. Exit." << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registration(log);
                break;
            case 2:
                if (login(log)) {
                    loggedIn = true;
                    cout << "\tSuccessfully Logged In!\n";
                }
                break;
            case 3:
                cout << "\tGoodbye!" << endl;
                return 0; // Exit the program cleanly
            default:
                cout << "\tInvalid Choice. Please try again." << endl;
                cin.ignore();
                cin.get();
        }
    }

    do {
        system("cls");
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                manager.addRecord();
                break;
            case 2:
                manager.displayRecords();
                break;
            case 3:
                manager.modifyRecord();
                break;
            case 4:
                manager.deleteRecord();
                break;
            case 5:
                cout << "Logging out...\n";
                loggedIn = false;
                break;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
                cin.ignore();
                cin.get();
        }
    } while (loggedIn);

    cout << "Goodbye!\n";
    return 0;
}