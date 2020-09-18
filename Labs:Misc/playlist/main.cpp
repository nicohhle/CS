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
    cout << "Choose an option:";
    // cout << endl;
    
}

int main() {
    PlaylistNode *head = 0;
    PlaylistNode *tail = 0;
    
    string title;
    cout << "Enter playlist's title:" << endl;
    getline(cin, title);
    cout << endl;
    
    PrintMenu(title);
    
    char action;
    
    cin >> action;
    
    cout << endl;
    
    while (action != 'q') {
        // cout << endl;
        
        if (action == 'a') {
            cout << "ADD SONG" << endl;
            
            // PlaylistNode *list;
            string uniqueID;
            string songName;
            string artistName;
            int songLength;
            
            cout << "Enter song's unique ID:" << endl;;
            cin >> uniqueID;
            cin.ignore();
            
            cout << "Enter song's name:" << endl;
            getline(cin, songName);
            
            cout << "Enter artist's name:" << endl;
            getline(cin, artistName);
            
            cout << "Enter song's length (in seconds):" << endl;
            cin >> songLength;
            // cout << endl;
            
            PlaylistNode *list = new PlaylistNode(uniqueID, songName, artistName, songLength);
            // list->SetNext(list);
            
            if (head == 0 && tail == 0) {
                head = tail = list;
                
            } else if (head->GetNext() == 0) {
                tail = list;
                head->SetNext(tail);
                
            } else {
                PlaylistNode *temp = tail;
                tail = new PlaylistNode(uniqueID, songName, artistName, songLength);
                temp->SetNext(tail);
                
            }
            
            cout << endl;
            
        } else if (action == 'd') {
            cout << "REMOVE SONG" << endl;
            cout << "Enter song's unique ID:" << endl;
            
            string uniqueID;
            cin >> uniqueID;
            // cout << endl;
            
            PlaylistNode *prev = 0;
            PlaylistNode *curr = head;
            
            if (curr->GetID() == uniqueID) {
                PlaylistNode *temp = head;
                head = head->GetNext();
                
                cout << "\"" << curr->GetSongName() << "\" removed." << endl;
                
                delete temp;
            }
            
            while (curr != 0) {
                if (curr->GetID() == uniqueID) {
                    cout << "\"" << curr->GetSongName() << "\" removed." << endl;
                    break;
                    
                }
                
                prev = curr;
                curr = curr->GetNext();
            }
            
            if (curr == head && curr == tail) {
                head = 0;
                delete tail;
                
            } else if (curr == head) {
                // PlaylistNode *temp = head;
                head = head->GetNext();
                delete curr;
                
            } else if (curr == tail) {
                tail = prev;
                delete curr;
                
            } else {
                prev->SetNext(curr->GetNext());
                delete curr;
            }
            
            // cout << "\"" << curr->GetSongName() << "\" removed" << endl;
            // delete curr;
            
            cout << endl;
            
        } else if (action == 'c') {
            cout << "CHANGE POSITION OF SONG" << endl;
            cout << "Enter song's current position:" << endl;
            
            int posCurr = 0;
            cin >> posCurr;
            
            cout << "Enter new position for song:" << endl;
            
            int posNew = 0;
            cin >> posNew;
            
            // cout << endl;
            
            // PlaylistNode *prev = 0;
            // PlaylistNode *curr = head;
            PlaylistNode *copy = 0;
            
            int nodes = 0;
            
            for (PlaylistNode *curr = head; curr != 0; curr = curr->GetNext()) {
                ++nodes;
            }
            
            if (posCurr == 1) {
                copy = head;
                head = head->GetNext();
            } else if (posCurr == nodes) {
                copy = tail;
                
                for (PlaylistNode *curr = head; curr->GetNext()->GetNext() != 0; curr = curr->GetNext()) {
                    tail = curr;
                }
                
                tail = tail->GetNext();
                tail->SetNext(0);
            } else {
                int num = 1;
                
                for (PlaylistNode *curr = head; curr != 0; curr = curr->GetNext()) {
                    if (num == posCurr - 1) {
                        copy = curr->GetNext();
                        curr->SetNext(curr->GetNext()->GetNext());
                    }
                    
                    ++num;
                }
            }
            
            int pos = 1;
            
            // while (curr != 0) {
            //     if (pos != posCurr) {
            //         pos = pos + 1;
            //         prev = curr;
            //         curr = curr->GetNext();
            //     }
            // }
            
            // if (posNew < 1) {
                
            //     PlaylistNode *temp = head;
            //     head = curr;
            //     head->SetNext(head);
                
            //     delete temp;
            // }
            
            // pos = 1;
            
            // prev->SetNext(curr->GetNext());
            
            if (posNew == 1) {
                PlaylistNode *temp = head;
                head = copy;
                copy->SetNext(temp);
                
            } else {
                for (PlaylistNode *curr = head; curr != 0; curr = curr->GetNext()) {
                    if (pos == posNew - 1) {
                        PlaylistNode *temp = curr->GetNext();
                        curr->SetNext(copy);
                        copy->SetNext(temp);
                    }
                    
                    ++pos;
                }
            }
            
            cout << "\"" << copy->GetSongName() << "\"" << " moved to position " << posNew << endl;
            cout << endl;
            
        } else if (action == 's') {
            cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
            cout << "Enter artist's name:" << endl;
            
            string artistName;
            cin.ignore();
            getline(cin, artistName);
            
            cout << endl;
            
            int i = 1;
            
            PlaylistNode *a = head;
            int counter = 0;
            while (a != 0) {
                if (a->GetArtistName() == artistName) {
                    cout << i << "." << endl;
                    
                    a->PrintPlaylistNode();

                    if (counter != i) {
                        cout << endl;
                    }
                    
                    ++counter;
                    
                }
                
                a = a->GetNext();
                ++i;
            }
            
            // cout << endl;
            
        } else if (action == 't') {
            cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
            
            PlaylistNode *t = head;
            int total = 0;
            
            while (t != 0) {
                total = total + t->GetSongLength();
                
                t = t->GetNext();
            }
            
            cout << "Total time: " << total << " seconds" << endl;
            
            cout << endl;
            
        } else if (action == 'o') {
            cout << title << " - OUTPUT FULL PLAYLIST" << endl;
            
            if (head == 0 && tail == 0) {
                cout << "Playlist is empty" << endl;
                
                cout << endl;
            }
            
            PlaylistNode *now = head;
            int i = 1;
            int counter = 0;
            while (now != 0) {
                cout << i << "." << endl;
                
                now->PrintPlaylistNode();
                // cout << endl;
                
                if (counter != i) {
                    cout << endl;
                }
                
                ++counter;
                
                now = now->GetNext();
                
                ++i;
            }      
            
            // cout << i << ". " << endl;
            // tail->PrintPlaylistNode();
            
        } else {
            cout << "Invalid option, please choose another." << endl;
        }
        
        // cout << endl;
        
        PrintMenu(title);
        
        cin >> action;
        
        cout << endl;
    }
    
    
    if (action == 'q') {
        // cout << "Goodbye!" << endl;
        return 0;
    }
    
    return 0;
}