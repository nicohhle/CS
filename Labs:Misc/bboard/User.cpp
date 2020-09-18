#include <iostream>
#include <string>

using namespace std;

#include "User.h"

User::User() {
    username = "";
    password = "";
}

User::User(const string &uname, const string &pass) {
    username = uname;
    password = pass;
}

string User::getUsername() const {
    return username;
}

bool User::check(const string &uname, const string &pass) const {
    if (username == "") {
        return false;
    } else if (username == uname && password == pass) {
        return true;
    }
    
    return false;
}

bool User::setPassword(const string &oldpass, const string &newpass) {
    if (check(username, oldpass)) {
        password = newpass;
        return true;
    }
    return false;
}