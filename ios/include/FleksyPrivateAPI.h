//
//  FleksyPrivateAPI.h
//  FleksyLib
//
//  Created by Vadim Maximov on 3/22/13.
//  Copyright (c) 2013 Syntellia. All rights reserved.
//

#ifndef FleksyLib_FleksyPrivateAPI_h
#define FleksyLib_FleksyPrivateAPI_h

#include "FLPoint.h"
#include "FleksyListenerInterface.h"
#include "FLFile.h"
#include "FLResourceArchive.h"

class FLTypingController;
class SystemsIntegrator;

class FleksyAPIpImpl{
private:
  FLResourceArchivePtr resourceArchive;
  string resourcePath;
  
  FLPoint internalKeyboardSize;
  FLPoint externalKeyboardSize;
  
public:
  FleksyAPIpImpl(FleksyListenerInterface &listener);
  ~FleksyAPIpImpl();
  FleksyListenerInterface &out;
  FLTypingController *tc = NULL;
  SystemsIntegrator *fleksy = NULL;
  
  // set this to have preprocessed files generated. Do not add "/" in the end.
  string writableDirectory;
  bool isEngineLoaded;
  void setExternalKeyboardSize(FLPoint xy);
  FLPoint transformPoint(FLPoint p, bool inverse);
  string getResourceDescription();
  void setMaxNumberOfSuggestions(int numberOfSuggestions);
  void postLoadSetup();
  void loadKeyboardData();
  void loadPreprocessedFile(int wordLength, const void* preprocessedFile, size_t preprocessedFileLength);
  void setResourceFLFile(FLFilePtr &file);
  void setResourcePath(string path);
  FLFilePtr FLFileForFileName(const char *filename);
  void initialize(FLFilePtr &preloaded, FLFilePtr &wordlist, FLFilePtr &blackListCapital, FLFilePtr &blackList, bool isEncrypted = true);
  
  string getLanguagePackVersion(const char *resourceFilePath);
  
  // Settings
  void setSettingTransformLayerWeight(float weight);
  void setSettingShapeLayerWeight(float weight);
  void setSettingContextLayerWeight(float weight);
  void setSettingPlatformLayerWeight(float weight);
  
  float getSettingShapeLayerWeight();
  float getSettingTransformLayerWeight();
  float getSettingContextLayerWeight();
  float getSettingPlatformLayerWeight();
  
  //Data Collection
  void setDataCollectionDirectory(string path); // folder/folder/dataFolder (no / at the end)
  void setIsCollectingData(bool isCollectingData);
  void setDataFileHeader(string header);
  void processEventData(string eventData);
  void writeDataToFile();
  
};

#endif
