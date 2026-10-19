# Vehicle Rental and Fleet Management System

A console-based **Vehicle Rental and Fleet Management System** developed in **C++**, implementing core **Object-Oriented Programming (OOP)** principles. This system allows users to manage a vehicle fleet (Cars, Bikes, Trucks), register customers, handle rental transactions, process vehicle returns, and calculate pricing dynamically in Indian Rupees (INR).

---

## Features

* **Fleet Management:** View all available and rented vehicles in the fleet categorized by type.
* **Polymorphic Rental Pricing:** Custom rental calculations and surcharges based on vehicle type (e.g., passenger capacity surcharges for cars, heavy load weight surcharges for trucks).
* **Customer Registration:** Maintain structured records of customers with unique IDs and contact information.
* **Transaction Logging:** Track every rental transaction with unique reference IDs and total cost breakdowns.
* **Return Processing:** Seamlessly update vehicle availability status upon return.

---

## Object-Oriented Programming (OOP) Principles

1. **Encapsulation:** Data members (such as `dailyRateINR`, `isAvailable`, `vehicleId`) are kept `protected` or `private` within classes, accessed and modified safely via getter and setter methods.
2. **Abstraction:** Uses an abstract base class (`Vehicle`) with pure virtual functions (`displayDetails()` and `calculateRentalCost()`) to define a standard interface for all vehicle types.
3. **Inheritance:** Specialized vehicle classes (`Car`, `Bike`, `Truck`) inherit common attributes and behavior from the base `Vehicle` class.
4. **Polymorphism:** Runtime polymorphism via smart pointers (`std::shared_ptr<Vehicle>`) allows dynamic dispatch of specialized vehicle behaviors and cost calculations.

---

## Prerequisites

To compile and run this project, you will need:
* A C++ compiler supporting **C++11** or higher (such as `g++` via MinGW on Windows, Clang on macOS, or GCC on Linux).
* Visual Studio Code (optional, for code editing and integrated terminal usage).

---

## How to Compile and Run

1. Clone or download this repository to your local machine.
2. Open your terminal or command prompt and navigate to the project directory.
3. Compile the source code using `g++`:
   ```bash
   g++ -std=c++11 main.cpp -o fleet_system
