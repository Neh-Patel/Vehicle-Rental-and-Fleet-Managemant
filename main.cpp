#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <iomanip>

using namespace std;

// ==========================================
// CLEAN UI HELPERS
// ==========================================
void printHeader(const string& title) {
    cout << "\n--------------------------------------------------------\n";
    cout << " " << title << "\n";
    cout << "--------------------------------------------------------\n";
}

void printSuccess(const string& msg) {
    cout << "[SUCCESS] " << msg << endl;
}

void printError(const string& msg) {
    cout << "[ERROR] " << msg << endl;
}

// ==========================================
// 1. ABSTRACT BASE CLASS
// ==========================================
class Vehicle {
protected:
    string vehicleId;
    string brand;
    string model;
    double dailyRateINR; // Converted to INR
    bool isAvailable;
    double mileage;

public:
    Vehicle(string id, string b, string m, double rate, double miles)
        : vehicleId(id), brand(b), model(m), dailyRateINR(rate), isAvailable(true), mileage(miles) {}

    virtual ~Vehicle() {}

    virtual void displayDetails() const = 0;
    virtual double calculateRentalCost(int days) const = 0;

    string getVehicleId() const { return vehicleId; }
    bool getAvailability() const { return isAvailable; }
    void setAvailability(bool status) { isAvailable = status; }
    double getDailyRate() const { return dailyRateINR; }
};

// ==========================================
// 2. DERIVED CLASSES (Inheritance & Polymorphism)
// ==========================================

class Car : public Vehicle {
private:
    int seatingCapacity;
    bool hasAC;

public:
    Car(string id, string b, string m, double rate, double miles, int seats, bool ac)
        : Vehicle(id, b, m, rate, miles), seatingCapacity(seats), hasAC(ac) {}

    void displayDetails() const override {
        cout << "[Car] ID: " << setw(6) << left << vehicleId 
             << "| " << brand << " " << model 
             << " | Seats: " << seatingCapacity 
             << " | AC: " << (hasAC ? "Yes" : "No")
             << " | Rate: Rs. " << fixed << setprecision(2) << dailyRateINR << "/day"
             << " | Status: " << (isAvailable ? "Available" : "Rented") << endl;
    }

    double calculateRentalCost(int days) const override {
        double cost = dailyRateINR * days;
        if (seatingCapacity > 5) cost *= 1.15; // 15% surcharge for large cars
        return cost;
    }
};

class Bike : public Vehicle {
private:
    int engineCapacityCC;

public:
    Bike(string id, string b, string m, double rate, double miles, int cc)
        : Vehicle(id, b, m, rate, miles), engineCapacityCC(cc) {}

    void displayDetails() const override {
        cout << "[Bike] ID: " << setw(5) << left << vehicleId 
             << "| " << brand << " " << model 
             << " | Engine: " << engineCapacityCC << " CC"
             << " | Rate: Rs. " << fixed << setprecision(2) << dailyRateINR << "/day"
             << " | Status: " << (isAvailable ? "Available" : "Rented") << endl;
    }

    double calculateRentalCost(int days) const override {
        return dailyRateINR * days;
    }
};

class Truck : public Vehicle {
private:
    double loadCapacityTons;

public:
    Truck(string id, string b, string m, double rate, double miles, double load)
        : Vehicle(id, b, m, rate, miles), loadCapacityTons(load) {}

    void displayDetails() const override {
        cout << "[Truck] ID: " << setw(5) << left << vehicleId 
             << "| " << brand << " " << model 
             << " | Load: " << loadCapacityTons << " Tons"
             << " | Rate: Rs. " << fixed << setprecision(2) << dailyRateINR << "/day"
             << " | Status: " << (isAvailable ? "Available" : "Rented") << endl;
    }

    double calculateRentalCost(int days) const override {
        return (dailyRateINR * days) + (loadCapacityTons * 3800.0); // Adjusted heavy load surcharge in INR
    }
};

// ==========================================
// 3. SUPPORTING CLASSES
// ==========================================

class Customer {
private:
    string customerId;
    string name;
    string contactNumber;

public:
    Customer(string id, string n, string contact)
        : customerId(id), name(n), contactNumber(contact) {}

    string getCustomerId() const { return customerId; }
    string getName() const { return name; }

    void displayCustomer() const {
        cout << "ID: " << setw(8) << left << customerId 
             << " | Name: " << setw(20) << left << name 
             << " | Contact: " << contactNumber << endl;
    }
};

class RentalTransaction {
private:
    string transactionId;
    string vehicleId;
    string customerId;
    int rentalDays;
    double totalCost;

public:
    RentalTransaction(string tId, string vId, string cId, int days, double cost)
        : transactionId(tId), vehicleId(vId), customerId(cId), rentalDays(days), totalCost(cost) {}

    void displayTransaction() const {
        cout << "TXN ID: " << setw(8) << left << transactionId 
             << " | Vehicle: " << setw(6) << left << vehicleId 
             << " | Customer: " << setw(8) << left << customerId 
             << " | Days: " << setw(3) << left << rentalDays 
             << " | Cost: Rs. " << fixed << setprecision(2) << totalCost << endl;
    }
};

// ==========================================
// 4. FLEET MANAGER CLASS
// ==========================================

class FleetManager {
private:
    vector<shared_ptr<Vehicle>> vehicles;
    vector<Customer> customers;
    vector<RentalTransaction> transactions;

public:
    void addVehicle(shared_ptr<Vehicle> v) {
        vehicles.push_back(v);
    }

    void registerCustomer(const Customer& c) {
        customers.push_back(c);
        printSuccess("Customer successfully registered!");
    }

    void displayAllVehicles() const {
        printHeader("ALL FLEET VEHICLES");
        if (vehicles.empty()) {
            cout << "No vehicles in the fleet.\n";
            return;
        }
        for (const auto& v : vehicles) {
            v->displayDetails();
        }
    }

    void displayAvailableVehicles() const {
        printHeader("AVAILABLE VEHICLES FOR RENT");
        bool found = false;
        for (const auto& v : vehicles) {
            if (v->getAvailability()) {
                v->displayDetails();
                found = true;
            }
        }
        if (!found) cout << "No vehicles currently available.\n";
    }

    void rentVehicle(string vId, string cId, int days) {
        shared_ptr<Vehicle> targetVehicle = nullptr;
        for (auto& v : vehicles) {
            if (v->getVehicleId() == vId) {
                targetVehicle = v;
                break;
            }
        }

        if (!targetVehicle) {
            printError("Vehicle ID not found.");
            return;
        }

        if (!targetVehicle->getAvailability()) {
            printError("Vehicle is already rented out.");
            return;
        }

        bool customerExists = false;
        for (const auto& c : customers) {
            if (c.getCustomerId() == cId) {
                customerExists = true;
                break;
            }
        }

        if (!customerExists) {
            printError("Customer ID not found. Please register customer first.");
            return;
        }

        double cost = targetVehicle->calculateRentalCost(days);
        targetVehicle->setAvailability(false);

        string tId = "TXN-" + to_string(transactions.size() + 1);
        transactions.emplace_back(tId, vId, cId, days, cost);

        printHeader("RENTAL CONFIRMATION");
        printSuccess("Vehicle rented successfully!");
        cout << "  Total Cost: Rs. " << fixed << setprecision(2) << cost << endl;
        cout << "  Transaction Reference ID: " << tId << endl;
    }

    void returnVehicle(string vId) {
        for (auto& v : vehicles) {
            if (v->getVehicleId() == vId) {
                if (v->getAvailability()) {
                    printError("Vehicle was not marked as rented.");
                    return;
                }
                v->setAvailability(true);
                printSuccess("Vehicle " + vId + " successfully returned and marked available.");
                return;
            }
        }
        printError("Vehicle ID not found.");
    }

    void displayTransactions() const {
        printHeader("RENTAL TRANSACTION LOGS");
        if (transactions.empty()) {
            cout << "No rental transactions recorded yet.\n";
            return;
        }
        for (const auto& t : transactions) {
            t.displayTransaction();
        }
    }
};

// ==========================================
// 5. DRIVER PROGRAM
// ==========================================

int main() {
    FleetManager manager;

    // Preload sample fleet items with rates in Indian Rupees (INR)
    manager.addVehicle(make_shared<Car>("C001", "Toyota", "Camry", 5250.0, 12000, 5, true));
    manager.addVehicle(make_shared<Bike>("B001", "Yamaha", "MT-15", 2850.0, 2500, 155));
    manager.addVehicle(make_shared<Truck>("T001", "Ford", "F-150", 11850.0, 18000, 3.5));

    manager.registerCustomer(Customer("CU001", "Aarav Sharma", "9876543210"));
    manager.registerCustomer(Customer("CU002", "Priya Patel", "9123456780"));

    int choice;
    do {
        cout << "\n========================================================\n";
        cout << "          VEHICLE RENTAL & FLEET MANAGEMENT             \n";
        cout << "========================================================\n";
        cout << " 1. Display All Fleet Vehicles\n";
        cout << " 2. Display Available Vehicles\n";
        cout << " 3. Register New Customer\n";
        cout << " 4. Rent a Vehicle\n";
        cout << " 5. Return a Vehicle\n";
        cout << " 6. View Rental Transaction Logs\n";
        cout << " 7. Exit System\n";
        cout << "--------------------------------------------------------\n";
        cout << "Enter your choice (1-7): ";
        cin >> choice;

        switch (choice) {
            case 1:
                manager.displayAllVehicles();
                break;
            case 2:
                manager.displayAvailableVehicles();
                break;
            case 3: {
                printHeader("CUSTOMER REGISTRATION");
                string id, name, contact;
                cout << "Enter Customer ID (e.g., CU003): ";
                cin >> id;
                cout << "Enter Full Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Contact Number: ";
                cin >> contact;
                manager.registerCustomer(Customer(id, name, contact));
                break;
            }
            case 4: {
                printHeader("VEHICLE RENTAL PORTAL");
                string vId, cId;
                int days;
                cout << "Enter Vehicle ID to rent (e.g., C001, B001): ";
                cin >> vId;
                cout << "Enter Customer ID (e.g., CU001): ";
                cin >> cId;
                cout << "Enter Number of Rental Days: ";
                cin >> days;
                manager.rentVehicle(vId, cId, days);
                break;
            }
            case 5: {
                printHeader("VEHICLE RETURN PORTAL");
                string vId;
                cout << "Enter Vehicle ID to return: ";
                cin >> vId;
                manager.returnVehicle(vId);
                break;
            }
            case 6:
                manager.displayTransactions();
                break;
            case 7:
                cout << "\nThank you for using the Fleet Management System. Goodbye!\n";
                break;
            default:
                printError("Invalid choice. Please select between 1 and 7.");
        }
    } while (choice != 7);

    return 0;
}