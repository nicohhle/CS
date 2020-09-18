//BBoard.h
#include <string>
#include <vector>
#include <fstream>
using namespace std;

#ifndef BBOARD_H
#define BBOARD_H
#include "Message.h"
#include "User.h"
#include "Reply.h"

class BBoard {
 private:
    string title;
    vector<User> userList;
    const User* currentUser;
    vector<Message *> messageList;

 public:
    BBoard();
    BBoard(const string & ttl);
    bool loadUsers(const string & userfile);
    void login();
    void run();
    
    //NEW ONES
    
    ~BBoard();
    bool loadMessages(const string & datafile);
    bool saveMessages(const string & datafile);

};

#endif

 
