#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

const int MAX_RECORDS = 100;

struct Product
{
    int productId;
    string productName;
    double price;
    int quantity;
};

void addProduct(Product products[], int& currentIndex, int maxRecords);
void viewProducts(const Product products[], int currentIndex);
void searchProduct(const Product products[], int currentIndex);
void updateProduct(Product products[], int currentIndex);
void deleteProduct(Product products[], int& currentIndex, int maxRecords);
void readProductFile(Product products[], int& currentIndex, int maxRecords);
void writeProductFile(const Product products[], int currentIndex);
bool productIdExists(const Product products[], int currentIndex, int productId);

void productManagement()
{
    const int maxRecords = 100;
    Product products[MAX_RECORDS];
    int currentIndex = 0;
    readProductFile(products, currentIndex, maxRecords);

    while (currentIndex < maxRecords)
    {
        cout << "\n1. Add Product \n2. View Products \n3. Search Product \n4. Update Product \n5. Delete Product \n6. Back" << endl;
        cout << "\nEnter the option: ";
        int option;
        cin >> option;

        switch (option)
        {
        case 1:
            cout << "-------------------------------------------------------" << endl
                << "\t\t\t ADD A NEW PRODUCT \n-------------------------------------------------------" << endl;
            addProduct(products, currentIndex, maxRecords);
            break;
        case 2:
            cout << "VIEW Product Records: " << endl;
            viewProducts(products, currentIndex);
            break;
        case 3:
            cout << "-------------------------------------------------------" << endl
                << "\t\t\t SEARCH EXISTING PRODUCT \n-------------------------------------------------------" << endl;
            searchProduct(products, currentIndex);
            break;
        case 4:
            cout << "-------------------------------------------------------" << endl
                << "\t\t\t UPDATE A PRODUCT RECORD \n-------------------------------------------------------" << endl;
            updateProduct(products, currentIndex);
            break;
        case 5:
            cout << "-------------------------------------------------------" << endl
                << "\t\t\t DELETE A PRODUCT RECORD \n-------------------------------------------------------" << endl;
            deleteProduct(products, currentIndex, maxRecords);
            break;
        case 6:
            cout << "\nGoing Back To Menu" << endl;
            writeProductFile(products, currentIndex);
            return;
        default:
            cout << "Invalid Option!\n";
        }
    }
    writeProductFile(products, currentIndex);
}

void addProduct(Product products[], int& currentIndex, int maxRecords)
{
    if (currentIndex < maxRecords)
    {
        do
        {
            cout << "Enter Product ID: ";
            cin >> products[currentIndex].productId;

            if (productIdExists(products, currentIndex, products[currentIndex].productId))
            {
                cout << "Product ID already exists. Please enter a different ID." << endl;
            }
            else
            {
                break;
            }
        } while (true);

        cout << "Enter Product Name: ";
        cin >> products[currentIndex].productName;

        cout << "Enter Product Price: ";
        cin >> products[currentIndex].price;

        cout << "Enter Product Quantity: ";
        cin >> products[currentIndex].quantity;

        currentIndex++;
    }
    else
    {
        cout << "Maximum Records Reached" << endl;
    }
}

void viewProducts(const Product products[], int currentIndex)
{
    cout << "-------------------------------------------------------" << setw(10) << "\nID" << setw(20) << " Name" << setw(15) << " Price" << setw(15) << " Quantity" << endl;
    cout << "-------------------------------------------------------" << endl
        << endl;

    for (int i = 0; i < currentIndex; i++)
    {
        cout << setw(10) << products[i].productId << setw(20) << products[i].productName
            << setw(15) << products[i].price << setw(15) << products[i].quantity << endl;
    }
}

void searchProduct(const Product products[], int currentIndex)
{
    int productCheck;
    cout << "Enter the Product ID of the product you want to check: " << endl;
    cin >> productCheck;
    bool exists = false;
    int i = 0;
    for (i = 0; i < currentIndex; i++)
    {
        if (productCheck == products[i].productId)
        {
            exists = true;
            break;
        }
    }

    if (exists)
    {
        cout << "Product with Product ID: " << productCheck << " exists in record: \n"
            << endl;
        cout << setw(10) << products[i].productId << setw(20) << products[i].productName
            << setw(15) << products[i].price << setw(15) << products[i].quantity << "\n"
            << endl;
    }
    else
    {
        cout << "Product with Product ID: " << productCheck << " does not exist in record.\n"
            << endl;
    }
}

void updateProduct(Product products[], int currentIndex)
{
    int productCheck;
    cout << "Enter the Product ID of the product you want to edit: " << endl;
    cin >> productCheck;
    bool update_record = false;
    int i = 0;
    for (i = 0; i < currentIndex; i++)
    {
        if (productCheck == products[i].productId)
        {
            update_record = true;
            break;
        }
    }
    if (update_record)
    {
        cout << "Enter Product ID: ";
        cin >> products[i].productId;

        cout << "Enter Product Name: ";
        cin >> products[i].productName;

        cout << "Enter Product Price: ";
        cin >> products[i].price;

        cout << "Enter Product Quantity: ";
        cin >> products[i].quantity;

        cout << "Product Record Successfully edited" << endl;
    }
    else
    {
        cout << "Product with Product ID: " << productCheck << " does not exist in record.\n"
            << endl;
    }
}

void deleteProduct(Product products[], int& currentIndex, int maxRecords)
{
    int productCheck;
    bool delete_record = false;
    cout << "Enter the Product ID of the product you want to delete: ";
    cin >> productCheck;
    for (int i = 0; i < currentIndex; i++)
    {
        if (productCheck == products[i].productId)
            delete_record = true;
        {
            for (int j = i; j < maxRecords - 1; j++)
            {
                products[i] = products[i + 1];
            }
        }
        currentIndex--;
        break;
    }
    if (delete_record)
    {
        cout << "Product with Product ID: " << productCheck << " successfully deleted from records. " << endl;
    }
    else
    {
        cout << "Failed to delete Product with Product ID: " << productCheck << ". " << endl;
    }
}

void readProductFile(Product products[], int& currentIndex, int maxRecords)
{
    ifstream fin;
    fin.open("Products.txt");
    try
    {
        if (fin.fail())
            throw runtime_error("Error opening File. Please create file 'Products.txt' and try again.");
    }
    catch (runtime_error& e)
    {
        cout << e.what() << endl;
        return;
    }

    while (!fin.eof())
    {
        fin >> products[currentIndex].productId >> products[currentIndex].productName >> products[currentIndex].price >> products[currentIndex].quantity;

        if (!fin.eof())
        {
            currentIndex++;
        }
    }
    fin.close();
}

void writeProductFile(const Product products[], int currentIndex)
{
    ofstream fout;
    fout.open("Products.txt");

    try
    {
        if (fout.fail())
            throw runtime_error("Error creating file 'Products.txt'");
    }
    catch (runtime_error& e)
    {
        cout << e.what() << endl;
        return;
    }

    for (int i = 0; i < currentIndex; i++)
    {
        fout << setw(10) << left << products[i].productId << setw(20) << left << products[i].productName
            << setw(15) << left << products[i].price << setw(15) << left << products[i].quantity << endl;
    }
    fout.close();
}

bool productIdExists(const Product products[], int currentIndex, int productId)
{
    for (int i = 0; i < currentIndex; i++)
    {
        if (productId == products[i].productId)
        {
            return true;
        }
    }
    return false;
}
