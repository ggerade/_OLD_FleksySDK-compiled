//
//  MathFunctions.h
//  PatternRecognizer
//
//  Copyright 2011 Syntellia Inc. All rights reserved.
//

#include "Structures.h"
#include "TimeFunctions.h"

// for some reason this produced a = 4 always, on the first run. Subsequent
// calls of rand() % 7 DID produce variable results, just not the first...
// srand(time(0));
// int a = rand() % 7;
// Seems that calling rand() a couple of times first "warms up" the generator...

#define RANDOM_SEED() srand( time(0) ); rand(); rand()
//rand vs random
#define RANDOM_POSITIVE_FLOAT_1() ( (float)rand() / (float)RAND_MAX )
#define RANDOM_POSITIVE_FLOAT(__UPLIMIT__) ( RANDOM_POSITIVE_FLOAT_1() * (__UPLIMIT__) )
//from 0 (inclusive) to __UPLIMIT__ (exclusive)
#define RANDOM_POSITIVE_INT(__UPLIMIT__) ((int)(rand() % (__UPLIMIT__)))
#define RANDOM_BOOL() (random() % 2 != 0)
#define RANDOM_FLOAT(__UPLIMIT__) ( RANDOM_POSITIVE_FLOAT(2 * __UPLIMIT__) - __UPLIMIT__ )

// This value is used as a limit to what "zero" is for us. We need this since we dont currently use fixed point arithmetic
#define FLEKSY_SMALL_VALUE 0.0001f

extern float distanceOfPoints(FLPoint p1, FLPoint p2);
extern float slopeBetweenPoints(FLPoint p1, FLPoint p2);
extern float slopeOfPoint(FLPoint p);
// Returns p1+p2
extern FLPoint addPoints(FLPoint p1, FLPoint p2);
// Returns p1-p2
extern FLPoint subtractPoints(FLPoint p1, FLPoint p2);
// Returns p/f
extern FLPoint dividePoint(FLPoint p, float f);
FLPoint multiplyPoint(FLPoint p, float f);
extern FLPoint normalizePoint(FLPoint p);
extern float dotProduct(FLPoint p1, FLPoint p2);
extern float magnitude(FLPoint p);
extern FLPoint rotatePoint(FLPoint p, float angle);

//modulo, handles negative a. b should be positive
extern int modulo(int a, int b);
extern bool isZero(float value);
extern float checkZero(float value);
extern float differenceOfAngles(float a1, float a2);
extern float sum(float* numbers, int n);
extern float average(float* numbers, int n);
extern float standardDeviation(float* numbers, int n);
extern float* zerofy(float* numbers, int n, float threshold);
extern float* deltas(float* numbers, int n);
extern int numberOfPeaks(float* numbers, int n, float threshold);
extern float* abs(float* numbers, int n);
extern float hausdorffDistance(float *numbers1, float *numbers2, float *weights, int n);

extern float getRatioLargerThan1(float s1, float s2);
