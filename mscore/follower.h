//
//  follower.h
//  mscore
//
//  Created by Jennifer Guo on 1/6/13.
//
//

#ifndef mscore_follower_h
#define mscore_follower_h

#include "libmscore/event.h"
#include <list>

using namespace std;    // for list

// information we save for each note for alignment
class NoteElement {
public:
      NoteElement(int _pitch, int _time) { pitch = _pitch; time = _time; played = false; error = false; };
      int pitch;
      int time;
      bool played;      // whether already played
      bool error;       // whether user made an error
};

class Follower {

      list<NoteElement *> notelist; // what's expected in the score
      list<int> playedlist;         // what was played by user
      
public:
      Follower();
      ~Follower();
      
      void createNotelist(EventMap *events);   // creating the note list by reading events.
      list<NoteElement *> getNotelist();
      list<NoteElement *>::iterator getNotelist_firstUnplayed();       // get position in note list of last played element
      void printNotelist();
      
      
      list<int> getPlayedlist();
      void insertPlayedlist(int pitch);   // insert new played note into played list;
      void emptyPlayedlist();       // sets it to empty again.
      void printPlayedlist();
      
      void update();    // call after insertPlayedlist() to update the played value in notelist. This is where the following happens.

};

#endif
