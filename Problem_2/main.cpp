#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <time.h>

#define PRINT(x) std::cout << x << std::endl

enum UserType {
    DOESNOTEXIST,STUDENT,ADMIN
}currentUser;

class {
    

public:
    std::string m_username = "DoesNotExist";

    void ChangeAdmin(std::string username)
    {
        m_username = username;
    }
}currentAdmin;

class {
    

public:
    std::string m_username = "DoesNotExist";

    void ChangeAdmin(std::string username)
    {
        m_username = username;
    }

}currentStudent;

struct CourseStructure {
    unsigned short m_courseNum = 255;
    char m_courseId[7] = "Null00";
    int m_credits = 4;

    

    CourseStructure(short courseNum,char courseId[7],int credits) {
        m_courseNum = courseNum;
        memcpy(m_courseId, courseId, 7);
        m_credits = credits;
    }

    CourseStructure() = default;
};

class Semester{
    short* m_allGrades = nullptr;
    CourseStructure* m_allCourseStrutures = nullptr;
    unsigned short m_semesterNumber = 0;
    unsigned short m_numOfCourses = 0;
    unsigned short m_numOfStudents = 10;
    std::string m_semesterDataFilepath;
    std::string m_semesterStructureFilepath;

public:

    void LoadSemesterStructure() {
        std::fstream SemesterDataFile(m_semesterStructureFilepath, (std::ios::openmode)(std::ios::binary | std::ios::in | std::ios::beg));

        SemesterDataFile.read((char*)&m_numOfCourses, 2);
        SemesterDataFile.read((char*)&m_numOfStudents, 2);

        m_allCourseStrutures = new CourseStructure[m_numOfCourses];
        
        SemesterDataFile.read((char*)m_allCourseStrutures, sizeof(CourseStructure) * m_numOfCourses);       

        SemesterDataFile.close();
    }

    void LoadSemesterData() {
        
        std::fstream StudentGradeFile(m_semesterDataFilepath, (std::ios::openmode)(std::ios::binary | std::ios::in | std::ios::beg));

        m_allGrades = new short[m_numOfCourses * m_numOfStudents];
        
        StudentGradeFile.read((char*)m_allGrades, (m_numOfStudents * m_numOfCourses)*2);

        StudentGradeFile.close();
    }

    void LoadSemesterWithData() {
        LoadSemesterStructure();
        LoadSemesterData();
    }

    void DeleteData() {
        delete[] m_allCourseStrutures;
        delete[] m_allGrades;
        m_allCourseStrutures = nullptr;
        m_allGrades = nullptr;
    }

    void ShowSemesterStructure() {
        std::cout << "There are " << m_numOfCourses << " of courses in this semester." << std::endl;

        for (int i = 0; i < m_numOfCourses; i++)
        {
            std::cout << m_allCourseStrutures[i].m_courseNum << "-" << m_allCourseStrutures[i].m_courseId << std::endl;
        }
    }

    void ShowSemesterGrade(int StudentRollNo) {
        std::cout << "Grades of Roll No: " << StudentRollNo << " in semester " << m_semesterNumber << " are\n";
        StudentRollNo = StudentRollNo % 1000;
        std::cout << " S.no | Course | Grade\n";
        for (int i = 0; i < m_numOfCourses; i++)
        {
            std::cout << "  " << i + 1 << "   |  " << (m_allCourseStrutures[i]).m_courseId << " | " << m_allGrades[(StudentRollNo-1) * m_numOfCourses + i] << '\n';
        }
    }

    void SetSemesterStructure() {
        if (!(currentUser == ADMIN)) {
            PRINT("Access Denied!!\nPlease contact Admin");
            return;
        }

        static_assert(sizeof(CourseStructure) == 16, "CoursesStructure size is wrong");

        DeleteData();
        
        PRINT("______Set Courses______");
        PRINT("First input the number of courses then provide details for each courses");
        std::cout << "Number of courses: ";
        std::cin >> m_numOfCourses;
        std::cin.get();

        m_allCourseStrutures = new CourseStructure[m_numOfCourses];
        std::fstream SemesterStructureFile(m_semesterStructureFilepath, (std::ios::openmode)(std::ios::binary | std::ios::out | std::ios::beg));

        SemesterStructureFile.write((char*)&m_numOfCourses, sizeof(short));
        SemesterStructureFile.write((char*)&m_numOfStudents, sizeof(short));

        PRINT("Fill each courseId");

        for (int i = 0; i < m_numOfCourses; i++)
        {
            short CourseNum = i + 1;
            std::string courseIdSTR = "Null00";
            char courseId[7] = "NULL00";
            int credits = 4;

            std::cout << "For " << i + 1 << " course: ";

            getline(std::cin, courseIdSTR);

            memcpy(courseId, (courseIdSTR.c_str()), 6);

            m_allCourseStrutures[i] = CourseStructure(CourseNum, courseId, credits);

            SemesterStructureFile.write((char*)&(m_allCourseStrutures[i]), sizeof(CourseStructure));
        }

        SemesterStructureFile.close();
    }

    void SetStudentGrades() {
        if (!(currentUser == ADMIN)) {
            PRINT("Access Denied!!\nPlease contact Admin");
            return;
        }

        PRINT("____Set grades of students____\n");
        std::cout << "For " << m_semesterNumber << " semester.\n";
        std::fstream StudentGradeFile(m_semesterDataFilepath, (std::ios::openmode)(std::ios::binary | std::ios::out | std::ios::beg));

        if(m_allGrades != nullptr) delete[] m_allGrades;

        m_allGrades = new short[m_numOfCourses * m_numOfStudents];

        for (int i = 0; i < m_numOfStudents; i++)
        {
            std::cout << "Input grades for Roll No: " << i + 240001001 <<'\n';
            
            for (int j = 0; j < m_numOfCourses; j++)
            {
                int grade = 0;
                std::cout << "For " << m_allCourseStrutures[j].m_courseId << " course: ";
                std::cin >> grade;
                std::cin.get();
                grade = std::clamp(grade, 0, 10);
                
                m_allGrades[i * m_numOfCourses + j] = grade;
               
            }
            std::cout << '\n';
        }

        StudentGradeFile.write((char*)m_allGrades, (m_numOfCourses * m_numOfStudents)* 2);       

        StudentGradeFile.close();

    }

        void SetStudentGradesRandomly() {
        if (!(currentUser == ADMIN)) {
            PRINT("Access Denied!!\nPlease contact Admin");
            return;
        }

        PRINT("____Set grades of students____\n");
        std::cout << "For " << m_semesterNumber << " semester.\n";
        std::fstream StudentGradeFile(m_semesterDataFilepath, (std::ios::openmode)(std::ios::binary | std::ios::out | std::ios::beg));

        if(m_allGrades != nullptr) delete[] m_allGrades;

        m_allGrades = new short[m_numOfCourses * m_numOfStudents];

        for (int i = 0; i < m_numOfStudents; i++)
        {
            std::cout << "Input grades for Roll No: " << i + 240001001 <<'\n';
            std::srand(time(0));
            for (int j = 0; j < m_numOfCourses; j++)
            {
                int grade = 0;
                
               
                std::srand(std::rand());
                m_allGrades[i * m_numOfCourses + j] = std::rand() % 6 + 4;
               
            }
            std::cout << '\n';
        }

        StudentGradeFile.write((char*)m_allGrades, (m_numOfCourses * m_numOfStudents)*2);       

        StudentGradeFile.close();

    }

    float CalculateSPI(int StudentRollNo) {
        StudentRollNo = StudentRollNo % 1000 - 1;
        float weightedSum = 0;
        float totalCredit = 0;
        for (int i = 0; i < m_numOfCourses; i++)
        {
            weightedSum += m_allGrades[StudentRollNo * m_numOfCourses + i] * m_allCourseStrutures[i].m_credits;
            totalCredit += m_allCourseStrutures[i].m_credits;
        }

        return weightedSum / totalCredit;


    }

    float CalculateTotalCredits() {
        float totalCredit = 0;
        for (int i = 0; i < m_numOfCourses; i++)
        {
            totalCredit += m_allCourseStrutures[i].m_credits;
        }
        return totalCredit;
    }

    Semester(short SemesterNumber,short numOfStudents) {
        m_semesterNumber = SemesterNumber;
        m_numOfStudents = numOfStudents;
        m_semesterStructureFilepath = "SemesterData/Semester" + std::to_string(SemesterNumber) + "Structure.dat";
        m_semesterDataFilepath = "SemesterData/StudentGrade" + std::to_string(SemesterNumber) + ".dat";
        
        LoadSemesterWithData();
        
    }

    ~Semester() {
        DeleteData();
    }
};

class {
    int numberOfStudents = 10;
    Semester semester1 = Semester(1, numberOfStudents);
    Semester semester2 = Semester(2, numberOfStudents);
    Semester semester3 = Semester(3, numberOfStudents);
    Semester semester4 = Semester(4, numberOfStudents);
    Semester semester5 = Semester(5, numberOfStudents);
    Semester semester6 = Semester(6, numberOfStudents);
    Semester semester7 = Semester(7, numberOfStudents);
    Semester semester8 = Semester(8, numberOfStudents);

    Semester* semesterList[8] = { &semester1 , &semester2 , &semester3 , &semester4 , &semester5 , &semester6 , &semester7 , &semester8 };

public:
    void LoadAllSemesterData() {

        for (int i = 0; i < 8; i++)
        {
            (*(semesterList[i])).LoadSemesterWithData();
        }
    }

    void DeleteAllSemesterData() {
        for (int i = 0; i < 8; i++)
        {
            (*(semesterList[i])).DeleteData();
        }
    }

    void SetSemesterStructure(int currentSemester) {
        (*(semesterList[currentSemester - 1])).SetSemesterStructure();
    }

    void SetStudentGrades(int currentSemester) {
        (*(semesterList[currentSemester - 1])).SetStudentGrades();
    }

    void SetStudentGradesRandomly(int currentSemester) {
        (*(semesterList[currentSemester - 1])).SetStudentGradesRandomly();
    }

    void ShowSemesterStructure(int currentSemester) {
        (*(semesterList[currentSemester - 1])).ShowSemesterStructure();
    }

    void ShowSemesterGrade(int StudentRollNo, int currentSemester) 
    { 
        (*(semesterList[currentSemester - 1])).ShowSemesterGrade(StudentRollNo);
    }

    void CalculateSPI(int StudentRollNo, int semesterNo) {
        std::cout << "SPI of " << StudentRollNo << " for semester " << semesterNo << " is " << (*(semesterList[semesterNo - 1])).CalculateSPI(StudentRollNo) << '\n';
    }

    void CalculateCPI(int StudentRollNo,int semesterNo) {
        float weightedSum = 0;
        float totalCredits = 0;

        for (int i = 0; i < semesterNo ; i++)
        {
            weightedSum += (*(semesterList[i])).CalculateSPI(StudentRollNo) * (*(semesterList[i])).CalculateTotalCredits();
            totalCredits += (*(semesterList[i])).CalculateTotalCredits();
        }


        std::cout << "CPI of " << StudentRollNo << " is " << weightedSum/totalCredits << '\n';
    }
    
    std::string GetStudentName(int StudentRollNo) {
        std::fstream StudentNamesFile("LoginInfo/StudentNames.txt", (std::ios::openmode)(std::ios::in | std::ios::beg));
        std::string line = "";
        while (getline(StudentNamesFile, line)) {
            if (StudentRollNo == std::stoi(line.substr(0, 9))) return line.substr(10, line.length() - 1);
        }
        return "No Name Found";
    }

    void ShowStudentDetails(int StudentRollNo,int currentSemester) {
        std::string StudentName = GetStudentName(StudentRollNo);
        std::cout << "Name: " << StudentName << '\n';

        for (int i = 1; i < currentSemester + 1; i++)
        {
            ShowSemesterGrade(StudentRollNo,i);
            CalculateSPI(StudentRollNo,i);
        }
        CalculateCPI(StudentRollNo,currentSemester);
        
    }

    void ShowAllStudentsGrade(int currentSemester){
        for (int i = 0; i < numberOfStudents; i++)
        {
            ShowSemesterGrade(240001001 + i,currentSemester);
        }
        
    }

    

}allData;

void Login() {
    std::string Username;
    std::string Password;

    std::string inputUsername;
    std::string inputPassword;

    PRINT("________Input your credentials________");

    std::cout << "Username: ";
    getline(std::cin, inputUsername);
    std::cout << "Password: ";
    getline(std::cin, inputPassword);

    std::fstream AdminLoginFile("LoginInfo/AdminLogin.txt", std::ios::in);

    while (getline(AdminLoginFile,Username)) {
        getline(AdminLoginFile, Password);

        if ((Username == inputUsername) && (Password == inputPassword)) {
            currentUser = ADMIN;
            PRINT("LOGIN CONFIRMED");
            break;
        }        
    }   

    AdminLoginFile.close();

    if (currentUser == DOESNOTEXIST) {
        std::fstream StudentLoginFile("LoginInfo/StudentLogin.txt", std::ios::in);

        while (getline(StudentLoginFile, Username)) {
            getline(StudentLoginFile, Password);

            if ((Username == inputUsername) && (Password == inputPassword)) {
                currentUser = STUDENT;
                PRINT("LOGIN CONFIRMED");
                break;
            }
        }

        StudentLoginFile.close();
    }

    if (currentUser == DOESNOTEXIST) {
        PRINT("Incorrect credentials.");
        return;
    }
    else if (currentUser == ADMIN) {
        currentAdmin.ChangeAdmin(inputUsername);
    }
    else if (currentUser == STUDENT) {
        currentStudent.ChangeAdmin(inputUsername);
    }

    
    
}

void AdminInterface() {
    if (!(currentUser == ADMIN)) {
        PRINT("Access Denied!!\nPlease contact Admin");
        return;
    }

    PRINT("____Welcome To Admin Interface____");
    
    int option = 0;
    int currentSemester = 0;
    bool LogIn = true;

    std::cout << "Choose current semester:";
    std::cin >> currentSemester;
    std::cin.get();

    while (LogIn) {
        PRINT("");
        PRINT("Choose the operation you want to do");
        PRINT("1 - Change Current Semester");
        PRINT("2 - Set Semester Structure");
        PRINT("3 - Set Student grades");
        PRINT("4 - View Course Structure");
        PRINT("5 - View All Students Grades");
        PRINT("Anything else to Logout");
        
        std::cout << "Select a option by typing the corresponding number: ";
        std::cin >> option;
        PRINT("");

        switch (option)
        {
        case 1:
            std::cout << "Change current semester to: ";
            std::cin >> currentSemester;
            break;
        case 2:
            allData.SetSemesterStructure(currentSemester);
            break;
        case 3:
            allData.SetStudentGrades(currentSemester);
            break;
        case 4:
            allData.ShowSemesterStructure(currentSemester);
            break;

        case 5:
            allData.ShowAllStudentsGrade(currentSemester);
            break;
        case 42:
            allData.SetStudentGradesRandomly(currentSemester);
            break;
        default:
            LogIn = false;
            break;
        }
    }
}

void StudentInterface() {
    PRINT("____Welcome To Student Interface____");

    int option = 0;
    int currentSemester = 0;
    bool LogIn = true;

    std::cout << "Choose current semester:";
    std::cin >> currentSemester;
    std::cin.get();

    while (LogIn) {
        PRINT(" ");
        PRINT("Choose the operation you want to do");
        PRINT("1 - Change Semester");
        PRINT("2 - Show grades");
        PRINT("3 - Calculate SPI");
        PRINT("4 - Calculate CPI");
        PRINT("5 - Show Student details");
        PRINT("Anything else to Logout");

        std::cout << "Select a option by typing the corresponding number: ";
        std::cin >> option;
        PRINT("");

        switch (option)
        {
        case 1:
            std::cout << "Change current semester to: ";
            std::cin >> currentSemester;
            break;
        case 2:
            allData.ShowSemesterGrade(std::stoi(currentStudent.m_username),currentSemester);
            break;
        case 3:
            allData.CalculateSPI(std::stoi(currentStudent.m_username), currentSemester);
            break;
        case 4:
            allData.CalculateCPI(std::stoi(currentStudent.m_username),currentSemester);
            break;
        case 5:
            allData.ShowStudentDetails(std::stoi(currentStudent.m_username),currentSemester);
            break;

        default:
            LogIn = false;
            break;
        }
    }
}

void FillStudentLoginInfo() {
    std::fstream StudentLoginFile("StudentLogin.txt", (std::ios::openmode)(std::ios::binary | std::ios::out | std::ios::beg));
    int RollNo = 240001001;
    int Password = 1001;
    int numOfStudents = 5;

    for (int i = 0; i < numOfStudents; i++,RollNo++,Password++)
    {
        StudentLoginFile << RollNo << '\n';
        StudentLoginFile << Password << '\n';
    }

    StudentLoginFile.close();
    
}

int main()
{
    
    
    while (true) {
        currentUser = DOESNOTEXIST;
        Login();

        if (currentUser == DOESNOTEXIST) {
            return -1;
        }
        else if (currentUser == ADMIN) {
            AdminInterface();
        }
        else if (currentUser == STUDENT) {
            StudentInterface();
        }
        
            char check = 0;
            std::cout << "Login as new user (y,n): ";
            std::cin >> check;
            std::cin.get();
        
        if (check == 'n' || check == 'N') break;
    }
    
    
    return 0;
}


