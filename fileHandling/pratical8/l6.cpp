#include <iostream>
using namespace std;

// Base class: Person
class Person {
public:
    // Default constructor
    Person() {
        name = "";
        age = 0;
    }

    // Setter functions to set Person details
    void setPersonDetails(string personName, int personAge) {
        name = personName;
        age = personAge;
    }

    // Show function to display Person details
    void Show() {
        cout << "Person Name: " << name << endl;
        cout << "Person Age: " << age << endl;
    }

protected:
    string name;
    int age;
};

// Base class: Employee
class Employee {
public:
    // Default constructor
    Employee() {
        employeeId = 0;
        department = "";
    }

    // Setter functions to set Employee details
    void setEmployeeDetails(int empId, string empDepartment) {
        employeeId = empId;
        department = empDepartment;
    }

    // Show function to display Employee details
    void Show() {
        cout << "Employee ID: " << employeeId << endl;
        cout << "Department: " << department << endl;
    }

protected:
    int employeeId;
    string department;
};

// Derived class: Teacher (inherits from Person and Employee)
class Teacher : public Person, public Employee {
public:
    // Default constructor
    Teacher() {
        subject = "";
    }

    // Setter function to set Teacher details
    void setTeacherDetails(string personName, int personAge, int empId, string empDepartment, string teacherSubject) {
        setPersonDetails(personName, personAge);  // Set Person details
        setEmployeeDetails(empId, empDepartment);  // Set Employee details
        subject = teacherSubject;  // Set Teacher subject
    }

    // Show function to display Teacher details (calls Show from both Person and Employee)
    void Show() {
        Person::Show();  // Call Person's Show()
        Employee::Show(); // Call Employee's Show()
        cout << "Subject: " << subject << endl;
    }

private:
    string subject;
};

int main() {
    // Create a Teacher object
    Teacher teacher;

    // Set details for the teacher using setter function
    teacher.setTeacherDetails("John Doe", 35, 12345, "Mathematics", "Physics");

    // Display Teacher details using Show function
    teacher.Show();

    return 0;
}
