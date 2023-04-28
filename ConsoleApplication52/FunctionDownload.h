#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Структура для хранения данных о студенте
struct Student {
    string name;
    vector<int> grades;
};

// Функция для импорта данных из файла
vector<Student> importData(string filename) {
    vector<Student> students;
    ifstream file(filename);
    if (!file) {
        cout << "Error: could not open file " << filename << endl;
    }
    else {
        string line;
        while (getline(file, line)) {
            Student student;
            size_t pos = line.find("-");
            if (pos != string::npos) {
                student.name = line.substr(0, pos - 1);
                string grades_str = line.substr(pos + 2);
                size_t pos2 = 0;
                while ((pos = grades_str.find(",", pos2)) != string::npos) {
                    int grade = stoi(grades_str.substr(pos2, pos - pos2));
                    student.grades.push_back(grade);
                    pos2 = pos + 1;
                }
                int grade = stoi(grades_str.substr(pos2));
                student.grades.push_back(grade);
                students.push_back(student);
            }
        }
        file.close();
    }
    return students;
}

// Функция для экспорта данных в файл
void exportData(vector<Student> students, string filename) {
    ofstream file(filename);
    if (!file) {
        cout << "Error: could not create file " << filename << endl;
    }
    else {
        for (Student student : students) {
            file << student.name << " - ";
            for (int grade : student.grades) {
                file << grade << ",";
            }
            file.seekp(-1, ios_base::cur);
            file << endl;
        }
        file.close();
    }
}

// Функция для добавления данных
void addData(vector<Student>& students) {
    Student student;
    cout << "Enter student name: ";
    getline(cin, student.name);
    cout << "Enter grades (comma-separated): ";
    string grades_str;
    getline(cin, grades_str);
    size_t pos = 0;
    while ((pos = grades_str.find(",")) != string::npos) {
        int grade = stoi(grades_str.substr(0, pos));
        student.grades.push_back(grade);
        grades_str.erase(0, pos + 1);
    }
    int grade = stoi(grades_str);
    student.grades.push_back(grade);
    students.push_back(student);
}

// Функция для обновления данных
void updateData(vector<Student>& students) {
    string name;
    cout << "Enter student name to update: ";
    getline(cin, name);
    auto it = find_if(students.begin(), students.end(), [&name](const Student& s) { return s.name == name; });
    if (it != students.end()) {
        Student& student = *it;
        cout << "Enter new grades (comma-separated): ";
        string grades_str;
        getline(cin, grades_str);
        student.grades.clear();
        size_t pos = 0;
        while ((pos = grades_str.find(",")) != string::npos) {
            int grade = stoi(grades_str.substr(0, pos));
            student.grades.push_back(grade);
            grades_str.erase(0, pos + 1);
        }
        int grade = stoi(grades_str);
        student.grades.push_back(grade);
    }
    else {
        cout << "Error: student " << name << " not found" << endl;
    }
}

// Функция для удаления данных
void deleteData(vector<Student>& students) {
    string name;
    cout << "Enter student name to delete: ";
    getline(cin, name);
    auto it = find_if(students.begin(), students.end(), [&name](const Student& s) { return s.name == name; });
    if (it != students.end()) {
        students.erase(it);
    }
    else {
        cout << "Error: student " << name << " not found" << endl;
    }
}

// Функция для поиска данных
void searchData(vector<Student> students) {
    string name;
    cout << "Enter student name to search: ";
    getline(cin, name);
    auto it = find_if(students.begin(), students.end(), [&name](const Student& s) { return s.name == name; });
    if (it != students.end()) {
        const Student& student = *it;
        cout << student.name << " - ";
        for (int grade : student.grades) {
            cout << grade << ",";
        }
        cout << endl;
    }
    else {
        cout << "Error: student " << name << " not found" << endl;
    }
}

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
    cout << "Имя студента: " << student.name << endl;
    cout << "Оценки: ";
    for (int grade : student.grades) {
        cout << grade << " ";
    }
    cout << endl;
}
