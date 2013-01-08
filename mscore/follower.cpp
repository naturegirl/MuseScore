//
//  follower.cpp
//  mscore
//
//  Created by Jennifer Guo on 1/7/13.
//
//

#include "follower.h"



Follower::Follower() {
      
}

Follower::~Follower() {
      
}

// creating the note list by reading events.
// events must have been read sofar.
// read whole score
void Follower::createNotelist(EventMap *events) {
      
      notelist.clear();       // empty first
      
      EventMap::iterator it = events->begin();
      Event *event;
      NoteElement *noteElm;
      int time;
      for (;it != events->end(); it++) {

            time = it.key();
            event = &(it.value());
            
            // skip metronome
            if (event->type() == ME_TICK1 || event->type() == ME_TICK2)
                  continue;
            
            // do another way. If time isn't a full number than it's not a note
            // this way we won't skip notes that are at the same time (chords)
            if (time % 10 != 0)
                  continue;
            
            int pitch = event->pitch();
            
            noteElm = new NoteElement(pitch, time);
            notelist.push_back(noteElm);
      }
      nextMatrixStart = notelist.begin();
}

list<NoteElement *> Follower::getNotelist() {
      return notelist;              // return pointer instead?
}

// border conditions: Everything played. Return null
list<NoteElement *>::iterator Follower::getNotelist_firstUnplayed() {
      list<NoteElement *>::iterator it;
      for (it = notelist.begin(); it != notelist.end(); ++it) {
            NoteElement *elm = *it;
            if (elm->played == false)
                  return it;
      }
      return it;      // everything played. Returning last elm?
}

void Follower::printNotelist() {
      list<NoteElement *>::const_iterator it;
      printf("printNotelist(): ");
      int cnt = 0;
      for (it = notelist.begin(); it != notelist.end(); ++it) {
            NoteElement *elm = *it;
            int pitch = elm->pitch;
            int time = elm->time;
            bool played = elm->played;
            printf("%d ", pitch);
            if (played)
                  printf("true\n");
            else
                  printf("false\n");
            cnt++;
            if (cnt > 20) break;
      }
      printf("\n");
}

list<int> Follower::getPlayedlist() {
      return playedlist;            // do I have to return pointer instead?
}

// insert new played note into played list;
void Follower::insertPlayedlist(int pitch) {
      playedlist.push_back(pitch);  // insert at end
}

// make it empty again
void Follower::emptyPlayedlist() {
      playedlist.clear();
}

void Follower::printPlayedlist() {
      list<int>::const_iterator it;
      printf("printPlayedlist(): ");
      for (it = playedlist.begin(); it != playedlist.end(); ++it)
            printf("%d ", *it);
      printf("\n");
      printf("size %d\n", playedlist.size());
      int pitch = playedlist.back();
}


// in the end all versions of update should or should not update played value
void Follower::update() {
      int pitch = playedlist.back();      // last element
      list<NoteElement *>::iterator it = getNotelist_firstUnplayed();
      NoteElement *elm = *it;
      if (elm->pitch == pitch)
            elm->played = true;     // sets played to true when right note.
      
      
}



// using Dannenberg's algorithm.
void Follower::update2() {
      static int pos_cnt;     // note that we start with 1. Col and Row zero are just for initialization
      
      // start a new matrix
      if (pos_cnt == 0) {
            // do some initialization
            memset(bestlength, 0, sizeof(bestlength));
            memset(score, 0, sizeof(score));
            memset(performance, 0, sizeof(performance));
            // not even necessary, just start with 1 then!
            for (int i = 0; i < n_matrix+1; ++i)
                  bestlength[i][0] = 0;  // set initialization col
            for (int i = 0; i < n_matrix+1; ++i)
                  bestlength[0][i] = 0;  // set initialization row
            
            // fill score array
            for (int i = 0; i < n_matrix; ++i) {
                  NoteElement *elm = *nextMatrixStart;
                  score[i] = elm->pitch;
                  nextMatrixStart++;
            }
      }
      printf("stop");
      // fill performance array on each call
      int pitch = playedlist.back();      // last element. No playedlist in current context? notelist neither. What's wrong??
      performance[pos_cnt] = pitch;
      
      // calculate each column for each new input. Note: calculating col 1~n_matrix. (instead of 0~n_matrix-1)
      int j = pos_cnt+1;      // j is position of performance in matrix. also goes from 1~n_matrix instead of 0~n_matrix-1
      for (int i = 1; i <= n_matrix; ++i) {
            bestlength[i][j] = max(bestlength[i-1][j], bestlength[i][j-1]);
            if (score[i-1] == performance[j-1])
                  bestlength[i][j] = max(bestlength[i][j], 1+bestlength[i-1][j-1]);
      }
      
      pos_cnt++;
      if (pos_cnt == 10)
            printBestlength();
      
      if (pos_cnt == n_matrix) pos_cnt = 0;
}

void Follower::printBestlength() {
      const int size = 10;     // just print so much
      for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j)
                  printf("%d ", bestlength[i][j]);
            printf("\n");
      }
}


