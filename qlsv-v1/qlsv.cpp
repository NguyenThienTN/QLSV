#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>

typedef struct Student {
	std::string fullName;
	std::string homeTown;
	std::string birthDay;
	float score;
	float GPA;
	int ID;
} Student;

/*
---------------------------------------
-------------------------------------
*/

Student students[100];

// Functions

// Print line
void printDash(int n) {
	for(int i = 0; i < n; i++) {
		std::cout << "-";
	}
	std::cout << std::endl;
}

void printDashO(int n, std::ofstream& outstream) {
	for(int i = 0; i < n; i++) {
		outstream << "-";
	}
	outstream << std::endl;
}

// Menu
void menu() {
	printDash(70);
	std::cout << "|" << std::setw(43) << std::right << "Student Management" << std::setw(26) << std::right << "|" << std::endl;
	std::cout << "|" << std::setw(69) << std::right << "|" << std::endl;
	std::cout << "|  " << "1. Add students" << std::setw(52) << std::right << "|" << std::endl;
	std::cout << "|  " << "2. Search for students by ID" << std::setw(39) << std::right << "|" << std::endl;
	std::cout << "|  " << "3. Display a list of students" << std::setw(38) << std::right << "|" << std::endl;
	std::cout << "|  " << "4. Sort students by GPA" << std::setw(44) << std::right << "|" << std::endl;
	std::cout << "|  " << "5. Sort students by name" << std::setw(43) << std::right << "|" << std::endl;
	std::cout << "|  " << "6. Update student information" << std::setw(38) << std::right << "|" << std::endl;
	std::cout << "|  " << "7. Remove student" << std::setw(50) << std::right << "|" << std::endl;
	std::cout << "|  " << "8. Output list of students" << std::setw(41) << std::right << "|" << std::endl;
	std::cout << "|  " << "0. Exit" << std::setw(60) << std::right << "|" << std::endl;
	std::cout << "|" << std::setw(69) << std::right << "|" << std::endl;
	printDash(70);
}

// 1. Add students
void inputStudent(Student& s, const Student arr[], int n) {
	std::cout << "Enter name: ";
	std::cin.ignore();
	std::getline(std::cin, s.fullName);
	std::cout << "Enter hometown: ";
	// std::cin.ignore();
	std::getline(std::cin, s.homeTown);
	std::cout << "Enter birthday: ";
	// std::cin.ignore();
	std::getline(std::cin, s.birthDay);
	static int currentID = 100000; // Assume ID starts from 100000
	if (currentID > 999999) {
			std::cout << "Error: Maximum number of students reached." << std::endl;
			return; // Exit the function if the maximum number of students is reached
	}
	s.ID = ++currentID;
	std::cout << "Enter score: ";
	std::cin >> s.score;
	s.GPA = s.score * 40 / 100;
}
void addStudent(Student arr[], int& n) {
	std::cout << "How many students do you want to add? ";
	int k; // The number of students you want to add
	std::cin >> k;
	for (int i = n; i < n + k; i++) {
		std::cout << "Student " << i + 1 << ":" << "\n";
		inputStudent(arr[i], arr, n); // Enter student information with ID checking
		std::cout << "\n";
	}
	n += k; // Update the number of students
}

// 2. Search for students by ID
int searchByID(const Student arr[], int n, int ID) {
  for (int i = 0; i < n; i++) {
    if (arr[i].ID == ID) {
      return i;
    }
  }
  return -1;
}
void displayStudentByID(Student arr[], int n) {\
	std::cout << "Enter the ID of the student: ";
  int ID;
  std::cin >> ID;
	int index = searchByID(arr, n, ID);
	if(index == -1) {
		std::cout << "No student found with ID: " << ID << std::endl;
		return;
	}
	std::cout << "The current information of the student:\n";
  std::cout << "Name: " << arr[index].fullName << std::endl;
  std::cout << "Hometown: " << arr[index].homeTown << std::endl;
  std::cout << "Birthday: " << arr[index].birthDay << std::endl;
  std::cout << "Score: " << arr[index].score << std::endl;
  std::cout << "GPA: " << arr[index].GPA << std::endl;
}

// 3. Display a list of students
void listOfStudents(const Student* s, int n) {
  int maxIDWidth = 11; // Set max width
  int maxNameWidth = 25; // Set max name
  int maxGPA = 12;
  int maxHometown = 16; // Set max hometown
  int maxBirthday = 16; // Set max birthday
  printDash(92);
	std::cout << "|" 
            << std::setw(53) << std::right << "List of students" 
            << std::setw(38) << std::right << "|" << std::endl;
  std::cout << "|" << std::setw(91) << std::right << "|" << std::endl;
	
  std::cout << "|" << std::left << std::setw(10) << "STT" 
            << std::left << std::setw(maxIDWidth) << "ID" 
            << std::left << std::setw(maxNameWidth) << "Full Name"
            << std::left << std::setw(maxGPA) << "GPA" 
            << std::left << std::setw(maxHometown) << "Hometown"
            << std::left << std::setw(maxBirthday) << "Birthday"
            << "|" 
            << std::endl;
  for (int i = 0; i < n; i++) {
    std::cout << "|" 
              << std::left << std::setw(10) << i + 1 
              << std::left << std::setw(maxIDWidth) << s[i].ID 
              << std::left << std::setw(maxNameWidth) << s[i].fullName 
              << std::left << std::setw(maxGPA) 
              << std::fixed 
              << std::setprecision(1) 
              << s[i].GPA 
              << std::left 
              << std::setw(maxHometown) 
              << s[i].homeTown
              << std::left 
              << std::setw(maxBirthday) 
              << s[i].birthDay
              <<"|" 
              <<std::endl;
  }
  printDash(92);
}

// 4. Sort students by GPA
bool compareByGPA(const Student& a, const Student& b) {
  return a.GPA > b.GPA;
}
void listOfStudentsByGPA(const Student* s, int n) {
  Student* temp = new Student[n];
  std::copy(s, s + n, temp);
  std::sort(temp, temp + n, compareByGPA);
  listOfStudents(temp, n);
  delete[] temp;
}

// 5. Sort students by name
std::string getFirstName(const Student& s) {
  int pos = s.fullName.find_last_of(" ");
  std::string firstName = s.fullName.substr(pos + 1);
  return firstName;
}
bool compareByFirstName(const Student& a, const Student& b) {
  std::string firstNameA = getFirstName(a);
  std::string firstNameB = getFirstName(b);
  return firstNameA < firstNameB;
}
void listOfStudentsByName(const Student* s, int n) {
  Student* temp = new Student[n];
  std::copy(s, s + n, temp);
  std::sort(temp, temp + n, compareByFirstName);
  listOfStudents(temp, n);
  delete[] temp;
}

// 6. Update student information
void updateStudent(Student* s, int n) {
  std::cout << "Enter the ID of the student: ";
  int ID;
  std::cin >> ID;
	int index = searchByID(s, n, ID);
	if(index == -1) {
		std::cout << "No student found with ID: " << ID << std::endl;
		return;
	}
  if (index != -1) {
    std::cout << "Enter the new information for the student:" << std::endl;
    std::cout << "Full name: ";
    std::cin.ignore(); // Ignore the newline character left in the buffer by previous input
    std::getline(std::cin, s[index].fullName);
    std::cout << "Home town: ";
    std::getline(std::cin, s[index].homeTown);
    std::cout << "Birth day: ";
    std::getline(std::cin, s[index].birthDay);
    std::cout << "Score: ";
    std::cin >> s[index].score;
    std::cout << "The information of the student with ID " << ID << " has been updated." << std::endl;
  }
  else {
    std::cout << "Cannot find the student with ID " << ID << "." << std::endl;
  }
}


// 7. Remove student
void removeStudent(Student s[], int n) {
  std::cout << "Enter the ID of the student: ";
  int ID;
  std::cin >> ID;
	int index = searchByID(s, n, ID);
	if(index == -1) {
		std::cout << "No student found with ID: " << ID << std::endl;
		return;
	}
  if (index != -1) {
    // Remove the student at position index
    for (int i = index; i < n - 1; i++) {
        s[i] = s[i + 1];
      }
      // decrement the number of students by one
      n--;
    // Deallocate memory of the removed student
    Student* temp = new Student[n];
    for (int i = 0; i < n; i++) {
      temp[i] = s[i];
    }
    delete[] s;
    s = temp;
    std::cout << "The student with ID " << ID << " has been removed." << std::endl;
  }
  else {
    std::cout << "Cannot find the student with ID " << ID << "." << std::endl;
  }
}


// 8. Put the student list in the "student.txt" file
void outFile(const Student* s, int n, std::ofstream& outstream) {
  std::ofstream outfile;
  int maxIDWidth = 11; // Set max width
  int maxNameWidth = 25; // Set max name
  int maxGPA = 12;
  int maxHometown = 16; // Set max hometown
  int maxBirthday = 16; // Set max birthday
  outstream << "List of students" << std::endl;
  outstream << std::endl;
  outstream << std::left << std::setw(10) << "STT" 
            << std::left << std::setw(maxIDWidth) << "ID" 
            << std::left << std::setw(maxNameWidth) << "Full Name" 
            << std::left << std::setw(maxGPA) << "GPA" 
            << std::left << std::setw(maxHometown) << "Hometown" 
            << std::left << std::setw(maxBirthday) << "Birthday" 
            << std::endl;
  for (int i = 0; i < n; i++) {
    outstream << std::left << std::setw(10) << i + 1 
              << std::left << std::setw(maxIDWidth) << s[i].ID 
              << std::left << std::setw(maxNameWidth) << s[i].fullName 
              << std::left << std::setw(maxGPA) << std::fixed << std::setprecision(1) << s[i].GPA 
              << std::left << std::setw(maxHometown) << s[i].homeTown 
              << std::left << std::setw(maxBirthday) << s[i].birthDay 
              <<std::endl;
  }
  outfile.open("students.txt");
  outFile(s, n, outfile);
  outfile.close();
}

int main() {
	int n = 0;
  std::ofstream outfile;
	int choose;
	do {
		menu();
		std::cout << "Choose (0 - 8): ";
		std::cin >> choose;
		switch(choose)
		{
		case 1:
			system("cls");
			addStudent(students, n);
			break;
		case 2:
			system("cls");
			displayStudentByID(students, n);
			break;
		case 3:
			system("cls");
      listOfStudents(students, n);
			break;
		case 4:
			system("cls");
      listOfStudentsByGPA(students, n);
			break;
		case 5:
			system("cls");
      listOfStudentsByName(students, n);
			break;
		case 6:
			system("cls");
      updateStudent(students, n);
			break;
		case 7:
			system("cls");
      removeStudent(students, n);
			break;
    case 8:
			system("cls");
      outFile(students, n, outfile);
			break;
		case 0:
			system("cls");
			break;
		}
	} while(choose != 0);
	return 0;
}