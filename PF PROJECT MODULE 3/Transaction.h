#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

const int MAX_TRANSACTIONS = 100;

struct Transaction
{
    int transactionId;
    int productId;
    int quantitySold;
    double unitPrice;
    double total;
};

void addTransaction(Transaction transactions[], int& currentTransactionIndex, int maxRecords);
void viewTransactions(const Transaction transactions[], int currentTransactionIndex);
void searchTransaction(const Transaction transactions[], int currentTransactionIndex);
void updateTransaction(Transaction transactions[], int currentTransactionIndex);
void deleteTransaction(Transaction transactions[], int& currentTransactionIndex);
void readTransactionFile(Transaction transactions[], int& currentTransactionIndex, int maxRecords);
void writeTransactionFile(const Transaction transactions[], int currentTransactionIndex);
bool transactionIdExists(const Transaction transactions[], int currentTransactionIndex, int transactionId);

void transactionManagement()
{
    const int maxRecords = 100;
    Transaction transactions[MAX_TRANSACTIONS];
    int currentTransactionIndex = 0;
    readTransactionFile(transactions, currentTransactionIndex, maxRecords);

    while (currentTransactionIndex < maxRecords)
    {
        cout << "\n1. Add Transaction \n2. View Transactions \n3. Search Transaction \n4. Update Transaction \n5. Delete Transaction \n6. Back" << endl;
        cout << "\nEnter the option: ";
        int option;
        cin >> option;

        switch (option)
        {
        case 1:
            cout << "-------------------------------------------------------" << endl
                << "\t\t\t ADD A NEW TRANSACTION \n-------------------------------------------------------" << endl;
            addTransaction(transactions, currentTransactionIndex, maxRecords);
            break;
        case 2:
            cout << " VIEW Transaction Records: " << endl;
            viewTransactions(transactions, currentTransactionIndex);
            break;
        case 3:
            cout << "-------------------------------------------------------" << endl
                << "\t\t\t SEARCH A TRANSACTION \n-------------------------------------------------------" << endl;
            searchTransaction(transactions, currentTransactionIndex);
            break;
        case 4:
            cout << "-------------------------------------------------------" << endl
                << "\t\t\t UPDATE A TRANSACTION \n-------------------------------------------------------" << endl;
            updateTransaction(transactions, currentTransactionIndex);
            break;
        case 5:
            cout << "-------------------------------------------------------" << endl
                << "\t\t\t DELETE A TRANSACTION \n-------------------------------------------------------" << endl;
            deleteTransaction(transactions, currentTransactionIndex);
            break;
        case 6:
            cout << "\nGoing Back To Menu" << endl;
            writeTransactionFile(transactions, currentTransactionIndex);
            return;
        default:
            cout << "Invalid Option!\n";
        }
    }
    writeTransactionFile(transactions, currentTransactionIndex);
}

void addTransaction(Transaction transactions[], int& currentTransactionIndex, int maxRecords)
{
    if (currentTransactionIndex < maxRecords)
    {
        do
        {
            cout << "Enter Transaction ID: ";
            cin >> transactions[currentTransactionIndex].transactionId;

            if (transactionIdExists(transactions, currentTransactionIndex, transactions[currentTransactionIndex].transactionId))
            {
                cout << "Transaction ID already exists. Please enter a different ID." << endl;
            }
            else
            {
                break;
            }
        } while (true);

        cout << "Enter Product ID: ";
        cin >> transactions[currentTransactionIndex].productId;

        cout << "Enter Quantity Sold: ";
        cin >> transactions[currentTransactionIndex].quantitySold;

        cout << "Enter Unit Price: ";
        cin >> transactions[currentTransactionIndex].unitPrice;

        transactions[currentTransactionIndex].total = transactions[currentTransactionIndex].quantitySold * transactions[currentTransactionIndex].unitPrice;

        currentTransactionIndex++;
    }
    else
    {
        cout << "Maximum Records Reached" << endl;
    }
}

void viewTransactions(const Transaction transactions[], int currentTransactionIndex)
{
    cout << "-------------------------------------------------------" << setw(15) << "\nID" << setw(15) << "Product ID" << setw(15) << "Quantity Sold" << setw(15) << "Unit Price" << setw(15) << "Total" << endl;
    cout << "-------------------------------------------------------" << endl
        << endl;

    for (int i = 0; i < currentTransactionIndex; i++)
    {
        cout << setw(15) << transactions[i].transactionId << setw(15) << transactions[i].productId
            << setw(15) << transactions[i].quantitySold << setw(15)  << transactions[i].unitPrice
            << setw(15) << transactions[i].total << endl;
    }

}

void searchTransaction(const Transaction transactions[], int currentTransactionIndex)
{
    int targetTransactionId;
    cout << "Enter the Transaction ID of the transaction you want to search: ";
    cin >> targetTransactionId;

    for (int i = 0; i < currentTransactionIndex; i++)
    {
        if (targetTransactionId == transactions[i].transactionId)
        {
            cout << "Transaction found:\n";
            cout << setw(15) << "ID" << setw(15) << "Product ID" << setw(15) << "Quantity Sold" << setw(15) << "Unit Price" << setw(15) << "Total" << endl;
            cout << setw(15) << transactions[i].transactionId << setw(15) << transactions[i].productId
                << setw(15) << transactions[i].quantitySold << setw(15)  << transactions[i].unitPrice
                << setw(15) << transactions[i].total << endl;

            return;
        }
    }

    cout << "Transaction with Transaction ID: " << targetTransactionId << " not found.\n"
        << endl;
}

void updateTransaction(Transaction transactions[], int currentTransactionIndex)
{
    int targetTransactionId;
    cout << "Enter the Transaction ID of the transaction you want to update: ";
    cin >> targetTransactionId;

    for (int i = 0; i < currentTransactionIndex; i++)
    {
        if (targetTransactionId == transactions[i].transactionId)
        {
            cout << "Enter new Product ID: ";
            cin >> transactions[i].productId;

            cout << "Enter new Quantity Sold: ";
            cin >> transactions[i].quantitySold;

            cout << "Enter new Unit Price: ";
            cin >> transactions[i].unitPrice;

            transactions[i].total = transactions[i].quantitySold * transactions[i].unitPrice;

            cout << "Transaction Successfully Updated" << endl;

            return;
        }
    }

    cout << "Transaction with Transaction ID: " << targetTransactionId << " does not exist in records.\n"
        << endl;
}

void deleteTransaction(Transaction transactions[], int& currentTransactionIndex)
{
    int targetTransactionId;
    cout << "Enter the Transaction ID of the transaction you want to delete: ";
    cin >> targetTransactionId;

    for (int i = 0; i < currentTransactionIndex; i++)
    {
        if (targetTransactionId == transactions[i].transactionId)
        {
            for (int j = i; j < currentTransactionIndex - 1; j++)
            {
                transactions[j] = transactions[j + 1];
            }

            currentTransactionIndex--;
            cout << "Transaction with Transaction ID: " << targetTransactionId << " successfully deleted from records. " << endl;

            return;
        }
    }

    cout << "Failed to delete Transaction with Transaction ID: " << targetTransactionId << ". " << endl;
}

void readTransactionFile(Transaction transactions[], int& currentTransactionIndex, int maxRecords)
{
    ifstream fin;
    fin.open("Transactions.txt");
    try
    {
        if (fin.fail())
            throw runtime_error("Error opening File. Please create file 'Transactions.txt' and try again.");
    }
    catch (runtime_error& e)
    {
        cout << e.what() << endl;
        return;
    }

    while (!fin.eof())
    {
        fin >> transactions[currentTransactionIndex].transactionId >> transactions[currentTransactionIndex].productId >> transactions[currentTransactionIndex].quantitySold >> transactions[currentTransactionIndex].unitPrice >> transactions[currentTransactionIndex].total;

        if (!fin.eof())
        {
            currentTransactionIndex++;
        }
    }
    fin.close();
}

void writeTransactionFile(const Transaction transactions[], int currentTransactionIndex)
{
    ofstream fout;
    fout.open("Transactions.txt");

    try
    {
        if (fout.fail())
            throw runtime_error("Error creating file 'Transactions.txt'");
    }
    catch (runtime_error& e)
    {
        cout << e.what() << endl;
        return;
    }

    for (int i = 0; i < currentTransactionIndex; i++)
    {
        fout << setw(15) << transactions[i].transactionId << setw(15) << transactions[i].productId
            << setw(15) << transactions[i].quantitySold << setw(15) << transactions[i].unitPrice
            << setw(15) << transactions[i].total << endl;
    }
    fout.close();
}

bool transactionIdExists(const Transaction transactions[], int currentTransactionIndex, int transactionId)
{
    for (int i = 0; i < currentTransactionIndex; i++)
    {
        if (transactionId == transactions[i].transactionId)
        {
            return true;
        }
    }
    return false;
}

