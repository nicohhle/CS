#include <iostream>
#include <string>

using namespace std;

#include "Message.h"

Message::Message() {
    author = "";
    subject = "";
    body = "";
}

Message::Message(const string &athr, const string &sbjct, const string &body) {
    author = athr;
    subject = sbjct;
    this -> body = body;
}

void Message::display() const {
    cout << subject << endl;
    cout << "from " << author << ": " << body << endl;
}
