//
//  FLPoint.h
//  PatternRecognizer
//
//  Created by Kostas Eleftheriou on 11/26/12.
//  Copyright (c) 2012 Syntellia Inc. All rights reserved.
//

#ifndef PatternRecognizer_FLPoint_h
#define PatternRecognizer_FLPoint_h

#ifdef __APPLE__
#include "TargetConditionals.h"
#endif

#if TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE
#include <CoreGraphics/CGGeometry.h>
typedef CGPoint FLPoint;
#define FLPointMake(__x__,__y__) CGPointMake(__x__,__y__)
#define FLPointZero CGPointZero
#define FLPointFromCGPoint(__p__) FLPointMake(__p__.x, __p__.y)
#else

typedef struct FLPoint {
  float x;
  float y;
} FLPoint;

static inline FLPoint FLPointMake(float x, float y) {
  FLPoint p; p.x = x; p.y = y; return p;
}

#define FLPointZero FLPointMake(0, 0)
#define FLPointFromCGPoint(__p__) FLPointMake(__p__.x, __p__.y)

#endif

#endif
