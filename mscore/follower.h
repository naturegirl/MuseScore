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
      /*
      void createNotelist(Eventmap *events);   // creating the note list by reading events.
      List<NoteElement *> getNotelist();
      List<int> getPlayedlist();
      void insertPlayedlist(int pitch);   // insert new played note into played list;
*/
};

#endif
