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
      
      // these variables are all for Dannnenberg's algorithm in update2
      static const int n_matrix = 20;      // size of bestlength matrix. Matrix is actually bigger by one!
      int bestlength[n_matrix+1][n_matrix+1];       // from Dannenberg's paper. one init row and col!
      int score[n_matrix];
      int score_time[n_matrix];     // in parallel with score to store corresponding time. Helps us find in notelist
      int performance[n_matrix];
      
      // when creating a new bestlength we should take this element.
      // initialized in createNotelist()
      // updated in update2() when initializing score array
      list<NoteElement *>::iterator nextMatrixStart;
      list<NoteElement *>::iterator lastMatch;  // last matched element. So we don't have to start searching for the next one from the beginning.
      
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
      
      void printBestlength();
      
      void update();    // call after insertPlayedlist() to update the played value in notelist. This is where the following happens.
      
      void update2();

};

#endif
