#include <iostream>
#include <string>

using namespace std;

#include "Playlist.h"

// Constructors -----------------------------------------------------------------------------------------

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

// Mutators -----------------------------------------------------------------------------------------

void PlaylistNode::InsertAfter(PlaylistNode* prev) {
    prev->nextNodePtr = this->nextNodePtr;  //prev will be inserted in btwn, prev point to this nxt
    this->nextNodePtr = prev;               //this will be reassigned to point to prev 
}

void PlaylistNode::SetNext(PlaylistNode* next) {
    nextNodePtr = next;
}

// Accessors -----------------------------------------------------------------------------------------

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

PlaylistNode* PlaylistNode::GetNext() const {
    return nextNodePtr;
}

// Print -----------------------------------------------------------------------------------------

void PlaylistNode::PrintPlaylistNode() const {
    cout << "Unique ID: " << this->GetID() << endl;
    cout << "Song Name: " << this-> GetSongName() << endl;
    cout << "Artist Name: " << this-> GetArtistName() << endl;
    cout << "Song Length (in seconds): " << this->GetSongLength() << endl;
}