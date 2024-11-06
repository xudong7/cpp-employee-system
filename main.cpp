#include "person.cpp"
#include "load.cpp"
int Person::count = 0;
int Manager::hasManager = 0;

void insertAll(EmployeeList &list)
{
    string name;
    setColor(RED);
    cout << "********************************" << endl;
    cout << "This Action Will Clear Old Data!!!!" << endl;
    cout << "********************************" << endl;
    setColor(WHITE);
    cout << "Are you sure to insert all employees? (y/n): ";
    char choice;
    cin >> choice;
    if (choice != 'y')
        return;
    list.clear();
    Person::setCount(0);
    colorTextForOneLine("*** Inserting employees ***\n", GREEN);
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
    cout << endl;
    colorTextForOneLine("Inserting employees done.\n", GREEN);
}

void addEmployee(EmployeeList &list)
{
    list.addEmployeeAction();
}

void deleteEmployee(EmployeeList &list)
{
    colorTextForOneLine("*** Deleting employee ***\n", GREEN);
    list.display();
    cout << endl;
    list.deleteByID();
    cout << endl;
    colorTextForOneLine("Deleting employee done.\n", GREEN);
}

void insertInfomation(EmployeeList &list)
{
    int workHours;
    double sales;
    colorTextForOneLine("*** Inserting infomation ***\n", GREEN);
    list.setWorkHour();
    list.setSales();
    colorTextForOneLine("Inserting infomation done.\n", GREEN);
}

void displaySalary(EmployeeList &list)
{
    if (!list.isPayed())
    {
        colorTextForOneLine("Some employees have not been paid.\n", RED);
        cout << "Are you sure to display salary table? (y/n): ";
        char choice;
        cin >> choice;
        if (choice != 'y') return;
    }
    colorTextForOneLine("*** Displaying salary table ***\n", GREEN);
    list.display();
    colorTextForOneLine("Displaying salary table done.\n", GREEN);
}
void loading()
{
    cout << "Loading...\n[";
    for (int i = 0; i < 25; i++)
    {
        cout << "=";
        Sleep(50);
    }
    cout << ">] 100%" << endl;
    return;
}
void menu()
{
    EmployeeList list;
    string loadFileName = "employees.txt";
    list.loadFromFile(loadFileName);
    // loadingMode(); // normal loading
    loadingMode(1);
    cout << "Loading successfully!\n"
         << endl;
    while (true)
    {
        Sleep(500);
        colorTextForOneLine("Company Employee Manage System\n", PALE_BLUE);
        cout << "--------------------------------" << endl;
        cout << "    1. Insert All Employee" << endl;
        cout << "    2. Add new Employee" << endl;
        cout << "    3. delete Employee" << endl;
        cout << "    4. Insert Infomation" << endl;
        cout << "    5. Display Salary Table" << endl;
        cout << "    0. Exit" << endl;
        cout << "--------------------------------" << endl;
        cout << "Choose Option: ";
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
            colorTextForOneLine("\n*** Goodbye! ***\n", PURPLE);
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