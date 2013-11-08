//
//  FLPoint.h
//  FleksySDK
//
//  Copyright (c) 2013 Syntellia Inc. All rights reserved.
//

#ifndef __FleksySDK_FLPoint_h__
#define __FleksySDK_FLPoint_h__

#include <math.h>

// This value is used as a limit to what "zero" is for us. We need this since we dont currently use fixed point arithmetic
#define FLEKSY_SMALL_VALUE 0.0001f

#ifdef __APPLE__
#include "TargetConditionals.h"
#endif

#if TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE
#include <CoreGraphics/CGGeometry.h>
typedef CGPoint FLPoint;
#define FLPointMake(__x__,__y__) CGPointMake(__x__,__y__)
#define FLPointEqualToPoint CGPointEqualToPoint
#else

typedef struct FLPoint {
  float x;
  float y;
} FLPoint;

static inline FLPoint FLPointMake(float x, float y) {
  FLPoint p; p.x = x; p.y = y; return p;
}

static inline bool FLPointEqualToPoint(FLPoint p1, FLPoint p2) {
  return p1.x == p2.x && p1.y == p2.y;
}

#define FLPointFromCGPoint(__p__) FLPointMake(__p__.x, __p__.y)

#endif

#define FLPointZero FLPointMake(0, 0)
#define FLPointInvalid FLPointMake(-99, -99)
#define FLPointFromCGPoint(__p__) FLPointMake(__p__.x, __p__.y)

static inline float FLDistanceBetweenPoints(FLPoint p1, FLPoint p2) {
  float dx = p1.x - p2.x;
  float dy = p1.y - p2.y;
  float result = hypotf(dx, dy);
  return((fabsf(result) < FLEKSY_SMALL_VALUE) ? 0.0f : result);
}

#endif /* defined(__FleksySDK_FLPoint_h__) */
