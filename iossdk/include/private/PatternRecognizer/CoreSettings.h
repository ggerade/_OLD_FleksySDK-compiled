//
//  CoreSettings.h
//  PatternRecognizer
//
//  Copyright 2011 Syntellia Inc. All rights reserved.
//

#ifndef CORESETTINGS_H
#define CORESETTINGS_H
///////////////////////////////////////////

#define SHAPE_TESTING 0
#define SHAPE_TESTING_ALL_TRIANGLES (1 && SHAPE_TESTING)

#ifdef FL_USE_DAWG_SVD_ENGINE
#define FL_DAWG_SVD_USE_CALCULATE_PRECISE_CANDIDATE_SCORE
#endif

#if defined(SHAPE_TESTING) && (SHAPE_TESTING == 1)
#define SHAPE_TESTING_USE_PRODUCTION_MATCHER
#endif

#if defined(SHAPE_TESTING) && (SHAPE_TESTING == 1)
//#define SHAPE_TESTING_ENABLE_TRIE
#endif

#define FL_MAX_WORD_ID 65000

//#define FLEKSY_ANCHORS_N 0
//should be same as number of cores for max efficiency
#define FLEKSY_MULTICORE_BATCHES 1
#define FLEKSY_MAX_WORD_SIZE 21


#endif
