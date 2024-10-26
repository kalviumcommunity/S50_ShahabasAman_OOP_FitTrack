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

    User(const string& newName, int newAge) {
        name = newName;
        age = newAge;
        userCount++;
    }

    virtual ~User() {
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
    Tracker() {}

    ~Tracker() {}


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

class Member : public User {
private:
    string membershipType;

public:
    Member() : User() {
        membershipType = "Basic";
    }

    Member(const string& name, int age, const string& type)
        : User(name, age), membershipType(type) {}

    string getMembershipType() const {
        return membershipType;
    }

    void setMembershipType(const string& type) {
        membershipType = type;
    }

    void displayInfo() const {
        User::displayInfo(); 
        cout << "Membership Type: " << membershipType << endl;
    }
};

class PremiumMember : public Member {
private:
    string premiumBenefits;

public:
    PremiumMember() : Member() {
        premiumBenefits = "Extended access to all fitness programs.";
    }
    PremiumMember(const string& name, int age, const string& type, const string& benefits)
        : Member(name, age, type), premiumBenefits(benefits) {}

    void displayInfo() const {
        Member::displayInfo();  
        cout << "Premium Benefits: " << premiumBenefits << endl;
    }
};

int main() {
    vector<User*> users; 
    Tracker* tracker = new Tracker;

    while (true) {
        int choice;
        cout << "\nMenu:\n";

        cout << "1. Add a Basic User\n";
        cout << "2. Add a Premium Member\n";
        cout << "3. Log Activities\n";
        cout << "4. View Profile and Activities\n";
        cout << "5. View User and Activity Counts\n";
        cout << "6. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                Member* newBasicUser = new Member();
                newBasicUser->setDetailsFromInput();
                users.push_back(newBasicUser);
                break;
            }

            case 2: {
                PremiumMember* newPremiumUser = new PremiumMember();
                newPremiumUser->setDetailsFromInput();
                newPremiumUser->setMembershipType("Premium");
                users.push_back(newPremiumUser);
                break;
            }
            case 3:
                for (int i = 0; i < users.size(); ++i) {
                    cout << "\nDetails of User " << i + 1 << ":\n";

                    PremiumMember* premiumUser = dynamic_cast<PremiumMember*>(users[i]);
                    Member* basicUser = dynamic_cast<Member*>(users[i]);

                    if (premiumUser) {
                        premiumUser->displayInfo();
                    } else if (basicUser) {
                        basicUser->displayInfo();
                    } else {
                        users[i]->displayInfo();
                    }
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