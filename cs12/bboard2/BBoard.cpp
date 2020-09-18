#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>

using namespace std;

#include "BBoard.h"
#include "User.h"
#include "Message.h"
#include "Topic.h"
#include "Reply.h"

BBoard::BBoard() {
    title = "Nicole's Board of Struggle and Too Many Tries";
    vector<User> userList;
    vector<Message *> messageList;
    currentUser = 0;
}

BBoard::BBoard(const string &tit) {
    title = tit;
    vector<User> userList;
    vector<Message *> messageList;
    currentUser = 0;
}

BBoard::~BBoard() {
    // while (!empty()) {
    //     pop_front();
    // }
    
    for (unsigned i = 0; i < messageList.size(); ++ i) {
        if (messageList.at(i) != 0) {
            delete messageList.at(i);
        }
    }
}

bool BBoard::loadUsers(const string &userfile) {
    ifstream file;
    string uname;
    string pass;
    
    file.open(userfile.c_str());
    
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        return false;
    }
    
    while (file >> uname >> pass) {
        if (uname!= "end" && pass != "end") {
            userList.push_back(User(uname, pass));
        } else {
            break;
        }
    }
    
    file.close();
    
    return true;
}

bool BBoard::loadMessages(const string &datafile) {
    ifstream file;
    string header, discard;
    unsigned childID;
    vector<string> childVec;
    
    file.open(datafile.c_str());
    
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        return false;
    } 
    
    
    
    unsigned numMessages;
    file >> numMessages;
    
    while (file >> header) {
        string athr, sbjct, body, line, childStr;
        unsigned id;
        
        file >> discard >> id;
        file >> discard;
        file.ignore();
        getline(file, sbjct);
        file >> discard >> athr;
        
        file >> discard;
        if (discard != ":children:") {
            childVec.push_back("0");
        } else {
            // string ok;
            // file.ignore();
            // childVec.push_back(getline(file, ok));
            getline(file, childStr);
            childVec.push_back(childStr);
            
            file >> discard;
        }
        
        file.ignore();
        getline(file, line);
        
        while (line != "<end>") {
            body = body + line;
            getline(file, line);
            
            if (line != "<end>") {
                body = body + "\n";
            }
        }
        
        if (header == "<begin_topic>") {
           Topic *topic = new Topic(athr, sbjct, body, id);
           messageList.push_back(topic);
           
        } else if (header == "<begin_reply>") {
            Reply *reply = new Reply(athr, sbjct, body, id);
            messageList.push_back(reply);
        }
    }
    
    for (unsigned i = 0; i < childVec.size(); ++i) {
        if (childVec.at(i) != "0") {
            stringstream stream(childVec.at(i));
        // }
            while (stream >> childID) {
                for (unsigned j = 0; j < messageList.size(); ++j) {
                    if (messageList.at(j)->getID() == childID) {
                        messageList.at(i)->addChild(messageList.at(j));
                    }
                }
            }
        }
    }
    
    file.close();
    
    return true;
}

bool BBoard::saveMessages(const string &datafile) {
    ofstream file;
    string output;
    stringstream buff;
    
    file.open(datafile.c_str());
    
    buff << messageList.size() << endl;
    
    file << buff.str();
    
    for (unsigned i = 0; i < messageList.size(); ++i) {
        output = messageList.at(i)->toFormattedString();
        file << output;
    }
    
    file.close();
    
    return true;
}

void BBoard::login() {
    string uname;
    string pass;
    
    cout << "Welcome to " << title << endl;
    
    // points at nothing for now until it finds valid login
    // while (currentUser == 0) {
        cout << "Enter your username ('Q' or 'q' to quit): ";
        cin >> uname;
    
        if (uname == "Q" || uname == "q") {
            cout << "Bye!" << endl;
            exit(0);
        }
    
        cout << "Enter your password: ";
        cin >> pass;
        
    while (getUser(uname, pass) == 0) {
        // for (unsigned i = 0; i < userList.size(); ++i) {
        //     if (userList.at(i).check(uname, pass)) {
        //         currentUser = &userList.at(i);
        //     }
        // }
        
        // currentUser = getUser(uname, pass);
        
        cout << "Invalid Username or Password!" << endl;
        cout << endl;
        
        cout << "Enter your username ('Q' or 'q' to quit): "; 
        cin >> uname;
        
        if (uname == "Q"|| uname == "q"){
            cout << "Bye!" << endl;
            exit(0);
        }
        cout << "Enter your password: "; 
        cin >> pass;
    }
    
    // currentUser = getUser(uname, pass);
    
    cout << endl;
    currentUser = getUser(uname, pass);
    cout << "Welcome back " << currentUser->getUsername() << "!" << endl;
    cout << endl;
}

void BBoard::run() {
    // string message;
    // using char isn't working
    // char ch;
    char ch;
    
    // cout << endl;
    
    if (currentUser == 0) {
        return;
    }
    
    while (ch != 'Q' && ch != 'q') {
        cout << "Menu" << endl;
        cout << "- Display Messages ('D' or 'd')" << endl;
        cout << "- Add New Topic ('N' or 'n')" << endl;
        cout << "- Add Reply to a Topic ('R' or 'r')" << endl;
        cout << "- Quit ('Q' or 'q')" << endl;
        cout << "Choose an action: ";
        cin >> ch;
        
        if (ch == 'D' || ch == 'd') {
            if (messageList.size() == 0) {
                cout << endl;
                cout << "Nothing to Display." << endl;
                cout << endl;
            } else {
                cout << endl;
                display();
                cout << endl;
            }
        } 
        if (ch == 'N' || ch == 'n') {
            addTopic();
            cout << endl;
        } 
        if (ch == 'R' || ch == 'r') {
            cout << endl;
            addReply();
        }
        if(ch == 'Q' || ch == 'q'){
            cout << "Bye!" << endl;
            return;
        }
    }
}

void BBoard::display() const {
   
        cout << "---------------------------------------------------------" << endl;
    
        for(unsigned int i = 0; i < messageList.size(); ++i){
            // cout << "Message #" << i + 1 << ": "; 
            // messageList.at(i).display();
            
            if (!(messageList.at(i)->isReply())) {
                // cout << "---------------------------------------------------------" << endl;
                messageList.at(i)->print(0);
            
                cout << "---------------------------------------------------------" << endl;
            }
        }
        
        // cout << "---------------------------------------------------------" << endl;
}

void BBoard::addTopic() {
    string subject;
    string body, line;
    string author;
    unsigned id;
    // string temp;
    
    cout << "Enter Subject: ";
    cin.ignore();
    getline(cin, subject);
    
    // cout << endl;
    
    cout << "Enter Body: ";
    
    getline(cin, line); // first line of body
    
    while (line != "") {
        body = body + line;
        getline(cin, line);
        
        if (line != "") {
            body = body + "\n";
        }
        // cin.ignore();
    }
    
    author = currentUser->getUsername();
    id = messageList.size() + 1;
    
    Topic *newtopic = new Topic(author, subject, body, id);
    messageList.push_back(newtopic);
}


void BBoard::addReply() {
//     string subject, body, author, line;
//     unsigned id, messageID;
//     int num = messageID;
    
//     cout << "Enter Message ID: ";
//     cin >> messageID;
        
//     while (messageID > messageList.size() || messageID == 0) {
//         cout << "Invalid Message ID!!" << endl;
//         cout << endl;
        
//         cout << "Enter Message ID: ";
//         cin >> num;
        
//         if (num < 0) {
//             cout << endl;
//             return;
//         }
        
//         messageID = num;
//     }
    
//     while (num < 0) {
//         cout << endl;
//         return;
//     }
    
//     // subject = "Re: " + messageList.at(messageID - 1)->getSubject();
//     cout << "Body: ";
//     cin.ignore();
//     getline(cin, line);
    
//     while (line != "") {
//         body = body + line;
//         getline(cin, line);
        
//         if (line != "") {
//             body = body + "\n";
//         }
        
//     }
    
//     subject = "Re: " + (messageList.at(messageID - 1)->getSubject());
//     author = currentUser->getUsername();
//     id = messageList.size() + 1;
    
//     Reply *newreply = new Reply(author, subject, body, id);
//     messageList.push_back(newreply);
    
//     messageList.at(messageID - 1)->addChild(messageList.at(messageList.size() - 1));
    
string Subject, Line, Body, Author;
   unsigned ID, ParentID;
   int temp = ParentID; 
   
   cout << "Enter Message ID: ";
   cin >> ParentID;
   
   while (ParentID > messageList.size() || ParentID == 0) {
     cout << "Invalid Message ID!!" << endl;
     cout << endl;
     
     cout << "Enter Message ID: ";
     cin >> temp;
     if (temp < 0) {
      cout << endl;
      return;
     }
     ParentID = temp;
   }
   
   while (temp < 0) {
    cout << endl;
     return;
   }
   
   cout << "Body: ";
   cin.ignore();
   getline(cin, Line);
   
   while (Line != "") {
      Body = Body + Line;
      getline(cin, Line);
      if (Line != "") {
         Body = Body + "\n";
      }
   }
   
   Author = currentUser ->getUsername();
   Subject = "Re: " + (messageList.at(ParentID - 1) -> getSubject());
   ID = messageList.size() + 1;
   
   Reply* reply = new Reply(Author, Subject, Body, ID);
   
   messageList.push_back(reply);
   
   messageList.at(ParentID - 1) ->addChild(messageList.at(messageList.size() - 1));
   
}

User* BBoard::getUser(const string &name, const string &pw) const {
    User* userCurr;
 
    for (unsigned i = 0; i < userList.size(); ++i) {
        if (userList.at(i).check(name, pw) == true ) {
            userCurr = new User(name, pw);
            return userCurr;
        }
    }
    
    return 0;
}

// const User * BBoard::getUser(const string &name, const string &pw) const {
//     //just like userExists
    
//     for (unsigned i = 0; i < userList.size(); ++i) {
//         if (userList.at(i).check(name, pw)) {
//             &userList.at(i);
//         }
//     }
    
//     //if not found return 0;
//     return 0;
// }

