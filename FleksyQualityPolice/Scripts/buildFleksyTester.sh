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
    echo ""
    echo "NOTE: This script does not take any arguments..."
    exit 1
fi


FLEKSYQP_SCRIPT_PATH=$(canonpath $0)
FLEKSYQP_SCRIPT_NAME=$(basename ${FLEKSYQP_SCRIPT_PATH})
if [[ ! "${FLEKSYQP_SCRIPT_PATH}" =~ \/Scripts\/${FLEKSYQP_SCRIPT_NAME} ]]; then
    echo "Expected the scripts executable path to end in 'Scripts/${FLEKSYQP_SCRIPT_NAME}'."
    exit 1
fi
FLEKSYQP_ROOT_DIR="${FLEKSYQP_SCRIPT_PATH/\/Scripts\/${FLEKSYQP_SCRIPT_NAME}//}"
FLEKSYQP_SCRIPTS_DIR="${FLEKSYQP_ROOT_DIR}/Scripts"
FLEKSYQP_BUILD_DIR="${FLEKSYQP_ROOT_DIR}/build"

FLEKSYSDK_COMPILED_ROOT_DIR=$(canonpath "${FLEKSYQP_ROOT_DIR}/..")
FLEKSYSDK_COMPILED_ANDROID_JAR="${FLEKSYSDK_COMPILED_ROOT_DIR}/Android/lib/fleksy.jar"

cd "${FLEKSYSDK_COMPILED_ROOT_DIR}"

rm -rf "${FLEKSYQP_BUILD_DIR}"

mkdir "${FLEKSYQP_BUILD_DIR}"

cd "${FLEKSYQP_ROOT_DIR}"

rm -rf bin

mkdir bin

echo ""
echo "Compiling 'FleksyQualityPolice'..."

# Compile the java sources
#javac -source 1.6 -target 1.6 -cp "${FLEKSYSDK_COMPILED_ANDROID_JAR}" src/engine/*.java src/utils/*.java src/views/*.java -d bin
javac -source 1.6 -target 1.6 src/engine/*.java src/utils/*.java src/views/*.java -d bin -classpath "${FLEKSYSDK_COMPILED_ANDROID_JAR}"
echo ""
echo "Creating 'FleksyTester.jar'..."

# Create the fleksy.jar file in FleksySDK-compiled/compiled...
#jar cfvm build/FleksyTester.jar manifest.txt -C bin/ . *src "${FLEKSYSDK_COMPILED_ANDROID_JAR}"
ant

pwd
mv "${FLEKSYQP_BUILD_DIR}/FleksyTester.jar" "${FLEKSYQP_ROOT_DIR}"

echo "... jar file: '${FLEKSYQP_ROOT_DIR}/FleksyTester.jar'."

rm -rf bin
rm -rf build

echo ""
#echo "WARNING: This script does not currently produce a working 'FleksyTest.jar' file!"
