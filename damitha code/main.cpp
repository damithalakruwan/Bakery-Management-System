a#include <iostream>
#include <fstream>

#include <sstream>
using namespace std;

// Function prototypes
void displaySystem();
bool adminAccess();
bool cashierAccess();
void adminportal();
void cashierPortal();
void addItem();
void viewItems();
void deleteItem();
void placeOrder();
void viewBill();
void cashierBill();
void about();

// Global variables
int total = 0;

int main() {
    displaySystem();
    return 0;
}

void displaySystem() {
    while (true) {
        system("cls");
        cout << "    *****************************************\n";
        cout << "    *      WELCOME TO AMBER PASTRY SHOP     *\n";
        cout << "    *****************************************\n\n\n";
        cout << "        ----------MENU-----------\n\n";
        cout << "         [1] Admin System \n";
        cout << "         [2] Cashier System\n";
        cout << "         [3] About Us\n";
        cout << "         [4] Exit\n\n\n";
        cout << "         Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                if (adminAccess()) {
                    adminportal();
                } else {
                    cout << "Admin login failed. Press Enter to continue...";
                    cin.ignore();
                    cin.get();
                }
                break;
            case 2:
                if (cashierAccess()) {
                    cashierPortal();
                } else {
                    cout << "Cashier login failed. Press Enter to continue...";
                    cin.ignore();
                    cin.get();
                }
                break;
            case 3:
                about();
                break;
            case 4:
                exit(0);
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}

bool adminAccess() {
    string username, Password;
    cout << "Admin Access\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> Password;

    if (username == "admin" && Password == "abcd") {
        return true; // Login successful
    } else {
        return false; // Login failed
    }
}

bool cashierAccess() {
    string username, password;
    cout << "Cashier Access\n";
    cout << "Username: ";
    cin >> username;
    cout << "password: ";
    cin >> password;

    if (username == "cashier" && password == "efgh") {
        return true; // Login successful
    } else {
        return false; // Login failed
    }
}

void adminportal() {
    while (true) {
        system("cls");
        cout << "..........ADMIN System.......\n\n\n";
        cout << "[ 1 ] Add pastry and beverage Items\n";
        cout << "[ 2 ] pastry and beverage Items List\n";
        cout << "[ 3 ] Delete foods Items\n";
        cout << "[ 4 ] View Bill Details\n";
        cout << "[ 5 ] Back to Main Menu\n\n\n";
        cout << "Input your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                addItem();
                break;
            case 2:
                viewItems();
                break;
            case 3:
                deleteItem();
                break;
            case 4:
                viewBill();
                break;
            case 5:
                return; // Back to the main menu
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}

void cashierPortal() {
    while (true) {
        system("cls");
        cout << " ......CASHIER System.....\n\n\n";
        cout << "[ 1 ] Place Orders\n";
        cout << "[ 2 ] pastry and beverage Items List\n";
        cout << "[ 3 ] View Balance Information\n";
        cout << "[ 4 ] Back to Main Menu\n\n\n";
        cout << "Input your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                placeOrder();
                break;
            case 2:
                viewItems();
                break;
            case 3:
                cashierBill();
                break;
            case 4:
                return; // Back to the main menu
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}



void cashierBill() {
    ifstream orderFile("order.txt");
    if (!orderFile) {
        cerr << "Failed to open order.txt file.\n";
        return;
    }

    cout << "Cashier balance Information:\n";
    cout << "Item\tQuantity\tTotal\n";
    cout << "--------------------------\n";

    string line;
    while (getline(orderFile, line)) {
        cout << line << endl;
    }

    orderFile.close();
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

void addItem() {
    ofstream file("data.txt", ios::out | ios::app);
    if (!file) {
        cerr << "Failed to open data.txt file.\n";
        return;
    }

    string itemNo, itemName;
    double itemPrice;

    cout << "Enter item Code: ";
    cin >> itemNo;
    cout << "Enter pastry item: ";
    cin.ignore();
    getline(cin, itemName);
    cout << "Enter Price: ";
    cin >> itemPrice;

    file << itemNo << ", " << itemName << ", " << itemPrice << endl;
    file.close();

    cout << "        pastry and beverage  item added successfully!!!!\n\n";
    cout << "                  Press Enter to continue...";
    cin.ignore();
    cin.get();
}

void viewItems() {
    ifstream file("data.txt");
    if (!file) {
        cerr << "Failed to open data.txt file.\n";
        return;
    }

    cout << "pastry and beverage Items List:\n";
    cout << "No\tItem\tPrice\n";
    cout << "--------------------------\n";

    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

void deleteItem() {
    string itemNoToDelete;
    cout << "Insert  the Food item Code you want to delete: ";
    cin >> itemNoToDelete;
    cout<< "\n\n\n";
    ifstream inputFile("data.txt");
    ofstream tempFile("temp.txt");

    if (!inputFile || !tempFile) {
        cerr << "Failed to open files for reading/writing." << endl;
        return;
    }

    string line;
    bool itemFound = false;

    while (getline(inputFile, line)) {
        // Check if the line contains the item number to delete
        if (line.find(itemNoToDelete) == string::npos) {
            tempFile << line << endl;
        } else {
            itemFound = true;
        }
    }

    inputFile.close();
    tempFile.close();

    if (itemFound) {
        remove("data.txt");
        rename("temp.txt", "data.txt");
        cout << "pastry Item with item Code " << itemNoToDelete << " has been successfully deleted.\n";
    } else {
        cout <<"                            soryy!! item Code " << itemNoToDelete << " does not exist in our inventory\n";
    }

    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

void placeOrder() {
    ifstream inputFile("data.txt");
    if (!inputFile) {
        cerr << "Failed to open data.txt file.\n";
        return;
    }

    ofstream orderFile("order.txt", ios::out | ios::app);
    if (!orderFile) {
        cerr << "Failed to open order.txt file.\n";
        return;
    }

    cout << "    Place Your Order\n";
    cout << "--------------------------\n";

    string line;
    int selectedNo;
    double itemPrice, totalPrice = 0.0;
    int quantity;
    string itemNo;

    cout << "\n\n Today Available Food Items:\n\n";
    cout << "No\tItem\tPrice\n";
    cout << "--------------------------\n";

    while (getline(inputFile, line)) {
        cout << line << endl;
    }

    inputFile.clear(); // Reset the file state.
    inputFile.seekg(0); // Move the file pointer to the beginning.

    while (true) {
        cout << "\n\n\n Insert item Codes and press [  1  ] to print Balance): ";
        cin >> selectedNo; // Use the new variable name


        if (selectedNo == 1) {
            break; // Finish order
        }

        bool itemFound = false;

        while (getline(inputFile, line)) {
            stringstream ss(line);
            ss >> itemNo >> itemPrice;
            getline(ss, line);

            if (stoi(itemNo) == selectedNo) {
                itemFound = true;
                break;
            }
        }

        if (!itemFound) {
            cout << "Item not found. Please enter a valid item Code.\n";
            continue;
        }

        cout << "Enter quantity: ";
        cin >> quantity;

        if (quantity <= 0 ) {
            cout << "Invalid quantity. Please enter a valid quantity.\n";
            continue;
        }

        double itemTotal = itemPrice * quantity;
        totalPrice == itemTotal + itemTotal;

        // Write the order details to the order.txt file
        orderFile << "Item: " << itemNo << ", Quantity: " << quantity << ", Total:" << totalPrice << "$" << endl;
    }

    inputFile.close();
    orderFile.close();

    cout << "   Order placed successfully!!!\n\n";
    cout << "Total Balance: $" << totalPrice << endl;
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

void viewBill() {
    ifstream orderFile("order.txt");
    if (!orderFile) {
        cerr << "Failed to open order.txt file.\n";
        return;
    }

    cout << "Order Details:\n";
    cout << "Item\tQuantity\tTotal\n";
    cout << "--------------------------\n";

    string line;
    while (getline(orderFile, line)) {
        cout << line << endl;
    }

    orderFile.close();
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

void about() {
    system("cls");
    cout << "                        =============================================\n";
    cout << "                                       AMBER ONLINE \n";
    cout << "                        =============================================\n\n\n";
    cout << "       At Amber Pastry Shop, we have been crafting delectable pastries and sweets since 2005.\n      Our journey began with a passion for baking and a commitment to using the finest ingredients \n                   to create mouthwatering treats that delight our customers.\n                                    *************************\n\n\n";
    cout << "         Visit Us\n\n";
    cout << "* Amber Pastry Shop - Downtown \n          Address: 123 Main Street \n          Phone: (555) 123-4567 \n* Amber Pastry Shop - Eastside \n          Address: 456 Oak Avenue \n          Phone: (555) 987-6543\n\n\n";
    cout << "Email: info@amberpastryshop.co.uk \nEmail: manchester@amberpastryshop.co.uk\n\n\n";
    cout << "Press Enter to return to the main menu...";
    cin.ignore();
    cin.get();

}
