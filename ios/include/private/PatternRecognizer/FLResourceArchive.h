//
//  FLResourceArchive.h
//  FleksyLib
//
//  Created by John Engelhart on 4/24/13.
//  Copyright (c) 2013 Syntellia. All rights reserved.
//

#ifndef __FleksyLib__FLResourceArchive__
#define __FleksyLib__FLResourceArchive__

#include "FLResourceArchiveCommon.h"

#include <stdint.h>
#include "FLFile.h"

typedef struct {
  const char *fileName;
  size_t fileSize;
  size_t contentsOffset;
} FLFileEntry;


class FLResourceArchive {

public:
  FLResourceArchive(FLFilePtr &file);
  ~FLResourceArchive();

  FLFilePtr FLFileForFileName(const char *fileName);
  string getTag();

private:
  FLFilePtr archiveFile;// = NULL;
  const unsigned char *archiveBytes = NULL;
  size_t archiveLength = 0;

  void parseArchive();
  void parseArchiveInfo();
  void parseTableOfContents(const unsigned char *tableOfContents, size_t length);
  void parseLanguageTag(const unsigned char *tableOfContentsBytes, size_t length);
  void parseGitCommitTag(const unsigned char *tableOfContentsBytes, size_t length);

  FLFileEntry *getFileEntry(const char *fileName);

  const char *gitCommit = NULL;
  
  struct {
    const char *ID = NULL;
    uint16_t major = 0;
    uint16_t minor = 0;
  } language;
  
  struct {
    uint16_t major = 0;
    uint16_t minor = 0;
  } version;

  struct {
    const unsigned char *bytes = NULL;
    size_t length = 0;
  } info;

  struct {
    const unsigned char *bytes = NULL;
    size_t length = 0;
  } contents;

  struct {
    size_t count;
    FLFileEntry *fileEntries = NULL;
  } tableOfContents;
};

typedef std::shared_ptr<FLResourceArchive> FLResourceArchivePtr;

#endif /* defined(__FleksyLib__FLResourceArchive__) */
