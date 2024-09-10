#include <iostream>
#include <string>
#include <vector>

using namespace std;

class User {
private:
    string name;
    int age;
    static int userCount;

public:
    User() {
        userCount++;
    }

    ~User() {
        userCount--;
    }

    string getName() const {
        return name;
    }

    void setName(const string& newName) {
        name = newName;
    }

    int getAge() const {
        return age;
    }

    void setAge(int newAge) {
        age = newAge;
    }

    void setDetailsFromInput() {
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Age: ";
        cin >> age;
        cin.ignore();
    }

    void displayInfo() const {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
    }

    static int getUserCount() {
        return userCount;
    }
};

int User::userCount = 0;

class Tracker {
private:
    vector<string> activities;
    static int totalActivities;

public:
    vector<string> getActivities() const {
        return activities;
    }

    void setActivities(const vector<string>& newActivities) {
        activities = newActivities;
    }

    void logActivitiesFromInput() {
        string activity;
        char more;
        do {
            cout << "Enter Activity: ";
            getline(cin, activity);
            activities.push_back(activity);
            totalActivities++;
            cout << "Add more activities? (y/n): ";
            cin >> more;
            cin.ignore();
        } while (more == 'y' || more == 'Y');
    }

    void displayActivities() const {
        cout << "Logged Activities:" << endl;
        for (const auto& activity : activities) {
            cout << activity << endl;
        }
    }

    static int getTotalActivities() {
        return totalActivities;
    }
};

int Tracker::totalActivities = 0;

int main() {
    vector<User*> users; 
    Tracker* tracker = new Tracker;

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
                User* newUser = new User();
                newUser->setDetailsFromInput();
                users.push_back(newUser);
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
                    delete user;
                }
                delete tracker;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}