#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct Student {
    string name;
    vector<int> grades;
};

vector<Student> loadGrades(const string& filename) {
    vector<Student> students;
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            size_t pos = line.find("-");
            string name = line.substr(0, pos);
            string gradesStr = line.substr(pos + 1);
            vector<int> grades;
            stringstream ss(gradesStr);
            int grade;
            while (ss >> grade) {
                grades.push_back(grade);
            }
            students.push_back({ name, grades });
        }
        file.close();
    }
    return students;
}

void printGrades(const Student& student) {
    cout << "Name student: " << student.name;
    cout << ": ";
    for (int grade : student.grades) {
        cout << grade << " ";
    }
    cout << endl;
}

void addStudent(vector<Student>& students) {
    string name;
    cout << "Enter name: ";
    getline(cin, name);

    vector<int> grades;
    string gradesStr;
    cout << "Enter grades: ";
    getline(cin, gradesStr);
    stringstream ss(gradesStr);
    int grade;
    while (ss >> grade) {
        grades.push_back(grade);
    }

    students.push_back({ name, grades });
}

void deleteStudent(vector<Student>& students, const string& name) {
    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->name == name) {
            students.erase(it);
            cout << "Student " << name << " Delete on list." << endl;
            return;
        }
    }
    cout << "Student " << name << " not found in list." << endl;
}
void updateStudent(vector<Student>& students, const string& name) {
    for (auto& student : students) {
        if (student.name == name) {
            string gradesStr;
            cout << "Enter updated grades for " << name << ": ";
            getline(cin, gradesStr);
            stringstream ss(gradesStr);
            int grade;
            student.grades.clear();
            while (ss >> grade) {
                student.grades.push_back(grade);
            }
            cout << "Grades updated for " << name << endl;
            return;
        }
    }
    cout << "Student " << name << " not found in list." << endl;
}
void searchStudents(const vector<Student>& students) {
    string searchTerm;
    cout << "Enter search term: ";
    getline(cin, searchTerm);

    bool found = false;
    for (const auto& student : students) {
        if (student.name.find(searchTerm) != string::npos) {
            printGrades(student);
            found = true;
        }
    }

    if (!found) {
        cout << "No students found with name containing " << searchTerm << endl;
    }
}
void exportGrades(const vector<Student>& students, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const Student& student : students) {
            file << student.name << "-";
            for (int grade : student.grades) {
                file << grade << " ";
            }
            file << endl;
        }
        file.close();
        cout << "Student data exported to file: " << filename << endl;
    }
    else {
        cout << "Unable to export student data to file: " << filename << endl;
    }
}
int main() {
    setlocale(LC_ALL, "rus");
    string filename = "grades.txt";
    vector<Student> students = loadGrades(filename);
    for (const Student& student : students) {
        printGrades(student);
    }

    addStudent(students);
    cout << "New list:" << endl;
    for (const Student& student : students) {
        printGrades(student);
    }
    string nameToUpdate;
    cout << "Enter name of student to update: ";
    getline(cin, nameToUpdate);
    updateStudent(students, nameToUpdate);
    cout << "Updated list:" << endl;
    for (const Student& student : students) {
        printGrades(student);
    }
    string nameToDelete;
    cout << "Enter name of student to delete: ";
    getline(cin, nameToDelete);
    deleteStudent(students, nameToDelete);
    cout << "Updated list:" << endl;
    for (const Student& student : students) {
        printGrades(student);
    }
    searchStudents(students);
    for (const Student& student : students) {
        printGrades(student);
    }
    exportGrades(students, "exported_grades.txt");
    for (const Student& student : students) {
        printGrades(student);
    }
    return 0;
}