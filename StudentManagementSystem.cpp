#include <iostream>
#include <vector>
#include <string>
#include <iomanip> // for formatting output

using namespace std;

struct Student {
    int id;
    string name;
    int age;
    double grade;

    void display() const {
        cout << setw(5) << id << setw(20) << name << setw(5) << age << setw(8) << grade << endl;
    }
};

class StudentManagementSystem {
private:
    vector<Student> students;

public:
    void addStudent() {
        Student s;
        cout << "Enter ID: ";
        cin >> s.id;
        cin.ignore(); // clear input buffer
        cout << "Enter Name: ";
        getline(cin, s.name);
        cout << "Enter Age: ";
        cin >> s.age;
        cout << "Enter Grade: ";
        cin >> s.grade;
        students.push_back(s);
        cout << "Student added successfully.\n";
    }

    void viewStudents() {
        if (students.empty()) {
            cout << "No students found.\n";
            return;
        }
        cout << setw(5) << "ID" << setw(20) << "Name" << setw(5) << "Age" << setw(8) << "Grade" << endl;
        for (const auto& s : students) {
            s.display();
        }
    }

    void searchStudent() {
        int id;
        cout << "Enter student ID to search: ";
        cin >> id;
        for (const auto& s : students) {
            if (s.id == id) {
                cout << "Student found:\n";
                s.display();
                return;
            }
        }
        cout << "Student not found.\n";
    }

    void deleteStudent() {
        int id;
        cout << "Enter student ID to delete: ";
        cin >> id;
        for (auto it = students.begin(); it != students.end(); ++it) {
            if (it->id == id) {
                students.erase(it);
                cout << "Student deleted successfully.\n";
                return;
            }
        }
        cout << "Student not found.\n";
    }

    void menu() {
        while (true) {
            cout << "\n--- Student Management System ---\n";
            cout << "1. Add Student\n";
            cout << "2. View Students\n";
            cout << "3. Search Student\n";
            cout << "4. Delete Student\n";
            cout << "5. Exit\n";
            cout << "Enter your choice: ";
            int choice;
            cin >> choice;

            switch (choice) {
                case 1: addStudent(); break;
                case 2: viewStudents(); break;
                case 3: searchStudent(); break;
                case 4: deleteStudent(); break;
                case 5: cout << "Exiting...\n"; return;
                default: cout << "Invalid choice. Please try again.\n";
            }
        }
    }
};

int main() {
    StudentManagementSystem sms;
    sms.menu();
    return 0;
}
