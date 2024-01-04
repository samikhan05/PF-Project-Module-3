#include "Product.h"
#include "Transaction.h"
using namespace std;

bool productIdExists(const Product products[], int currentIndex, int productId);
bool transactionIdExists(const Transaction transactions[], int currentTransactionIndex, int transactionId);
void readProductFile(Product products[], int& currentIndex, int maxRecords);
void readTransactionFile(Transaction transactions[], int& currentTransactionIndex, int maxRecords);
void viewProductRecord(const Product products[], int currentIndex, int productId, const Transaction transactions[], int currentTransactionIndex);
void viewTransactionRecord(const Transaction transactions[], int currentTransactionIndex, int transactionId, const Product products[], int currentProductIndex);

struct Inventory
{
    Product products[MAX_RECORDS];
    Transaction transactions[MAX_RECORDS];
    int currentProductIndex;
    int currentTransactionIndex;
};

void InventoryManagement()
{
    Inventory inventory;
    inventory.currentProductIndex = 0;
    inventory.currentTransactionIndex = 0;

    readProductFile(inventory.products, inventory.currentProductIndex, MAX_RECORDS);
    readTransactionFile(inventory.transactions, inventory.currentTransactionIndex, MAX_RECORDS);

    int option;
    cout << "1. View Product Record\n2. View Transaction Record\nEnter the option: ";
    cin >> option;

    switch (option)
    {
    case 1:
    {
        int productId;
        cout << "Enter Product ID: ";
        cin >> productId;
        viewProductRecord(inventory.products, inventory.currentProductIndex, productId, inventory.transactions, inventory.currentTransactionIndex);
    }
    break;

    case 2:
    {
        int transactionId;
        cout << "Enter Transaction ID: ";
        cin >> transactionId;
        viewTransactionRecord(inventory.transactions, inventory.currentTransactionIndex, transactionId, inventory.products, inventory.currentProductIndex);
    }
    break;

    default:
        cout << "Invalid Option!\n";
    }
}

void viewProductRecord(const Product products[], int currentIndex, int productId, const Transaction transactions[], int currentTransactionIndex)
{
    bool exists = false;
    int productIndex = 0;

    for (int i = 0; i < currentIndex; i++)
    {
        if (productId == products[i].productId)
        {
            exists = true;
            productIndex = i;
            break;
        }
    }

    if (exists)
    {
        cout << "Product Record:\n";
        cout << setw(10) << "ID" << setw(20) << "Name" << setw(15) << "Price" << setw(15) << "Quantity" << endl;
        cout << setw(10) << products[productIndex].productId << setw(20) << products[productIndex].productName
            << setw(15) << products[productIndex].price << setw(15) << products[productIndex].quantity << endl;

        // Display transactions for the specified product
        cout << "\nTransactions for Product ID " << productId << ":\n";
        cout << setw(15) << "Transaction ID" << setw(15) << "Quantity Sold" << setw(15) << "Unit Price" << setw(15) << "Total" << endl;

        for (int i = 0; i < currentTransactionIndex; i++)
        {
            if (productId == transactions[i].productId)
            {
                cout << setw(15) << transactions[i].transactionId << setw(15) << transactions[i].quantitySold
                    << setw(15)  << transactions[i].unitPrice << setw(15) << transactions[i].total << endl;
            }
        }
    }
    else
    {
        cout << "Product with ID " << productId << " does not exist." << endl;
    }
}

void viewTransactionRecord(const Transaction transactions[], int currentTransactionIndex, int transactionId, const Product products[], int currentProductIndex)
{
    bool exists = false;
    int transactionIndex = 0;

    for (int i = 0; i < currentTransactionIndex; i++)
    {
        if (transactionId == transactions[i].transactionId)
        {
            exists = true;
            transactionIndex = i;
            break;
        }
    }

    if (exists)
    {
        cout << "Transaction Record:\n";
        cout << setw(15) << "Transaction ID" << setw(15) << "Product ID" << setw(15) << "Quantity Sold" << setw(15)  << "Unit Price" << setw(15)  << "Total" << endl;
        cout << setw(15) << transactions[transactionIndex].transactionId << setw(15)  << transactions[transactionIndex].productId
            << setw(15) << transactions[transactionIndex].quantitySold << setw(15)  << transactions[transactionIndex].unitPrice
            << setw(15) << transactions[transactionIndex].total << endl;

        // Display product details for the specified transaction
        int productIndex = -1;
        for (int i = 0; i < currentProductIndex; i++)
        {
            if (transactions[transactionIndex].productId == products[i].productId)
            {
                productIndex = i;
                break;
            }
        }

        if (productIndex != -1)
        {
            cout << "\nProduct Details for Product ID " << transactions[transactionIndex].productId << ":\n";
            cout << setw(10) << "ID" << setw(20)  << "Name" << setw(15)  << "Price" << setw(15)  << "Quantity" << endl;
            cout << setw(10) << products[productIndex].productId << setw(20)  << products[productIndex].productName
                << setw(15) << products[productIndex].price << setw(15)  << products[productIndex].quantity << endl;
        }
    }
    else
    {
        cout << "Transaction with ID " << transactionId << " does not exist." << endl;
    }
}
