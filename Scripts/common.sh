#!/bin/sh

# If any command fails, cause the script to fail and exit with non-zero status.
set -e
# If any variable is used but unset, cause the script to fail and exit with non-zero status.
set -u

_PROC_RUNNING_="running"
_PROC_FINISHED_="finished"

function checkProcess() 
{
    pid=$1
    __state=$2
    if [[ -z `ps -p $pid -o 'pid='` ]]; then
        eval $__state="'$_PROC_FINISHED_'"
    else
        eval $__state="'$_PROC_RUNNING_'"
    fi
}

function waitProc()
{
    PID=$1
    SLEEP=$2
    CUR_SLEEP=0
    PROC_STATE=${_PROC_RUNNING_}
    while [[ $PROC_STATE == ${_PROC_RUNNING_} ]]; do
	sleep ${CUR_SLEEP}
	checkProcess $PID PROC_STATE
	CUR_SLEEP=$SLEEP
    done
}

function waitAllProcs() {
    declare -a PROC_IDS=("${!1}")
    SLEEP=$2
    for IDS in ${PROC_IDS[@]}; do
	waitProc $IDS $SLEEP
    done 
}

errorHandler () {
    errorCode=$?
    echo "$0:${BASH_LINENO[0]} error: Command failed: '$BASH_COMMAND'"
    exit $errorCode
}
trap errorHandler ERR

function canonPath () 
{
    echo $(cd $(dirname "$1"); pwd -P)/$(basename "$1")
}

function scriptPath()
{
    echo "$(canonPath $0)"
}

function scriptName()
{
    SCRIPT_DIR=$(scriptPath)
    echo "$(basename ${SCRIPT_DIR})"
}

# Root directory of the /Scripts, ie ~/DataMining/LanguagePacks/Scripts
# will return ~/DataMining/LanguagePacks/
function rootDir()
{
    CURRENT=$1
    SCRIPT_DIR=`scriptPath`
    SCRIPT_NAME=$(scriptName) 
    ROOT_DIR="${SCRIPT_DIR/\/${CURRENT}\/${SCRIPT_NAME}//}"
    echo "$ROOT_DIR"
}

