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


FLEKSYSDK_COMPILED_SCRIPT_PATH=`canonpath $0`
FLEKSYSDK_COMPILED_SCRIPT_NAME=$(basename "${FLEKSYSDK_COMPILED_SCRIPT_PATH}")
if [[ ! "${FLEKSYSDK_COMPILED_SCRIPT_PATH}" =~ \/Scripts\/${FLEKSYSDK_COMPILED_SCRIPT_NAME} ]]; then
    echo "Expected the scripts executable path to end in 'Scripts/${FLEKSYSDK_COMPILED_SCRIPT_NAME}'."
    exit 1
fi
FLEKSYSDK_COMPILED_ROOT_DIR="${FLEKSYSDK_COMPILED_SCRIPT_PATH/\/Scripts\/${FLEKSYSDK_COMPILED_SCRIPT_NAME}//}"
FLEKSYSDK_COMPILED_SCRIPTS_DIR="${FLEKSYSDK_COMPILED_ROOT_DIR}/Scripts"

cd "${FLEKSYSDK_COMPILED_ROOT_DIR}"

echo "Building FleksySDK archive..."



FLEKSYSDK_COMPILED_BUILD_DIR="${FLEKSYSDK_COMPILED_ROOT_DIR}/build"
FLEKSYSDK_COMPILED_STAGE_DIR="${FLEKSYSDK_COMPILED_BUILD_DIR}/stage"

rm -rf "${FLEKSYSDK_COMPILED_BUILD_DIR}"
rm -rf "${FLEKSYSDK_COMPILED_STAGE_DIR}"

mkdir -p "${FLEKSYSDK_COMPILED_BUILD_DIR}"
mkdir -p "${FLEKSYSDK_COMPILED_STAGE_DIR}"



echo ""
echo "Staging Android..."

rsync -aC --include='lib*.so' --delete "${FLEKSYSDK_COMPILED_ROOT_DIR}/Android/" "${FLEKSYSDK_COMPILED_STAGE_DIR}/Android/"
mv "${FLEKSYSDK_COMPILED_STAGE_DIR}/Android/lib" "${FLEKSYSDK_COMPILED_STAGE_DIR}/Android/lib_STAGING"
mv "${FLEKSYSDK_COMPILED_STAGE_DIR}/Android/lib_STAGING/Release" "${FLEKSYSDK_COMPILED_STAGE_DIR}/Android/lib"
rm -rf "${FLEKSYSDK_COMPILED_STAGE_DIR}/Android/lib_STAGING"



echo ""
echo "Staging iOS..."

rsync -aC --include='lib*.a' --delete "${FLEKSYSDK_COMPILED_ROOT_DIR}/ios/" "${FLEKSYSDK_COMPILED_STAGE_DIR}/ios/"
mv "${FLEKSYSDK_COMPILED_STAGE_DIR}/ios/lib" "${FLEKSYSDK_COMPILED_STAGE_DIR}/ios/lib_STAGING"
mv "${FLEKSYSDK_COMPILED_STAGE_DIR}/ios/lib_STAGING/Release" "${FLEKSYSDK_COMPILED_STAGE_DIR}/ios/lib"
rm -rf "${FLEKSYSDK_COMPILED_STAGE_DIR}/ios/lib_STAGING"

cd "${FLEKSYSDK_COMPILED_STAGE_DIR}/ios/lib"
for FLEKSYSDK_COMPILED_LIB in lib*.a
do
    echo "Stripping debug symbols from iOS lib      : '${FLEKSYSDK_COMPILED_LIB}'..."
    /usr/bin/strip -S "${FLEKSYSDK_COMPILED_LIB}"
    echo "Verifing expected architectures in iOS lib: '${FLEKSYSDK_COMPILED_LIB}'..."
    lipo "${FLEKSYSDK_COMPILED_LIB}" -verify_arch i386
    lipo "${FLEKSYSDK_COMPILED_LIB}" -verify_arch armv7
    lipo "${FLEKSYSDK_COMPILED_LIB}" -verify_arch armv7s
done

cd "${FLEKSYSDK_COMPILED_ROOT_DIR}"



echo ""
echo "Staging OSX..."

rsync -aC --delete "${FLEKSYSDK_COMPILED_ROOT_DIR}/osx/" "${FLEKSYSDK_COMPILED_STAGE_DIR}/osx/"
mv "${FLEKSYSDK_COMPILED_STAGE_DIR}/osx/lib" "${FLEKSYSDK_COMPILED_STAGE_DIR}/osx/lib_STAGING"
mv "${FLEKSYSDK_COMPILED_STAGE_DIR}/osx/lib_STAGING/Release" "${FLEKSYSDK_COMPILED_STAGE_DIR}/osx/lib"
rm -rf "${FLEKSYSDK_COMPILED_STAGE_DIR}/osx/lib_STAGING"

cd "${FLEKSYSDK_COMPILED_STAGE_DIR}/osx/lib"
for FLEKSYSDK_COMPILED_LIB in *.dylib
do
    echo "Stripping debug symbols from OSX lib      : '${FLEKSYSDK_COMPILED_LIB}'..."
    /usr/bin/strip -S "${FLEKSYSDK_COMPILED_LIB}"
    echo "Verifing expected architectures in OSX lib: '${FLEKSYSDK_COMPILED_LIB}'..."
    lipo "${FLEKSYSDK_COMPILED_LIB}" -verify_arch i386
    lipo "${FLEKSYSDK_COMPILED_LIB}" -verify_arch x86_64
done

cd "${FLEKSYSDK_COMPILED_ROOT_DIR}"



echo ""
echo "Staging samples..."

mkdir -p "${FLEKSYSDK_COMPILED_STAGE_DIR}/samples"
rsync -aC --exclude='*.xcodeproj/xcuserdata' --exclude='*.xcodeproj/project.xcworkspace' --exclude='build' --delete "${FLEKSYSDK_COMPILED_ROOT_DIR}/samples/" "${FLEKSYSDK_COMPILED_STAGE_DIR}/samples/"
rm -rf "${FLEKSYSDK_COMPILED_STAGE_DIR}/samples/NOKIA-FleksySample2.zip"



echo ""
echo "Creating FleksySDK archive..."

mv "${FLEKSYSDK_COMPILED_BUILD_DIR}/stage" "${FLEKSYSDK_COMPILED_BUILD_DIR}/FleksySDK"
cd "${FLEKSYSDK_COMPILED_BUILD_DIR}"
/usr/bin/tar czf FleksySDK.tar.gz FleksySDK

cd "${FLEKSYSDK_COMPILED_ROOT_DIR}"



echo ""
echo "Finished!"
echo ""
echo "FleksySDK archive: 'build/FleksySDK.tar.gz'"
