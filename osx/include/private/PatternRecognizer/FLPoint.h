//
//  FLPoint.h
//  FleksySDK
//
//  Copyright (c) 2013 Syntellia Inc. All rights reserved.
//

#ifndef __FleksySDK_FLPoint_h__
#define __FleksySDK_FLPoint_h__

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


#endif /* defined(__FleksySDK_FLPoint_h__) */
