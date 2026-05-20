#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <limits>

using namespace std;



// Abstract class:
class BaseUser {
public:

    // Pure virtual functions (=0)
    virtual void displayInfo() const = 0;
    virtual void logActivity() = 0;
    virtual void displayActivities() const = 0;

    // Virtual destructor:
    virtual ~BaseUser() {}
};



class Tracker {
private:

    vector<string> activities;

    static int totalActivities;

public:

    void logActivitiesFromInput() {

        string activity;
        char more;

        do {

            cout << "Enter Activity: ";
            getline(cin, activity);

            // Store activity inside vector
            activities.push_back(activity);

            totalActivities++;

            cout << "Add more activities? (y/n): ";
            cin >> more;

            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

        }
        while (more == 'y' || more == 'Y');
    }


    void displayActivities() const {

        if (activities.empty()) {
            cout << "No activities logged.\n";
            return;
        }

        cout << "\nActivities:\n";

        for (const auto& activity : activities) {
            cout << "- " << activity << endl;
        }
    }


    // Accesses static member without creating object
    static int getTotalActivities() {
        return totalActivities;
    }
};


// Static member initialization
int Tracker::totalActivities = 0;


class User : public BaseUser {

private:

    string name;
    int age;

    Tracker tracker;

protected:

    static int userCount;

public:

    // Default constructor
    User()
        : name("Unknown"),
          age(0)
    {
        userCount++;
    }

    // Parameterized constructor
    User(string n, int a)
        : name(n),
          age(a)
    {
        userCount++;
    }

    // Copy constructor
    User(const User& other)
        : name(other.name),
          age(other.age)
    {
        userCount++;
    }

    // Destructor
    virtual ~User() {
        userCount--;
    }

    string getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    void setName(string n) {
        name = n;
    }

    void setAge(int a) {
        age = a;
    }

    void setDetailsFromInput() {

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Age: ";

        // Input validation
        while (!(cin >> age) || age <= 0) {

            cin.clear();

            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

            cout << "Invalid age. Enter again: ";
        }

        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n'
        );
    }


    void displayInfo() const override {

        cout << "Name: "
             << name << endl;

        cout << "Age: "
             << age << endl;
    }


    void logActivity() override {
        tracker.logActivitiesFromInput();
    }


    void displayActivities() const override {
        tracker.displayActivities();
    }


    static int getUserCount() {
        return userCount;
    }
};


int User::userCount = 0;


class Member : public User {

private:

    string membershipType;

public:

    Member()
        : User(),
          membershipType("Basic")
    {}

    Member(
        string n,
        int a,
        string type
    )
        : User(n, a),
          membershipType(type)
    {}

    string getMembershipType() const {
        return membershipType;
    }

    void setMembershipType(string type) {
        membershipType = type;
    }


    void displayInfo() const override {

        User::displayInfo();

        cout << "Membership Type: "
             << membershipType
             << endl;
    }
};



class PremiumMember : public Member {

private:

    string premiumBenefits;

public:

    PremiumMember()
        : Member()
    {
        setMembershipType("Premium");

        premiumBenefits =
            "Extended access to fitness programs";
    }


    PremiumMember(
        string n,
        int a,
        string type,
        string benefits
    )
        : Member(n, a, type),
          premiumBenefits(benefits)
    {}


    void displayInfo() const override {

        Member::displayInfo();

        cout
            << "Premium Benefits: "
            << premiumBenefits
            << endl;
    }
};




int main() {

    // Smart pointer for automatic memory management
    vector<unique_ptr<BaseUser>> users;


    while (true) {

        int choice;

        cout << "\n===== MENU =====\n";

        cout << "1. Add Basic Member\n";
        cout << "2. Add Premium Member\n";
        cout << "3. Log Activities\n";
        cout << "4. View Profiles & Activities\n";
        cout << "5. View Counts\n";
        cout << "6. Exit\n";

        cout << "Enter choice: ";

        cin >> choice;

        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n'
        );


        switch (choice) {


        // Add Basic Member
        case 1: {

            // Create object dynamically
            auto user =
                make_unique<Member>();

            user->setDetailsFromInput();

            // Move ownership to vector
            users.push_back(move(user));

            cout
                << "Basic Member Added.\n";

            break;
        }


        // Add Premium Member
        case 2: {

            auto user =
                make_unique<PremiumMember>();

            user->setDetailsFromInput();

            users.push_back(move(user));

            cout
                << "Premium Member Added.\n";

            break;
        }


        // Log activities
        case 3: {

            if (users.empty()) {

                cout
                    << "No users available.\n";

                break;
            }

            int userChoice;

            cout
                << "\nSelect User:\n";


            // Display all users
            for (
                size_t i = 0;
                i < users.size();
                i++
            )
            {
                cout << i + 1
                     << ". ";

                users[i]->displayInfo();

                cout << endl;
            }

            cout
                << "Enter user number: ";

            cin >> userChoice;

            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );


            if (
                userChoice > 0 &&
                userChoice <= users.size()
            )
            {
                users[userChoice - 1]
                    ->logActivity();
            }
            else {

                cout
                    << "Invalid user.\n";
            }

            break;
        }


        // Display profile and activities
        case 4: {

            if (users.empty()) {

                cout
                    << "No users found.\n";

                break;
            }

            for (
                size_t i = 0;
                i < users.size();
                i++
            )
            {

                cout
                    << "\n===== User "
                    << i + 1
                    << " =====\n";


                // Runtime polymorphism:
                // Appropriate displayInfo()
                // executes based on object type
                users[i]->displayInfo();

                users[i]
                    ->displayActivities();
            }

            break;
        }


        // Show counts
        case 5:

            cout
                << "\nTotal Users: "
                << User::getUserCount()
                << endl;

            cout
                << "Total Activities Logged: "
                << Tracker::getTotalActivities()
                << endl;

            break;


        // Exit program
        case 6:

            cout
                << "Exiting Program...\n";

            return 0;


        default:

            cout
                << "Invalid choice.\n";
        }
    }

    return 0;
}
