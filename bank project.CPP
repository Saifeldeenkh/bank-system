#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Function to check if a string contains only alphabetic characters and spaces
bool isAlpha(const string& str) {
    for (char c : str) {
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' ')) {
            return false;
        }
    }
    return true;
}

// Client class
class Client {
private:
    int id;          // Client ID
    string name;     // Client name
    string password; // Client password
    double balance;  // Client balance

public:
    // Default constructor
    Client() {
        id = 0;
        balance = 0;
    }

    // Parameterized constructor
    Client(int id, double balance, string name, string password) {
        this->id = id;
        this->balance = balance;
        set_name(name); // Validate and set name
        this->password = password;
    }

    // Getters
    int get_id() {
        return id;
    }

    double get_balance() {
        return balance;
    }

    string get_name() {
        return name;
    }

    string get_password() {
        return password;
    }

    // Setters
    void set_id(int id) {
        this->id = id;
    }

    void set_name(string name) {
        if (name.size() >= 5 && name.size() <= 20 && isAlpha(name)) {
            this->name = name;
        }
        else {
            cout << "Invalid name - Must be alphabetic and between 5 to 20 characters" << endl;
        }
    }

    void set_password(string password) {
        if (password.size() >= 8 && password.size() <= 20) {
            this->password = password;
        }
        else {
            cout << "Invalid password - Must be between 8 to 20 characters" << endl;
        }
    }

    void set_balance(double balance) {
        if (balance >= 1500) {
            this->balance = balance;
        }
        else {
            cout << "Invalid balance - Min balance 1500" << endl;
        }
    }

    // Deposit money
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited: " << amount << " to " << name << "'s account," << " And your current balance is " << balance << endl;
        }
        else {
            cout << "Invalid deposit amount. Amount must be greater than 0" << endl;
        }
    }

    // Withdraw money
    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawn: " << amount << " from " << name << "'s account" << " And your current balance is " << balance << endl;
        }
        else {
            cout << "Invalid withdrawal amount or insufficient balance." << endl;
        }
    }

    // Check balance
    void check_balance() {
        cout << "Current balance for " << name << ": " << balance << endl;
    }

    // Transfer money to another client
    void transferTo(double amount, Client& recipient) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            recipient.deposit(amount);
            cout << "Transferred " << amount << " to " << recipient.get_name() << "'s account." << endl;
            cout << "Your new balance is " << balance << endl;
        }
        else {
            cout << "Transfer failed" << endl;
        }
    }

    // Display client details
    void display() {
        cout << "Client ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Balance: " << balance << endl;
    }
};

// Employee class
class Employee {
private:
    // Function to check if the name contains only alphabetic characters
    bool isAlpha(const string& str) const {
        for (char c : str) {
            if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) {
                return false;
            }
        }
        return true;
    }

protected:
    int id;
    string name, password;
    double balance;

public:
    // Default constructor
    Employee() {
        this->balance = 0;
        this->id = 0;
    }

    // Parameterized constructor
    Employee(int id, string name, string password, double balance) {
        this->id = id;
        this->name = name;
        this->password = password;
        this->balance = balance;
    }

    // Setters
    void setId(int id) {
        this->id = id;
    }

    void setName(string name) {
        if (name.length() >= 5 && name.length() <= 20 && isAlpha(name)) {
            this->name = name;
        }
        else {
            cout << "Name must be alphabetic and between 5 to 20 characters." << endl;
        }
    }

    void setPassword(string password) {
        if (password.length() >= 8 && password.length() <= 20) {
            this->password = password;
        }
        else {
            cout << "Password must be between 8 to 20 characters." << endl;
        }
    }

    void setBalance(double balance) {
        if (balance >= 5000) {
            this->balance = balance;
        }
        else {
            cout << "Salary must be at least 5000." << endl;
        }
    }

    // Getters
    int getId() {
        return this->id;
    }

    string getName() {
        return this->name;
    }

    string getPassword() {
        return this->password;
    }

    double getBalance() {
        return this->balance;
    }

    // Display employee details
    void display() {
        cout << "ID = " << id << endl;
        cout << "Name = " << name << endl;
        cout << "Password = " << password << endl;
        cout << "Balance = " << balance << endl;
    }
};

// Admin class inherits from Employee
class Admin : public Employee {
public:
    // Default constructor
    Admin() : Employee() {}

    // Parameterized constructor
    Admin(int id, string name, string password, double balance) : Employee(id, name, password, balance) {}

    // Add new employee
    void addEmployee(vector<Employee>& employees, int id, string name, string password, double balance) {
        Employee newEmployee(id, name, password, balance);
        employees.push_back(newEmployee);
        cout << "Employee added successfully!" << endl;
    }

    // Search for employee by ID
    Employee* searchEmployee(vector<Employee>& employees, int id) {
        for (Employee& employee : employees) {
            if (employee.getId() == id) {
                return &employee;
            }
        }
        return nullptr;
    }

    // Edit employee details
    void editEmployee(vector<Employee>& employees, int id, string newName, string newPassword, double newBalance) {
        Employee* employee = searchEmployee(employees, id);
        if (employee != nullptr) {
            employee->setName(newName);
            employee->setPassword(newPassword);
            employee->setBalance(newBalance);
            cout << "Employee details updated successfully!" << endl;
        }
        else {
            cout << "Employee not found!" << endl;
        }
    }

    // List all employees
    void listAllEmployees(vector<Employee>& employees) {
        cout << "List of all employees:" << endl;
        for (Employee& employee : employees) {
            employee.display();
            cout << "-------------------" << endl;
        }
    }
};

// Main function
int main() {
    vector<Client> clients;
    vector<Employee> employees;

    // Create some clients
    Client c1(112, 2000, "Ahmed Ali", "password@12345");
    Client c2(113, 1500, "Sara Ahmed", "password@54321");
    clients.push_back(c1);
    clients.push_back(c2);

    // Create some employees
    Employee e1(1, "Farmersteam", "Password12345", 6000);
    employees.push_back(e1);

    // Create an admin
    Admin admin(100, "AdminUser", "AdminPassword", 10000);

    // Display all clients
    cout << "Clients:" << endl;
    for (Client& client : clients) {
        client.display();
    }

    // Display all employees
    cout << "\nEmployees:" << endl;
    for (Employee& employee : employees) {
        employee.display();
    }

    // Perform some operations
    cout << "\nPerforming operations..." << endl;
    c1.transferTo(500, c2);
    c1.deposit(5000);
    c1.withdraw(2000);
    c1.check_balance();

    // Admin operations
    cout << "\nAdmin operations..." << endl;
    admin.addEmployee(employees, 2, "NewEmployee", "NewPassword", 7000);
    admin.listAllEmployees(employees);

    Employee* foundEmployee = admin.searchEmployee(employees, 2);
    if (foundEmployee != nullptr) {
        cout << "Employee found: " << foundEmployee->getName() << endl;
    }
    else {
        cout << "Employee not found!" << endl;
    }

    admin.editEmployee(employees, 2, "UpdatedEmployee", "UpdatedPassword", 8000);
    admin.listAllEmployees(employees);

    return 0;
}