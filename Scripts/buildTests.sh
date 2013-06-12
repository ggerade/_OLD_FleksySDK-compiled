#!/bin/sh

# If any command fails, cause the script to fail and exit with non-zero status.
set -e
# If any variable is used but unset, cause the script to fail and exit with non-zero status.
set -u

errorHandler () {
    errorCode=$?
    echo "$0:${BASH_LINENO[0]} error: Command failed: '$BASH_COMMAND'"
    exit $errorCode
}
trap errorHandler ERR

function canonpath () 
{
    echo $(cd $(dirname "$1"); pwd -P)/$(basename "$1")
}


if [[ "$#" != "0" ]]; then
    echo "Usage: $0"
    echo "NOTE: The command takes no arguments."
    echo ""
    exit 1
fi


FLEKSYSDK_COMPILED_SCRIPT_PATH=$(canonpath "$0")
FLEKSYSDK_COMPILED_SCRIPT_NAME=$(basename "${FLEKSYSDK_COMPILED_SCRIPT_PATH}")
if [[ ! "${FLEKSYSDK_COMPILED_SCRIPT_PATH}" =~ \/Scripts\/${FLEKSYSDK_COMPILED_SCRIPT_NAME} ]]; then
    echo "Expected the scripts executable path to end in 'Scripts/${FLEKSYSDK_COMPILED_SCRIPT_NAME}'."
    exit 1
fi
FLEKSYSDK_COMPILED_ROOT_DIR="${FLEKSYSDK_COMPILED_SCRIPT_PATH/\/Scripts\/${FLEKSYSDK_COMPILED_SCRIPT_NAME}/}"
FLEKSYSDK_COMPILED_SCRIPTS_DIR="${FLEKSYSDK_COMPILED_ROOT_DIR}/Scripts"

cd "${FLEKSYSDK_COMPILED_ROOT_DIR}"

####
echo "Building 'FleksySample1'..."
echo ""

cd samples/FleksySample1

rm -rf build

xcodebuild -configuration Debug   -target FleksySample_OSX >/dev/null
xcodebuild -configuration Release -target FleksySample_OSX >/dev/null
rsync -a "${FLEKSYSDK_COMPILED_ROOT_DIR}/osx/lib/Release/FleksyLib.dylib" "build/Release/FleksyLib.dylib"

xcodebuild -configuration Debug   -sdk iphonesimulator6.1 -target FleksySample_iOS >/dev/null
xcodebuild -configuration Release -sdk iphonesimulator6.1 -target FleksySample_iOS >/dev/null

cd "${FLEKSYSDK_COMPILED_ROOT_DIR}"

####
echo "Building 'TypingControllerTests'..."
echo ""

cd TypingControllerTests/FleksyTestCases

rm -rf build

xcodebuild -configuration Debug   -target FleksyApiTest >/dev/null
xcodebuild -configuration Release -target FleksyApiTest >/dev/null
rsync -a "${FLEKSYSDK_COMPILED_ROOT_DIR}/osx/lib/Release/FleksyLib.dylib" "build/Release/FleksyLib.dylib"

cd "${FLEKSYSDK_COMPILED_ROOT_DIR}"
