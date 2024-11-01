#include "person.cpp"

int Person::count = 0;

void setColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void colorTextForOneLine(string text, int color)
{
    setColor(color);
    cout << text;
    setColor(7);
}

void insertAll(EmployeeList& list)
{
    string name;
    setColor(12);
    cout << "********************************" << endl;
    cout << "This Action Will Clear Old Data!!!!" << endl;
    cout << "********************************" << endl;
    setColor(7);
    cout << "Are you sure to insert all employees? (y/n): ";
    char choice;
    cin >> choice;
    if (choice != 'y') return;
    list.clear();
    Person::setCount(0);
    colorTextForOneLine("*** Inserting employees ***\n", 10);
    cout << "please enter the name of Manager: ";
    cin >> name;
    list.addEmployee(new Manager(name));
    cout << "please enter the name of Technician, exit if enter @" << endl;
    while (true)
    {
        cout << "the name of Technician: ";
        cin >> name;
        if (name != "@") 
            list.addEmployee(new Technician(name));
        else 
            break;
    }
    cout << "please enter the name of SalesManager, exit if enter @: " << endl;
    while (true)
    {
        cout << "the name of SalesManager: ";
        cin >> name;
        if (name != "@") 
            list.addEmployee(new SalesManager(name));
        else 
            break;
    }
    cout << "please enter the name of SaleMan, exit if enter @: " << endl;
    while (true)
    {
        cout << "the name of SaleMan: ";
        cin >> name;
        if (name != "@") 
            list.addEmployee(new SaleMan(name));
        else 
            break;
    }
    colorTextForOneLine("Inserting employees done.\n", 10);
}

void addEmployee(EmployeeList& list)
{
    string name;
    int grade;
    colorTextForOneLine("*** Adding new employee ***\n", 10);
    cout << "please enter employee name and grade(4 Manager 3 Technician 2 SalesManager 1 SaleMan): ";
    cin >> name >> grade;
    switch (grade)
    {
        case 4:
            list.addEmployee(new Manager(name));
            break;
        case 3:
            list.addEmployee(new Technician(name));
            break;
        case 2:
            list.addEmployee(new SalesManager(name));
            break;
        case 1:
            list.addEmployee(new SaleMan(name));
            break;
        default:
            cout << "Invalid grade." << endl;
    }
    colorTextForOneLine("Adding new employee done.\n", 10);
}

void deleteEmployee(EmployeeList& list)
{
    int id;
    colorTextForOneLine("*** Deleting employee ***\n", 10);
    list.display();
    cout << "please enter the ID of employee: ";
    cin >> id;
    list.deleteByID(id);
    colorTextForOneLine("Deleting employee done.\n", 10);
}

void insertInfomation(EmployeeList& list)
{
    int workHours;
    double sales;
    colorTextForOneLine("*** Inserting infomation ***\n", 10);
    list.setWorkHour();
    list.setSales();
    colorTextForOneLine("Inserting infomation done.\n", 10);
}

void displaySalary(EmployeeList& list)
{
    colorTextForOneLine("*** Displaying salary table ***\n", 10);
    list.display();
    colorTextForOneLine("Displaying salary table done.\n", 10);
}

void menu()
{
    EmployeeList list;
    string loadFileName = "employees.txt";
    list.loadFromFile(loadFileName);
    while (true)
    {
        colorTextForOneLine("Company Employee Manage System\n", 3);
        cout << "--------------------------------" << endl;
        cout << "    1. Insert All Employee" << endl;
        cout << "    2. Add new Employee" << endl;
        cout << "    3. delete Employee" << endl;
        cout << "    4. Insert Infomation" << endl;
        cout << "    5. Display Salary Table" << endl;
        cout << "    0. Exit" << endl;
        cout << "--------------------------------" << endl;
        cout << "Please choose: ";
        int choice;
        cin >> choice;
        switch (choice)
        {
            case 1:
                insertAll(list);
                break;
            case 2:
                addEmployee(list);
                break;
            case 3:
                deleteEmployee(list);
                break;
            case 4:
                insertInfomation(list);
                break;
            case 5:
                displaySalary(list);
                break;
            case 0:
                colorTextForOneLine("*** Goodbye! ***\n", 13);
                list.saveToFile("employees.txt");
                return;
        }
        cout << endl;
        cout << "Press any key to continue...";
        getchar();
        getchar();
        cout << endl;
    }
}

int main()
{
    menu();
}