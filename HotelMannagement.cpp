#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 
using namespace std;

// Customer Class
class Customer {
private:
    string name;
    string address;
    string phone;
    string fromDate;
    string toDate;
    float paymentAdvance;
    int bookingId;

public:
    Customer() : paymentAdvance(0.0), bookingId(0) {}

    void inputDetails() {
        cout << "\nEnter Booking ID: ";
        cin >> bookingId;
        cout << "Enter Customer Name (First Name): ";
        cin >> name;
        cout << "Enter Address (City): ";
        cin >> address;
        cout << "Enter Phone: ";
        cin >> phone;
        cout << "Enter From Date: ";
        cin >> fromDate;
        cout << "Enter To Date: ";
        cin >> toDate;
        cout << "Enter Advance Payment: ";
        cin >> paymentAdvance;
    }

    void displayDetails() const {
        cout << "\nCustomer Name: " << name;
        cout << "\nAddress: " << address;
        cout << "\nPhone: " << phone;
        cout << "\nBooking ID: " << bookingId;
        cout << "\nPayment Advance: " << paymentAdvance;
    }

    string getName() const { return name; }
    float getPaymentAdvance() const { return paymentAdvance; }
};

// Room Class
class Room {
private:
    int roomNumber;
    string type;      // AC or Non-AC
    string comfort;   // Standard or Non-standard
    string size;      // Big or Small
    int rent;
    bool isOccupied;
    Customer customer;

public:
    Room(int roomNo, string acType, string comfortLevel, string roomSize, int dailyRent)
        : roomNumber(roomNo), type(acType), comfort(comfortLevel), size(roomSize),
          rent(dailyRent), isOccupied(false) {}

    void displayRoomInfo() const {
        cout << "\nRoom Number: " << roomNumber;
        cout << "\nType: " << (type == "A" ? "AC" : "Non-AC");
        cout << "\nComfort: " << (comfort == "S" ? "Standard" : "Non-standard");
        cout << "\nSize: " << (size == "B" ? "Big" : "Small");
        cout << "\nRent: " << rent;
        cout << "\nStatus: " << (isOccupied ? "Occupied" : "Available");
    }

    int getRoomNumber() const { return roomNumber; }
    int getRent() const { return rent; }
    bool getStatus() const { return isOccupied; }

    void checkIn(const Customer &cust) {
        customer = cust;
        isOccupied = true;
        cout << "\nCustomer checked in successfully.\n";
    }

    void checkOut(int days) {
        float billAmount = days * rent;
        cout << "\n\t######## CheckOut Details ########\n";
        customer.displayDetails();
        cout << "\nRoom Number: " << roomNumber;
        cout << "\nTotal Amount Due: " << billAmount;
        cout << "\nAdvance Paid: " << customer.getPaymentAdvance();
        cout << "\n*** Total Payable: " << billAmount - customer.getPaymentAdvance() << " only\n";
        isOccupied = false;
    }

    const Customer& getCustomer() const { return customer; }
};

// Hotel Management Class
class HotelManagement {
private:
    vector<Room> rooms;

public:
    void addRoom() {
        int roomNumber, rent;
        string acType, comfort, size;
        cout << "\nEnter Room Number: ";
        cin >> roomNumber;
        if (find_if(rooms.begin(), rooms.end(), [&roomNumber](const Room &r) {
            return r.getRoomNumber() == roomNumber;
        }) != rooms.end()) {
            cout << "Room already exists. Enter a unique room number.\n";
            return;
        }

        cout << "Type AC/Non-AC (A/N): ";
        cin >> acType;
        cout << "Type Comfort (S/N): ";
        cin >> comfort;
        cout << "Type Size (B/S): ";
        cin >> size;
        cout << "Daily Rent: ";
        cin >> rent;

        rooms.emplace_back(roomNumber, acType, comfort, size, rent);
        cout << "\nRoom Added Successfully!\n";
    }

    void searchRoom(int roomNumber) const {
        auto it = find_if(rooms.begin(), rooms.end(), [&roomNumber](const Room &r) {
            return r.getRoomNumber() == roomNumber;
        });

        if (it != rooms.end()) {
            cout << "\nRoom Found:\n";
            it->displayRoomInfo();
        } else {
            cout << "\nRoom not found.\n";
        }
    }

    void getAvailableRooms() const {
        bool found = false;
        cout << "\nAvailable Rooms:\n";
        for (const auto &room : rooms) {
            if (!room.getStatus()) {
                room.displayRoomInfo();
                cout << "\n--------------------------------";
                found = true;
            }
        }
        if (!found) {
            cout << "\nNo available rooms.\n";
        }
    }

    void checkInRoom() {
        int roomNumber;
        cout << "\nEnter Room Number for Check-In: ";
        cin >> roomNumber;
        auto it = find_if(rooms.begin(), rooms.end(), [&roomNumber](Room &r) {
            return r.getRoomNumber() == roomNumber;
        });

        if (it != rooms.end() && !it->getStatus()) {
            Customer cust;
            cust.inputDetails();
            it->checkIn(cust);
        } else {
            cout << "\nRoom is either occupied or not available.\n";
        }
    }

    void checkOutRoom() {
        int roomNumber, days;
        cout << "\nEnter Room Number for Check-Out: ";
        cin >> roomNumber;
        cout << "Enter Number of Days Stayed: ";
        cin >> days;
        auto it = find_if(rooms.begin(), rooms.end(), [&roomNumber](Room &r) {
            return r.getRoomNumber() == roomNumber;
        });

        if (it != rooms.end() && it->getStatus()) {
            it->checkOut(days);
        } else {
            cout << "\nRoom is either not occupied or does not exist.\n";
        }
    }

    void guestSummaryReport() const {
        bool found = false;
        cout << "\nGuest Summary Report:\n";
        for (const auto &room : rooms) {
            if (room.getStatus()) {
                room.displayRoomInfo();
                cout << "\nGuest Details:";
                room.getCustomer().displayDetails();
                cout << "\n--------------------------------";
                found = true;
            }
        }
        if (!found) {
            cout << "\nNo guests in the hotel currently.\n";
        }
    }
};

// Main Function
int main() {
    HotelManagement hm;
    int option;

    do {
        cout << "\n######## Hotel Management ########\n";
        cout << "1. Add Room\n";
        cout << "2. Search Room\n";
        cout << "3. Available Rooms\n";
        cout << "4. Check-In Room\n";
        cout << "5. Check-Out Room\n";
        cout << "6. Guest Summary Report\n";
        cout << "7. Exit\n";
        cout << "Enter Option: ";
        cin >> option;

        switch (option) {
        case 1:
            hm.addRoom();
            break;
        case 2: {
            int roomNumber;
            cout << "Enter Room Number to Search: ";
            cin >> roomNumber;
            hm.searchRoom(roomNumber);
            break;
        }
        case 3:
            hm.getAvailableRooms();
            break;
        case 4:
            hm.checkInRoom();
            break;
        case 5:
            hm.checkOutRoom();
            break;
        case 6:
            hm.guestSummaryReport();
            break;
        case 7:
            cout << "Thank you for using the hotel management system!\n";
            break;
        default:
            cout << "Please enter a valid option.\n";
        }
    } while (option != 7);

    return 0;
}
