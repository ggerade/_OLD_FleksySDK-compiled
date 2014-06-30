//
//  FLWord.h
//  PatternRecognizer
//
//  Copyright 2011 Syntellia Inc. All rights reserved.
//


#ifndef FLWORD_H
#define FLWORD_H

#include <memory>
#include <unordered_map>

#include "FLKeyboard.h"
#include "Platform.h"

typedef float probability;

class FLWord;
typedef std::shared_ptr<FLWord> FLWordPtr;

class FLWord {
  
private:
  
  void initFromPoints(short nPoints, FLPoint points[]);

  bool pointsFromLetters = false;
  FLPoint* rawPoints = NULL;
  std::shared_ptr<FLKeyboard> keyboard;

public:

  short nPoints; // Although this is "public", it should be treated as "private", use getNPoints() instead.
                 // This was moved here because SystemsIntegrator::processContextResults() needed to call getNPoints() sufficiently often that profiling justified a direct access exception.

  FLUnicodeStringPtr lettersPtr;
  FLUnicodeStringPtr printLettersPtr;

  FLPoint getPoint(size_t pointIdx) const;
  
  bool canBeRemovedByUser;
  
  ////////////////////

  FLWord(short nPoints, FLPoint* points);
  FLWord(FLUnicodeStringPtr &_letters, FLUnicodeStringPtr &_printLetters, short _nPoints, FLPoint pointsToUse[], bool usePointsFromLetters, bool canBeRemoved, std::shared_ptr<FLKeyboard> &keyboardPtr);
  ~FLWord();

  FLUnicodeStringPtr getLetters();
  FLUnicodeStringPtr getPrintLetters();
  
  short getNPoints() const;
};

typedef std::vector<FLWord*> FLWordList;
typedef std::vector<FLWordPtr> FLWordPtrList;

#endif
