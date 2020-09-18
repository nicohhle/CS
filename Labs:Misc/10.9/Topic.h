#ifndef TOPIC_H
#define TOPIC_H
#include <iostream>
#include <vector>
#include "Message.h"
#include "Reply.h"
#include "BBoard.h"
#include "User.h"

  class Topic : public Message {   
   public:

     Topic();

     Topic(const string &athr, 
           const string &sbjct, 
           const string &body, 
           unsigned id);
	 
	virtual bool isReply() const;
    
     virtual string toFormattedString() const;

  };

#endif