#include <iostream>

using namespace std;

#include "IntList.h"

/* 
IntList::IntList() {
    head = 0;
    tail = 0;
}

IntList::~IntList() {
    delete head;
    delete tail;
}

void IntList::display() const {
    IntNode *curr = head;
    
    while (curr != 0) {
        cout << curr->data;
        
        if (curr->next != 0) {
            cout << " ";
        }
        
        curr = curr->next;
    }
}

void IntList::push_front(int value) {
    IntNode *temp = this->head;
    head = new IntNode(value);
    head->next = temp;
    
    if (tail == 0) {
        tail = head;
    }
}

void IntList::pop_front() {
    if (empty()) {
        return;
    } 
    
    if (head == tail) {
        delete head;
        head = 0;
        tail = 0;
        
        return;
    }
    
    // IntNode* curr;
    // curr = this->head;
    
    // this->head = curr->next;
    // return;
    
    IntNode *curr;
    curr = this->head;
    this->head = curr->next;
    
    delete curr;
}

bool IntList::empty() const {
    if (head == 0 && tail == 0) {
        return true;
    } else {
        return false;
    }
}
*/
IntList::IntList() {
    head = 0;
    tail = 0;
}

IntList::~IntList(){
    while (!empty()) {
        pop_front();
    }
}

void IntList::display() const{
    if(empty()) {
        return;
    }
    else {
        IntNode* currentNode = head;
        
        cout << currentNode->data;
        while(currentNode->next != 0) {
            currentNode = currentNode->next;
            cout << ' ' << currentNode->data;
        }
    }
}

void IntList::push_front(int value){
  
    IntNode* temp = new IntNode(value);
  
    temp->next = head;
    head = temp;
    if(tail == 0) {
        tail = temp;
    }
}

void IntList::pop_front(){
    if(empty()) {
        return;
    }
    else {
        IntNode* temp = head;
        head = head->next;
        delete temp;
    }
    if(head == 0) {
        tail = 0;
    }
  
}

bool IntList::empty() const{
    if(head == 0 && tail == 0) {
        return true;
    }
    return false;
}

IntList::IntList(const IntList &cpy) {
    head = 0;
    tail = 0;
    
    if(!cpy.empty()) {
        IntNode* curr = cpy.head;
        
        while(curr != 0) {
            push_back(curr->data);
            curr = curr->next;
        }
    }

}

IntList & IntList::operator=(const IntList &rhs) {
    if (this == &rhs) {
        return *this;
    }
    else if(rhs.empty()) {
        head = 0;
        tail = 0;
    }
    else {
        clear();
        IntNode* curr = rhs.head;
        while(curr != 0) {
            push_back(curr->data);
            curr = curr->next;
        }
    }
    return *this;
}

void IntList::push_back(int value) {
  
    IntNode* temp = new IntNode(value);

    if (empty()) {
        head = temp;
        tail = temp;
    }
    else {
        tail->next = temp;
        tail = temp;
    }
}
  
void IntList::clear() {
    while (!empty()) {
        pop_front();
    }
}

void IntList::selection_sort() {
    if (empty()) {
        return;
    }
    else {
        IntNode* min = head;
        int temp = 0;
        for (IntNode* i = head; i->next != 0; i = i->next) {
            min = i;
            for(IntNode* j = i->next; j != 0; j = j->next) {
          
                if (min->data > j->data) {
                    min = j;
                }
            }
            temp = i->data;
            i->data = min->data;
            min->data = temp;
        }
    }
}

void IntList::insert_ordered(int value) {
    if(empty()) {
        push_front(value);
    }
    else if (value <= head->data) {
        push_front(value);
    }
    else if (value >= tail->data) {
        push_back(value);
    }
    else {
        IntNode* prev = head;
        IntNode* curr = head->next;
        IntNode* temp = new IntNode(value);
        while(curr != 0) {
          
            if(value < curr->data) {
                prev->next = temp;
                temp->next = curr;
                return;
            }
          
            prev = prev->next;
            curr = curr->next;
        }
    }
  
}

void IntList::remove_duplicates() { //TODO
    if(empty() || head == tail) {
        return;
    }
    else {
        IntNode* prev = 0;
        // int ite9ration = 0;
        // int jiter = 0;
        for(IntNode* i = head; i != 0; i = i->next) { //FIXME seg fault! maybe issue with the deleting??
            prev = i;
            for(IntNode* j = i->next; j != 0; j = prev->next) {
              
                if(i->data == j->data) {
                    if (j == tail) {
                        delete j;
                        tail = prev;
                        tail->next = 0;
                        //cout << "tail" << endl;
                        //cout << "j " << j->next << '/' << j->data << endl;
                        if (head == tail) {
                            //cout << "alsdhalsdkh" << endl;
                            return;
                        }
                    }
                    else {
                        prev->next = j->next;
                        delete j;
                        //j = prev->next;  
                        //cout << "match found" << endl;
                    }
                }
              
              
                // if (j == tail && i->data == j->data) { //working with last node, WORKS!! :D (i think)
                //     delete j;
                //     tail = prev;
                //     tail->next = 0;
                //     cout << "tail" << endl;
                //     if (head == tail) {
                //         //cout << "alsdhalsdkh" << endl;
                //         return;
                //     }
                //     // else {
                //     //     j = tail;
                //     // }
                // }
                // else if(i->data == j->data) {

                //     prev->next = j->next;
                //     delete j;
                //     //j = prev->next;  
                //     cout << "match found" << endl;
                // }
                else {
                    prev = prev->next;
                }
            }
           // cout << "J LOOPed" << endl;
        }
    }
}
  
ostream & operator<<(ostream &out, const IntList &rhs) {
    if(rhs.empty()) {
        return out;
    }
    else {
        IntNode* currentNode = rhs.head;
        // currentNode = head->next;
        out << currentNode->data;
        while(currentNode->next != 0) {
            currentNode = currentNode->next;
            out << ' ' << currentNode->data;
        }
    }
    return out;
}


/*

IntList::IntList(const IntList & copy) {
    // head = new IntNode(copy.head->data);
        
    head = 0;
    tail = 0;
    
    // for (IntNode *i = copy.head->next; i != copy.tail; i = i->next) {
    //     tail = new IntNode(i->data);
    // }
    
    for (IntNode *i = copy.head; i; i = i->next) {
        push_back(i->data);
    }
}

IntList & IntList::operator=(const IntList &rhs) {
    if (this != &rhs) {
        // delete head;
        // delete tail;
        
        // head = rhs.head;
        // tail = rhs.tail;
        
        head = 0;
        tail = 0;
        
        for (IntNode *i = rhs.head; i; i = i->next) {
            push_back(i->data);
        }
    }
    
    return *this;
}
    
void IntList::push_back(int value) {
    if (head == 0 && tail == 0) {
        head = new IntNode(value);
        tail = head;
        
        return;
    }
    
    IntNode *temp = new IntNode(value);
    tail->next = temp;
    tail = temp;
}
    
void IntList::clear() {
    // IntNode *temp = head;
    
    // while (head->next != 0) {
    //     temp = head;
    //     head = head->next;
    //     delete temp;
    // }
    
    // if (head->next == 0) {
    //     temp = head;
    //     head = 0;
    //     tail = 0;
    //     delete temp;
    // }
    
    for (IntNode *i = head; i != 0; i = i->next) {
        i->data = 0;
    }
    
    head = 0;
    tail = head;
}

void IntList::selection_sort() {
    // IntNode *temp = head;
    
    for (IntNode *i = head; i != 0; i = i->next) {
        int min = i->data;
        
        for (IntNode *j = i->next; j != 0; j = j->next) {
            if (j->data < min) {
                // if (j->next->next == 0) {
                //     i->next = 0;
                // }    
                // temp->data = j->next->data;
                // temp->next = j->next->next;
                // j->next->data = i->data;
                // j->next->next = i->next;
                // i->data = temp->data;
                // i->next = temp->next;
                
                min = j->data;
                j->data = i->data;
                i->data = min;
            }
        }
    }
}

void IntList::insert_ordered(int value) {
    if (head == 0) {
        // head = new IntNode(value);
        // tail = head;
        
        push_front(value);
        
        return;
    } else if (head->next == 0) {
        if (head->data >= value) {
            push_front(value);
            
            return;
        } else {
            push_back(value);
            
            return;
        }
    } else if (head->data >= value) {
        push_front(value);
        
        return;
    } else if (tail->data <= value) {
        push_back(value);
        
        return;
    } else {
        
    // else if (head == tail) {
    //     if (head->data < value) {
    //         head->next = new IntNode(value);
    //         tail = head->next;
    //     }
    // }
    
    IntNode *prev = head;
    IntNode *curr = prev->next;
    while (curr->data < value) {
        prev = prev->next;
        curr = curr->next;
    }
    
    IntNode *temp = new IntNode(value);
    prev->next = temp;
    temp->next = curr;
    
    // IntNode *prev = head;
    // IntNode *curr = head->next;
    
    // for (IntNode *k = head; !(prev->data <= value && value <= curr->data); k = k->next) {
    //     prev = prev->next;
    //     curr = curr->next;
    // }
    
    // IntNode *temp = new IntNode(value);
    // temp->next = curr;
    // prev->next = temp;
    }
}

void IntList::remove_duplicates() {
    // if (head == 0) {
    //     return;
    // } 
    if (empty() || head == tail) {
        return;
    } else {
        IntNode* prev = 0;
        
        for(IntNode* i = head; i != 0; i = i->next) { 
            for(IntNode* j = i->next; j != 0; j = prev->next) {
              
                if(i->data == j->data) {
                    if (j == tail) {
                        delete j;
                        tail = prev;
                        tail->next = 0;
                        
                        if (head == tail) {
                            
                            return;
                        }
                    }
                    else {
                        prev->next = j->next;
                        delete j;
                        
                    }
                } else {
                    prev = prev->next;
                }
            }
        }
    }
    
    // for (IntNode *i = head; i != tail; i = i->next) {
    //     int val = i->data;
    //     IntNode *prev = i;
        
//        // for (IntNode *j = i; j->next != tail; j = j->next) {
        
    //     for (IntNode *j = i->next; j != 0;) {
    // 		if(val == j->data && j->next != 0) {
    // 			prev->next = j->next;
    // 			delete j;
    // 			j = prev;
    // 		} else if(val == j->data && j == tail) {
    // 			tail = prev;
    // 			delete j;
    // 			tail->next = 0;
    // 		}
    //         if(j == prev) {
    // 			j = j->next;
    // 		} else {
    // 			j = j->next;
    // 			prev = prev->next;
    // 		}
	   // }
//            // if (i->data == j->next->data) {
//            //     if (j->next == tail) {
//            //         j = tail;
//            //         break;
//            //     }
            
//            //     IntNode *curr = j;
//            //     j = j->next;
//            //     i->next = i->next->next;
//            //     delete curr;
//            // }
    // }
}

ostream & operator<<(ostream &out, const IntList &rhs) {
    if (rhs.head == 0) {
        out << "";
        
        return out;
    }
    
    // while (rhs.head != 0) {
    //     out << rhs.head->data;
        
    //     if (rhs.head->next != 0) {
    //         out << " ";
    //     }
    // }
    
    IntNode *curr = rhs.head;
    
    while (curr->next != 0) {
        out << curr->data << " ";
        
        curr = curr->next;
    }
    
    out << curr->data;
    
    return out;
}

*/
