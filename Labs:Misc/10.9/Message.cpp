#include <iostream>
#include <string>
#include <vector>
#include "Message.h"

using namespace std;

Message::Message() {
    author = "";
    subject = "";
    body = "";
    id = 0;
}

Message::Message(const string &athr, const string &sbjct, const string &body, unsigned id) {
    this->author = athr;
    this->subject = sbjct;
    
    string tempBody = body;
    this->body = tempBody;
    this->id = id;
}

Message::~Message() {
	
}

void Message::print(unsigned indentation) const {
    string space = "";
	string tempBody = body;

	for(unsigned i = 0; i < indentation; ++i) {
		space = space + "  ";
	}
	
	if(isReply()) {
			cout << endl;
	}
	
	cout << space << "Message #" << getID() << ": " << getSubject() << endl;
	cout << space << "from " << author << ": ";
	
	for(int i = 0; i < static_cast<int>(tempBody.size()) - 1; i++) {
		if(tempBody.at(i) == '\n') {
			tempBody.insert(i + 1, space);
		}
	}
	
	cout << tempBody << endl;
	
	if(childList.size() != 0) {
		for(unsigned i = 0; i < childList.size(); i++) {
			childList.at(i)->print(indentation + 1);
		}
	}
	
}

const string& Message::getSubject() const {
    return subject;
}

unsigned Message::getID() const {
    return id;
}

void Message::addChild(Message *child) {
    childList.push_back(child);
}
