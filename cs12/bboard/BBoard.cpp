#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>

using namespace std;

#include "BBoard.h"

BBoard::BBoard() {
    title = "Nicole's Board of Too Many Tries";
    vector<User> userList;
    vector<Message> messageList;
    currentUser = User();
}

BBoard::BBoard(const string &tit) {
    title = tit;
    vector<User> userList;
    vector<Message> messageList;
    currentUser = User();
}

bool BBoard::loadUsers(const string &userfile) {
    ifstream file;
    string uname;
    string pass;
    
    file.open(userfile.c_str());
    
    if (!file.is_open()) {
        return false;
    }
    
    while (file >> uname >> pass) {
        userList.push_back(User(uname, pass));
    }
    
    file.close();
    
    return true;
}

bool BBoard::login() {
    string uname;
    string pass;
    
    cout << "Welcome to " << title << endl;
    cout << "Enter your username ('Q' or 'q' to quit): " << endl;
    cin >> uname;
    
    if (uname == "Q" || uname == "q") {
        cout << "Bye!" << endl;
        return false;
    }
    
    cout << "Enter your password: " << endl;
    cin >> pass;
    
    // bool validlogin = false;
    // for (unsigned int i = 0; i < userList.size(); ++i) {
    //     User temp(userList.at(i));
    //     if (userList.at(i).check(uname, pass)) {
    //         validlogin = true;
    //         currentUser = temp;
    //         cout << "Welcome back " << uname << "!" << endl;
    //         return true;
    //     } 
    // }
    
    // while (!validlogin) {
    //     cout << "Invalid Username or Password!" << endl;
    //     cout << "Enter your username ('Q' or 'q' to quit): ";
    //     cin >> uname;
    //     cout << endl;
        
    //     if (uname == "Q" || uname == "q") {
    //     cout << "Bye!" << endl;
    //     return false;
    //     }
        
    //     cout << "Enter your password: ";
    //     cin >> pass;
    //     cout << endl;
        
    //     for (unsigned int i = 0; i < userList.size(); ++i) {
    //         // User temp(userList.at(i));
    //         if (userList.at(i).check(uname, pass)) {
    //             validlogin = true;
    //             currentUser = User(uname, pass);
    //             cout << "Welcome back " << uname << "!" << endl;
    //             return true;
    //         }
    //     }
    // }
    
    if (userExists(uname, pass)) {
        cout << "Welcome back " << uname << "!" << endl;
        currentUser = User(uname, pass);
        return true;
    }
    
    while (!userExists(uname, pass)) {
        cout << "Invalid Username or Password!" << endl;
        cout << endl;
        cout << "Enter your username ('Q' or 'q' to quit): " << endl;
        cin >> uname;
        
        if (uname == "Q" || uname == "q") {
            cout << "Bye!" << endl;
            return false;
        }
        
        cout << "Enter your password: " << endl;
        cin >> pass;
        
        if (userExists(uname, pass)) {
            cout << "Welcome back " << uname << "!" << endl;
            currentUser = User(uname, pass);
            return true;
        }
    }
    
    return false;
}

void BBoard::run() {
    // string message;
    // using char isn't working
    // char ch;
    char ch;
    
    cout << endl;
    // BBoard ok;
    
    // ok.login();
    
    // if (currentUser.getUsername() == "") {
    //     return;
    // }
    
    // if (ok.login()) {
    cout << "Menu" << endl;
    cout << "- Display Messages ('D' or 'd')" << endl;
    cout << "- Add New Message ('N' or 'n')" << endl;
    cout << "- Quit ('Q' or 'q')" << endl;
    cout << "Choose an action: " << endl;
    cin >> ch;
    
    if(ch == 'Q' || ch == 'q'){
            cout << "Bye!" << endl;
    }
    
    while (!(ch == 'Q') && !(ch == 'q')) {
        if (ch == 'D' || ch == 'd') {
            display();
        } else if (ch == 'N' || ch == 'n') {
            addMessage();
        } 
        cout << endl;
        
        cout << "Menu" << endl;
        cout << "- Display Messages ('D' or 'd')" << endl;
        cout << "- Add New Message ('N' or 'n')" << endl;
        cout << "- Quit ('Q' or 'q')" << endl;
        cout << "Choose an action: " << endl;
        cin >> ch;

        if(ch == 'Q' || ch == 'q'){
            cout << "Bye!" << endl;
        }
    }
    
    
}

// USE .DISPLAY() FROM MESSAGE.H INSTEAD
void BBoard::display() const {
    if (messageList.size() == 0) {
            cout << "Nothing to Display." << endl;
        } else {
            // for (unsigned i = 0; i < messageList.size(); ++i) {
            //     cout << "---------------------------------------------------------" << endl;
            //     cout << "Message #" << i + 1 << ": ";
            //     messageList.at(i).display();
            //     cout << "---------------------------------------------------------" << endl;
            // }
            
            // cout << "---------------------------------------------------------" << endl;
            
        cout << "---------------------------------------------------------" << endl;
        cout << "Message #" << 1 << ": "; 
        messageList.at(0).display();
        cout << "---------------------------------------------------------" << endl;
        
    
        for(unsigned int i = 1; i < messageList.size(); i++){
            cout << "Message #" << i + 1 << ": "; 
            messageList.at(i).display();
            cout << "---------------------------------------------------------" << endl;
        }
    }
}


void BBoard::addMessage () {
    string sbjct;
    string body;
    
    string uname;
    Message message;
    
    cout << "Enter Subject: " << endl;
    cin.ignore();
    getline(cin, sbjct);
        
    cout << "Enter Body: " << endl;
    getline(cin, body);
        
    uname = currentUser.getUsername();
    message = Message(uname, sbjct, body);
        
    messageList.push_back(message);
        
    cout << "Message Recorded!" << endl;
}


bool BBoard::userExists(const string &user, const string &pass) const {
    for (unsigned i = 0; i < userList.size(); ++i) {
        if (userList.at(i).check(user, pass)) {
            return true;
        }
    }
    
    return false;
}