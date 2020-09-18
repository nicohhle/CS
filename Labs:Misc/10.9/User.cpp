#include <iostream>
#include <string>
#include <vector>
#include "User.h"

using namespace std;

User::User() {
    username = "";
    password = "";
    return;
}

User::User(const string& uname, const string& pass) {
    username = uname;
    password = pass;
    return;
}

string User::getUsername() const {
    string tempString;
    tempString = username;
    return tempString;
}

bool User::check(const string &uname, const string &pass) const {
    if (uname == "") {
        return false;
    }
    
    if ( (uname == username) && (pass == password) ) {
        return true;
    }
    
    return false;
}

bool User::setPassword(const string &oldpass, const string &newpass) {
    if (password == oldpass) {
        password = newpass;
        return true;
    }
    
    return false;
}

