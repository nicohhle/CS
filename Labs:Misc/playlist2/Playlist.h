#include <iostream>

#ifndef PLAYLIST_H
#define PLAYLIST_H

class PlaylistNode {
  private:
    string uniqueID;
    string songName;
    string artistName;
    int songLength;
    PlaylistNode* nextNodePtr;
    
  public:
    PlaylistNode();
    PlaylistNode(string uniqueID, string songName, string artistName, int songLength);
    void InsertAfter(PlaylistNode*);
    void SetNext(PlaylistNode*);
    string GetID() const;
    string GetSongName() const;
    string GetArtistName() const;
    int GetSongLength() const;
    PlaylistNode* GetNext() const;
    void PrintPlaylistNode() const;
};

#endif