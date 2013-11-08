//
//  EncryptionUtilities.h
//  Fleksy
//
//  Created by Kostas Eleftheriou on 2/6/13.
//  Copyright (c) 2013 Syntellia Inc. All rights reserved.
//

#include <stdio.h>

// default decryption key
#define DEFAULT_M_VALUE "fleksy/CONTENTS_PATH_FOLDER/PATH"

#define USE_APPLE_CRYPTO 0

//using namespace std;

namespace EncryptionUtilities {

  void* readBinaryFile(const char* filename, size_t& bytesRead);
  
  // caller is responsible for freeing returned pointer when done
  // A 16-byte header block will be added at the beginning of the returned pointer, contains dataLength information for decryption later
  void* encrypt(void* data, size_t dataLength, size_t& outLength, const char* key);
  
  // this will decrypt data IN-PLACE, but will return a pointer within data, namely right after the 16-byte header block.
  // So the caller should not free the returned pointer, instead the data pointer should be freed when done.
  // outLength maybe be less than dataLength by up to 15 bytes, due to added padding in encryption
  void* decrypt(void* data, size_t dataLength, size_t& outLength, const char* key);

#if USE_APPLE_CRYPTO
  size_t appleCrypt(void* data, size_t dataLength, bool encrypt, const char* key);
#endif
  
  void encryptionTests();

};
