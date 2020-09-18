#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

#include "Message.h"

Message::Message() {
    author = "";
    subject = "";
    body = "";
    id = 0;
}

Message::Message(const string &athr, const string &sbjct, const string &body, unsigned id) {
    author = athr;
    subject = sbjct;
    this->body = body;
    this->id = id;
}

Message::~Message() { }

void Message::print(unsigned indentation) const {
    string indent = "";
    string line;
    istringstream buff(body);
    
    
    // cannot multiply space by indentation
    for (unsigned i = 0; i < indentation; ++ i) {
        indent = indent + "  ";
    }
    
    cout << indent << "Message #" << id << ": " << subject << endl;
    getline(buff, line);
    
    cout << indent << "from " << author << ": " << line << endl;
    
    while(getline(buff, line)) {
        cout << indent << line << endl;
    }
    
    if (childList.size() == 0) {
        return;
    } else {
        for (unsigned i = 0; i < childList.size(); ++i) {
            cout << endl;
            // cout << childList.at(i) -> getID() << endl;
            childList.at(i)->print(indentation + 1);
        }
    }
}

     //returns the subject string.
const string & Message::getSubject() const {
    return subject;
}

// const string & Message::getAuthor() const {
//     return author;
// }

// const string & Message::getBody() const {
//     return body;
// }

     // returns the ID.
unsigned Message::getID() const {
    return id;
}   

     // Adds a pointer to the child to the parent's childList. 
void Message::addChild(Message *child) {
    childList.push_back(child);
} 
