#include <iostream>
#include <vector>
#include <fstream>
#include <windows.h>
using namespace std;
#define RED 12
#define GREEN 10
#define PURPLE 13
#define WHITE 7
#define PALE_BLUE 3

void setColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void colorTextForOneLine(string text, int color)
{
    setColor(color);
    cout << text;
    setColor(WHITE);
}

class Person
{
protected:
    string name;
    int id = 2001;
    int grade;
    double salary;
    static int count;

public:
    Person(string name, int grade) : name(name), grade(grade)
    {
        id += count;
        count++;
    }
    string getName() { return name; }
    int getID() { return id; }
    int getGrade() { return grade; }
    double getSalary() { return salary; }
    static int getCount() { return count; }
    void display()
    {
        printf("%-6d%-8s%-9d%-10.2f\n", id, name.c_str(), grade, salary);
    };
    virtual void setSalary() = 0;
    virtual void setWorkHours(int workHours) {}
    virtual void setSales(double sales) {}
    static void setCount(int _count) { count = _count; }
    virtual ~Person() {}
};

class SaleMan : virtual public Person
{
protected:
    double sales;

public:
    SaleMan(string name, double sales = 0) : Person(name, 1), sales(sales)
    {
        setSalary();
    }
    double getSales() { return sales; }
    virtual void setSalary() { this->salary = 0.04 * sales; }
    void setSales(double sales) { this->sales = sales; }
};

class Technician : virtual public Person
{
protected:
    int workHours;

public:
    Technician(string name, int workHours = 0) : Person(name, 3), workHours(workHours)
    {
        setSalary();
    }
    int getWorkHours() { return workHours; }
    virtual void setSalary() { this->salary = 100 * workHours; }
    void setWorkHours(int workHours) { this->workHours = workHours; }
};

class Manager : virtual public Person
{
    static int hasManager;
public:
    Manager(string name) : Person(name, 4)
    {
        setSalary();
        hasManager = 1;
    }
    virtual void setSalary() { this->salary = 18000; }
    static void setHasManager(int _hasManager) { hasManager = _hasManager; }
    static int getHasManager() { return hasManager; }
};

class SalesManager : virtual public SaleMan
{
public:
    SalesManager(string name, double sales = 0) : SaleMan(name, sales), Person(name, 2)
    {
        setSalary();
    }
    virtual void setSalary() { this->salary = 0.05 * sales + 5000; }
};

class EmployeeList
{
protected:
    vector<Person *> employees;

public:
    void addEmployee(Person *p)
    {
        employees.push_back(p);
    }
    void display()
    {
        cout << "ID    " << "Name    " << "Grade    " << "Salary" << endl;
        cout << "--------------------------------" << endl;
        for (Person *p : employees)
        {
            p->display();
            cout << "--------------------------------" << endl;
        }
    }
    void deleteByName(string name)
    {
        for (int i = 0; i < employees.size(); i++)
        {
            if (employees[i]->getName() == name)
            {
                employees.erase(employees.begin() + i);
                cout << "Employee " << name << " has been deleted." << endl;
                return;
            }
        }
        cout << "Employee " << name << " not found." << endl;
    }
    void deleteByID(int id)
    {
        for (int i = 0; i < employees.size(); i++)
        {
            if (employees[i]->getID() == id)
            {
                employees.erase(employees.begin() + i);
                cout << "Employee with ID " << id << " has been deleted." << endl;
                return;
            }
        }
        cout << "Employee with ID " << id << " not found." << endl;
    }
    void setWorkHour()
    {
        for (Person *p : employees)
        {
            Technician *t = dynamic_cast<Technician *>(p);
            if (t)
            {
                int workHours;
                colorTextForOneLine(t->getName(), PURPLE);
                cout << " is a technician.\n";
                cout << "Enter work hours, or enter -1 to skip: ";
                cin >> workHours;
                if (workHours == -1)
                    continue;
                t->setWorkHours(workHours);
                t->setSalary();
            }
        }
    }
    void setSales()
    {
        for (Person *p : employees)
        {
            SaleMan *s = dynamic_cast<SaleMan *>(p);
            if (s)
            {
                double sales;
                colorTextForOneLine(s->getName(), PURPLE);
                cout << " is a saleman.\n";
                cout << "Enter sales, or enter -1 to skip: ";
                cin >> sales;
                if (sales == -1)
                    continue;
                s->setSales(sales);
                s->setSalary();
            }
        }
    }
    vector<Person *> getEmployees() { return employees; }
    void clear()
    {
        employees.clear();
    }
    void saveToFile(string filename)
    {
        ofstream file(filename);
        for (Person *p : employees)
        {
            file << p->getID() << " " << p->getName() << " " << p->getGrade() << " " << p->getSalary() << endl;
        }
        file.close();
    }
    void loadFromFile(const string &filename)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        int id, grade;
        double salary;
        string name;

        while (file >> id >> name >> grade >> salary)
        {
            Person *employee = nullptr;
            switch (grade)
            {
            case 1:
                employee = new SaleMan(name, salary / 0.04); 
                break;
            case 2:
                employee = new SalesManager(name, salary - 5000); 
                break;
            case 3:
                employee = new Technician(name, salary / 100); 
                break;
            case 4:
                employee = new Manager(name);
                break;
            default:
                cerr << "Invalid grade for employee: " << name << endl;
                continue; 
            }
            if (employee)
            {
                employee->setSalary(); 
                employees.push_back(employee);
            }
        }

        file.close();
    }
};
