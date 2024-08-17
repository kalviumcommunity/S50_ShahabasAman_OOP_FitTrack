#include <iostream>
#include <string>
#include <vector>

using namespace std;

class User {
private:
    string name;
    int age;
    static int userCount; // Static variable to count the number of User objects

public:
    User() {
        userCount++; // Increment the count whenever a new User object is created
    }

    ~User() {
        userCount--; // Decrement the count whenever a User object is destroyed
    }

    // Method to set details from console input
    void setDetailsFromInput() {
        cout << "Enter Name: ";
        getline(cin, name); 
        cout << "Enter Age: ";
        cin >> age;
        cin.ignore(); 
    }

    // Method to display user information
    void displayInfo() const {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
    }

    // Static method to get the current user count
    static int getUserCount() {
        return userCount;
    }
};

// Definition of static variable
int User::userCount = 0;

class Tracker {
private:
    vector<string> activities;
    static int totalActivities; // Static variable to keep track of total activities

public:
    // Method to log activities from console input
    void logActivitiesFromInput() {
        string activity;
        char more;
        do {
            cout << "Enter Activity: ";
            getline(cin, activity);
            activities.push_back(activity);
            totalActivities++; // Increment the total activities count
            cout << "Add more activities? (y/n): ";
            cin >> more;
            cin.ignore(); 
        } while (more == 'y' || more == 'Y');
    }

    // Method to display activities
    void displayActivities() const {
        cout << "Logged Activities:" << endl;
        for (const auto& activity : activities) {
            cout << activity << endl;
        }
    }

    // Static method to get the total number of activities logged
    static int getTotalActivities() {
        return totalActivities;
    }
};

// Definition of static variable
int Tracker::totalActivities = 0;

int main() {
    vector<User*> users; // Vector to hold pointers to User objects
    Tracker* tracker = new Tracker; // Dynamically allocate Tracker object

    while (true) {
        int choice;
        cout << "\nMenu:\n";
        cout << "1. Add a new User\n";
        cout << "2. Log Activities\n";
        cout << "3. View Profile and Activities\n";
        cout << "4. View User and Activity Counts\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                User* newUser = new User(); // Create a new User object
                newUser->setDetailsFromInput();
                users.push_back(newUser); // Add the new user to the vector
                break;
            }
            case 2:
                tracker->logActivitiesFromInput();
                break;
            case 3:
                for (int i = 0; i < users.size(); ++i) {
                    cout << "\nDetails of User " << i + 1 << ":\n";
                    users[i]->displayInfo();
                }
                tracker->displayActivities();
                break;
            case 4:
                cout << "Total Users: " << User::getUserCount() << endl;
                cout << "Total Activities Logged: " << Tracker::getTotalActivities() << endl;
                break;
            case 5:
                cout << "Exiting..." << endl;
                for (User* user : users) {
                    delete user; // Free the memory allocated for each user
                }
                delete tracker; // Free the memory allocated for tracker
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
