//
//  ZipUtilities.h
//  FleksySDK
//
//  Created by Vadim Maximov on 7/8/13.
//  Copyright (c) 2013 Syntellia. All rights reserved.
//

#ifndef __FleksySDK__ZipUtilities__
#define __FleksySDK__ZipUtilities__

#include <iostream>
#define SKYNET "fleksy/SYNTELLIA_DRONE_FILE_PATH"

namespace ZipUtilities {
  
  int zipFile(std::string src, std::string destination);
  bool unzipBytes(const char *compressedBytes, size_t compressedLength, std::string &decompressedString);

};

#endif /* defined(__FleksySDK__ZipUtilities__) */

