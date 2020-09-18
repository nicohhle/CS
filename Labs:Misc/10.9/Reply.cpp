#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Message.h"
#include "Reply.h"
#include "Topic.h"

using namespace std;

Reply::Reply()
	: Message()
{}

Reply::Reply(const string &athr, const string &sbjct, const string &body, unsigned id)
	: Message(athr, "Re: " + sbjct, body, id)
{}

bool Reply::isReply() const {
	return true;
}

string Reply::toFormattedString() const {
    stringstream s;
	string temp;
	
	s << "<begin_reply>" << endl;
	s << ":id: " << id  << endl;
	s << ":subject: " << subject << endl;
	s << ":from: " << author << endl;
	if(childList.size() != 0)
	{
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
	temp = s.str();
	
	return temp;
}