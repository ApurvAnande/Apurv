#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Car {
    int id;
    string model;
    string manufacturer;
    int year;
    bool isAvailable;
};

struct Customer {
    int id;
    string name;
    string contact;
};

struct Rental {
    int rentalId;
    int carId;
    int customerId;
    string rentalDate;
    string returnDate;
    bool isReturned;
};

vector<Car> cars;
vector<Customer> customers;
vector<Rental> rentals;

void addCar() {
    Car car;
    cout << "Enter car ID: ";
    cin >> car.id;
    cout << "Enter car model: ";
    cin >> car.model;
    cout << "Enter car manufacturer: ";
    cin >> car.manufacturer;
    cout << "Enter car year: ";
    cin >> car.year;
    car.isAvailable = true;
    cars.push_back(car);
    cout << "Car added successfully!" << endl;
}

void addCustomer() {
    Customer customer;
    cout << "Enter customer ID: ";
    cin >> customer.id;
    cout << "Enter customer name: ";
    cin.ignore(); // To ignore the newline character from the previous input
    getline(cin, customer.name);
    cout << "Enter customer contact: ";
    getline(cin, customer.contact);
    customers.push_back(customer);
    cout << "Customer added successfully!" << endl;
}

void rentCar() {
    int carId, customerId;
    cout << "Enter car ID to rent: ";
    cin >> carId;
    cout << "Enter customer ID: ";
    cin >> customerId;
    bool carFound = false, customerFound = false;

    for (auto &car : cars) {
        if (car.id == carId && car.isAvailable) {
            carFound = true;
            car.isAvailable = false;

            for (auto &customer : customers) {
                if (customer.id == customerId) {
                    customerFound = true;
                    Rental rental;
                    rental.rentalId = rentals.size() + 1;
                    rental.carId = carId;
                    rental.customerId = customerId;
                    cout << "Enter rental date (DD/MM/YYYY): ";
                    cin >> rental.rentalDate;
                    rental.isReturned = false;
                    rentals.push_back(rental);
                    cout << "Car rented successfully!" << endl;
                    break;
                }
            }
            if (!customerFound) {
                cout << "Customer ID not found!" << endl;
                car.isAvailable = true; // Make car available again if customer not found
            }
            break;
        }
    }
    if (!carFound) {
        cout << "Car ID not found or car is not available!" << endl;
    }
}

void returnCar() {
    int rentalId;
    cout << "Enter rental ID to return: ";
    cin >> rentalId;
    bool rentalFound = false;

    for (auto &rental : rentals) {
        if (rental.rentalId == rentalId && !rental.isReturned) {
            rentalFound = true;
            rental.isReturned = true;
            cout << "Enter return date (DD/MM/YYYY): ";
            cin >> rental.returnDate;

            for (auto &car : cars) {
                if (car.id == rental.carId) {
                    car.isAvailable = true;
                    break;
                }
            }
            cout << "Car returned successfully!" << endl;
            break;
        }
    }
    if (!rentalFound) {
        cout << "Rental ID not found or car is already returned!" << endl;
    }
}

void displayAvailableCars() {
    cout << "Available cars:" << endl;
    for (const auto &car : cars) {
        if (car.isAvailable) {
            cout << "ID: " << car.id
                 << ", Model: " << car.model
                 << ", Manufacturer: " << car.manufacturer
                 << ", Year: " << car.year << endl;
        }
    }
}

int main() {
    int choice;

    while (true) {
        cout << "\nCar Rental System Menu" << endl;
        cout << "1. Add Car" << endl;
        cout << "2. Add Customer" << endl;
        cout << "3. Rent Car" << endl;
        cout << "4. Return Car" << endl;
        cout << "5. Display Available Cars" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addCar();
                break;
            case 2:
                addCustomer();
                break;
            case 3:
                rentCar();
                break;
            case 4:
                returnCar();
                break;
            case 5:
                displayAvailableCars();
                break;
            case 6:
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
