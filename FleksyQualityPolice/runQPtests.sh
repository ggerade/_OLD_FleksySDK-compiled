#!/bin/sh


if [[ $# -lt 1 ]]; then
#echo "Usage: $0 PATH_TO_ASSETS"
echo ""
exit 1
fi


for dir in $1/* ; do
if [[ -d "$dir" && ! -L "$dir" ]]; then

#echo "Directory: $dir"
  FILES=$(find $dir -type f)

  SUBDIR="$(basename $dir)"
#echo  "Running tests on files from: $SUBDIR"
  if [[ $# -gt 1 ]];
  then
    java -Xmx2048M -jar FleksyTester.jar -ip -e -a -q "$@" -loc:$SUBDIR
  else
    java -Xmx2048M -jar FleksyTester.jar -ip -e -a -q s10 n20 -loc:$SUBDIR
 fi
#echo ""
 fi
 done
#echo ""
echo "Ding! Finished running all tests!"
