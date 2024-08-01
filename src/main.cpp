#include <iostream>
#include <string>
#include <vector>

using namespace std;

class User {
private:
    string name;
    int age;

public:
    // Method to set details from console input
    void setDetailsFromInput() {
        cout << "Enter Name: ";
        getline(cin, name); // Use getline to allow spaces in the name
        cout << "Enter Age: ";
        cin >> age;
        cin.ignore(); // Ignore leftover newline character in the input buffer
    }

    // Method to display user information
    void displayInfo() const {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
    }

    // Method to set details using this pointer
    void setDetails(const string& userName, int userAge) {
        this->name = userName;
        this->age = userAge;
    }
};

class Tracker {
private:
    vector<string> activities;

public:
    // Method to log activities from console input
    void logActivitiesFromInput() {
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

    // Method to display activities
    void displayActivities() const {
        cout << "Logged Activities:" << endl;
        for (const auto& activity : activities) {
            cout << activity << endl;
        }
    }

    // Method to add an activity using this pointer
    void addActivity(const string& activity) {
        this->activities.push_back(activity);
    }
};

int main() {
    const int userCount = 3; // Number of users
    User users[userCount];   // Array of User objects
    Tracker tracker;

    // Set user details from input
    for (int i = 0; i < userCount; ++i) {
        cout << "\nEnter details for User " << i + 1 << ":\n";
        users[i].setDetailsFromInput();
    }

    // Display user details
    for (int i = 0; i < userCount; ++i) {
        cout << "\nDetails of User " << i + 1 << ":\n";
        users[i].displayInfo();
    }

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
                for (int i = 0; i < userCount; ++i) {
                    cout << "\nDetails of User " << i + 1 << ":\n";
                    users[i].displayInfo();
                }
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
