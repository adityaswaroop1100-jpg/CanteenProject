#include "Canteen.h"

int Token::globalID = 100;

void Token::loadID() {
    ifstream f("lastID.txt");
    if(f.is_open()) { f >> globalID; f.close(); }
}

void Token::saveID() {
    ofstream f("lastID.txt");
    if(f.is_open()) { f << globalID; f.close(); }
}

void Token::speak(string msg) {
    // Built-in macOS command
    string cmd = "say \"" + msg + "\" &";
    system(cmd.c_str());
}

double FoodItem::getCurrentPrice() const {
    time_t t = time(0);
    tm* now = localtime(&t);
    // Happy Hour: 4-5 PM gets 15% discount
    if(now && now->tm_hour == 16) return basePrice * 0.85; 
    return basePrice;
}

void Student::showRole() {
    cout << MAGENTA << BOLD << "[ STUDENT SESSION AUTHORIZED ]" << RESET << endl;
}

void Token::printImageLogo() {
    cout << CYAN << R"(
    _________________________________________
   |                                         |
   |   _______  _______  __    _  _______    |
   |  |       ||   _   ||  |  | ||       |   |
   |  |       ||  |_|  ||   |_| ||    ___|   |
   |  |       ||       ||       ||   |___    |
   |  |      _||       ||  _    ||    ___|   |
   |  |     |_ |   _   || | |   ||   |___    |
   |  |_______||__| |__||_|  |__||_______|   |
   |           SMART CANTEEN v3.0            |
   |_________________________________________|
    )" << RESET << endl;
}

Token::Token() : total(0), wait(0) {
    currentID = ++globalID;
}

void Token::addItem(FoodItem& item) {
    items.push_back(item);
    total += item.getCurrentPrice();
    wait += item.getPrepTime();
    item.reduceStock();
}

void Token::displayQR() {
    cout << WHITE << BOLD << "\n📲 SCAN TO PAY (UPI/WALLET):" << RESET << endl;
    cout << "  ▄▄▄▄▄▄▄  ▄ ▄▄▄▄▄▄▄ " << endl;
    cout << "  █ ▄▄▄ █ ▀█ █ ▄▄▄ █ " << endl;
    cout << "  █ ███ █ █▀ █ ███ █ " << endl;
    cout << "  █▄▄▄▄▄█ █▀ █▄▄▄▄▄█ " << endl;
    cout << "  ▄▄▄ ▄▄▄▄█  ▄▄▄ ▄▄  " << endl;
    cout << "  █ ▄▄▄ █ ▄▀ █ ▄▄▄ █ " << endl;
    cout << "  █ ███ █ █  █ ███ █ " << endl;
    cout << "  █▄▄▄▄▄█ █  █▄▄▄▄▄█ " << endl;
    cout << RESET << "  [ Merchant ID: SRM_CANTEEN_" << currentID << " ]" << endl;
}

void Token::printReceipt() {
    system("clear");
    cout << YELLOW << "========================================" << RESET << endl;
    cout << GREEN << BOLD << "    RECEIPT GENERATED | TOKEN #" << currentID << RESET << endl;
    cout << YELLOW << "========================================" << RESET << endl;
    for(auto &i : items) {
        cout << left << setw(20) << i.getName() << "Rs." << i.getCurrentPrice() << endl;
    }
    cout << "----------------------------------------" << endl;
    cout << BOLD << "TOTAL PAYABLE: Rs." << total << RESET << endl;
    displayQR();
}

void Token::startKitchenAnimation() {
    speak("Payment received. We are preparing your order.");
    int barLen = 30;
    cout << "\n" << BOLD << "👨‍🍳 KITCHEN IS COOKING:" << RESET << endl;
    for (int i = 0; i <= wait; i++) {
        float p = (float)i / wait;
        int pos = barLen * p;
        cout << "\r" << BOLD << "PROGRESS: " << RESET << "[";
        for (int j = 0; j < barLen; ++j) {
            if (j < pos) cout << GREEN << "■" << RESET;
            else cout << " ";
        }
        cout << "] " << int(p * 100.0) << "% | " << YELLOW << wait - i << "s left" << RESET;
        cout.flush();
        this_thread::sleep_for(chrono::seconds(1));
    }
    cout << "\n\n" << GREEN << BOLD << "🔔 ORDER #" << currentID << " IS READY!" << RESET << endl;
    speak("Order " + to_string(currentID) + " is ready for pickup.");
}
