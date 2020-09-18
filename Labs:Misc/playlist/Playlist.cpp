#include <iostream>
#include <string>

using namespace std;

#include "Playlist.h" 

PlaylistNode::PlaylistNode() {
    uniqueID = "none";
    songName = "none";
    artistName = "none";
    songLength = 0;
    nextNodePtr = 0;
}

PlaylistNode::PlaylistNode(string uniqueID, string songName, string artistName, int songLength)
                        : uniqueID(uniqueID), songName(songName), 
                          artistName(artistName), songLength(songLength) { 
                              nextNodePtr = 0;
                          }

void PlaylistNode::InsertAfter(PlaylistNode *prev) {
    // prev->SetNext(this);
    
    prev->nextNodePtr = this->nextNodePtr;
    this->nextNodePtr = prev;
}

void PlaylistNode::SetNext(PlaylistNode *next) {
    nextNodePtr = next;
}

string PlaylistNode::GetID() const {
    return uniqueID;
}

string PlaylistNode::GetSongName() const {
    return songName;
}

string PlaylistNode::GetArtistName() const {
    return artistName;
}

int PlaylistNode::GetSongLength() const {
    return songLength;
}  

PlaylistNode * PlaylistNode::GetNext() const {
    return nextNodePtr;
}

void PlaylistNode::PrintPlaylistNode() const {
    cout << "Unique ID: " << this->GetID() << endl;
    cout << "Song Name: " << this->GetSongName() << endl;
    cout << "Artist Name: " << this->GetArtistName() << endl;
    cout << "Song Length (in seconds): " << this->GetSongLength() << endl;
}