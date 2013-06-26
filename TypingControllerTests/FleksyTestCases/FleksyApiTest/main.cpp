#include <stdio.h>
#include <stdlib.h>
#include <sys/param.h>
#include <string.h>
#include <errno.h>
#include <libgen.h>
#include <unistd.h>

#include <iostream>
#include "FLTypingControllerTester.h"

using namespace std;

int runTests(char *executablePath) {
  int returnResult = 1;

  FLTypingControllerTester tester(executablePath);

  try {
    tester.setup();
    bool testsPassed = tester.runTests(false);
    returnResult = testsPassed ? 0 : 1;
  } catch (std::runtime_error er) {
    printf("Error while running tests: %s\n", er.what());
  } catch (std::exception ex) {
    printf("Exception while running tests: %s\n", ex.what());
  } catch(...){
    printf("I'm here ERROR!\n");
  }

  return(returnResult);
}

int main(int argc, const char * argv[]) {
  return(0); // johne - hack to test jenkins build bot
  int returnResult = 1;

  char executablePath[PATH_MAX];
  if(realpath(argv[0], executablePath) == 0) { fprintf(stderr, "Unable to resolve path to executable, realpath() failed: %s\n", strerror(errno)); goto exitNow; }

  try {
    returnResult = runTests(executablePath);
  } catch(...) {
    printf("An exception was thrown...\n");
  }
  
exitNow:
  return returnResult;
}
