#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

// تعريف هيكل لتخزين بيانات الطالب (Structure)
struct Student {
    string name;
    long long universityID;
    double coursework;
    double midterm;
    double finalExam;
    double totalScore;
    double percentage;
    char grade;
};

// دالة لحساب المجموع، النسبة المئوية، والتقدير باستخدام الشروط (if-else)
void calculateStudentData(Student &s) {
    s.totalScore = s.coursework + s.midterm + s.finalExam;
    
    // حساب النسبة المئوية بدقة (باعتبار المجموع الكلي من 100)
    double maxTotal = 100.0;
    s.percentage = (s.totalScore / maxTotal) * 100.0;

    if (s.percentage >= 90) {
        s.grade = 'A';
    } else if (s.percentage >= 80) {
        s.grade = 'B';
    } else if (s.percentage >= 70) {
        s.grade = 'C';
    } else if (s.percentage >= 60) {
        s.grade = 'D';
    } else {
        s.grade = 'F';
    }
}

// دالة لإضافة بيانات 10 طلاب افتراضياً
void loadDefaultStudents(vector<Student> &students) {
    vector<Student> defaultStudents = {
        {"Ahmed Ali", 2023001, 18.5, 27.0, 45.0, 0, 0, ' '},
        {"Fatima Omar", 2023002, 20.0, 29.5, 48.0, 0, 0, ' '},
        {"Mohamed Hassan", 2023003, 15.0, 22.0, 35.0, 0, 0, ' '},
        {"Aya Mahmoud", 2023004, 19.0, 28.0, 46.5, 0, 0, ' '},
        {"Khaled Youssef", 2023005, 12.0, 18.0, 28.0, 0, 0, ' '},
        {"Salma Ibrahim", 2023006, 17.5, 25.0, 40.0, 0, 0, ' '},
        {"Omar Farouk", 2023007, 14.0, 20.0, 32.0, 0, 0, ' '},
        {"Nouran Tarek", 2023008, 19.5, 29.0, 49.0, 0, 0, ' '},
        {"Ziad Adel", 2023009, 16.0, 24.0, 38.0, 0, 0, ' '},
        {"Mariam Nabil", 2023010, 18.0, 26.5, 44.0, 0, 0, ' '}
    };

    for (auto &s : defaultStudents) {
        calculateStudentData(s);
        students.push_back(s);
    }
}

// دالة لإدخال بيانات طالب جديد وعرض نتيجته فوراً
void addStudent(vector<Student> &students) {
    Student s;
    cout << "\n--- Enter Student Details ---\n";
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, s.name);
    
    cout << "Enter University ID: ";
    cin >> s.universityID;
    
    cout << "Enter Coursework Score (out of 20): ";
    cin >> s.coursework;
    
    cout << "Enter Midterm Score (out of 30): ";
    cin >> s.midterm;
    
    cout << "Enter Final Exam Score (out of 50): ";
    cin >> s.finalExam;

    // حساب البيانات (المجموع، النسبة، التقدير)
    calculateStudentData(s);
    students.push_back(s);

    // طباعة النتيجة فوراً للمستخدم
    cout << "\n----------------------------------------\n";
    cout << " Student Added & Evaluated Successfully!\n";
    cout << "----------------------------------------\n";
    cout << " Name       : " << s.name << endl;
    cout << " Total Score: " << s.totalScore << " / 100\n";
    cout << " Percentage : " << fixed << setprecision(1) << s.percentage << "%\n";
    cout << " Grade      : " << s.grade << endl;
    cout << "----------------------------------------\n";
}

// دالة لعرض جميع الطلاب في جدول منسق
void displayStudents(const vector<Student> &students) {
    if (students.empty()) {
        cout << "\nNo student records found.\n";
        return;
    }

    cout << "\n-----------------------------------------------------------------------------------\n";
    cout << setw(15) << left << "Name" 
         << setw(15) << "University ID" 
         << setw(12) << "Coursework" 
         << setw(10) << "Midterm" 
         << setw(10) << "Final" 
         << setw(10) << "Total" 
         << setw(12) << "Percentage" 
         << setw(8) << "Grade" << endl;
    cout << "-----------------------------------------------------------------------------------\n";

    for (const auto &s : students) {
        cout << setw(15) << left << s.name 
             << setw(15) << s.universityID 
             << setw(12) << s.coursework 
             << setw(10) << s.midterm 
             << setw(10) << s.finalExam 
             << setw(10) << s.totalScore 
             << setw(10) << fixed << setprecision(1) << s.percentage << "%" 
             << setw(8) << s.grade << endl;
    }
    cout << "-----------------------------------------------------------------------------------\n";
}

// دالة لترتيب الطلاب حسب المجموع تنازلياً
void sortStudents(vector<Student> &students) {
    if (students.empty()) {
        cout << "\nNo student records to sort.\n";
        return;
    }

    sort(students.begin(), students.end(), [](const Student &a, const Student &b) {
        return a.totalScore > b.totalScore;
    });

    cout << "\nStudents successfully sorted by total score (Highest to Lowest)!\n";
    displayStudents(students);
}

// دالة للبحث عن طالب بالرقم الجامعي
void searchStudent(const vector<Student> &students) {
    if (students.empty()) {
        cout << "\nNo student records to search.\n";
        return;
    }

    long long searchID;
    cout << "\nEnter University ID to search: ";
    cin >> searchID;

    bool found = false;
    for (const auto &s : students) {
        if (s.universityID == searchID) {
            cout << "\n=== Student Found ===\n";
            cout << "Name: " << s.name << endl;
            cout << "University ID: " << s.universityID << endl;
            cout << "Total Score: " << s.totalScore << "/100\n";
            cout << "Percentage: " << fixed << setprecision(1) << s.percentage << "%\n";
            cout << "Grade: " << s.grade << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nStudent with ID " << searchID << " not found.\n";
    }
}

// الدالة الرئيسية
int main() {
    vector<Student> students;

    // تحميل بيانات الـ 10 طلاب افتراضياً
    loadDefaultStudents(students);
    cout << "[Info] 10 default student records have been loaded successfully!\n";

    int choice;

    do {
        cout << "\n=== Student Grades Management System ===\n";
        cout << "1. Add Student Data\n";
        cout << "2. Display All Students\n";
        cout << "3. Sort Students by Total Score (Highest to Lowest)\n";
        cout << "4. Search Student by University ID\n";
        cout << "5. Exit\n";
        cout << "Enter your choice (1-5): ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent(students);
                break;
            case 2:
                displayStudents(students);
                break;
            case 3:
                sortStudents(students);
                break;
            case 4:
                searchStudent(students);
                break;
            case 5:
                cout << "\nExiting program. Goodbye!\n";
                break;
            default:
                cout << "\nInvalid choice! Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
