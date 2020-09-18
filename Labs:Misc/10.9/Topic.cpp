#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Topic.h"

using namespace std;

Topic::Topic()
	: Message()
{}

Topic::Topic(const string &athr, const string &sbjct, const string &body,
			unsigned id)
	: Message(athr, sbjct, body, id)
{}

bool Topic::isReply() const {
    return false;
}

string Topic::toFormattedString() const {
    stringstream s;
	string tempString;
	
	s << "<begin_topic>" << endl;
	s << ":id: " << id << endl;
	s << ":subject: " << subject << endl;
	s << ":from: " << author << endl;
	
	if (childList.size() != 0) {
		s << ":children: ";
		for(unsigned i = 0; i < childList.size(); i++)
		{
			s << childList.at(i)->getID();
			if(i != childList.size() - 1)
				s << " ";
		}
		s << endl;
	}
		
	s << ":body: " << body << endl;
	s << "<end>" << endl;
	
	tempString = s.str();
	
	return tempString;
}