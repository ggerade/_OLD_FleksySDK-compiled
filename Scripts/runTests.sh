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

# ANSI color codes...
FLEKSYSDK_COMPILED_BLACK_WHITE="\033[0m"
FLEKSYSDK_COMPILED_BLACK_CYAN="\033[36m"
FLEKSYSDK_COMPILED_BLACK_YELLOW="\033[33m"

echo "${FLEKSYSDK_COMPILED_BLACK_YELLOW}------------------------------------${FLEKSYSDK_COMPILED_BLACK_WHITE}"
echo "${FLEKSYSDK_COMPILED_BLACK_CYAN}Building FleksySDK-compiled tests...${FLEKSYSDK_COMPILED_BLACK_WHITE}"
echo "${FLEKSYSDK_COMPILED_BLACK_YELLOW}------------------------------------${FLEKSYSDK_COMPILED_BLACK_WHITE}"
echo ""

if [ ! -x "${FLEKSYSDK_COMPILED_SCRIPTS_DIR}/buildTests.sh" ]; then
    echo "Scripts/buildTests.sh does not exist or is not valid."
    exit 1;
fi;

"${FLEKSYSDK_COMPILED_SCRIPTS_DIR}/buildTests.sh"

echo ""
echo "${FLEKSYSDK_COMPILED_BLACK_YELLOW}--------------------------------${FLEKSYSDK_COMPILED_BLACK_WHITE}"
echo "${FLEKSYSDK_COMPILED_BLACK_CYAN}Running 'FleksyQualityPolice'...${FLEKSYSDK_COMPILED_BLACK_WHITE}"
echo "${FLEKSYSDK_COMPILED_BLACK_YELLOW}--------------------------------${FLEKSYSDK_COMPILED_BLACK_WHITE}"
echo ""

FleksyQualityPolice/Scripts/runFleksyTester.sh

echo ""
echo "${FLEKSYSDK_COMPILED_BLACK_YELLOW}--------------------------------------------${FLEKSYSDK_COMPILED_BLACK_WHITE}"
echo "${FLEKSYSDK_COMPILED_BLACK_CYAN}Executing 'FleksySample1/FleksySample_OSX' (Debug)...${FLEKSYSDK_COMPILED_BLACK_WHITE}"
echo "${FLEKSYSDK_COMPILED_BLACK_YELLOW}--------------------------------------------${FLEKSYSDK_COMPILED_BLACK_WHITE}"
echo ""

samples/FleksySample1/build/Debug/FleksySample_OSX

echo ""
echo "${FLEKSYSDK_COMPILED_BLACK_YELLOW}----------------------------------------------${FLEKSYSDK_COMPILED_BLACK_WHITE}"
echo "${FLEKSYSDK_COMPILED_BLACK_CYAN}Executing 'FleksySample1/FleksySample_OSX' (Release)...${FLEKSYSDK_COMPILED_BLACK_WHITE}"
echo "${FLEKSYSDK_COMPILED_BLACK_YELLOW}----------------------------------------------${FLEKSYSDK_COMPILED_BLACK_WHITE}"
echo ""

samples/FleksySample1/build/Release/FleksySample_OSX

echo ""
echo "${FLEKSYSDK_COMPILED_BLACK_YELLOW}--------------------------------------------${FLEKSYSDK_COMPILED_BLACK_WHITE}"
echo "${FLEKSYSDK_COMPILED_BLACK_CYAN}Executing 'TypingControllerTests' (Debug)...${FLEKSYSDK_COMPILED_BLACK_WHITE}"
echo "${FLEKSYSDK_COMPILED_BLACK_YELLOW}--------------------------------------------${FLEKSYSDK_COMPILED_BLACK_WHITE}"
echo ""

TypingControllerTests/FleksyTestCases/build/Debug/FleksyApiTest

echo ""
echo "${FLEKSYSDK_COMPILED_BLACK_YELLOW}----------------------------------------------${FLEKSYSDK_COMPILED_BLACK_WHITE}"
echo "${FLEKSYSDK_COMPILED_BLACK_CYAN}Executing 'TypingControllerTests' (Release)...${FLEKSYSDK_COMPILED_BLACK_WHITE}"
echo "${FLEKSYSDK_COMPILED_BLACK_YELLOW}----------------------------------------------${FLEKSYSDK_COMPILED_BLACK_WHITE}"
echo ""

TypingControllerTests/FleksyTestCases/build/Release/FleksyApiTest

export MallocGuardEdges=YES
export MallocScribble=YES
export MallocStackLoggingNoCompact=YES

echo ""
echo "${FLEKSYSDK_COMPILED_BLACK_YELLOW}--------------------------------------------${FLEKSYSDK_COMPILED_BLACK_WHITE}"
echo "${FLEKSYSDK_COMPILED_BLACK_CYAN}Executing 'FleksySample1/FleksySample_OSX' (Debug) w/ MallocGuardEdges & MallocScribble...${FLEKSYSDK_COMPILED_BLACK_WHITE}"
echo "${FLEKSYSDK_COMPILED_BLACK_YELLOW}--------------------------------------------${FLEKSYSDK_COMPILED_BLACK_WHITE}"
echo ""

samples/FleksySample1/build/Debug/FleksySample_OSX

echo ""
echo "${FLEKSYSDK_COMPILED_BLACK_YELLOW}----------------------------------------------${FLEKSYSDK_COMPILED_BLACK_WHITE}"
echo "${FLEKSYSDK_COMPILED_BLACK_CYAN}Executing 'FleksySample1/FleksySample_OSX' (Release) w/ MallocGuardEdges & MallocScribble...${FLEKSYSDK_COMPILED_BLACK_WHITE}"
echo "${FLEKSYSDK_COMPILED_BLACK_YELLOW}----------------------------------------------${FLEKSYSDK_COMPILED_BLACK_WHITE}"
echo ""

samples/FleksySample1/build/Release/FleksySample_OSX

echo ""
echo "${FLEKSYSDK_COMPILED_BLACK_YELLOW}--------------------------------------------${FLEKSYSDK_COMPILED_BLACK_WHITE}"
echo "${FLEKSYSDK_COMPILED_BLACK_CYAN}Executing 'TypingControllerTests' (Debug) w/ MallocGuardEdges & MallocScribble...${FLEKSYSDK_COMPILED_BLACK_WHITE}"
echo "${FLEKSYSDK_COMPILED_BLACK_YELLOW}--------------------------------------------${FLEKSYSDK_COMPILED_BLACK_WHITE}"
echo ""

TypingControllerTests/FleksyTestCases/build/Debug/FleksyApiTest

echo ""
echo "${FLEKSYSDK_COMPILED_BLACK_YELLOW}----------------------------------------------${FLEKSYSDK_COMPILED_BLACK_WHITE}"
echo "${FLEKSYSDK_COMPILED_BLACK_CYAN}Executing 'TypingControllerTests' (Release) w/ MallocGuardEdges & MallocScribble...${FLEKSYSDK_COMPILED_BLACK_WHITE}"
echo "${FLEKSYSDK_COMPILED_BLACK_YELLOW}----------------------------------------------${FLEKSYSDK_COMPILED_BLACK_WHITE}"
echo ""

TypingControllerTests/FleksyTestCases/build/Release/FleksyApiTest
