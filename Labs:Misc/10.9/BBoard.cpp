#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include "BBoard.h"

using namespace std;

BBoard::BBoard() {
    title = "Default Board";
    currentUser = NULL;
    return;
}

BBoard::BBoard(const string & ttl) {
    title = ttl;
    currentUser = NULL;
    return;
}

BBoard::~BBoard() {
    for (unsigned i = 0; i < messageList.size(); ++i) {
        if (messageList.at(i) != NULL) {
            delete messageList.at(i);
        }
    }
    return;
}

bool BBoard::loadUsers(const string & userfile) {
    ifstream inFS;
    inFS.open(userfile.c_str());
    if (!inFS.is_open()) {
        return false;
    }
    
    string userTemp;
    string passTemp;
    
    while ( (inFS >> userTemp) && (userTemp != "end") ) {
        inFS >> passTemp;
        
        userList.push_back( User(userTemp, passTemp) );
        
    }
    
    inFS.close();
    
    return true;
}

bool BBoard::loadMessages(const string &datafile) {
    ifstream inFS;
    inFS.open(datafile.c_str());
    if (!inFS.is_open()) {
        return false;
    }
    
    unsigned numMsg;
    inFS >> numMsg;
    
    stringstream s;
    string author;
    string subject;
    string username;
    string body;
    string child;
    string temp;
    unsigned ID;
    unsigned childID;
    vector<string> children;
    Message* tempTopic = NULL;
    Message* tempReply = NULL;
    
    while (!inFS.eof()) {
        inFS >> temp;
        
        if (temp == "<begin_topic>") {
            while (temp != "<end>") {
                inFS >> temp;
                if(temp == ":id:") {
                    inFS >> ID;
                } else if(temp == ":subject:") {
                    inFS.get();
					getline(inFS, subject);
                } else if(temp == ":from:") {
                    inFS >> author;
                } else if(temp == ":children:") {
                    getline(inFS, temp);
                    children.push_back(temp);
                } else if(temp == ":body:") {
                    body = "";
                    inFS.get();
                    while (temp != "<end>") {
                        getline(inFS, temp);
                        if(temp != "<end>") {
                            body = body + temp;
                        }
                        inFS >> temp;
                        if(temp != "<end>") {
                            body = body + '\n';
                            body = body + temp;
                        }
                    }
                    
                    if( (body.size() != 0) && body.at(body.size() - 1) == '\n') {
                        body.erase(body.size() - 1);
                    }
                    children.push_back("0");
                }
            }
            
            tempTopic = new Topic(author, subject, body, ID);
            messageList.push_back(tempTopic);
            
        } else if (temp == "<begin_reply>") {
            while(temp != "<end>") {
                inFS >> temp;
                if(temp == ":id:") {
                    inFS >> ID;
                } else if (temp == ":subject:") {
                    inFS.get();
                    inFS >> temp;
                    inFS.get();
                    getline(inFS, subject);
                } else if(temp == ":from:") {
                    inFS >> author;
                } else if (temp == ":children:") {
                    getline(inFS, temp);
                    children.push_back(temp);
                } else if (temp == ":body:") {
                    body = "";
                    inFS.get();
                    while(temp != "<end>") {
                        getline(inFS, temp);
                        if (temp != "<end>") {
                            body = body + temp;
                        }
                        
                        inFS >> temp;
                        
                        if (temp != "<end>") {
                            body = body + "\n";
                            body = body + temp;
                        }
                    }
                    
                    if( (body.size() != 0 ) && body.at(body.size() - 1) == '\n') {
                        body.erase(body.size() - 1);
                    }
                    child = "0";
                    children.push_back(child);
                }
            }
            
            tempReply = new Reply(author, subject, body, ID);
            
            messageList.push_back(tempReply);
            
        }
    }

    
    /*
    for(unsigned i = 0; i < children.size(); ++i) {
        s << children.at(i) << endl;
    }
    
    bool tempBool;
    for (unsigned i = 0; i < messageList.size(); ++i) {
        while (tempBool) {
            s >> childID;
            if (childID == 0) {
                tempBool = false;
            }
            if (tempBool) {
                
                messageList.at(childID)->addChild(messageList.at(childID - 1));
            }
        }
    }*/
    
    for(unsigned i = 0; i < children.size(); ++i) {
        s << children.at(i) << endl;
    }
    
    for(unsigned i = 0; i < numMsg; ++i) {
        while (true) {
            s >> childID;
            if (childID == 0) {
                break;
            }
            messageList.at(i)->addChild(messageList.at(childID-1));
        }
    }
    
    inFS.close();
    return true;
}

bool BBoard::saveMessages(const string &datafile) {
    ofstream onFS;
    onFS.open(datafile.c_str());
    onFS << messageList.size() << endl;
    
    if (messageList.size() != 0) {
        for(unsigned k = 0; k < messageList.size(); ++k) {
            onFS << messageList.at(k)->toFormattedString();
        }
    }
    
    onFS.close();
    return true;
}

void BBoard::login() {
    cout << "Welcome to " << title << endl;
    
    string tempU;
    string tempP;
    while(currentUser == NULL) {
        cout << "Enter your username ('Q' or 'q' to quit): ";
        cin >> tempU;
        
        if (tempU == "Q" || tempU == "q") {
            cout << "Bye!" << endl;
            return;
        }
        
        cout << "Enter your password: ";
        cin >> tempP;
        
        unsigned m = 0;
        bool found = false;
        while (m < userList.size() && !found) {
            if (userList.at(m).check(tempU, tempP)) {
                currentUser = &userList.at(m);
                found = true;
            } else {
                currentUser = NULL;
            }
            
            ++m;
        }
        
        if(currentUser == NULL) {
            cout << "Invalid Username or Password!" << endl;
            cout << endl;
        }
    }
    
    cout << endl;
    cout << "Welcome back " << currentUser->getUsername() << "!" << endl;
    cout << endl;
}

void BBoard::run() {
    if (currentUser == NULL) {
        return;
    }
    char userInput;
    string tempGarb;
    while (userInput != 'Q' && userInput != 'q') {
        cout << "Menu" << endl;
        cout << "- Display Messages ('D' or 'd')" << endl;
        cout << "- Add New Topic ('N' or 'n')" << endl;
		cout << "- Add Reply to a Topic ('R' or 'r')" << endl;
        cout << "- Quit ('Q' or 'q')" << endl;
        cout << "Choose an action: ";
        cin >> userInput;
        if(userInput == 'Q' || userInput == 'q') {
        	cout << "Bye!" << endl;
        	return;
        }
        
        //cin >> tempGarb;
        //cout << endl;
        
        if((userInput != 'D' && userInput != 'd') && (userInput != 'N' && userInput != 'n') && (userInput != 'Q' && userInput != 'q') && (userInput != 'R' && userInput != 'r') && (userInput != 'Q' && userInput != 'q')) {
            cout << endl;
            cout << "Invalid action. Please try again.";
            cout << endl;
            return;
        }
        
        
        if(userInput == 'D' || userInput == 'd') {
            if(messageList.size() == 0) {
		        cout << endl;
		        cout << "Nothing to Display.";
		        cout << endl;
	        } else {
	            cout << endl;
                for(unsigned i = 0; i < messageList.size(); ++i) {
    		        if(!messageList.at(i)->isReply()) {
    			        cout << "---------------------------------------------------------" << endl;
    			        messageList.at(i)->print(0);
    		        }
    	        }
    	        cout << "---------------------------------------------------------" << endl;
	        }
	        cout << endl;
        } else if (userInput == 'N' || userInput == 'n') {
        	string sbj;
        	string tempGarb;
        	string body = "";
        	string fullBody = "";
        	
        	cout << "Enter Subject: ";
        	getline(cin, tempGarb);
        	getline(cin, sbj);
        	
        	cout << "Enter Body: ";
        	bool tempBool = true;
        	while(tempBool) {
        		getline(cin, body);
        		if(body.empty()) {
        			tempBool = false;
        		}
        		if (tempBool) {
        		    fullBody = fullBody + body;
        		    fullBody = fullBody + "\n";
        		}
        		if (!tempBool) {
        		    fullBody.pop_back();
        		}
        	}
        	
        	Topic *newTopic = new Topic(currentUser->getUsername(), sbj, fullBody, messageList.size() + 1);
        	messageList.push_back(newTopic);
        	
        	cout << endl;
    
        } else if(userInput == 'R' || userInput == 'r') {
            /*
            bool tempBool = false;
        	string body, subject, temp = "";
        	string fullBody = "";
        	int search;
        	
            cout << endl;
            
        	while(!tempBool) {
        		cout << "Enter Message ID (-1 for Menu): ";
        		cin >> search;
        		cout << endl;
        		
        		if(search == 0 || search > static_cast<int>(messageList.size())) {
        			    cout << "Invalid Message ID!!" << endl << endl;
        		} else {	
        			    tempBool = true;
        		}
        	}
        	
        	if(search < 0) {
        		cout << endl;
        	} else {
            	//cin.ignore();
            	cout << "Enter Body: ";
            	tempBool = true;
            	while(tempBool) {
            		getline(cin, body);
            		if(body == "\n") {
            			tempBool = false;
            			fullBody = fullBody + body;
            		} else {
            		    fullBody = fullBody + body;
            		    fullBody = fullBody + '\n';
            		}
            	}
            	
            	subject = messageList.at(search - 1)->getSubject();
            	Reply* userRep = new Reply(currentUser->getUsername(), subject, fullBody, messageList.size() + 1);
            	messageList.at(search - 1)->addChild(userRep);
            	messageList.push_back(userRep);
        	}
        	*/
        	bool correctIndex = false;
        	string body, subject, temp = "";
        	string fullBody = "";
        	int searchIndex;
        	
        	while(!correctIndex) {
        		cout << "Enter Message ID (-1 for Menu): ";
        		cin >> searchIndex;
        		
        		if(searchIndex == 0 ||
        			searchIndex > static_cast<int>(messageList.size())) {
        			cout << "Invalid Message ID!!" << endl << endl;
        		} else {	
        			correctIndex = true;
        		}
        	}
        	
        	if(searchIndex < 0) {
        		cout << endl;
        		return;
        	}
        
        	cin.ignore();
        	cout << "Enter Body: ";
        	while(true)	{
        		getline(cin, body);
        		if(body.empty()) {
        			break;
        		}
        		
        		fullBody += (body + "\n");
        	}
        	fullBody.pop_back();
        	
        	
        	subject = messageList.at(searchIndex - 1)->getSubject();
        	
        	Reply* userRep = new Reply(currentUser->getUsername(),
        		subject, fullBody, messageList.size() + 1);
        		
        	messageList.at(searchIndex - 1)->addChild(userRep);
        	messageList.push_back(userRep);
		}
    }
    
    cout << "Bye!" << endl;
    return;
}