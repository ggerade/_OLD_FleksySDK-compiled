#!/bin/sh


if [[ "$#" != "1" ]]; then
echo "Usage: $0 PATH_TO_ASSETS"
echo ""
exit 1
fi


for dir in $1/* ; do
if [[ -d "$dir" && ! -L "$dir" ]]; then

echo "Directory: $dir"
  FILES=$(find $dir -type f)

  for file in $FILES;
    do
      if [ -f $file ];
      then
          SUBDIR="$(basename $dir)"
          echo  "Running tests on files from: $SUBDIR"
          java -Xmx2048M -jar FleksyTester.jar -ip -e -a -s -n w10000 -loc:$SUBDIR
      fi
    done
fi
done
