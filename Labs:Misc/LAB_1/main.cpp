#include <iostream>
#include <string>

using namespace std;

#include "Playlist.h"


void PrintMenu(string title) {
    cout << title << " PLAYLIST MENU" << endl;
    cout << "a - Add song" << endl;
    cout << "d - Remove song" << endl;
    cout << "c - Change position of song" << endl;
    cout << "s - Output songs by specific artist" << endl;
    cout << "t - Output total time of playlist (in seconds)" << endl;
    cout << "o - Output full playlist" << endl;
    cout << "q - Quit" << endl;
    cout << endl;
    cout << "Choose an option:" << endl;
    return;
} 


int main() {
    string title;
    char choice;
    PlaylistNode* head = 0;
    PlaylistNode* tail = 0;
    PlaylistNode* curr = 0;
    PlaylistNode* prev = 0;
    string uniqueID; 
    string songName; 
    string artistName; 
    int songLength; 
    
    cout << "Enter playlist's title:" << endl;
    getline(cin, title);
    cout << endl;
    
    PrintMenu(title);
    
    while (cin >> choice) {
        if (choice == 'q') {
            return 0;
        }
        else if ( choice == 'a') {
            cout << endl;
            cout << "ADD SONG" << endl;
            cout << "Enter song's unique ID:" << endl;
            cin >> uniqueID;
            cout << "Enter song's name:" << endl;
            cin.ignore();
            getline(cin, songName);
            cout << "Enter artist's name:" << endl;
            getline(cin, artistName);
            cout << "Enter song's length (in seconds):" << endl;
            cin >> songLength;
            
            if (head == 0) {
                head = new PlaylistNode(uniqueID, songName, artistName, songLength);
                tail = head;
            }
            else {
              PlaylistNode* temp = new PlaylistNode(uniqueID, songName, artistName, songLength);
              tail -> SetNext(temp);
              tail = temp;
              temp = 0;
            }
            
            
            cout << endl;
        }
        
        else if ( choice == 'd') {
            cout << "REMOVE SONG" << endl;
            cout << "Enter song's unique ID:" << endl;
            cin >> uniqueID;
            
            curr = head;
            
            while (curr != 0) {
                if (curr -> GetID() == uniqueID) {
                    cout << "\"" << curr -> GetSongName() << "\" removed." << endl;
                    break;
                }
                else {
                    prev = curr;
                    curr = curr -> GetNext();
                }
                
            }
            
            if (curr == head && curr == tail) {
                head = 0;
                tail = 0;
                delete curr;
            }
            else if (curr == head) {
                head = head -> GetNext();
                delete curr;
            }
            else if (curr == tail) {
                tail = prev;
                tail -> SetNext(0);
                delete curr;
            }
            else {
                prev -> SetNext(curr -> GetNext()); 
                delete curr;
            }
            cout << endl;
        
        }
        
        else if ( choice == 'c') {
            cout << "CHANGE POSITION OF SONG" << endl;
            PlaylistNode* newPos = 0;
            PlaylistNode* prevNewPos = 0;
            unsigned counter  = 0;
            unsigned i = 0;
            unsigned currPosition;
            unsigned newPosition;
            curr = head;
            
            while ( curr != 0 ) {
                ++counter;
                prev = curr;
                curr = curr -> GetNext();
            }
            
            cout << "Enter song's current position:" << endl;
            cin >> currPosition;
            cout << "Enter new position for song:" << endl;
            cin >> newPosition;
            
            if (currPosition <= 1) {
                curr = head;
                prev = 0;
            }
            else if (currPosition >= counter){
                curr = tail;
                prev = head;
                while (prev -> GetNext() != tail) {
                    prev = prev -> GetNext();
                }
            }
            else {
                curr = head;
                prev = 0;
                for (i = 1; i < currPosition; ++i) {
                        prev = curr;
                        curr = curr -> GetNext();
                    }
            }
            
            
            
            if (newPosition <= 1) {
                newPos = head;
                prevNewPos = 0;
                newPosition = 1;
            }
            else if (newPosition >= counter) {
                newPos = tail;
                prevNewPos = head;
                while (prevNewPos -> GetNext() != tail) {
                    prevNewPos = prevNewPos -> GetNext();
                }
                newPosition = counter;
            }
            
            else {
                newPos = head;
                for (i = 1; i < newPosition; ++i) {
                        prevNewPos = newPos;
                        newPos = newPos -> GetNext();
                    }
            }
            
            if (newPos == curr) {
                cout << "\"" << curr -> GetSongName() << "\" moved to position " << newPosition << endl;
            }
            else if (newPos == head) {
                if (curr == tail) {
                    tail = prev;
                    tail -> SetNext(0);
                    curr -> SetNext(head);
                    head = curr;
                    cout << "\"" << curr -> GetSongName() << "\" moved to position " << newPosition << endl;
                }
                else {
                    prev -> SetNext(curr -> GetNext());
                    curr -> SetNext(head);
                    head = curr;
                }
                
                
            }
            
            else if (newPos == tail) {
                if (curr == head) {
                    head = curr -> GetNext();
                    tail -> SetNext(curr);
                    curr -> SetNext(0);
                    tail = curr;
                    cout << "\"" << curr -> GetSongName() << "\" moved to position " << newPosition << endl;
                }
                else {
                    prev -> SetNext(curr -> GetNext());
                    tail -> SetNext(curr);
                    tail = curr;
                    curr -> SetNext(0);
                    cout << "\"" << curr -> GetSongName() << "\" moved to position " << newPosition << endl;
                }
                
                
            }
            
            else {
                if (curr == head) {
                    head = curr -> GetNext();
                    curr -> SetNext(newPos -> GetNext());
                    newPos -> SetNext(curr);
                    cout << "\"" << curr -> GetSongName() << "\" moved to position " << newPosition << endl;
                }
                else if (curr == tail) {
                    tail = prev;
                    tail -> SetNext(0);
                    curr -> SetNext(newPos);
                    prevNewPos -> SetNext(curr);
                    cout << "\"" << curr -> GetSongName() << "\" moved to position " << newPosition << endl;
                }
                else {
                    if (currPosition < newPosition) {
                        prev -> SetNext(curr -> GetNext());
                        curr -> SetNext(newPos -> GetNext());
                        newPos -> SetNext(curr);
                        cout << "\"" << curr -> GetSongName() << "\" moved to position " << newPosition << endl;
                    }
                    else if (currPosition > newPosition) {
                        prev -> SetNext(curr -> GetNext());
                        curr -> SetNext(newPos);
                        prevNewPos -> SetNext(curr);
                        cout << "\"" << curr -> GetSongName() << "\" moved to position " << newPosition << endl;
                    }
                    
                }
                
                
            }
            
            cout << endl;
        }
        
        
        else if ( choice == 's') {
            cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
            cout << "Enter artist's name:" << endl;
            cin.ignore();
            getline(cin, artistName);
            cout << endl;
            
            curr = head;
            for (unsigned i = 1; curr != 0; ++i  ) {
                if (curr -> GetArtistName() == artistName) {
                    cout << i << "." << endl;
                    curr -> PrintPlaylistNode();
                    cout << endl;
                }
                curr = curr -> GetNext();
            }
            
        }
        
        else if ( choice == 't') {
            cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
            
            unsigned seconds = 0;
            curr = head;
            while (curr != 0) {
                seconds += curr -> GetSongLength();
                curr = curr -> GetNext();
            }
            
            cout << "Total time: " << seconds << " seconds" << endl;
            cout << endl;
            
        }
        
        
        else if ( choice == 'o') {
            if (head == 0){
                cout << title << " - OUTPUT FULL PLAYLIST" << endl;
                cout << "Playlist is empty" << endl;
                cout << endl;
            }
            else {
                curr = head;
                int counter = 1;
                cout << title << " - OUTPUT FULL PLAYLIST" << endl;
                while (curr != 0) {
                    cout << counter << "." << endl;
                    curr -> PrintPlaylistNode();
                    curr = curr -> GetNext();
                    ++counter;
                    cout << endl;
                }
                
            }
            
                
        }
        
        PrintMenu(title);
            
            
        
    } 
    
    

return 0;
}
