#ifndef CANTEEN_H
#define CANTEEN_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <thread>
#include <chrono>

using namespace std;

// Colors for Mac Terminal
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define RED     "\033[31m"

class User {
protected:
    string name;
public:
    User(string n) : name(n) {}
    virtual void showRole() = 0;
    virtual ~User() {}
};

class Student : public User {
public:
    Student(string n) : User(n) {}
    void showRole() override;
};

class FoodItem {
private:
    string itemName;
    double price;
public:
    FoodItem(string n, double p) : itemName(n), price(p) {}
    string getName() const { return itemName; }
    double getPrice() const { return price; }
};

class Token {
private:
    static int globalTokenID; 
    int currentTokenID;
    vector<FoodItem> orderedItems;
    double totalBill;

public:
    Token();
    static void loadLastID();
    static void saveLastID();
    void addItem(FoodItem item);
    void printReceipt();
    void saveOrderDetails();
    static void showLoading(); // Special Loading Effect
};

#endif