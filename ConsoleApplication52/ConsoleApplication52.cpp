
#include "Header.h"

using namespace std;


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