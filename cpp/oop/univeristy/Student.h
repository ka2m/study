#ifndef libs
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#endif

using namespace std;

class Student {
public:
    Student(string aName, string aSurname, string aPatronim, short aYear, short aFacultyId, int aScholarship) {
        name = aName;
        surname = aSurname;
        patronim = aPatronim;
        year = aYear;
        facultyId = aFacultyId;
        scholarship = aScholarship;

        try {
            if (aYear < 1 && aYear > 6) throw -1;
            if (aFacultyId < 1) throw -2;
            if (aScholarship < 0) throw -3;
        }
        catch (int errorCode) {
            switch (errorCode) {
                case -1: cerr << "Invalid year entered\n"; break;
                case -2: cerr << "Invalid faculty id (must be positive)\n"; break;
                case -3: cerr << "Invalid scholarship (must be non-negative)"; break;
                default: cerr << "Some error occurred";
            }
        }

    }

    string getName() {
        return name;
    }

    void setName(string &name) {
        this->name = name;
    }

    string getSurname() {
        return surname;
    }

    void setSurname(string &surname) {
        this->surname = surname;
    }

    string getPatronim() {
        return patronim;
    }

    void setPatronim(string patronim) {
        this->patronim = patronim;
    }

    short getYear() {
        return year;
    }

    void setYear(short year) {
        this->year = year;
    }

    short getFacultyId() const {
        return facultyId;
    }

    void setFacultyId(short facultyId) {
        this->facultyId = facultyId;
    }

    void setMarks(vector<int> &marks) {
        this->marks = marks;
    }

    vector<int>& getMarks() {
        return marks;
    }

    void setScholarship(int scholarship) {
        this->scholarship = scholarship;
    }

    int getScholarship() {
        return scholarship;
    }

    string toString() {
        stringstream ss;
        ss << "Student: " <<
                name << " " <<
                patronim << " " <<
                surname << "\nYear: " <<
                year << "\nFaculty ID: " <<
                facultyId << "\nScholarship: " <<
                scholarship << endl;
        return ss.str();
    }

private:
    string name;
    string surname;
    string patronim;
    short year;
    short facultyId;
    int scholarship;

    vector<int> marks;
};