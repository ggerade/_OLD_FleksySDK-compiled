//
//  FLTrie.h
//  FleksySDK
//
//  Created by Kosta Eleftheriou on 7/25/13.
//  Copyright (c) 2013 Syntellia. All rights reserved.
//

#ifndef __FleksySDK__FLTrie__
#define __FleksySDK__FLTrie__

// ~10% speedup
#define FLTRIE_FLATTEN_FOR_INLINE_OPTIMIZATION 0

#include <iostream>
#include <vector>
#include "FLString.h"
#include "FLPoint.h"
#include "CoreSettings.h"

// Keep (x,y) point data as a single byte vs 2 bytes
#define USE_COMPACT 0

#if USE_COMPACT
#define METADATA_TYPE uint8_t
#else
#define METADATA_TYPE FLPoint
#endif

using namespace std;

class FLTrieNode {
  
public:
  
  static FLTrieNode* FLTrieNodeMake(FLChar data, size_t metadataLength);
  
  void addChild(FLTrieNode* child);
  
  FLTrieNode** children;
  
  void setChildCount(uint8_t count);
  uint8_t getChildCount();
  void setData(uint8_t c);
  uint8_t getData();
  
  void setMetadata(int i, METADATA_TYPE data);
  METADATA_TYPE getMetadata(int i);
  
  METADATA_TYPE* getMetadataPointer();
  
  bool isItemNode();
  void setIsItemNode(bool b);

  bool isActiveForLength(size_t length);
  void setIsActiveForLength(size_t length, bool b);
  
private:
  uint8_t _data1[5];
  METADATA_TYPE _metadata[];
};

typedef vector<FLTrieNode*> TrieStack;

class FLTrie {
  
  int totalDuplicates = 0;
  FLTrieNode* rootNode;
  size_t (*metadataLengthFunction)(size_t); // function that returns length of metadata required at given depth
  
private:
  bool insert(FLString& str, FLTrieNode* node, int depth);
  bool contains(FLString& str, FLTrieNode* node, int depth);
  void traverse(FLTrieNode* node, TrieStack& stack, void (*traverseFunction)(TrieStack&, void*));

public:
  FLTrie(size_t (*metadataLengthFunction)(size_t));
  bool insert(FLString& str);
  bool remove(FLString& str);
  bool contains(FLString& str);
  void traverse(void (*traverseFunction)(TrieStack&, void*));
  FLTrieNode* getRootNode();
};

#if FLTRIE_FLATTEN_FOR_INLINE_OPTIMIZATION
#include "FLTrie.cpp"
#endif

#endif /* defined(__FleksySDK__FLTrie__) */
