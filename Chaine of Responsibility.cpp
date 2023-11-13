#include <iostream>
#include <string>
#include <memory>

using namespace std;


class Handler {
public:
    virtual Handler* setNext(Handler* handler) = 0;
    virtual void handleRequest(string& username,  string& password) = 0;
};


class UsernameLengthValidator : public Handler {
private:
    Handler* nextHandler;

public:
    Handler* setNext(Handler* handler) override {
        nextHandler = handler;
        return handler;
    }

    void handleRequest( string& username,  string& password) override {
        if (username.length() >= 5) {
            cout << "Username length is valid." << endl;
            if (nextHandler) {
                nextHandler->handleRequest(username, password);
            }
        }
        else {
            cout << "Username length must be at least 5 characters." << endl;
        }
    }
};


class PasswordStrengthValidator : public Handler {
private:
    Handler* nextHandler;

public:
    Handler* setNext(Handler* handler) override {
        nextHandler = handler;
        return handler;
    }

    void handleRequest( string& username, string& password) override {
        if (password.length() >= 8) {
            cout << "Password strength is valid." << endl;
            if (nextHandler) {
                nextHandler->handleRequest(username, password);
            }
        }
        else {
            cout << "Password strength must be at least 8 characters." << endl;
        }
    }
};


class UserRegistrationHandler : public Handler {
public:
    Handler* setNext(Handler* handler) override {
        return nullptr;
    }

    void handleRequest(string& username, string& password) override {
        cout << "\nUser registered successfully:\nUsername - " << username;
        cout << "\nPassword - " << password << endl;
    }
};

int main() {
    
    Handler* usernameValidator = new UsernameLengthValidator();
    Handler* passwordValidator = new PasswordStrengthValidator();
    Handler* registrationHandler = new UserRegistrationHandler();

    usernameValidator->setNext(passwordValidator)->setNext(registrationHandler);

    string username;
    string password;
    while (true) {
        cout << "e -exit\n";
        cout << "Input Username: ";
        cin >> username;
        if (username == "e" || username == "E") {
            break;
        }
        cout << "Input Password: ";
        cin >> password;
        cout << endl;
        usernameValidator->handleRequest(username, password);
    }
   

    
  
    return 0;
}
