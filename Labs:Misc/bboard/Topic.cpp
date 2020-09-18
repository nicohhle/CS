#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

#include "Message.h"
#include "Topic.h"
#include "Reply.h"

//default constructor
Topic::Topic() {
    author = "";
    subject = "";
    body = "";
    id = 0;
}

//Parameterized constructor
Topic::Topic(const string &athr, 
           const string &sbjct, 
           const string &body, 
           unsigned id)
           : Message(athr, sbjct, body, id) { }

Topic::~Topic() {
    for(unsigned i = 0; i < childList.size(); ++i) {
        delete childList.at(i);
    }
}

// Returns false
bool Topic::isReply() const {
    return false;
}

string Topic::toFormattedString() const {
    string str;
    
    stringstream buff;
    
    buff << "<begin_topic>" << endl;
    buff << ":id: " << id << endl;
    buff << ":subject: " << subject << endl;
    buff << ":from: " << author << endl;
    
    if (childList.size() != 0) {
        buff << ":children: ";
        
        for (unsigned i = 0; i < childList.size(); ++i) {
            if (i == childList.size() - 1) {
                buff << childList.at(i)->getID() << endl;
            } else {
                buff << childList.at(i)->getID() << " ";
            }
        }
    }
    
    // buff << endl;
    
    buff << ":body: " << body << endl;
    buff << "<end>" << endl;
    
    str = buff.str();
    return str;
}