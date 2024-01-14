#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
using namespace std;
#include <ctime>

// #include <openssl/sha.h> // Required for SHA256 hashing algorithm
// #include <cstdlib> // Required for rand function
// #include <ctime> // Required for time function

// string hashPassword(string password) {
//     // Generate random salt
//     srand(time(NULL));
//     const int SALT_LENGTH = 16;
//     char salt[SALT_LENGTH + 1];
//     const char *CHARACTERS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz./";
//     for (int i = 0; i < SALT_LENGTH; i++) {
//         int index = rand() % strlen(CHARACTERS);
//         salt[i] = CHARACTERS[index];
//     }
//     salt[SALT_LENGTH] = '\0';
//     // Concatenate salt and password
//     string saltedPassword = salt + password;
//     // Hash salted password using SHA256 algorithm
//     const int SHA256_LENGTH = 64;
//     unsigned char sha256[SHA256_LENGTH];
//     SHA256((const unsigned char*) saltedPassword.c_str(), saltedPassword.length(), sha256);
//     // Convert SHA256 hash to string
//     char hex[SHA256_LENGTH * 2 + 1];
//     for (int i = 0; i < SHA256_LENGTH; i++) {
//         sprintf(hex + i * 2, "%02x", sha256[i]);
//     }
//     hex[SHA256_LENGTH * 2] = '\0';
//     return hex;
// }





struct date {
    int day; int month; int year; int hour; int minute; int second;
};

struct course {
    string courseID;

    string courseName;
    int credit;

};
struct Enrollment {
    string studentId;
    string courseId;
    int grade;
};
struct student {
    int ID;
    string firstname;
    string lastname;
    string password;
    string DateOfBirth;
    string address;
    string tel;
    double gpa;
    string problem;
    course* c;
    Enrollment* e;
};



void getphone(student& s1) {
    int counter = 0;
    string temp;
    cout << "enter a valid phone number" << endl;
    cin >> s1.tel;
    if (s1.tel.length() != 8) {
        counter = 0;
        cout << "enter a valid phone number" << endl;
        cin >> s1.tel;
    }
    if (s1.tel.length() == 8) {
        temp = s1.tel.substr(0, 2);
    }
    if (temp == "03" || temp == "71" || temp == "76" || temp == "78" || temp == "81" || temp == "86" || temp == "70") { counter++; }
    //it not work if I write here cin to enter the number again since it will enter yes but it stops it will
    //not go again to check again the length of the number so I solve it using recursion.  

    if (counter == 0) { getphone(s1); }
}

void getEmail(student& s1) {
    int counter = 0;

    cout << "enter your email address: " << endl;
    cin >> s1.address;
    int check = s1.address.find("@");
    while (check < 0) {
        cout << "enter your email address wrong format: " << endl;
        cin >> s1.address;
        check = s1.address.find("@");
    }

    string temp1 = s1.address.substr(s1.address.find("@"), s1.address.length() - 1);
    if (temp1 == "@gmail.com" || temp1 == "@hotmail.com" || temp1 == "@yahoo.com" || temp1 == "@live.com") {
        counter++;
    }
    if (counter == 0) { getEmail(s1); }

}

void getPass(student& s1) {
    int i = 0;
    int numbers = 0, characters = 0, symbols = 0;
    cout << "enter a password it must contains numbers,letters,capital and small.. : " << endl;
    cin >> s1.password;
    while (s1.password.length() < 8) {
        cout << "enter password again its wrong format should be of>8: " << endl;
        cin >> s1.password;
    }
    while (i < s1.password.length() - 1) {
        if (s1.password[i] > 47 && s1.password[i] < 58) { numbers++; }
        if (s1.password[i] > 96 && s1.password[i] < 123) { characters++; }
        if (s1.password[i] > 64 && s1.password[i] < 91) { characters++; }
        if (s1.password[i] > 32 && s1.password[i] <= 47) { symbols++; }
        if (s1.password[i] >= 58 && s1.password[i] <= 64) { symbols++; }
        if (s1.password[i] >= 91 && s1.password[i] <= 96) { symbols++; }
        if (s1.password[i] > 123) { symbols++; }
        i++;
    }
    if (numbers == 0 || characters == 0 || symbols == 0) { getPass(s1); }

}

void getDateOfBirth(student& s1) {
    cout << "enter the birthdate of the student: example: 26-3-2002" << endl;

    cin >> s1.DateOfBirth;
    int counter = 0;

    if (s1.DateOfBirth.length() != 10) {
        counter = 0;
        cout << "enter a valid birthdate: " << endl;
        cin >> s1.DateOfBirth;
    }
    if (s1.DateOfBirth.length() == 10) {
        counter++;
    }
    if (counter == 0) { getDateOfBirth; };

}

void incrementID(student& s1) {
    //not:it works only if we dont delete the file, we need to have the file and inside it there is the first
    //id in order to increment it.
    fstream inputstudent("student.txt", ios::in);
    int id;
    double gpa;
    string name, lastname, pass, birth, address, phone;
    while (inputstudent.good()) {
        inputstudent >> id;
        inputstudent.ignore(INT_MAX, '\t');
        getline(inputstudent, name, '\t');
        getline(inputstudent, lastname, '\t');
        getline(inputstudent, pass, '\t');
        getline(inputstudent, birth, '\t');
        getline(inputstudent, address, '\t');
        getline(inputstudent, phone, '\t');
        inputstudent >> gpa;
        inputstudent.ignore(INT_MAX, '\n');
        if (inputstudent.eof()) {
            break;
        }

    }
    id++;
    s1.ID = id;
    inputstudent.close();


}

void CalcGpa(student& s1) {
    cout << "enter the gpa of the student: it should be zero" << endl;
    cin >> s1.gpa;

}


void checkAdmin(student& s1) {
    cout << "enter your password: " << endl;
    cin >> s1.password;
    cout << "enter your email: " << endl;
    cin >> s1.address;

    fstream readstudent("student.txt", ios::in);

    readstudent.close();
    readstudent.clear();
    readstudent.seekg(0);
    readstudent.open("student.txt");

    int id, counter = 0;;
    double gpa;
    string name, lastname, pass, birth, address, phone;
    while (readstudent.good()) {
        readstudent >> id;
        readstudent.ignore(INT_MAX, '\t');
        getline(readstudent, name, '\t');
        getline(readstudent, lastname, '\t');
        getline(readstudent, pass, '\t');
        getline(readstudent, birth, '\t');
        getline(readstudent, address, '\t');
        getline(readstudent, phone, '\t');
        readstudent >> gpa;
        readstudent.ignore(INT_MAX, '\n');

        if (readstudent.eof()) {
            break;
        }
        if (pass == s1.password && address == s1.address) {
            counter++;

        }
    }
    readstudent.close();

    if (counter == 0) {
        cout << "wrong pass or  email" << endl;
        checkAdmin(s1);
    }

}

//To create a new student profile, the admin should enter the student's ID, 
//full name, password, date of birth, and email. The program should generate 
//unique ID for the student and hash the password using a suitable hash function
// like SHA-256 or bcrypt. The program should also validate the password to ensure it 
//meets the required length and complexity requirements.
void createProfile(student& s1) {
    string temp;
    cout << "enteR your first name: " << endl;
    cin >> s1.firstname;

    cout << "enter your last name :" << endl;
    cin >> s1.lastname;
    getPass(s1);
    getEmail(s1);
    getphone(s1);
    getDateOfBirth(s1);
    CalcGpa(s1);
    incrementID(s1);

    fstream inputstudent("student.txt", ios::out | ios::app);
    int id;
    double gpa;
    string name, lastname, pass, birth, address, phone;
    name = s1.firstname;
    lastname = s1.lastname;
    pass = s1.password;
    birth = s1.DateOfBirth;
    address = s1.address;
    phone = s1.tel;
    gpa = s1.gpa;

    inputstudent << s1.ID << "\t" << name << "\t" << lastname << "\t" << pass << "\t" << birth << "\t" << address << "\t" << phone << "\t" << gpa << endl;

}


//To delete a student, the admin should enter the student ID. The program should remove the student from the student file and all enrollment records for that student
void DeleteStudent(student& s1) {

    fstream theStudentFile("student.txt", ios::in);
    fstream theStudenttemp("tempy.txt", ios::out | ios::app);

    fstream theEnrollFile("enrollment.txt", ios::in);
    fstream theEnrolltemp("tempe.txt", ios::out | ios::app);


    cout << "enter the ID of the student that leaves the university: " << endl;
    cin >> s1.ID;

    int id1;
    double gpa1;
    string fname1, lname1, pass1, birth1, address1, phone1;

    while (theStudentFile.good()) {
        theStudentFile >> id1;
        theStudentFile.ignore(INT_MAX, '\t');
        getline(theStudentFile, fname1, '\t');
        getline(theStudentFile, lname1, '\t');
        getline(theStudentFile, pass1, '\t');
        getline(theStudentFile, birth1, '\t');
        getline(theStudentFile, address1, '\t');
        getline(theStudentFile, phone1, '\t');
        theStudentFile >> gpa1;
        theStudentFile.ignore(INT_MAX, '\n');

        if (theStudentFile.eof()) {
            break;
        }

        if (s1.ID != id1) {
            theStudenttemp << id1 << "\t" << fname1 << "\t" << lname1 << "\t" << pass1 << "\t" << birth1 << "\t" << address1 << "\t" << phone1 << "\t" << gpa1 << endl;

        }

        if (s1.ID == id1) {
            cout << "this student will be deleted successfully: " << endl;
            cout << id1 << "\t" << fname1 << "\t" << lname1 << "\t" << pass1 << "\t" << birth1 << "\t" << address1 << "\t" << phone1 << "\t" << gpa1 << endl;

        }
    }

    theStudentFile.close();
    theStudenttemp.close();
    remove("student.txt");
    rename("tempy.txt", "student.txt");

    int id2;
    string courseID;
    int grade;

    while (theEnrollFile.good()) {

        theEnrollFile >> id2;
        theEnrollFile.ignore(INT_MAX, '\t');
        getline(theEnrollFile, courseID, '\t');
        theEnrollFile >> grade;
        theEnrollFile.ignore(INT_MAX, '\n');

        if (theEnrollFile.eof()) {
            break;

        }

        if (s1.ID != id2) {

            theEnrolltemp << id2 << "\t" << courseID << "\t" << grade << endl;
        }

        if (s1.ID == id2) {

            cout << "this student will be deleted also from the enrollment file of the courses and this will be deleted: " << endl;
            cout << id2 << "\t" << courseID << "\t" << grade << endl;
        }



    }

    theEnrollFile.close();
    theEnrolltemp.close();
    remove("enrollment.txt");
    rename("tempe.txt", "enrollment.txt");

}

//To update a student's grade for a given course,
// the admin should enter the student ID, course ID,
// and the new grade. The program should update the enrollment file 
//with the new grade for the student in the specified course.
void UpdateGrade(student& s1, Enrollment& e1) {

    cout << "enter the student ID that need to update his grade: " << endl;
    cin >> s1.ID;
    cout << "enter the courseID that need to update his grade: " << endl;
    cin >> e1.courseId;

    fstream theEnrollFile("enrollment.txt", ios::in);
    fstream theEnrolltemp("tempEnroll.txt", ios::out | ios::app);

    int id2;
    string courseID;
    int grade;

    while (theEnrollFile.good()) {

        theEnrollFile >> id2;
        theEnrollFile.ignore(INT_MAX, '\t');
        getline(theEnrollFile, courseID, '\t');
        theEnrollFile >> grade;
        theEnrollFile.ignore(INT_MAX, '\n');

        if (theEnrollFile.eof()) {
            break;

        }

        // if(s1.ID!=id2){
        // cout<<"there is no student with this id"<<endl;
        // break;
        //  }
        //  if(e1.courseId!=courseID){
        //     cout<<"there is no course with ID the student is enrolled in"<<endl;

        //  }


        if (s1.ID != id2 || e1.courseId != courseID) {

            theEnrolltemp << id2 << "\t" << courseID << "\t" << grade << endl;


        }
        if (s1.ID == id2 && e1.courseId == courseID) {
            cout << "enter the new grade for the student: " << endl;
            cin >> e1.grade;
            theEnrolltemp << id2 << "\t" << courseID << "\t" << e1.grade << endl;

        }



    }
    theEnrollFile.close();
    theEnrolltemp.close();
    remove("enrollment.txt");
    rename("tempEnroll.txt", "enrollment.txt");

}


//To calculate the average grade for a course, 
//the admin should enter the course ID. 
//The program should read the enrollment file and calculate the average grade for all students enrolled 
//in the specified course.

double CalcAvgCourse(Enrollment& e1) {

    cout << "enter the courseID you want to calculate its average:" << endl;
    cin >> e1.courseId;

    int sumOfGrade = 0;
    int NumberOfStudent = 0;
    fstream EnrollFile("enrollment.txt", ios::in);

    int id2;
    string courseID;
    int grade;

    while (EnrollFile.good()) {

        EnrollFile >> id2;

        EnrollFile.ignore(INT_MAX, '\t');
        getline(EnrollFile, courseID, '\t');
        EnrollFile >> grade;
        EnrollFile.ignore(INT_MAX, '\n');

        if (EnrollFile.eof()) {
            break;

        }


        if (e1.courseId == courseID) {

            sumOfGrade = sumOfGrade + grade;
            NumberOfStudent++;
        }

    }

    // Calculate and return average grade
    if (NumberOfStudent > 0) {
        return static_cast<double>(sumOfGrade) / NumberOfStudent;
    }
    else {
        cout << "No records found for course " << courseID << "." << endl;
        return 0;
    }



}

void SortStudentDecGpa() {

    fstream StudentFile("student.txt", ios::in);

    int id1;
    double gpa1;
    string fname1, lname1, pass1, birth1, address1, phone1;

    // Count the number of students in the file

    int count = 0;
    while (StudentFile.good()) {
        StudentFile >> id1;
        StudentFile.ignore(INT_MAX, '\t');
        getline(StudentFile, fname1, '\t');
        getline(StudentFile, lname1, '\t');
        getline(StudentFile, pass1, '\t');
        getline(StudentFile, birth1, '\t');
        getline(StudentFile, address1, '\t');
        getline(StudentFile, phone1, '\t');
        StudentFile >> gpa1;
        StudentFile.ignore(INT_MAX, '\n');

        if (StudentFile.eof()) {
            break;
        }

        count++;

    }

    StudentFile.close();
    // StudentFile.clear();
    // StudentFile.seekg(0);
    // Create a dynamic array of students
    student* arr = new student[count];

    int id2;
    double gpa2;
    string fname2, lname2, pass2, birth2, address2, phone2;

    //store the data in the array:
    StudentFile.open("student.txt");
    int i = 0;
    while (StudentFile.good()) {
        StudentFile >> id2;
        StudentFile.ignore(INT_MAX, '\t');
        getline(StudentFile, fname2, '\t');
        getline(StudentFile, lname2, '\t');
        getline(StudentFile, pass2, '\t');
        getline(StudentFile, birth2, '\t');
        getline(StudentFile, address2, '\t');
        getline(StudentFile, phone2, '\t');
        StudentFile >> gpa2;
        StudentFile.ignore(INT_MAX, '\n');

        if (StudentFile.eof()) {
            break;
        }



        arr[i].firstname = fname2;
        arr[i].lastname = lname2;
        arr[i].password = pass2;
        arr[i].DateOfBirth = birth2;
        arr[i].address = address2;
        arr[i].tel = phone2;
        arr[i].gpa = gpa2;
        i++;
    }
    StudentFile.close();
    //sort the array:

    for (int m = 0; m < count; m++) {

        for (int h = m + 1; h < count; h++) {
            if (arr[h].gpa > arr[m].gpa) {

                student temp = arr[m];
                arr[m] = arr[h];
                arr[h] = temp;

            }
        }

    }

    // Write the sorted array to a temp file

    fstream outfileStudent("studentTempx.txt", ios::out | ios::app);


    for (int l = 0; l < count; l++) {

        outfileStudent << arr[l].firstname << "\t" << arr[l].lastname << "\t" << arr[l].password << "\t" << arr[l].DateOfBirth << "\t" << arr[l].address << "\t" << arr[l].tel << "\t" << arr[l].gpa << endl;
    }
    outfileStudent.close();
    remove("student.txt");
    rename("studentTempx.txt", "student.txt");

    delete[] arr;


}

//student functions:

void ViewListOfGrades(student& s1, string language) {

    fstream theEnrollFile("enrollment.txt", ios::in);
    cout << ((language == "en") ? "Enter your ID: " : (language == "fr") ? "Entrez votre identifiant: " : "");
    cin >> s1.ID;

    int id2;
    string courseID;
    int grade;

    while (theEnrollFile.good()) {

        theEnrollFile >> id2;
        theEnrollFile.ignore(INT_MAX, '\t');
        getline(theEnrollFile, courseID, '\t');
        theEnrollFile >> grade;
        theEnrollFile.ignore(INT_MAX, '\n');

        if (theEnrollFile.eof()) {
            break;

        }

        if (s1.ID == id2) {

            cout << courseID << "\t" << grade << endl;

        }
    }
    theEnrollFile.close();

}


void SearchGradeForCourse(student& s1, Enrollment& e1, string language) {

    fstream EnrollF("enrollment.txt", ios::in);
    cout << ((language == "en") ? "Enter your ID: " : (language == "fr") ? "Entrez votre identifiant: " : "");
    cin >> s1.ID;
    // cout<<"enter the courseID to give you the grade: "<<endl;
    cout << ((language == "en") ? "Enter the courseID: " : (language == "fr") ? "Saisissez l'identifiant du cours : : " : "");

    cin >> e1.courseId;

    int id2;
    string courseID;
    int grade;

    while (EnrollF.good()) {

        EnrollF >> id2;
        EnrollF.ignore(INT_MAX, '\t');
        getline(EnrollF, courseID, '\t');
        EnrollF >> grade;
        EnrollF.ignore(INT_MAX, '\n');

        if (EnrollF.eof()) {
            break;

        }

        if (s1.ID == id2 && e1.courseId == courseID) {

            cout << grade << endl;

        }
    }
    EnrollF.close();
}


double CalcGPA(student& s1, string language) {

    fstream EnrollF("enrollment.txt", ios::in);
    fstream courseF("courses.txt", ios::in);

    cout << ((language == "en") ? "Enter your ID: " : (language == "fr") ? "Entrez votre identifiant: " : "");
    cin >> s1.ID;

    int id2;
    string courseID;
    int grade;


    string courseI, courseName;
    int credit;

    int sumOfGrade = 0;


    int i = 0;
    course* data = new course[i];


    while (EnrollF.good()) {

        EnrollF >> id2;
        EnrollF.ignore(INT_MAX, '\t');
        getline(EnrollF, courseID, '\t');
        EnrollF >> grade;
        EnrollF.ignore(INT_MAX, '\n');

        if (EnrollF.eof()) {
            break;

        }

        if (s1.ID == id2) {
            sumOfGrade = sumOfGrade + grade;

            data[i].courseID = courseID;
            i++;

        }

    }

    int sumOfCredits = 0;

    while (courseF.good()) {

        getline(courseF, courseI, '\t');
        getline(courseF, courseName, '\t');
        courseF >> credit;
        courseF.ignore(INT_MAX, '\n');

        if (courseF.eof()) {
            break;
        }

        for (int j = 0; j < i; j++) {
            if (data[j].courseID == courseI) {
                sumOfCredits = sumOfCredits + credit;
            }
        }


    }

    EnrollF.close();
    courseF.close();


    double gpa = (sumOfGrade / sumOfCredits) / 5.0;
    delete[] data;
    return gpa;
}



void AddProblem(student& s1, string language) {

    fstream problemF("problem.txt", ios::out | ios::app);
    cout << ((language == "en") ? "Enter your ID: " : (language == "fr") ? "Entrez votre identifiant: " : "");
    cin >> s1.ID;
    cin.ignore();
    cout << ((language == "en") ? "Enter your problem: " : (language == "fr") ? "Saisissez votre problème : " : "");
    getline(cin, s1.problem);
    problemF << s1.ID << "\t" << s1.problem << endl;
    cout << ((language == "en") ? "Enter your problem: " : (language == "fr") ? "votre problème est bien reçu " : "");
    problemF.close();


}


void ShowOrderInClass(student& s1, string language) {

    //sort the student file in decreasing order
    SortStudentDecGpa();

    fstream theStudentFile("student.txt", ios::in);

    cout << ((language == "en") ? "Enter your ID: " : (language == "fr") ? "Entrez votre identifiant: " : "");

    cin >> s1.ID;

    int id1;
    double gpa1;
    string fname1, lname1, pass1, birth1, address1, phone1;

    int counter = 0;
    while (theStudentFile.good()) {
        theStudentFile >> id1;
        theStudentFile.ignore(INT_MAX, '\t');
        getline(theStudentFile, fname1, '\t');
        getline(theStudentFile, lname1, '\t');
        getline(theStudentFile, pass1, '\t');
        getline(theStudentFile, birth1, '\t');
        getline(theStudentFile, address1, '\t');
        getline(theStudentFile, phone1, '\t');
        theStudentFile >> gpa1;
        theStudentFile.ignore(INT_MAX, '\n');

        if (theStudentFile.eof()) {
            break;
        }

        if (s1.ID != id1) {
            counter++;
        }

        if (s1.ID == id1) {
            break;
        }

    }

    cout << ((language == "en") ? "your order in the class based on the gpa is: " : (language == "fr") ? "votre commande dans la classe basée sur le gpa est : " : "");

    cout << counter;

}


void ShowClassesSortedByGrade(student& s1, string language) {

    fstream EnrollF("enrollment.txt", ios::in);

    cout << ((language == "en") ? "Enter your ID: " : (language == "fr") ? "Entrez votre identifiant: " : "");
    cin >> s1.ID;

    int id2;
    string courseID;
    int grade;

    int countcourses = 0;
    while (EnrollF.good()) {

        EnrollF >> id2;
        EnrollF.ignore(INT_MAX, '\t');
        getline(EnrollF, courseID, '\t');
        EnrollF >> grade;
        EnrollF.ignore(INT_MAX, '\n');

        if (EnrollF.eof()) {
            break;

        }

        if (s1.ID == id2) {

            //count number of courses that taken by the student:
            countcourses++;

        }

    }
    EnrollF.close();

    //create dynamic array of enrollment
    Enrollment* arr = new Enrollment[countcourses];


    EnrollF.open("enrollment.txt");

    int id;
    string cID;
    int g;

    int i = 0;
    while (EnrollF.good()) {

        EnrollF >> id;
        EnrollF.ignore(INT_MAX, '\t');
        getline(EnrollF, cID, '\t');
        EnrollF >> g;
        EnrollF.ignore(INT_MAX, '\n');

        if (EnrollF.eof()) {
            break;

        }

        if (s1.ID == id) {

            //fill the array 
            arr[i].courseId = cID;
            arr[i].grade = g;
            i++;

        }

    }

    EnrollF.close();


    //sort the array in dec:
    for (int m = 0; m < countcourses; m++) {

        for (int h = m + 1; h < countcourses; h++) {
            if (arr[h].grade > arr[m].grade) {

                Enrollment temp = arr[m];
                arr[m] = arr[h];
                arr[h] = temp;
            }
        }
    }

    cout << "your courses sorted by decreasing order of the grades are: " << endl;

    for (int l = 0; l < countcourses; l++) {
        cout << arr[l].courseId << "\t" << arr[l].grade << endl;

    }

}

int main() {

    cout << "Do you want to proceed as admin or student: a:admin    s:student  ";
    char sign;
    cin >> sign;

    while ((sign != 'a') && (sign != 's')) {
        cout << "enter AGAIN: Do you want to proceed as admin or student: a:admin    s:student " << endl;
        cin >> sign;
    }
    student s1{};
    Enrollment e1{};

    if (sign == 'a') {

        // checkAdmin(s1);

        char serviceType;

        cout << "1)Create a profile for a new student. 2)Update the grade of any course for a given student.3) Delete a student when leaving the university.4)Calculate the average of a course for all the students. 5)Show the list of students sorted by decreasing order of their gpa." << endl;

        cin >> serviceType;
        while ((serviceType != 'c') && (serviceType != 'u') && (serviceType != 'd') && (serviceType != 'v') && (serviceType != 's')) {
            cout << "enter again...1)Create a profile for a new student. 2)Update the grade of any course for a given student.3) Delete a student when leaving the university.4)Calculate the average of a course for all the students. 5)Show the list of students sorted by decreasing order of their gpa." << endl;

            cin >> serviceType;
        }

        if (serviceType == 'c') {
            //create a profile for a new student:
            createProfile(s1);
        }

        if (serviceType == 'd') {
            DeleteStudent(s1);
        }

        if (serviceType == 'u') {
            UpdateGrade(s1, e1);
        }

        if (serviceType == 'v') {
            cout << "the average of the course is: " << endl;
            cout << CalcAvgCourse(e1);
        }

        if (serviceType == 's') {
            SortStudentDecGpa();
        }

    }


    //student section:

    if (sign == 's') {

        cout << "choose language: (fr) or (en)" << endl;
        string l;
        cin >> l;

        cout << ((l == "en") ? "1)View the list of its grades :v. 2)Search the grade for a given course:s  3) Calculate its gpa:c  4)add a proposition or problem  5)show its order in the class in terms of its gpa:p  6) show the classes sorting by decreasing order of grade:g" : (l == "fr") ? "1) Voir la liste de ses notes. 2) Rechercher la note d'un cours donné. 3) Calculez son gpa.  4)ajouter une proposition ou un problème  5)montrer son ordre dans la classe en fonction de son gpa." : "") << endl;
        char serviceTypeOfstudent;
        cin >> serviceTypeOfstudent;

        while (serviceTypeOfstudent != 'v' && serviceTypeOfstudent != 's' && serviceTypeOfstudent != 'c' && serviceTypeOfstudent != 'p' && serviceTypeOfstudent != 'o' && serviceTypeOfstudent != 'g') {
            cout << ((l == "en") ? "Enter again: " : (l == "fr") ? "Entrez encore: " : "") << endl;
            cin >> serviceTypeOfstudent;

        }

        if (serviceTypeOfstudent == 'v') {

            ViewListOfGrades(s1, l);

        }
        if (serviceTypeOfstudent == 's') {
            SearchGradeForCourse(s1, e1, l);
        }

        if (serviceTypeOfstudent == 'c') {
            cout << ((l == "en") ? "Your GPA is: " : (l == "fr") ? "Votre GPA est: " : "") << endl;

            cout << "your gpa is : " << endl;
            cout << CalcGPA(s1, l);
        }

        if (serviceTypeOfstudent == 'p') {
            AddProblem(s1, l);
        }

        if (serviceTypeOfstudent == 'o') {
            ShowOrderInClass(s1, l);
        }

        if (serviceTypeOfstudent == 'g') {
            ShowClassesSortedByGrade(s1, l);
        }

    }
}