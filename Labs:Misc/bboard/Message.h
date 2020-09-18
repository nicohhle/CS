#include <iostream>
#include <string>
#include <vector>

using namespace std;

#ifndef MESSAGE_H
#define MESSAGE_H

class Message {  // abstract base class
   // protected will allow access to these members by objects of derived classes
   protected:
     string author;
     string subject;
     string body;
     unsigned id;
     // This will be the size of the messageList vector to which the
     // newly constructed Message * is being pushed_back
     vector<Message *> childList; // This is how a Message is able to keep track of its Replies
 
   public:

     // default constructor
     Message();

     // Parameterized constructor; 
     // id will be the size of current BBoard's messageList
     Message(const string &athr, 
             const string &sbjct, 
             const string &body, 
             unsigned id);

     // Be very careful here: some Messages will have two pointers to 
     // them, stored in very different places!
     // Where are they, and who should be responsible for deleting 
     // them?
     virtual ~Message();
	 
     // returns true if the object is a Reply.
     virtual bool isReply() const = 0;	 

     virtual string toFormattedString() const = 0; 

     /* This function is responsible for printing the Message 
      * (whether Topic or Reply), and and all of the Message's 
      * "subtree" recursively:
      * After printing the Message with indentation n and appropriate 
      * format (see output details), it will invoke itself 
      * recursively on all of the Replies in its childList,
      * incrementing the indentation value at each new level.
      *
      * Note: Each indentation increment represents 2 spaces. e.g. if 
      * indentation == 1, the reply should be indented 2 spaces, if 
      * it's 2, indent by 4 spaces, etc.
      */       
     void print(unsigned indentation) const; // New !!

     //returns the subject string.
     const string & getSubject() const;
     
     //these are temporary functions created myself;
     //const string & getAuthor() const;
     //const string & getBody() const;

     // returns the ID.
     unsigned getID() const; // New !!    

     // Adds a pointer to the child to the parent's childList. 
     void addChild(Message *child); // New !! 

};

// class Message {
//  private:
// 	string author;
// 	string subject;
// 	string body;

//  public:

// 	// default constructor
// 	Message();
	
// 	// Parameterized constructor; 
// 	Message(const string &athr, const string &sbjct, const string &body);
     
// 	// Displays the Message using the following format:

// 	// subject
// 	// from author: body
// 	void display() const;	
// };

#endif