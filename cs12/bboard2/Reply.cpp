#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

#include "Message.h"
#include "Reply.h"
#include "Topic.h"

//default constructor
Reply::Reply() {
    // Message();
    author = "";
    subject = "";
    body = "";
    id = 0;
}

    /* Parameterized constructor - similar to Message's constructor
     */
Reply::Reply(const string &athr, 
           const string &sbjct, 
           const string &body, 
           unsigned id)
           : Message(athr, sbjct, body, id) { }
     
Reply::~Reply() {
    for(unsigned i = 0; i < childList.size(); ++i) {
        delete childList.at(i);
    }
}

    // Returns true
bool Reply::isReply() const {
    return true;
}

string Reply::toFormattedString() const {
    string str;
    
    stringstream buff;
    
    buff << "<begin_reply>" << endl;
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