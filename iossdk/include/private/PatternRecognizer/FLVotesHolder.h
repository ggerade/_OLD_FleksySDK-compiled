//
//  FLVotesHolder.h
//  PatternRecognizer
//
//  Created by Kostas Eleftheriou on 7/5/12.
//  Copyright (c) 2012 Syntellia Inc. All rights reserved.
//

#ifndef VOTES_HOLDER_H
#define VOTES_HOLDER_H

#include "CoreSettings.h"

#define WORD_VOTE_SLOTS 2

class FLVotesHolder {
  
private:
  float votes[WORD_VOTE_SLOTS][FL_MAX_WORD_ID];

public:
  FLVotesHolder();
  double reset();
  float* getVoteSlot(int slot);
};


#endif
