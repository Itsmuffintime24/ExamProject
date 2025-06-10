
#include <iostream>
#include <cstdlib>

using namespace std;

class Basic {

private:
    int capacity;
    int count;
    string* logins;
    string* passwords;
    
    string signedInLogin;
    string signedInPassword;


public:

    bool keepSignedIn = false;

    Basic(int maxUsers = 40) {
        capacity = maxUsers;
        count = 0;
        logins = new string[capacity];
        passwords = new string[capacity];

        addUser("admin", "Abc4312");
    }

    ~Basic() {
        delete[] logins;
        delete[] passwords;
    }

    bool addUser(const string& login, const string& password) {
        if (count >= capacity) { return false; cout << "Sorry, we are unable to add your account!"; }

        logins[count] = login;
        passwords[count] = password;
        count++;
        return true;
    }

    void title() {
        cout << "######   ######    #####      ####  #######    ####   ######            ######   ####       ##     ##   ##  ##   ##  #######  ######" << endl;
        cout << "##  ##   ##  ##  ##   ##      ##    ##   #   ##  ##  # ## #             ##  ##   ##       ####    ###  ##  ###  ##   ##   #   ##  ##" << endl;
        cout << "##  ##   ##  ##  ##   ##      ##    ## #    ##         ##               ##  ##   ##      ##  ##   #### ##  #### ##   ## #     ##  ##" << endl;
        cout << "#####    #####   ##   ##      ##    ####    ##         ##               #####    ##      ##  ##   ## ####  ## ####   ####     #####  " << endl;
        cout << "##       ## ##   ##   ##  ##  ##    ## #    ##         ##               ##       ##   #  ######   ##  ###  ##  ###   ## #     ## ##  " << endl;
        cout << "##       ##  ##  ##   ##  ##  ##    ##   #   ##  ##    ##               ##       ##  ##  ##  ##   ##   ##  ##   ##   ##   #   ##  ## " << endl;
        cout << "####     #### ##   #####    ####    #######    ####    ####             ####     #######  ##  ##   ##   ##  ##   ##  #######  #### ##\n\n" << endl;
        // Logo
        cout << "----------------------------------------------------------------------------\n\n" << endl;
    }

    void mainMenu() {
        //So empty...
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
        if (password.length() < 4 || password.length() > 16) {
            cout << "Password must have from 4 to 16 symbols" << endl;
            return false;
        }

        bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;

        for (char c : password) {
            if (isupper(c)) hasUpper = true;
            else if (islower(c)) hasLower = true;
            else if (isdigit(c)) hasDigit = true;
        }

        if (!hasUpper) cout << "Password must have one uppercase letter" << endl;

        if (!hasLower) cout << "Password must have atleast one lowercase letter" << endl;

        if (!hasDigit) cout << "Password must have atleast one digit" << endl;

        return hasUpper && hasLower && hasDigit;
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

            if (!emailValid || !passwordValid) greeting = "Please try again! Enter email and password you want to register in this format --> email password";
            else break;
            
            while (true) {
                cout << "Enter:\n0 - if you'd like to continue\n1 - if you'd like to leave to main menu\n2 - if you'd like to close the app" << endl;
                cin >> choice;
                if (choice == "0") break;
                else if (choice == "1") return;
                else if (choice == "2") exit(0);
            }
            
        } while (true);

        system("cls");
        title();

        addUser(userEmail, userPassword);

        cout << "Congratulations, you've succesfully signed in! Enter anything to continue" << endl;
        cin >> choice;
        
    }

    void loginMenu() {
        string choice, userEmail, userPassword;

        system("cls");
        title();

        while (true) {
            system("cls");
            title();

            cout << "Please enter email and password of account you want to log into in this format --> email password" << endl;
            cin >> userEmail >> userPassword;
            
            if (login(userEmail, userPassword)) { 
                while (true) {
                    cout << "Welcome back, would you like to keep being signed in?\n1 - Yes\n0 - No" << endl;
                    cin >> choice;
                    if (choice == "1") {
                        keepSignedIn = true;
                        signedInLogin = userEmail;
                        signedInPassword = userPassword;
                        break;
                    }

                    else if (choice == "0") { keepSignedIn = false; break; }
                }
            }


            while (true) {
                cout << "Enter:\n0 - if you'd like to continue\n1 - if you'd like to leave to main menu\n2 - if you'd like to close the app" << endl;
                cin >> choice;
                if (choice == "0") break;
                else if (choice == "1") return;
                else if (choice == "2") exit(0);
            }

        }
        //(No) Error here, fix later wanna sleeeeeeeep
    }

    bool login(const string& login, const string& password) {
        for (int i = 0; i < count; i++) {
            if (logins[i] == login && passwords[i] == password) { 
                return true;
                break;
            }
        }
        return false;
    }



};

int main()
{
    Basic stuff;
    string choice;

    if (stuff.keepSignedIn) {

    }

    while (true) {
        system("cls");
        stuff.title();


        cout << "It looks like you're new here! Would you like to sign, or log in?" << endl;
        cout << "1 - Log in" << endl;
        cout << "2 - Sign in" << endl;
        cout << "3 - Leave\n" << endl;

        cin >> choice;

        if (choice == "1") stuff.loginMenu();
        else if (choice == "2") stuff.signinMenu();
        else if (choice == "3") return 0;
    }
}
