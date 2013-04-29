//
//  FLResourceArchiveCommon.h
//  FleksyLib
//
//  Created by John Engelhart on 4/25/13.
//  Copyright (c) 2013 Syntellia. All rights reserved.
//

#ifndef FleksyLib_FLResourceArchiveCommon_h
#define FleksyLib_FLResourceArchiveCommon_h

#include <stdint.h>

// Header magic bytes: 0x46 0x4c 0x73 0x61, aka "FLsa"
#define FL_SDKA_MAGIC_BYTE_0 (0x46u)
#define FL_SDKA_MAGIC_BYTE_1 (0x4cu)
#define FL_SDKA_MAGIC_BYTE_2 (0x73u)
#define FL_SDKA_MAGIC_BYTE_3 (0x61u)

/*
 Header: 16 bytes
 
 0 4 Magic
 4 2 Version, Major
 6 2 Version, Minor
 8 4 Length of Info
 12 4 Length of Contents
 
 Tag + Length
 
 0 4 Tag
 4 4 Length
 
 */

enum {
  FLSDKArchiveTagTableOfContents = 1,
  FLSDKArchiveTagGitCommit = 2,
  FLSDKArchiveTagLanguage = 3,
};


#endif
