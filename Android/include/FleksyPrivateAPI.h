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
  void initResources();
  std::string resourcePath;
  
  FLPoint internalKeyboardSize;
  FLPoint externalKeyboardSize;
  
public:
  FleksyAPIpImpl(FleksyListenerInterface &listener);
  ~FleksyAPIpImpl();
  FleksyListenerInterface &out;
  FLTypingController *tc = NULL;
  SystemsIntegrator *fleksy = NULL;
  
  bool areSwipesInverted;
  
  // set this to have preprocessed files generated. Do not add "/" in the end.
  bool isEngineLoaded;
  void setExternalKeyboardSize(FLPoint xy);
  FLPoint transformPoint(FLPoint p, bool inverse);
  FLUnicodeString getResourceDescription();
  void setMaxNumberOfSuggestions(int numberOfSuggestions);
  void postLoadSetup();
  void loadKeyboardData();
  void setResourceFLFile(FLFilePtr &file);
  void initResourceArchive(FLResourceArchivePtr rsrcArchivePtr);
  void setResourcePath(const std::string &path);
  FLFilePtr FLFileForFileName(const char *filename);
  void initialize(FLFilePtr &blackListCapital, FLFilePtr &blackList, bool isEncrypted = true);
  
  FLUnicodeString getLanguagePackVersion(const char *resourceFilePath);
  bool isValidLanguagePack(const char *resourceFilePath);
  
  // Settings
  void setSettingTransformLayerWeight(float weight);
  void setSettingShapeLayerWeight(float weight);
  void setSettingContextLayerWeight(float weight);
  void setSettingPlatformLayerWeight(float weight);
  
  float getSettingShapeLayerWeight();
  float getSettingTransformLayerWeight();
  float getSettingContextLayerWeight();
  float getSettingPlatformLayerWeight();
  kLanguage getLanguage() const;
  
  //Data Collection
  void setDataCollectionDirectory(const std::string &path); // folder/folder/dataFolder (no / at the end)
  void setIsCollectingData(bool isCollectingData);
  void setDataFileHeader(const std::string &header);
  void processEventData(const FLUnicodeString &eventData);
  void writeDataToFile();
  
  void spaceWithHint(const FLUnicodeString& hint, float length);
  
  std::vector<FLUnicodeString> getWordsInTemporaryDictionary();
  void setWordsInTemporaryDictionary(std::vector<FLUnicodeString> temp_words);
};

#endif
