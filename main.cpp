#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include<limits>
#include<time.h>
#include<ctime>
#define MAX_SIZE 100
using namespace std;

class Service
{
public:
    string name;
    double price;

    Service(string name, double price) : name(name), price(price) {}
};
// Class Customer
class Customer
{
public:
    int booking_id;
    string name;
    string address;
    string phone;
    string from_date;
    string to_date;
    double payment_advance;
    string additionalRequirements;
    double additionalServices;
    double additionalFees;
    string paymentMethod;
    vector<Service> services; // Services requested by the customer
    void inputDetails();
    void saveToFile(ofstream &file);
    void saveCustomerToFile();
    void requestService(const Service &service);
    void displayServices() const;
};
void Customer::inputDetails()
{
    try {
        cout << "\nEnter booking id: ";
        cin >> booking_id;
        if(cin.fail()) {
            cin.clear();
            cin.ignore(std::numeric_limits<streamsize>::max(), '\n'); // Add 'std::' before 'numeric_limits'
            throw invalid_argument("Invalid input for booking id. Please enter a number.");
        }

        cin.ignore();

        cout << "\nEnter Customer Name (First Name): ";
        getline(cin, name);

        cout << "\nEnter Address (only city): ";
        getline(cin, address);

        cout << "\nEnter Phone: ";
        getline(cin, phone);

        cout << "\nEnter From Date: ";
        getline(cin, from_date);

        cout << "\nEnter to  Date: ";
        getline(cin, to_date);

        cout << "\nEnter Advance Payment: ";
        cin >> payment_advance;

        cin.ignore(); // Add this line to ignore the newline character

        cout << "\nEnter Additional Requirements: ";
        getline(cin, additionalRequirements);
        cout << "\nEnter Cost of Additional Services: ";
        cin >> additionalServices;

        cout << "\nEnter Additional Fees: ";
        cin >> additionalFees;

        cin.ignore(); // Ignore the newline character

        cout << "\nEnter Payment Method: ";
        getline(cin, paymentMethod);
    } catch(const invalid_argument& e) {
        cerr << e.what() << '\n';
    }
}
void Customer::saveToFile(ofstream &file)
{
    file << "Booking ID: " << booking_id << "\n";
    file << "Customer Name: " << name << "\n";
    file << "Address: " << address << "\n";
    file << "Phone: " << phone << "\n";
    file << "From Date: " << from_date << "\n";
    file << "To Date: " << to_date << "\n";
    file << "Advance Payment: " << payment_advance << "\n";
    file << "Additional Requirements: " << additionalRequirements << "\n";
}
void Customer::saveCustomerToFile()
{
    ofstream file;
    file.open("customers.txt", ios::app); // Open the file in append mode
    if(!file.is_open()) {
        throw runtime_error("Unable to open file customers.txt");
    }
    file << "Booking ID: " << booking_id << "\n";
    file << "Customer Name: " << name << "\n";
    file << "Address: " << address << "\n";
    file << "Phone: " << phone << "\n";
    file << "From Date: " << from_date << "\n";
    file << "To Date: " << to_date << "\n";
    file << "Advance Payment: " << payment_advance << "\n";
    file << "Additional Requirements: " << additionalRequirements << "\n";
    file << "------------------------\n";
    file.close();
}
void Customer::requestService(const Service &service)
{
    services.push_back(service);
    cout << "\nService " << service.name << " requested successfully.";
}
void Customer::displayServices() const
{
    cout << "\nRequested services: ";
    for (const Service &service : services)
    {
        cout << "\nService: " << service.name << ", Price: " << service.price;
    }
}
class Room
{
public:
    Room addRoom(int rno);
    char type;
    char stype;
    char ac;
    int roomNumber;
    int rent;
    int status;
    Customer cust;
    double dailyRate;
    int daysOccupied;

    static std::vector<Room> rooms; // Replace the array with a vector
    double calculateRoomCharge();
    void searchRoom(int);
    void displayRoom(Room);
    void saveRoomsToFile();
};

std::vector<Room> Room::rooms; // Initialize the static member
double Room::calculateRoomCharge()
{
    return dailyRate * daysOccupied;
}

Room Room::addRoom(int rno)
{
    Room room;
    room.roomNumber = rno;
    cout << "\nType AC/Non-AC (A/N) : ";
    cin >> room.ac;
    cout << "\nType Comfort (S/N) : ";
    cin >> room.type;
    cout << "\nType Size (B/S) : ";
    cin >> room.stype;
    cout << "\nDaily Rent : ";
    cin >> room.rent;
    room.status = 0;

    cout << "\n Room Added Successfully!";
    rooms.push_back(room); // Use push_back to add the room to the vector
    saveRoomsToFile();     // Save rooms to file
    return room;
}

void Room::searchRoom(int rno)
{
    auto it = std::find_if(rooms.begin(), rooms.end(), [&](const Room &room)
                           { return room.roomNumber == rno; });

    if (it != rooms.end())
    {
        cout << "Room Details\n";
        if (it->status == 1)
        {
            cout << "\nRoom is Reserved";
        }
        else
        {
            cout << "\nRoom is available";
        }
        displayRoom(*it);
    }
    else
    {
        throw runtime_error("Room not found");
    }
    
}
void Room::displayRoom(Room tempRoom)
{
    cout << "\nRoom Number: \t" << tempRoom.roomNumber;
    cout << "\nType AC/Non-AC (A/N) " << tempRoom.ac;
    cout << "\nType Comfort (S/N) " << tempRoom.type;
    cout << "\nType Size (B/S) " << tempRoom.stype;
    cout << "\nRent: " << tempRoom.rent;
}
void Room::saveRoomsToFile()
{
    ofstream file;
    file.open("rooms.txt");
    for (const Room &room : rooms)
    {
        file << "Room Number: " << room.roomNumber << "\n";
        file << "Type AC/Non-AC (A/N): " << room.ac << "\n";
        file << "Type Comfort (S/N): " << room.type << "\n";
        file << "Type Size (B/S): " << room.stype << "\n";
        file << "Rent: " << room.rent << "\n";
        file << "Status: " << room.status << "\n";
        file << "------------------------\n";
    }
    file.close();
}
// Class to represent a service or amenity
class Payment {
    private:
    std::string method;
    double amount;
public:
    Payment(std::string method, double amount) : method(method), amount(amount) {}

    void processPayment() {
        if (method == "Cash") {
            // Cash payment (already implemented, skip)
        } else if (method == "Bank Account") {
            std::cout << "Processing Bank Account payment of " << amount << " ETB\n";
            std::cout << "**WARNING:** This is a mock system. Do not use real bank accounts.\n";
            std::cout << "Enter a placeholder confirmation code (for demonstration purposes only): ";
            std::string mockConfirmationCode;
            std::cin >> mockConfirmationCode;

            std::cout << "Simulating admin review...\n";
            // Simulate random verification status (approved, pending, rejected)
            srand(time(NULL)); // Seed random number generator
            int verificationStatus = rand() % 3; // 0=approved, 1=pending, 2=rejected

            switch (verificationStatus) {
                case 0:
                    std::cout << "Payment confirmed! Thank you.\n";
                    break;
                case 1:
                    std::cout << "Payment pending review. You will be notified soon.\n";
                    break;
                case 2:
                    std::cout << "Payment rejected. Please contact support for assistance.\n";
                    break;
            }

        } else if (method == "Mobile Banking") {
            // Placeholder for future electronic payments
            std::cout << "This payment option is currently unavailable.\n";
            std::cout << "Coming soon! We will offer secure electronic payments in the future.\n";
        } else if (method == "Dummy Gateway") {
            std::cout << "Processing Dummy Gateway payment of " << amount << " ETB\n";
            std::cout << "**This is a demonstration of an online payment flow.\n";
            std::cout << "Enter a mock transaction ID: ";
            std::string mockTransactionID;
            std::cin >> mockTransactionID;

            std::cout << "Processing payment...\n";
            // Simulate random payment status (successful, failed)
            srand(time(NULL));
            int paymentStatus = rand() % 2; // 0=successful, 1=failed

            if (paymentStatus == 0) {
                std::cout << "Payment successful! Thank you.\n";
            } else {
                std::cout << "Payment failed. Please try again or contact support.\n";
            }
        } else {
            std::cout << "Invalid payment method\n";
        }
    }

    void generateReceipt() {
        std::ofstream receipt("receipt.txt");
        if (receipt.is_open()) {
            receipt << "Receipt for " << method << " payment of " << amount << " ETB\n";
            receipt.close();
            std::cout << "Generated receipt for " << method << " payment of " << amount << " ETB\n";
        } else {
            std::cout << "Unable to open file for receipt\n";
        }
    }
};
// hotel management class
class HotelMgnt : protected Room
{
public:
    vector<Room> rooms;
    int count = 0;

    void checkIn();
    void getAvailRoom();
    void searchCustomer(std::string); // Change this line
    void checkOutRoom(int);           // Rename this function to have a unique name
    void guestSummaryReport();
    void saveReservationsToFile();
    void manageRooms();
    void checkOut(int roomNum);
    double taxRate;
    void generateReport();
    void addServiceToCustomer(int booking_id, const Service &service);
    void displayCustomerServices(int booking_id); // Add the 'const' keyword here
};
void HotelMgnt::generateReport() {
    for (int i = 0; i < rooms.size(); i++) {
        try {
            rooms[i].cust.saveCustomerToFile();
        } catch(const runtime_error& e) {
            cerr << e.what() << '\n';
            return;
        }
    }
    ofstream file;
    file.open("report.txt");

    for (const Room &room : rooms)
    {
        file << "Room Number: " << room.roomNumber << "\n";
        file << "Type AC/Non-AC (A/N): " << room.ac << "\n";
        file << "Type Comfort (S/N): " << room.type << "\n";
        file << "Type Size (B/S): " << room.stype << "\n";
        file << "Rent: " << room.rent << "\n";
        file << "Status: " << (room.status == 1 ? "Booked" : "Available") << "\n";

        if (room.status == 1)
        {
            file << "Customer Name: " << room.cust.name << "\n";
            file << "Address: " << room.cust.address << "\n";
            file << "Phone: " << room.cust.phone << "\n";
            file << "From Date: " << room.cust.from_date << "\n";
            file << "To Date: " << room.cust.to_date << "\n";
            file << "Advance Payment: " << room.cust.payment_advance << "\n";
            file << "Additional Requirements: " << room.cust.additionalRequirements << "\n";
        }

        file << "------------------------\n";
    }

    file.close();
}
void HotelMgnt::guestSummaryReport()
{
    if (count == 0)
    {
        cout << "\n No Guest in Hotel !!";
    }
    for (int i = 0; i < count; i++)
    {
        if (rooms[i].status == 1)
        {
            cout << "\n Customer First Name : " << rooms[i].cust.name;
            cout << "\n Room Number : " << rooms[i].roomNumber;
            cout << "\n Address (only city) : " << rooms[i].cust.address;
            cout << "\n Phone : " << rooms[i].cust.phone;
            cout << "\n---------------------------------------";
        }
    }
}
void HotelMgnt::addServiceToCustomer(int booking_id, const Service &service)
{
    for (Room &room : rooms)
    {
        if (room.cust.booking_id == booking_id)
        {
            room.cust.requestService(service);
            return;
        }
    }
    cout << "\nCustomer not found.";
}

void HotelMgnt::displayCustomerServices(int booking_id)
{
    for (const Room &room : rooms)
    {
        if (room.cust.booking_id == booking_id)
        {
            room.cust.displayServices();
            return;
        }
    }
    cout << "\nCustomer not found.";
}

// hotel management reservation of room
void HotelMgnt::checkIn()
{
    int i, found = 0, rno;

    cout << "\nEnter Room number : ";
    cin >> rno;
    for (i = 0; i < count; i++)
    {
        if (rooms[i].roomNumber == rno)
        {
            found = 1;
            break;
        }
    }
    if (found == 1)
    {
        if (rooms[i].status == 1)
        {
            cout << "\nRoom is already Booked";
            return;
        }

        rooms[i].cust.inputDetails();
        rooms[i].status = 1;

        // Save the customer details to a file
        rooms[i].cust.saveCustomerToFile();

        cout << "\n Customer Checked-in Successfully..";
    }
}

// hotel management shows available rooms
void HotelMgnt::getAvailRoom()
{
    int i, found = 0;
    for (i = 0; i < count; i++)
    {
        if (rooms[i].status == 0)
        {
            displayRoom(rooms[i]);
            cout << "\n\nPress enter for next room";
            found = 1;
        }
    }
    if (found == 0)
    {
        cout << "\nAll rooms are reserved";
    }
}

// hotel management shows all persons that have booked room
void HotelMgnt::searchCustomer(std::string pname)
{
    int i, found = 0;
    for (i = 0; i < count; i++)
    {
        if (rooms[i].status == 1 && rooms[i].cust.name == pname)
        {
            cout << "\nCustomer Name: " << rooms[i].cust.name;
            cout << "\nRoom Number: " << rooms[i].roomNumber;

            cout << "\n\nPress enter for next record\n";
            found = 1;
        }
    }
    if (found == 0)
    {
        cout << "\nPerson not found.\n";
    }
}

// hotel managemt generates the bill of the expenses
void HotelMgnt::checkOut(int roomNum)
{
    int i, found = 0, days, rno;
    float billAmount = 0;
    for (i = 0; i < count; i++)
    {
        if (rooms[i].status == 1 && rooms[i].roomNumber == roomNum)
        {
            found = 1;
            break;
        }
    }
    if (found == 1)
    {
        cout << "\nEnter Number of Days:\t";
        cin >> days;

        // Calculate the bill for room charges
        billAmount = rooms[i].calculateRoomCharge();

        // Add the cost of requested services to the bill
        for (const Service &service : rooms[i].cust.services)
        {
            billAmount += service.price;
        }

        billAmount += rooms[i].cust.additionalServices + rooms[i].cust.additionalFees;
        billAmount += billAmount * taxRate;

        cout << "\n\t######## CheckOut Details ########\n";
        cout << "\nCustomer Name : " << rooms[i].cust.name;
        cout << "\nRoom Number : " << rooms[i].roomNumber;
        cout << "\nAddress : " << rooms[i].cust.address;
        cout << "\nPhone : " << rooms[i].cust.phone;
        cout << "\nTotal Amount Due : " << billAmount << " /";
        cout << "\nAdvance Paid: " << rooms[i].cust.payment_advance << " /";
        cout << "\n*** Total Payable: " << billAmount - rooms[i].cust.payment_advance << "/ only";
        cout << "\nAdditional Services: " << rooms[i].cust.additionalServices << " /";
        cout << "\nAdditional Fees: " << rooms[i].cust.additionalFees << " /";
        cout << "\nTax: " << billAmount * taxRate << " /";
        cout << "\nPayment Method: " << rooms[i].cust.paymentMethod;
        cout << "\n*** Total Payable: " << billAmount - rooms[i].cust.payment_advance << "/ only";
        rooms[i].status = 0;
    }
}
void HotelMgnt::saveReservationsToFile()
{
    ofstream file;
    file.open("reservations.txt");
    for (int i = 0; i < count; i++)
    {
        if (rooms[i].status == 1)
        {
            file << "Room Number: " << rooms[i].roomNumber << "\n";
            rooms[i].cust.saveToFile(file);
            file << "------------------------\n";
        }
    }
    file.close();
}
// managing rooms (adding and searching available rooms)
void manageRooms()
{
    HotelMgnt hotel;
    int opt, rno, flag = 0;
    char ch;
    Room room; // Move this line here
    do
    {
        cout << "\n### Manage Rooms ###";
        cout << "\n1. Add Room";
        cout << "\n2. Search Room";
        cout << "\n3. Back to Main Menu";
        cout << "\n\nEnter Option: ";
        cin >> opt;

        switch (opt)
        {
        case 1:
            for (int i = 0; i < hotel.count; i++)
            {
                if (hotel.rooms[i].roomNumber == rno)
                {
                    flag = 1;
                }
            }
            if (flag == 1)
            {
                cout << "\nRoom Number is Present.\nPlease enter unique Number";
                flag = 0;
            }
            else
            {
                hotel.rooms.push_back(room.addRoom(rno));
                hotel.count++;
            }
            break;
        case 2:
            cout << "\nEnter room number: ";
            cin >> rno;
            room.searchRoom(rno);
            break;
        case 3:
            // nothing to do
            break;
        default:
            cout << "\nPlease Enter correct option";
            break;
        }
    } while (opt != 3);
}
class Dish {
public:
    std::string name;
    std::string category;
    double price;

    Dish(std::string name, std::string category, double price) : name(name), category(category), price(price) {}
};

class Menu {
public:
    std::vector<Dish> dishes;

    void addDish(std::string dishName, std::string category, double price);
    void searchDishByName(std::string dishName);
    void searchDishByCategory(std::string category);
    void searchDishByPriceRange(double minPrice, double maxPrice);
};

void Menu::addDish(std::string dishName, std::string category, double price) {
    dishes.push_back(Dish(dishName, category, price));
}

void Menu::searchDishByName(std::string dishName) {
    auto it = std::find_if(dishes.begin(), dishes.end(), [&](const Dish &dish) { return dish.name == dishName; });

    if (it != dishes.end()) {
        std::cout << "Dish found: " << it->name << ", Category: " << it->category << ", Price: " << it->price << std::endl;
    } else {
        std::cout << "Dish not found" << std::endl;
    }
}

void Menu::searchDishByCategory(std::string category) {
    bool found = false;
    for (const Dish &dish : dishes) {
        if (dish.category == category) {
            std::cout << "Dish: " << dish.name << ", Price: " << dish.price << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "No dishes found in this category" << std::endl;
    }
}

void Menu::searchDishByPriceRange(double minPrice, double maxPrice) {
    bool found = false;
    for (const Dish &dish : dishes) {
        if (dish.price >= minPrice && dish.price <= maxPrice) {
            std::cout << "Dish: " << dish.name << ", Category: " << dish.category << ", Price: " << dish.price << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "No dishes found in this price range" << std::endl;
    }
}
class Order
{
public:
    std::map<int, std::pair<std::string, std::string>> orders;

    void placeOrder(int orderId, std::string dishName);
    void modifyOrder(int orderId, std::string newDishName);
    void trackOrder(int orderId);
};

void Order::placeOrder(int orderId, std::string dishName)
{
    orders[orderId] = {dishName, "Placed"};
}

void Order::modifyOrder(int orderId, std::string newDishName)
{
    if (orders.find(orderId) != orders.end())
    {
        orders[orderId].first = newDishName;
        std::cout << "Order modified successfully\n";
    }
    else
    {
        std::cout << "Order not found\n";
    }
}
void Order::trackOrder(int orderId)
{
    if (orders.find(orderId) != orders.end())
    {
        std::cout << "Order Status: " << orders[orderId].second << "\n";
    }
    else
    {
        std::cout << "Order not found\n";
    }
}
int main()
{
    class HotelMgnt hm;
    int i, j, opt, rno;
    Menu menu;
    Order order;
    char ch;
    char pname[100];

    do
    {
        cout << "######## Hotel Management #########\n";
        cout << "\n1. Manage Rooms";
        cout << "\n2. Check-In Room";
        cout << "\n3. Available Rooms";
        cout << "\n4. Search Customer";
        cout << "\n5. Check-Out Room";
        cout << "\n6. Guest Summary Report";
        cout << "\n7. Manage Menu";
        cout << "\n8. Place Order";
        cout << "\n9. Modify Order";
        cout << "\n10. Track Order";
        cout << "\n11. Generate Report"; // New option for generating report
        cout << "\n12. Exit";
        cout << "\n\nEnter Option: ";
        cin >> opt;
        int orderId;
        std::string dishName;
        std::string pname;

        switch (opt)
        {
        case 1:
            manageRooms();
            break;
        case 2:
            if (hm.count == 0)
            {
                cout << "\nRooms data is not available.\nPlease add the rooms first.";
            }
            else if (hm.rooms.size() == 0)
            {
                cout << "\nNo rooms are available.\nPlease add rooms first.";
            }
            else
            {
                hm.checkIn();
            }
            break;
        case 3:
            if (hm.count == 0)
            {
                cout << "\nRooms data is not available.\nPlease add the rooms first.";
            }
            else if (hm.rooms.size() == 0)
            {
                cout << "\nNo rooms are available.\nPlease add rooms first.";
            }
            else
            {
                hm.getAvailRoom();
            }
        case 4:
            if (hm.count == 0)
            {
                cout << "\nRooms data is not available.\nPlease add the rooms first.";
            }
            else if (hm.rooms.size() == 0)
            {
                cout << "\nNo rooms are available.\nPlease add rooms first.";
            }
            else
            {
                cout << "Enter Customer Name: ";
                cin >> pname;
                hm.searchCustomer(pname);
            }
            break;
        case 5:
            if (hm.count == 0)
            {
                cout << "\nRooms data is not available.\nPlease add the rooms first.";
            }
            else if (hm.rooms.size() == 0)
            {
                cout << "\nNo rooms are available.\nPlease add rooms first.";
            }
            else
            {
                cout << "Enter Room Number : ";
                cin >> rno;
                hm.checkOut(rno);
            }
            break;
        case 6:
            hm.guestSummaryReport();
            break;
        case 7:
    if (hm.count == 0)
    {
        cout << "\nRooms data is not available.\nPlease add the rooms first.";
    }
    else if (hm.rooms.size() == 0)
    {
        cout << "\nNo rooms are available.\nPlease add rooms first.";
    }
    else
    {
        cout << "\nEnter Dish Name: ";
        cin >> dishName;
        string category; // Declare the variable "category"
        cout << "\nEnter Category: ";
        cin >> category;
        float price; // Declare the variable "price"
        cout << "\nEnter Price: ";
        cin >> price;
        menu.addDish(dishName, category, price); // Pass the category to addDish
    }
    break;
        case 8:
            std::cout << "\nEnter Order Id: ";
            std::cin >> orderId;
            std::cout << "\nEnter Dish Name: ";
            std::cin >> dishName;
            order.placeOrder(orderId, dishName);
            break;
        case 9:
            std::cout << "\nEnter Order Id: ";
            std::cin >> orderId;
            std::cout << "\nEnter New Dish Name: ";
            std::cin >> dishName;
            order.modifyOrder(orderId, dishName);
            break;
        case 10:
            std::cout << "\nEnter Order Id: ";
            std::cin >> orderId;
            order.trackOrder(orderId);
            break;
        case 11:
            hm.generateReport();
            cout << "\nReport generated successfully.";
            break;

            break;
        case 12:
            hm.saveReservationsToFile();
            cout << "\nExiting...";
            break;
        default:
            cout << "\nPlease Enter correct option";
            break;
        }
    } while (opt != 12);
}