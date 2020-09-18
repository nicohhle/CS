#include <iostream>

#ifndef PLAYLIST_H
#define PLAYLIST_H

using namespace std;

class PlaylistNode {
    private: 
        string uniqueID; // Initialized to "none" in default constructor
        string songName; // Initialized to "none" in default constructor
        string artistName; // Initialized to "none" in default constructor
        int songLength; // Initialized to 0 in default constructor
        PlaylistNode* nextNodePtr; // Initialized to 0 in default constructor
        
        
    public:
        PlaylistNode();
        PlaylistNode(string ID, string songName, string artistName,int songLength );
        void InsertAfter(PlaylistNode* before); //(1 pt)
        void SetNext(PlaylistNode* after); //- Mutator (1 pt)
        string GetID();// - Accessor
        string GetSongName();// - Accessor
        string GetArtistName();// - Accessor
        int GetSongLength(); // - Accessor
        PlaylistNode* GetNext(); // - Accessor
        void PrintPlaylistNode();
};





#endif