#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <map>


using namespace std;

class Basic {

private:
    vector<string> logins;
    vector<string> passwords;

    string signedInLogin;
    string signedInPassword;

    const int minPasswordLen = 4;
    const int maxPasswordLen = 16;

    struct Event {
        string title;
        string type;
        string deadlineString;
        string userName;
    };

    map<string, vector<Event>> userEvents;


public:

    bool keepSignedIn = false;
    bool isLoggedIn = false;


    Basic() {
        addUser("admin", "Abc4312");
    }

    bool addUser(const string& login, const string& password) {
        if (logins.size() >= 40) {
            cout << "Sorry, we are unable to add your account!" << endl;
            return false;
        }

        logins.push_back(login);
        passwords.push_back(password);
        return true;
    }

    void title() {
        cout << "######   ######   #####     ####   #######    ####   ######            ######   ####       ##     ##   ##  ##   ##  #######  ######" << endl;
        cout << "##  ##   ##  ##  ##   ##      ##    ##   #   ##  ##  # ## #             ##  ##   ##       ####    ###  ##  ###  ##   ##   #   ##  ##" << endl;
        cout << "##  ##   ##  ##  ##   ##      ##    ## #    ##         ##               ##  ##   ##      ##  ##   #### ##  #### ##   ## #     ##  ##" << endl;
        cout << "#####    #####   ##   ##      ##    ####    ##         ##               #####    ##      ##  ##   ## ####  ## ####   ####     #####  " << endl;
        cout << "##       ## ##   ##   ##  ##  ##    ## #    ##         ##               ##       ##   #  ######   ##  ###  ##  ###   ## #     ## ##  " << endl;
        cout << "##       ##  ##  ##   ##  ##  ##    ##   #   ##  ##    ##               ##       ##  ##  ##  ##   ##   ##  ##   ##   ##   #   ##  ## " << endl;
        cout << "####     #### ##  #####    ####    #######    ####    ####              ####     ####### ##  ##   ##   ##  ##   ##  #######  #### ##\n\n" << endl;
        cout << "----------------------------------------------------------------------------\n\n" << endl;
    }

    void mainMenu() {
        string choice;

        while (true) {
            system("cls");
            title();

            cout << "Welcome to Project Planner made by Gavrylov Rostyslav!\n" << endl;

            cout << "=== MAIN MENU ===" << endl;
            cout << "1 - Events (Save, Add, Delete)" << endl;
            cout << "2 - Goals (Status, Update, Regularity)" << endl;
            cout << "3 - Information (Storage, Encryption)" << endl;
            cout << "5 - Log out" << endl;
            cout << "6 - Exit the program" << endl;

            cout << "\nEnter your choice: ";
            cin >> choice;

            if (choice == "1") {
                eventsMenu();
            }
            else if (choice == "2") {
                cout << "Goals module is under development...\n";
                system("pause");
            }
            else if (choice == "3") {
                cout << "Information module is under development...\n";
                system("pause");
            }
            else if (choice == "4") {
                cout << "Interaction menu is under development...\n";
                system("pause");
            }
            else if (choice == "5") {
                keepSignedIn = false;
                isLoggedIn = false;
                signedInLogin = "";
                signedInPassword = "";
                cout << "Logging out...\n";
                system("pause");
                return;
            }
            else if (choice == "6") {
                cout << "Thank you for using the program! Goodbye!\n";
                exit(0);
            }
            else {
                cout << "Invalid choice. Please try again.\n";
                system("pause");
            }
        }
    }

    bool isValidEmail(const string& email) {
        auto atPos = email.find('@');
        auto dotPos = email.find('.', atPos);

        return atPos != string::npos &&
            dotPos != string::npos &&
            atPos > 0 &&
            dotPos > atPos + 1 &&
            dotPos < email.length() - 1;
    }

    bool isValidPassword(const string& password) {
        if (password.length() < minPasswordLen || password.length() > maxPasswordLen) {
            cout << "Password must have from 4 to 16 symbols" << endl;
            return false;
        }

        bool hasUpper = false, hasLower = false, hasDigit = false;

        for (char c : password) {
            if (isupper(c)) hasUpper = true;
            else if (islower(c)) hasLower = true;
            else if (isdigit(c)) hasDigit = true;
        }

        if (!hasUpper) cout << "Password must have one uppercase letter" << endl;
        if (!hasLower) cout << "Password must have at least one lowercase letter" << endl;
        if (!hasDigit) cout << "Password must have at least one digit" << endl;

        return hasUpper && hasLower && hasDigit;
    }

    bool isSignedIn() {
        return isLoggedIn && login(signedInLogin, signedInPassword);
    }



    bool login(const string& login, const string& password) {
        for (size_t i = 0; i < logins.size(); i++) {
            if (logins[i] == login && passwords[i] == password) {
                return true;
            }
        }
        return false;
    }

    void signinMenu() {
        string userEmail, userPassword, choice;
        bool emailValid, passwordValid;

        string greeting = "Please enter email and password you want to register in this format --> email password";

        system("cls");
        title();

        do {
            emailValid = false;
            passwordValid = false;
            cout << greeting << endl;
            cin >> userEmail >> userPassword;

            emailValid = isValidEmail(userEmail);
            passwordValid = isValidPassword(userPassword);

            if (!emailValid || !passwordValid) {
                greeting = "Please try again! Enter email and password you want to register in this format --> email password";
            }
            else {
                break;
            }

            while (true) {
                cout << "Enter:\n0 - to continue\n1 - to return to main menu\n2 - to close the app" << endl;
                cin >> choice;
                if (choice == "0") break;
                else if (choice == "1") return;
                else if (choice == "2") exit(0);
            }

        } while (true);

        system("cls");
        title();

        addUser(userEmail, userPassword);

        signedInLogin = userEmail;
        signedInPassword = userPassword;
        isLoggedIn = true;


        cout << "Congratulations, you've successfully signed in!" << endl;
        system("pause");
    }

    void loginMenu() {
        string choice, userEmail, userPassword;

        while (true) {
            system("cls");
            title();

            cout << "Please enter email and password of the account you want to log into in this format --> email password" << endl;
            cin >> userEmail >> userPassword;

            if (login(userEmail, userPassword)) {
                while (true) {
                    cout << "Welcome back! Would you like to stay signed in?\n1 - Yes\n0 - No" << endl;
                    cin >> choice;
                    if (choice == "1") {
                        keepSignedIn = true;
                        signedInLogin = userEmail;
                        signedInPassword = userPassword;
                        isLoggedIn = true;
                        return;
                    }
                    else if (choice == "0") {
                        keepSignedIn = false;
                        isLoggedIn = true;
                        return;
                    }
                }
            }

            while (true) {
                cout << "Enter:\n0 - to try again\n1 - to return to main menu\n2 - to close the app" << endl;
                cin >> choice;
                if (choice == "0") break;
                else if (choice == "1") return;
                else if (choice == "2") exit(0);
            }
        }
    }

    void eventsMenu() {
        string choice;
        string currentUser = signedInLogin;
        vector<Event>& events = userEvents[currentUser];

        while (true) {
            system("cls");
            title();

            cout << "=== EVENTS & GOALS MENU ===\n";
            cout << "1 - Add new event or goal\n";
            cout << "2 - View all\n";
            cout << "3 - Edit existing\n";
            cout << "4 - Delete\n";
            cout << "5 - Return to main menu\n\n";
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == "1") {
                Event newEvent;
                system("cls");
                title();
                cout << "Enter type (event/goal): ";
                cin >> newEvent.type;
                cout << "Enter title: ";
                cin.ignore();
                getline(cin, newEvent.title);
                cout << "Enter deadline (just a text, e.g. 'next Friday'): ";
                getline(cin, newEvent.deadlineString);
                newEvent.userName = signedInLogin;
                events.push_back(newEvent);
                cout << "\nAdded successfully!\n";
                system("pause");
            }

            else if (choice == "2") {
                system("cls");
                title();

                if (events.empty()) {
                    cout << "No events or goals found.\n";
                }
                else {
                    cout << "Your events/goals:\n";
                    for (size_t i = 0; i < events.size(); i++) {
                        cout << i + 1 << ". [" << events[i].type << "] "
                            << events[i].title
                            << " | Deadline: " << events[i].deadlineString << endl;

                    }
                }
                system("pause");
            }

            else if (choice == "3") {
                if (events.empty()) {
                    cout << "Nothing to edit.\n";
                    system("pause");
                    continue;
                }
                int index;
                system("cls");
                title();
                for (size_t i = 0; i < events.size(); i++) {
                    cout << i + 1 << ". " << events[i].title << " (" << events[i].type << ")\n";
                }
                cout << "\nEnter number of the item to edit: ";
                cin >> index;
                if (index < 1 || index > events.size()) {
                    cout << " Invalid index.\n";
                }
                else {
                    index--;
                    cin.ignore();
                    cout << "Enter new title (leave empty to keep current): ";
                    string newTitle;
                    getline(cin, newTitle);
                    if (!newTitle.empty()) events[index].title = newTitle;

                    cout << "Enter new deadline (leave empty to keep current): ";
                    string newDeadline;
                    getline(cin, newDeadline);
                    if (!newDeadline.empty()) events[index].deadlineString = newDeadline;

                    cout << " Event updated!\n";
                }
                system("pause");
            }

            else if (choice == "4") {
                if (events.empty()) {
                    cout << "Nothing to delete.\n";
                    system("pause");
                    continue;
                }
                int index;
                system("cls");
                title();
                for (size_t i = 0; i < events.size(); i++) {
                    cout << i + 1 << ". " << events[i].title << " (" << events[i].type << ")\n";
                }
                cout << "\nEnter number of the item to delete: ";
                cin >> index;
                if (index < 1 || index > events.size()) {
                    cout << "Invalid index.\n";
                }
                else {
                    events.erase(events.begin() + index - 1);
                    cout << "Deleted successfully!\n";
                }
                system("pause");
            }

            else if (choice == "5") {
                return;
            }

            else {
                cout << "Invalid choice. Try again.\n";
                system("pause");
            }
        }
    }



};


int main()
{
    Basic stuff;
    string choice;

    while (true) {
        if (stuff.isSignedIn() || stuff.isLoggedIn) {
            stuff.mainMenu();
        }

        system("cls");
        stuff.title();

        cout << "====WELCOME====" << endl;
        cout << "1 - Log in" << endl;
        cout << "2 - Sign in" << endl;
        cout << "3 - Leave" << endl;

        cin >> choice;

        if (choice == "1") stuff.loginMenu();
        else if (choice == "2") stuff.signinMenu();
        else if (choice == "3") return 0;
    }
}

