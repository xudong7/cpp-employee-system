#include <iostream>
#include <vector>
#include <fstream>
#include <windows.h>
#include <limits>
#include <sstream>
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
    SaleMan(string name, double sales = 0) : Person(name, 1)
    {
        setSales(sales);
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
    Technician(string name, int workHours = 0) : Person(name, 3)
    {
        setWorkHours(workHours);
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
        setSales(sales);
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
        colorTextForOneLine("Employee with Name " + name + " not found.\n", RED);
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
        colorTextForOneLine("Employee with ID " + to_string(id) + " not found.\n", RED);
    }
    void setWorkHour()
    {
        for (Person *p : employees)
        {
            Technician *t = dynamic_cast<Technician *>(p);
            if (t)
            {
                int workHours, isCorrectInput=0;
                string info;
                cout << "Enter work hours for Technician ";
                colorTextForOneLine(t->getName(), PURPLE);
                cout << ", or enter -1 to skip: ";
                while (!isCorrectInput)
                {
                    cin >> info;
                    if (info == "-1")
                    {
                        isCorrectInput = 1;
                        continue;
                    }
                    int i = 0;
                    for (; i < info.size(); i++)
                    {
                        char c = info[i];
                        if (!isdigit(c))
                        {
                            colorTextForOneLine("Invalid input", RED);
                            cout << ". Please enter an integer or -1 to skip: ";
                            isCorrectInput = 0;
                            break;
                        }
                    }
                    if (i == info.size())
                    {
                        isCorrectInput = 1;
                    }
                }
                stringstream ss(info);
                ss >> workHours;
                if (workHours == -1)
                    continue;
                t->setWorkHours(workHours);
                t->setSalary();
                cout << "Salary for Technician ";
                colorTextForOneLine(t->getName(), PURPLE);
                cout << " is set to " << t->getSalary() << endl;
            }
        }
    }
    void setSales()
    {
        for (Person *p : employees)
        {
            string position;
            if (p->getGrade() == 1) position = "SaleMan";
            else if (p->getGrade() == 2) position = "SalesManager";
            else continue;
            double sales, isCorrectInput=0;
            string info;
            cout << "Enter sales for " << position << " ";
            colorTextForOneLine(p->getName(), PURPLE);
            cout << ", or enter -1 to skip: ";
            while (!isCorrectInput)
            {
                cin >> info;
                if (info == "-1")
                {
                    isCorrectInput = 1;
                    continue;
                }
                int i = 0;
                for (; i < info.size(); i++)
                {
                    char c = info[i];
                    if (!isdigit(c) && c != '.')
                    {
                        colorTextForOneLine("Invalid input", RED);
                        cout << ". Please enter a number or -1 to skip: ";
                        isCorrectInput = 0;
                        break;
                    }
                }
                if (i == info.size())
                {
                    isCorrectInput = 1;
                }
            }
            stringstream ss(info);
            ss >> sales;
            if (sales == -1)
                continue;
            if (position == "SaleMan")
            {
                SaleMan *s = dynamic_cast<SaleMan *>(p);
                s->setSales(sales);
                s->setSalary();
                cout << "Salary for SaleMan ";
                colorTextForOneLine(s->getName(), PURPLE);
                cout << " is set to " << s->getSalary() << endl;
            }
            else if (position == "SalesManager")
            {
                SalesManager *s = dynamic_cast<SalesManager *>(p);
                s->setSales(sales);
                s->setSalary();
                cout << "Salary for SalesManager ";
                colorTextForOneLine(s->getName(), PURPLE);
                cout << " is set to " << s->getSalary() << endl;
            }
        }
    }
    void addEmployeeAction()
    {
        string name;
        int grade, isCorrectInput=0;
        colorTextForOneLine("*** Adding new employee ***\n", GREEN);
        cout << "please enter name: ";
        cin >> name;
        cout << endl;
        string info;
        cout << "please enter grade(4 for Manager, 3 for Technician, 2 for SalesManager, 1 for SaleMan): ";
        cin >> info;
        while (!isCorrectInput)
        {
            if (info.size() != 1 || info[0] < '1' || info[0] > '4')
            {
                colorTextForOneLine("Invalid grade", RED);
                cout << ". Please enter a number from 1 to 4: ";
                cin >> info;
            }
            else
            {
                isCorrectInput = 1;
            }
        }
        stringstream ss(info);
        ss >> grade;
        switch (grade)
        {
        case 4:
            if (Manager::getHasManager())
            {
                colorTextForOneLine("There is already a manager.\n", RED);
                return;
            }
            addEmployee(new Manager(name));
            break;
        case 3:
            addEmployee(new Technician(name));
            break;
        case 2:
            addEmployee(new SalesManager(name));
            break;
        case 1:
            addEmployee(new SaleMan(name));
            break;
        default:
            colorTextForOneLine("Invalid grade.\n", RED);
            return;
        }
        cout << endl;
        colorTextForOneLine("Adding new employee done.\n", GREEN);
    }
    void clear()
    {
        employees.clear();
    }
    bool isPayed()
    {
        for (Person *p : employees)
        {
            if (p->getSalary() == 0)
            {
                return false;
            }
        }
        return true;
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
                employee = new SalesManager(name, (salary - 5000) * 20);
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
    vector<Person *> getEmployees() { return employees; }
};
