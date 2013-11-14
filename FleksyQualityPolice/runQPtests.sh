#!/bin/sh


if [[ $# -lt 1 ]]; then
echo "Usage: $0 PATH_TO_ASSETS"
exit 1
fi

for dir in $1/* ; do
if [[ -d "$dir" && ! -L "$dir" ]]; then

  LANG_CODE="$(basename $dir)"

  FILES=$(find $dir -type f)

  for file in $FILES;
    do
      if [ -f $file ];
      then
        FILE="$(basename $file)" 
          #echo "LangCode: $LANG_CODE, File: $FILE"
          if [[ $# -gt 1 ]];
          then
java -Xmx2048M -jar FleksyTester.jar -ip -e -a -q -fol:"$@" -loc:$LANG_CODE -fil:$FILE
          else
java -Xmx2048M -jar FleksyTester.jar -ip -e -a -q s10 n20 -fol:Assets -loc:$LANG_CODE -fil:$FILE
          fi
      fi
    done
 fi
 done

echo "Ding! Finished running all tests!"
