// M2 Managing Memory Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct Student
{
    string name;
    int idNum;
    int* tests;
    double average;
    char grade;
};

//function prototypes
char getLetterGrade(double avg);
void calcGrades(Student* students, int numStudents, int numTests);
void displayReport(const Student* students, int numStudents, int numTests);
void releaseMemory(Student* students, int numStudents);

int main()
{
    int numStudents, numTests;
    ifstream inputFile("student_data.txt");

    if (!inputFile)
    {
        cerr << "Error: could not open input file student_data.txt" << endl;
        return 1;
    }

    inputFile >> numStudents >> numTests;

    if (numStudents <= 0 || numTests <= 0)
    {
        cerr << "Error: Invalid number of students or tests in file." << endl;
        inputFile.close();
        return 1;
    }

    Student* students = new Student[numStudents];

    for (int i = 0; i < numStudents; ++i)
    {
        inputFile >> students[i].name >> students[i].idNum;
        students[i].tests = new int[numTests];
        for (int j = 0; j < numTests; ++j)
        {
            inputFile >> students[i].tests[j];
        }
    }

    inputFile.close();

    calcGrades(students, numStudents, numTests);

    displayReport(students, numStudents, numTests);

    releaseMemory(students, numStudents);

    students = nullptr;

    return 0;
}

//functions
void calcGrades(Student* students, int numStudents, int numTests)
{
    for (int i = 0; i < numStudents; ++i)
    {
        int total = 0;
        for (int j = 0; j < numTests; ++j)
        {
            total += students[i].tests[j];
        }
        students[i].average = static_cast<double>(total) / numTests;
        students[i].grade = getLetterGrade(students[i].average);
    }
}

char getLetterGrade(double avg)
{
    if (avg >= 90.0) return 'A';
    else if (avg >= 80.0) return 'B';
    else if (avg >= 70.0) return 'C';
    else if (avg >= 60.0) return 'D';
    else return 'F';
}

void displayReport(const Student* students, int numStudents, int numTests)
{
    cout << fixed << setprecision(2);
    cout << "\n-- Course Grade Report--\n";
    cout << left << setw(15) << "Name"
        << setw(10) << "ID#"
        << setw(10) << "Average"
        << setw(5) << "Grade" << endl;
    cout << "---------------------------\n";

    for (int i = 0; i < numStudents; ++i) 
    {
        cout << left << setw(15) << students[i].name
            << setw(10) << students[i].idNum
            << setw(10) << students[i].average
            << setw(5) << students[i].grade << endl;
    }
}

void releaseMemory(Student* students, int numStudents) 
{
    for (int i = 0; i < numStudents; ++i)
    {
        delete[] students[i].tests;
        students[i].tests = nullptr;
    }
    delete[] students;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
