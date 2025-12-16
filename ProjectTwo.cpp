//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Emerald Tresch
// Description : Course Planner Hash Table
//============================================================================


#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

string toUpper(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

struct Course {
    string courseNumber;
    string title;
    vector<string> prerequisites;

    Course() {}
    Course(string number, string title, vector<string> prereqs)
        : courseNumber(number), title(title), prerequisites(prereqs) {
    }

    void printInfo() const {
        cout << courseNumber << ", " << title << endl;
        if (!prerequisites.empty()) {
            cout << "Prerequisites: ";
            for (const string& prereq : prerequisites) {
                cout << prereq << " ";
            }
            cout << endl;
        }
        else {
            cout << "Prerequisites: None" << endl;
        }
    }
};

unordered_map<string, Course> courses;

void loadCourses(const string& csvPath) {
    ifstream file(csvPath);
    if (!file.is_open()) {
        cout << "Could not open file: " << csvPath << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string courseNumber, title, prereq;
        vector<string> prereqs;
        getline(ss, courseNumber, ',');
        getline(ss, title, ',');
        while (getline(ss, prereq, ',')) {
            if (!prereq.empty())
                prereqs.push_back(prereq);
        }
        courses[toUpper(courseNumber)] = Course(courseNumber, title, prereqs);
    }
    cout << "Data loaded successfully from " << csvPath << "." << endl;
}

void printCourseList() {
    vector<string> keys;
    for (const auto& pair : courses) keys.push_back(pair.first);
    sort(keys.begin(), keys.end());
    cout << "Here is a sample schedule:" << endl;
    for (const string& key : keys) {
        cout << courses[key].courseNumber << ", " << courses[key].title << endl;
    }
}

void printCourseDetails(const string& courseNumber) {
    auto it = courses.find(toUpper(courseNumber));
    if (it != courses.end()) {
        it->second.printInfo();
    }
    else {
        cout << "Course not found." << endl;
    }
}

int main() {
    int choice;
    const string csvPath = "CS 300 ABCU_Advising_Program_Input.csv";

    cout << "Welcome to the course planner." << endl;

    do {
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do? ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer

        switch (choice) {
        case 1:
            loadCourses(csvPath);
            break;
        case 2:
            printCourseList();
            break;
        case 3: {
            string courseNumber;
            cout << "What course do you want to know about? ";
            getline(cin, courseNumber);
            printCourseDetails(courseNumber);
            break;
        }
        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;
        default:
            cout << choice << " is not a valid option." << endl;
            break;
        }
    } while (choice != 9);

    return 0;
}