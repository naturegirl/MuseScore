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
}

list<NoteElement *> Follower::getNotelist() {
      return notelist;              // return pointer instead?
}

void Follower::printNotelist() {
      list<NoteElement *>::const_iterator it;
      printf("printNotelist(): ");
      int cnt = 0;
      for (it = notelist.begin(); it != notelist.end(); ++it) {
            NoteElement *elm = *it;
            int pitch = elm->pitch;
            int time = elm->time;
            printf("%d ", pitch);
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
}


void Follower::update() {
      
}
