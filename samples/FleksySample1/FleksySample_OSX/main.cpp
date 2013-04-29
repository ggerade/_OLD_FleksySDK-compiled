#include <stdio.h>
#include <stdlib.h>
#include <sys/param.h>
#include <string.h>
#include <errno.h>
#include <libgen.h>
#include <unistd.h>

#include "FleksyTester.h"

int main(int argc, const char * argv[]) {
  char resolved_path[PATH_MAX];
  if(realpath(argv[0], resolved_path) == 0) { fprintf(stderr, "Unable to resolve path to executable, realpath() failed: %s\n", strerror(errno)); exit(1); }

  char FleksySDKResourcesPath[PATH_MAX];
  snprintf(FleksySDKResourcesPath, sizeof(FleksySDKResourcesPath), "%s/FleksySDKResources/encrypted/resourceArchive-en-US.jet", dirname(resolved_path));

  FleksyTester::run(FleksySDKResourcesPath);

  return 0;
}