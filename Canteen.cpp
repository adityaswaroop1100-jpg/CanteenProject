#include "Canteen.h"

int Token::globalTokenID = 100;

void Token::loadLastID() {
    ifstream inFile("lastID.txt");
    if (inFile.is_open()) { inFile >> globalTokenID; inFile.close(); }
}

void Token::saveLastID() {
    ofstream outFile("lastID.txt");
    if (outFile.is_open()) { outFile << globalTokenID; outFile.close(); }
}

void Token::showLoading() {
    cout << YELLOW << "Generating your token ";
    for(int i = 0; i < 3; i++) {
        cout << ". ";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    cout << RESET << endl;
}

void Student::showRole() {
    cout << CYAN << BOLD << "\n[ STUDENT ACCESS GRANTED ]" << RESET << endl;
    cout << "Welcome to the Digital Canteen, " << name << "!" << endl;
}

Token::Token() : totalBill(0) {
    currentTokenID = ++globalTokenID;
}

void Token::addItem(FoodItem item) {
    orderedItems.push_back(item);
    totalBill += item.getPrice();
}

void Token::printReceipt() {
    system("clear");
    cout << YELLOW << "====================================" << RESET << endl;
    cout << GREEN << BOLD << "       CANTEEN TOKEN: #" << currentTokenID << RESET << endl;
    cout << YELLOW << "====================================" << RESET << endl;
    
    for (const auto &item : orderedItems) {
        cout << left << setw(20) << item.getName() << "Rs. " << right << setw(6) << item.getPrice() << endl;
    }
    
    cout << "------------------------------------" << endl;
    cout << BOLD << left << setw(20) << "TOTAL BILL :" << GREEN << "Rs. " << right << setw(6) << totalBill << RESET << endl;
    cout << YELLOW << "====================================" << RESET << endl;
    cout << "  Please pay at the pickup counter  " << endl;
    cout << YELLOW << "====================================" << RESET << endl;
}

void Token::saveOrderDetails() {
    ofstream outFile("all_orders.txt", ios::app);
    if (outFile.is_open()) {
        outFile << "Token: #" << currentTokenID << " | Bill: Rs." << totalBill << endl;
        outFile.close();
    }
}