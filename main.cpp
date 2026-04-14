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
    Token::loadID();
    system("clear");
    Token::printImageLogo();
    Token::speak("Welcome to the smart canteen menu.");

    string n;
    cout << BOLD << "👤 Enter Student Name: " << RESET;
    getline(cin, n);
    Student user(n);

    // EXPANDED MENU: 15 Items with Emojis, Stock, and PrepTime (seconds)
    vector<FoodItem> menu = {
        {"🍔 Maharaja Burger", 120.0, 10, 6},
        {"🍕 Cheese Pizza", 180.0, 5, 10},
        {"🥪 Veg Sandwich", 85.0, 12, 4},
        {"☕ Hot Coffee", 40.0, 20, 3},
        {"🍟 French Fries", 60.0, 15, 5},
        {"🍝 Red Sauce Pasta", 140.0, 8, 8},
        {"🥤 Cold Coffee", 55.0, 15, 3},
        {"🍩 Chocolate Donut", 70.0, 10, 2},
        {"🍱 Veg Thali", 210.0, 6, 12},
        {"🍦 Vanilla Cone", 35.0, 25, 2},
        {"🌮 Spicy Taco", 95.0, 10, 5},
        {"🥗 Fresh Salad", 110.0, 7, 4},
        {"🥟 Paneer Momos", 90.0, 12, 7},
        {"🍹 Lemon Iced Tea", 45.0, 20, 3},
        {"🍰 Red Velvet Cake", 130.0, 5, 2}
    };

    Token order;
    int choice;

    while(true) {
        system("clear");
        Token::printImageLogo();
        user.showRole();
        cout << "Welcome, " << BOLD << n << RESET << " | " << CYAN << "Happy Hour (4-5 PM): 15% OFF" << RESET << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << left << setw(4) << "ID" << setw(22) << "Item Name" << setw(15) << "Price" << "Status" << endl;
        cout << "------------------------------------------------------------" << endl;

        for(int i = 0; i < menu.size(); i++) {
            cout << YELLOW << setw(3) << i + 1 << ". " << RESET 
                 << left << setw(21) << menu[i].getName() 
                 << "Rs." << setw(11) << menu[i].getCurrentPrice();
            
            if(menu[i].getStock() == 0) cout << RED << "[SOLD OUT]";
            else if(menu[i].getStock() < 5) cout << RED << "[LOW STOCK]";
            else cout << GREEN << "[AVAILABLE]";
            cout << RESET << endl;
        }
        
        cout << "------------------------------------------------------------" << endl;
        cout << RED << BOLD << " 0. Proceed to Checkout & Pay" << RESET << endl;
        cout << "------------------------------------------------------------" << endl;
        
        cout << "\n👉 Select Item ID to add: ";
        
        // BUFFER FIX: Handle non-integer input and clear buffer
        if(!(cin >> choice)) {
            cin.clear(); // reset error flags
            cin.ignore(1000, '\n'); // discard bad input
            continue;
        }
        
        // Clear the leftover newline so it doesn't skip the next input
        cin.ignore(1000, '\n');

        if(choice == 0) break;

        if(choice > 0 && choice <= menu.size()) {
            if(menu[choice-1].getStock() > 0) {
                order.addItem(menu[choice-1]);
                cout << GREEN << BOLD << "✅ Added " << menu[choice-1].getName() << " to plate!" << RESET << endl;
                Token::speak("Added " + menu[choice-1].getName());
                this_thread::sleep_for(chrono::milliseconds(600)); // Short pause for visual feedback
            } else {
                cout << RED << "❌ Sorry, this item is out of stock!" << RESET << endl;
                this_thread::sleep_for(chrono::seconds(1));
            }
        } else {
            cout << RED << "❌ Invalid Choice! Please pick a number between 1 and " << menu.size() << RESET << endl;
            this_thread::sleep_for(chrono::seconds(1));
        }
    }

    // Process Order
    order.printReceipt();
    
    char confirm;
    cout << "\n" << YELLOW << BOLD << "Staff: Confirm payment received? (y/n): " << RESET;
    cin >> confirm;
    
    if(confirm == 'y' || confirm == 'Y') {
        order.startKitchenAnimation();
    } else {
        cout << RED << BOLD << "\nTransaction Cancelled. Returning items to stock..." << RESET << endl;
        Token::speak("Order cancelled.");
    }

    Token::saveID();
    cout << "\nPress Enter to return to main menu...";
    cin.ignore(); 
    cin.get();
    
    return 0;
}
