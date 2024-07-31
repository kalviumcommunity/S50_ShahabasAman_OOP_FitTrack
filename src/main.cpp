#include <iostream>
#include <string>
#include <vector>

using namespace std;

class User {
public:
    void setDetailsFromInput(); // Method to set details from console input
    void displayInfo(); // Method to display user information
    
private:
    string name;
    int age;
};

void User::setDetailsFromInput() {
    cout << "Enter Name: ";
    getline(cin, name); // Use getline to allow spaces in the name
    cout << "Enter Age: ";
    cin >> age;
    cin.ignore(); // Ignore leftover newline character in the input buffer
}

void User::displayInfo() {
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
}

class Tracker {
public:
    void logActivitiesFromInput(); // New method to log activities from console input
    void displayActivities(); // Existing method to display activities
    
private:
    vector<string> activities;
};

void Tracker::logActivitiesFromInput() {
    string activity;
    char more;
    do {
        cout << "Enter Activity: ";
        getline(cin, activity);
        activities.push_back(activity);
        cout << "Add more activities? (y/n): ";
        cin >> more;
        cin.ignore(); // Ignore leftover newline character in the input buffer
    } while (more == 'y' || more == 'Y');
}

void Tracker::displayActivities() {
    cout << "Logged Activities:" << endl;
    for (const auto& activity : activities) {
        cout << activity << endl;
    }
}

int main() {
    User user1;
    Tracker tracker;

    // Set user details from input
    user1.setDetailsFromInput();
    user1.displayInfo();

    // Log activities from input
    tracker.logActivitiesFromInput();
    tracker.displayActivities();

    while (true) {
        int choice;
        cout << "\nMenu:\n";
        cout << "1. View Profile\n";
        cout << "2. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Ignore leftover newline character in the input buffer

        switch (choice) {
            case 1:
                user1.displayInfo();
                tracker.displayActivities();
                break;
            case 2:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
