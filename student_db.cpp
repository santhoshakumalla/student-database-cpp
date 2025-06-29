#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

struct Student {
    string name;
    string roll;
    float cgpa;
};

const string FILENAME = "students.csv";

// Function to add student to file
void addStudent() {
    Student s;
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, s.name);
    cout << "Enter roll number: ";
    getline(cin, s.roll);
    cout << "Enter CGPA: ";
    cin >> s.cgpa;

    ofstream file(FILENAME, ios::app);
    file << s.name << "," << s.roll << "," << s.cgpa << endl;
    file.close();

    cout << "Student added successfully.\n";
}

// Function to display all students
void viewAllStudents() {
    ifstream file(FILENAME);
    string line;
    cout << left << setw(20) << "Name" << setw(10) << "Roll" << setw(5) << "CGPA" << endl;
    cout << "----------------------------------------\n";

    while (getline(file, line)) {
        stringstream ss(line);
        Student s;
        getline(ss, s.name, ',');
        getline(ss, s.roll, ',');
        string cgpaStr;
        getline(ss, cgpaStr);
        s.cgpa = stof(cgpaStr);

        cout << left << setw(20) << s.name << setw(10) << s.roll << setw(5) << s.cgpa << endl;
    }

    file.close();
}

// Function to search by roll number
void searchStudent() {
    string roll;
    cout << "Enter roll number to search: ";
    cin.ignore();
    getline(cin, roll);

    ifstream file(FILENAME);
    string line;
    bool found = false;

    while (getline(file, line)) {
        stringstream ss(line);
        Student s;
        getline(ss, s.name, ',');
        getline(ss, s.roll, ',');
        string cgpaStr;
        getline(ss, cgpaStr);
        s.cgpa = stof(cgpaStr);

        if (s.roll == roll) {
            cout << "Found: " << s.name << " | Roll: " << s.roll << " | CGPA: " << s.cgpa << endl;
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Student not found.\n";

    file.close();
}

// Function to delete by roll number
void deleteStudent() {
    string roll;
    cout << "Enter roll number to delete: ";
    cin.ignore();
    getline(cin, roll);

    ifstream file(FILENAME);
    vector<string> lines;
    string line;
    bool deleted = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string name, r, cgpa;
        getline(ss, name, ',');
        getline(ss, r, ',');
        getline(ss, cgpa);

        if (r != roll) {
            lines.push_back(line);
        } else {
            deleted = true;
        }
    }
    file.close();

    ofstream outFile(FILENAME);
    for (const auto &l : lines)
        outFile << l << endl;

    outFile.close();

    if (deleted)
        cout << "Student deleted successfully.\n";
    else
        cout << "Student not found.\n";
}

// Menu
void menu() {
    int choice;
    do {
        cout << "\n==== Student Database Manager ====\n";
        cout << "1. Add Student\n2. View All Students\n3. Search Student\n4. Delete Student\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewAllStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 5);
}

int main() {
    menu();
    return 0;
}
