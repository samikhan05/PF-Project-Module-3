#include "Inventory.h"
#include <iostream>

using namespace std;

int main()
{
    int option;
    while (true)
    {
        cout << "--------------------------------------------------------------------------" << endl
            << "\t\t\tCASH AND CARRY MANAGEMENT SYSTEM\n--------------------------------------------------------------------------" << endl;
        cout << "1. Product System \n2. Transaction System \n3. Inventory System \n4. Exit \n"
            << endl;
        cout << "\nEnter your option: ";
        cin >> option;
        switch (option)
        {
        case 1:
            cout << "\n--------------------------------------------------------------------------" << endl 
                << "\t\t\t      Product System\n--------------------------------------------------------------------------" << endl;
            productManagement();
            break;
        case 2:
            cout << "\n--------------------------------------------------------------------------" << endl 
                << "\t\t\t    Transaction System\n--------------------------------------------------------------------------" << endl;
            transactionManagement();
            break;
        case 3:
            cout << "\n--------------------------------------------------------------------------" << endl 
                << "\t\t\t      Inventory System\n--------------------------------------------------------------------------" << endl;
            InventoryManagement();
            break;
        case 4:
            cout << "Program Terminated!";
            exit(0);

        default:
            cout << "Invalid Option!";
            break;
        }
    }
    return 0;
}