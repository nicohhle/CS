#include <iostream>

using namespace std;

#include "Playlist.h"


PlaylistNode::PlaylistNode() {
    uniqueID = "none";
    songName = "none";
    artistName = "none";
    songLength = 0;
    nextNodePtr = 0;
    return;
}

PlaylistNode::PlaylistNode(string ID, string songName, string artistName,int songLength ) {
    uniqueID = ID;
    this -> songName = songName;
    this -> artistName = artistName;
    this -> songLength = songLength;
    nextNodePtr = 0;
    return;
}


void PlaylistNode::InsertAfter(PlaylistNode* before) {
    before -> nextNodePtr = this -> nextNodePtr; 
    this -> nextNodePtr = before;
    return;
    
}

void PlaylistNode::SetNext(PlaylistNode* after) {
    this->nextNodePtr = after;
    return;
}

string PlaylistNode::GetID() {
    return uniqueID;
}

string PlaylistNode::GetSongName() {
    return songName;
}

string PlaylistNode::GetArtistName() {
    return artistName;
}

int PlaylistNode::GetSongLength() {
    return songLength;
}

PlaylistNode* PlaylistNode::GetNext() {
    return this->nextNodePtr;
}

void PlaylistNode::PrintPlaylistNode() {
    cout << "Unique ID: " << uniqueID << endl;
    cout << "Song Name: " << songName << endl;
    cout << "Artist Name: " << artistName << endl;
    cout << "Song Length (in seconds): " << songLength << endl;
}