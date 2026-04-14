#include "Canteen.h"

void printHeader() {
    cout << CYAN << BOLD;
    cout << "  ____                      _                                " << endl;
    cout << " / ___|__ _ _ __  ___  ___ ___ _ __                         " << endl;
    cout << "| |   / _` | '_ \\/ __|/ _ \\/ _ \\ '_ \\                        " << endl;
    cout << "| |__| (_| | | | \\__ \\  __/  __/ | | |                       " << endl;
    cout << " \\____\\__,_|_| |_|___/\\___|\\___|_| |_|                       " << endl;
    cout << "          TOKEN ORDERING SYSTEM v2.0                         " << RESET << endl;
    cout << "------------------------------------------------------------" << endl;
}

int main() {
    Token::loadLastID();
    system("clear");
    printHeader();

    string sName;
    cout << "Please enter your name: ";
    getline(cin, sName);

    Student student(sName);
    student.showRole();

    vector<FoodItem> menu = {
        {"Samosa", 15.00}, {"Masala Dosa", 60.00}, {"Vada Pav", 20.00},
        {"Veg Maggi", 35.00}, {"Cold Coffee", 45.00}, {"Tea", 10.00},
        {"Paneer Roll", 70.00}, {"Veg Thali", 110.00}
    };

    Token currentOrder;
    int choice;

    cout << "\n" << BOLD << "--- TODAY'S SPECIAL MENU ---" << RESET << endl;
    for(int i = 0; i < menu.size(); i++) {
        cout << YELLOW << i+1 << ". " << RESET << left << setw(15) << menu[i].getName() << " Rs. " << menu[i].getPrice() << endl;
    }
    cout << RED << "0. Complete Order" << RESET << endl;

    while (true) {
        cout << "\nAdd Item ID: ";
        cin >> choice;
        if (choice == 0) break;
        if (choice > 0 && choice <= menu.size()) {
            currentOrder.addItem(menu[choice - 1]);
            cout << GREEN << "Added " << menu[choice - 1].getName() << RESET;
        }
    }

    cout << endl;
    Token::showLoading();
    currentOrder.printReceipt();
    currentOrder.saveOrderDetails();
    Token::saveLastID();

    return 0;
}