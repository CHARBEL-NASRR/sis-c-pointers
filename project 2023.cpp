using namespace std;
#include <iostream>
#include<cmath>
#include <iomanip>
#include<cstring>
#include <regex> 
#include<cstdlib>
#include<ctime>
#include<fstream>
#include <sstream>	
#include "md5.h"
#include <algorithm>
#include <cctype>


struct student {
	int id;
	string firstname;
	string lastname;
	string password;
	string dateofbirth;
	string emailaddress;
	string phone;
	double gpa;
};

struct course {
	string couresid;
	string coursename;
	int credits;
};

struct enrollment {
    int  studentid;
	string courseID;
	int grade;
};


void copyf(fstream& fout, student user) {
	fout.open("student.txt", ios::out | ios::app);
	fout << user.id << "\t"
		<< user.firstname << "\t"
		<< user.lastname << "\t"
		<< user.password << "\t"
		<< user.dateofbirth << "\t"
		<< user.emailaddress << "\t"
		<< user.phone << "\t"
		<< user.gpa << "\t"
		<< "\n";
	fout.close();
}


void readStudent(ifstream& file, student student) {
	file >> student.id >> student.firstname >> student.lastname >> student.password
		>> student.dateofbirth >> student.emailaddress >> student.phone >> student.gpa;
}

void writeEnrollment(ofstream& file, const enrollment& enrollment) {
	file << enrollment.studentid << "\t" << enrollment.courseID << "\t" << enrollment.grade << endl;
}


bool is_valid(string email) {
	string email2;
	bool atFlag = false;
	bool comFlag = false;

	int size = email.length();
	for (int c = 0; c < email.length(); c++) {
		if (email[c] == '@') {
			atFlag = true;


			email2 = email.substr(size - (c + 2), size - 2);
			for (int i = 0; i < email2.length(); i++)
			{
				if (email2[i] == '.') {
					comFlag = true;
				}
			}



		}

	}
	if (atFlag && comFlag) {

		return true;

	}
	return false;
}
bool is_valid2(string email) {
	bool t = false;
	ifstream studentt("student.txt");
	student junk;
	while (studentt)
	{
		studentt >> junk.id >> junk.firstname >> junk.lastname >> junk.password >> junk.dateofbirth >> junk.emailaddress >> junk.phone >> junk.gpa;
		if (email == junk.emailaddress) {

			return false;
		}
	}
	return true;
}
void strongPass(string& str) {
	int lowcase = 0, upcase = 0, d = 0, s = 0;

	cout << "plz enter your password ";
	getline(cin, str);
	while (str.length() < 8)
	{
		cout << " your pass is short please inter a 8 digits at least ";
		getline(cin, str);
	}
	while (lowcase == 0 || upcase == 0 || d == 0 || s == 0) {

		for (int i = 0; i < str.length(); i++)
		{
			if (islower(str[i]))
				lowcase++;
			if (isupper(str[i]))
				upcase++;
			if (isdigit(str[i]))
				d++;
			if (!isalpha(str[i]) && !isdigit(str[i]))
				s++;
		}
		if (lowcase + upcase + d + s < 8 || (lowcase == 0 || upcase == 0 || d == 0 || s == 0))
		{
			cout << "week password pls enter a password ontaining numbers, letters, and special characters and at least 8 char" << endl;
			getline(cin, str);
		}
		if (lowcase && upcase && d && s && str.length() >= 8)
		{
			break;
		}
	}
}
bool checkPhone(string& pass) {
	if (pass.length() != 8) {
		cout << "the number most be  8 nubers plz enter the number correctly";

		return 0;
	}
	if ((pass[0] == '0' && pass[1] == '3') || (pass[0] == '7 ' && pass[1] == '1') || (pass[0] == '7' && pass[1] == '0') || (pass[0] == '7' && pass[1] == '6') || (pass[0] == '8' && pass[1] == '1') || (pass[0] == '7' && pass[1] == '8') || (pass[0] == '7 ' && pass[1] == '9')) {

		return 1;

	}
	else {
		cout << "plz the nuer most be star with (03,70,71,76,81)";


		return 0;
	}


}


void hash(student& password) {
	password.password = md5(password.password);
}


void IDgen(student& str1) {
	student junk;
	str1.id = 1;
	junk.id = 0;
	ifstream studentt("student.txt");
	while (studentt)
	{

		studentt >> junk.id >> junk.firstname >> junk.lastname >> junk.password >> junk.dateofbirth >> junk.emailaddress >> junk.phone >> junk.gpa;
	}
	str1.id = junk.id + 1;

	studentt.close();
}


void signIn(student& user) {
	IDgen(user);

	bool t = false;
	ifstream studentt("student.txt");
	student junk;
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	cout << "pls enter your first name " << endl;
	getline(cin, user.firstname);
	cout << "pls enter your last name" << endl;
	getline(cin, user.lastname);


	strongPass(user.password);

	user.password = md5(user.password);

	cout << "enter the date of birth" << endl;
	cin >> user.dateofbirth;


	while ((is_valid(user.emailaddress) == 0) || (is_valid2(user.emailaddress) == 0)) {
		while ((is_valid(user.emailaddress) == 0))
		{
			cout << "your email is incorect plz enternt correctly" << endl;
			getline(cin, user.emailaddress);
		}
		while ((is_valid2(user.emailaddress) == 0)) {
			cout << "your email is already exist enter onother onr plz ";
			getline(cin, user.emailaddress);
		}
	}

	cout << "plz enter your number ";
	getline(cin, user.phone);
	while (checkPhone(user.phone) == 0) {
		getline(cin, user.phone);
	}
	user.gpa = 0;

	fstream fout;
	copyf(fout, user);


}



void add_courses() {
	
	ofstream courses_file("Courses.txt", ios::out | ios::app);

	
	int num_courses;
	cout << "Enter the number of courses: ";
	cin >> num_courses;

	
	for (int i = 0; i < num_courses; i++) {
		string course_id, course_name;
		int credits;

		
		cout << "Enter the course ID: ";
		cin >> course_id;
		cout << "Enter the course name: ";
		cin >> course_name;
		cout << "Enter the number of credits: ";
		cin >> credits;

		
		courses_file << course_id << "\t" << course_name << "\t" << credits << endl;
	}

	
	courses_file.close();

	cout << "Courses added successfully!" << endl;
}





void UpdateGrade(student& s1, enrollment& e1) {

	cout << "enter the student ID that need to update his grade: " << endl;
	cin >> s1.id;
	cout << "enter the courseID that need to update his grade: " << endl;
	cin >> e1.courseID;

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
		if (s1.id != id2 || e1.courseID != courseID) {

			theEnrolltemp << id2 << "\t" << courseID << "\t" << grade << endl;


		}
		if (s1.id == id2 && e1.courseID == courseID) {
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










void DeleteStudent(student& s1) {

	fstream StudentFile("student.txt", ios::in);
	fstream Studenttemp("temp.txt", ios::out | ios::app);
	fstream EnrollFile("enrollment.txt", ios::in);
	fstream Enrolltemp("tempe.txt", ios::out | ios::app);


	cout << "enter the ID of the student that leaves the university: " << endl;
	cin >> s1.id;

	int id;
	double gpa;
	string firstname, lastname, pass, dob, email, phonenum;

	while (StudentFile.good()) {
		StudentFile >> id;
		StudentFile.ignore(INT_MAX, '\t');
		getline(StudentFile, firstname, '\t');
		getline(StudentFile, lastname, '\t');
		getline(StudentFile, pass, '\t');
		getline(StudentFile, dob, '\t');
		getline(StudentFile, email, '\t');
		getline(StudentFile, phonenum, '\t');
		StudentFile >> gpa;
		StudentFile.ignore(INT_MAX, '\n');
		cout << gpa;
		if (StudentFile.eof()) {
			break;
		}

		if (s1.id != id) {
			Studenttemp << id << "\t" << firstname << "\t" << lastname << "\t" << pass << "\t" << dob << "\t" << email << "\t" << phonenum << "\t" << gpa << endl;

		}

		
	}
	StudentFile.close();
	Studenttemp.close();
	remove("student.txt");
	rename("temp.txt", "student.txt");

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

		if (s1.id != id2) {

			Enrolltemp << id2 << "\t" << courseID << "\t" << grade << endl;
		}
		if (s1.id != id2) {

			Enrolltemp << id2 << "\t" << courseID << "\t" << grade << endl;
		}

	
	}

	EnrollFile.close();
	Enrolltemp.close();
	remove("enrollment.txt");
	rename("tempe.txt", "enrollment.txt");

}









double calculateCourseAverageGrade(enrollment* enrollments, int numEnrollments) {
	ifstream file("enrollment.txt");
	if (!file) {
	 cerr << "Failed to open enrollment file." <<endl;
		return 0.0;
	}
	enrollment junkk;
	std::string courseID;
	int sum = 0;
	int count = 0;
	cout << "Enter the course ID: ";
	cin >> courseID;
	
	while (file)
	{
		file >> junkk.studentid >> junkk.courseID >> junkk.grade;
		if (junkk.courseID == courseID) {
			sum = +junkk.grade;
			count++;
		}
	}
	
	

	file.close();

	if (count == 0) {
		return 0.0;
	}
	else {
		return sum / count;
	}
}







void sort(student s[],int count) {



	
	fstream StudentFile("student.txt", ios::in);

	int id1;
	double gpa1;
	string fname1, lname1, pass1, birth1, address1, phone1;


	int counttt = 0;
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

		counttt++;

	}
	
	StudentFile.close();
	int id2;
	double gpa2;
	string fname2, lname2, pass2, birth2, address2, phone2;

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


		s[i].firstname = fname2;
		s[i].lastname = lname2;
		s[i].password = pass2;
		s[i].dateofbirth = birth2;
		s[i].emailaddress = address2;
		s[i].phone = phone2;
		s[i].gpa = gpa2;
		i++;
	}
	StudentFile.close();
	for (int j = 0; j < counttt ; j++) {
		for (int k = j + 1; k < counttt; k++) {
			if (s[j].gpa > s[k].gpa) {
				double tmp = s[j].gpa;
				s[j].gpa = s[k].gpa;
				s[k].gpa = tmp;
			}
		}
	}
	for (int j = 0; j < counttt ; j++) {
		cout << s[j].firstname << s[j].lastname << ": " << s[j].gpa << endl;
	}

}


void viewgrades(int studentID) {
	ifstream enrollmentFile("enrollment.txt");
	if (!enrollmentFile.is_open()) {
		cout << "Error: Unable to open enrollment file." << endl;
		return;
	}

	bool found = false;
	enrollment e;
	while (enrollmentFile >> e.studentid >> e.courseID >> e.grade) {
		if (e.studentid == studentID) {
			found = true;
			cout << "Course ID: " << e.courseID << ", Grade: " << e.grade << endl;
		}
	}

	if (!found) {
		cout << "No grades found for student ID " << studentID << endl;
	}

	enrollmentFile.close();
}

int searchgrade(enrollment enrollments) {
	
	fstream file("enrollment.txt", ios::in);
	int idds;
	string courseId;
	int grade;
	cout << "enter your id" << endl;
	cin >> idds;
	cout << "enter the cours id" << endl;
	cin >> courseId;

	while (file.good()) {

		file >> enrollments.studentid>>enrollments.courseID>>enrollments.grade;
		
		
	
		

			if (enrollments.studentid == idds && enrollments.courseID == courseId)
				return enrollments.grade;

			return -1;
	
	}


	file.close();
}



void calculateGPA(course e[], enrollment y[], int id, student students[]) {
	
	double gpa = 0;
	int creditt = 0;

	enrollment t;

	fstream file("enrollment.txt", ios::in);
	string coursess;
	int cnt = 0;
	while (file) {
		file >> y[cnt].studentid;
		file >> y[cnt].courseID;
		file >> y[cnt].grade;


		cnt++;
	}
	for (int i = 0; i < cnt - 1; i++) {
		if (id == y[i].studentid)
			gpa += y[i].grade;

	}
	file.close();
	fstream file1("courses.txt", ios::in);
	int i = 0;
	while (file1) {
		file1 >> e[i].couresid;
		file1 >> e[i].coursename;
		file1 >> e[i].credits;
		i++;
	}
	for (int j = 0; j < i - 1; j++) {
		for (int k = 0; k < cnt - 1; k++) {
			if (e[j].couresid == y[k].courseID && y[k].studentid == id) {
				
				creditt += e[j].credits;
			}

		}
	}
	gpa = gpa / creditt;
	cout << gpa;

	
  
}
	







int countStudents() {
	int count = 0;
	string line;
	ifstream file("student.txt");

	if (file.is_open()) {
		while (getline(file, line)) {
			count++;
		}
		file.close();
	}
	else {
		cout << "Error: Unable to open file" << endl;
	}

	return count;
} 

int countEnrollments() {
	ifstream enrollmentIn("enrollment.txt");
	int count = 0;
	string line;
	while (getline(enrollmentIn, line)) {
		count++;
	}
	enrollmentIn.close();
	return count;
}

int countcourse() {
	ifstream coursein("courses.txt");
		int count = 0;
		string line;
		while (getline(coursein, line)) {
			count++;
		}
		coursein.close();
		return count;
}

void showStudentOrder(student students[], int numStudents) {
	// Sort the students array based on their GPA in descending order
	for (int i = 0; i < numStudents - 1; i++) {
		for (int j = 0; j < numStudents - i - 1; j++) {
			if (students[j].gpa < students[j + 1].gpa) {
				// Swap the positions of students if their GPA is in the wrong order
				swap(students[j], students[j + 1]);
			}
		}
	}

	// Print the order of the students based on their GPA
	cout << "Order of students in terms of GPA:" << endl;
	for (int i = 0; i < numStudents; i++) {
		cout << students[i].firstname << " " << students[i].lastname << ": GPA - " << students[i].gpa << endl;
	}
}


void show_courses_sorted_by_grades(int student_id,enrollment enrollments[]) {
	ifstream infile("enrollment.txt");
	if (!infile) {
		cerr << "Error: could not open the enrollment.txt file." << endl;
		return;
	}

	string line;
	int count = 0;
	while (getline(infile, line)) {
		// Parse the line into enrollment data
		istringstream iss(line);
		int sid, grade;
		string cid;
		iss >> sid >> cid >> grade;

		// If the enrollment is for the given student, add it to the array
		if (sid == student_id) {
			enrollments[count].studentid = sid;
			enrollments[count].courseID = cid;
			enrollments[count].grade = grade;
			count++;
		}
	}

	// Sort the enrollments array based on grades (in descending order)
	for (int i = 0; i < count - 1; i++) {
		for (int j = i + 1; j < count; j++) {
			if (enrollments[i].grade < enrollments[j].grade) {
				enrollment temp = enrollments[i];
				enrollments[i] = enrollments[j];
				enrollments[j] = temp;
			}
		}
	}

	// Print the sorted courses
	for (int i = 0; i < count; i++) {
		cout << enrollments[i].courseID << ": " << enrollments[i].grade << endl;
	}

	// Close the file
	infile.close();
}


void add_proposition() {
	string filename;
	string proposition;

	cout << "Enter the filename to save the proposition: ";
	cin >> filename;

	ofstream outfile(filename, ios::app); // open the file in append mode

	if (!outfile) {
		cout << "Error: Unable to open file." << endl;
		return;
	}

	cout << "Enter the proposition or problem: ";
	cin.ignore();
	getline(cin, proposition);

	outfile << proposition << endl; // write the proposition to the file
	outfile.close();

	cout << "Proposition saved successfully!" << endl;
}










int main() {
	bool flag = true;
	string role;
	int a, b;
	student s;
	enrollment y;
	int r, cnt;
	string email, pass;
	course t;
	int coursett = countcourse();
	course* courses = new course[coursett];
	cnt = countEnrollments();
	enrollment* p = new enrollment[cnt];
	int numofstudent = countStudents();
	student* o = new student[numofstudent];
	string emailaddress, password;
	
	
	
	while (true) {
		cout << "Enter your role (admin or student): ";
		cin >> role;
		if (role == "admin" || role == "student") {
			break;
		}
	}
	cout << "plz enter your email" << endl;
	cin.ignore();
	getline(cin, emailaddress);
	while ((is_valid(emailaddress) == 0) || (is_valid2(emailaddress) == 0)) {
		while ((is_valid(emailaddress) == 0))
		{
			cout << "your email is incorect plz enternt correctly" << endl;
			getline(cin, emailaddress);
		}
		while ((is_valid2(emailaddress) == 0)) {
			cout << "your email is already exist enter onother onr plz ";
			getline(cin,emailaddress);
		}
	}
	strongPass(password);
	
	if (role == "admin") {
		cout << "you are admin" << endl;

		cout << "enter 0 if you want to add any course and enter -1 if no" << endl;
		cin >> r;
		if (r == 0) {
			add_courses();
		}


		else cout << "next" << endl;
		cnt = countEnrollments();
		enrollment* p = new enrollment[cnt];
		int numofstudent = countStudents();
		student* o = new student[numofstudent];while (flag) {
		cout << "1. Create a profile for a new student" << endl;
		cout << "2. Update the grade of any course for a given student" << endl;
		cout << "3. Delete a student when leaving the university" << endl;
		cout << "4. Calculate the average of a course for all the students" << endl;
		cout << "5. Show the list of students sorted by decreasing order of their GPA" << endl;
		cin >> a;
		
			if (a == 1)
				signIn(s);
			if (a == 2) {

				UpdateGrade(s, y);
			}
			if (a == 3) {

				DeleteStudent(s);
			}
			if (a == 4) {
				cout << calculateCourseAverageGrade(p, cnt);
			}if (a == 5) {
				sort(o, cnt);
			} int a;
			cout << "if you want to stil admin press 1" << endl;
			cin >> a;
			if (a != 1)
				flag = false;

		}

	}

	
	if (role == "student") {
		int studentid;
		int s, w;
		while (flag) {
			cout << "enter your id" << endl;
			cin >> studentid;

			cout << "1. view the list of grads" << endl;
			cout << "2. search the grade of a given coures" << endl;
			cout << "3. calculate the gpa" << endl;
			cin >> s;
			if (s == 1)
				viewgrades(studentid);

			if (s == 2) {
				int grade = searchgrade(y);
				cout << grade;
			}
			if (s == 3) {

				calculateGPA(courses, p, studentid, o);
			}
			int t;
			cout << "enter 1 to show your order in class" << endl;
			cout << "enter 2 to show your courses in term of greads" << endl;
			cout << " enter 3 to add a proposition" << endl;
			cin >> t;
			if (t == 1)
				showStudentOrder(o, numofstudent);

			if (t == 2)
				show_courses_sorted_by_grades(studentid, p);

			if (t == 3)
				add_proposition();

			cout << "enter 1 if you want to stil a student" << endl;
			cin >> w;
			if (w != 1)
				flag = false;
		}
	}
	}





























