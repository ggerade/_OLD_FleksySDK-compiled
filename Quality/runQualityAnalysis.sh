function baseDir() 
{
    echo $(dirname $(cd $(dirname "$0"); pwd -P)/$(basename "$0"))
}

function runQPMeasure()
{
    TYPE=$1
    echo "Sampling sentences from the ${TYPE} source..."
    $PYTHON3 ${FL_COMPILED_QUALITY_DIR}/sampleSentences.py ${QPM_FILE} ${QPM_SRC_SIZE} > \
	${QPM_SAMPLE}
    
    let CNT=1
    for NOISE in ${QPM_NOISE_SEQUENCE}; do
	echo "Launching QP for noise ${NOISE}"
	${FL_QP} ${FL_JET_FILE} ${QPM_SAMPLE} 0 ${NOISE} ${QPM_RUN_SIZE} >> ${QPM_OUTPUT_FILE}_$NOISE &
	PROC_IDS[$CNT]=$!
	if [[ $CNT -eq $NUM_PROCS ]]; then
	    echo "Waiting for procs..."
	    waitAllProcs PROC_IDS[@] 10
	    let CNT=1
	else
	    let CNT=CNT+1
	fi
    done

    if [[ $CNT -gt 1 ]]; then
	echo "Waiting for procs..."
	waitAllProcs PROC_IDS[@] 10
    fi

    echo "Preparing QPM output"
    for NOISE in ${QPM_NOISE_SEQUENCE}; do
	cat ${QPM_OUTPUT_FILE}_$NOISE >> ${QPM_OUTPUT_FILE}
	rm ${QPM_OUTPUT_FILE}_$NOISE
    done
}

source $(baseDir)/../Scripts/common.sh
source $(baseDir)/qualityAnalysis.config

PYTHON3=/Library/Frameworks/Python.framework/Versions/3.3/bin/python3

if [[ -z `type -t ${PYTHON3}` ]]; then
    echo "/Library/Frameworks/Python.framework/Versions/3.3/bin/python3 not found"
    PYTHON3=/usr/bin/python3
    if [[ -z `type -t ${PYTHON3}` ]]; then
	echo "/usr/bin/python3 not found. exiting..."
	exit
    fi
fi

FL_COMPILED_SCRIPT_PATH=$(canonPath "$0")
FL_COMPILED_ROOT_DIR=`rootDir Quality`
FL_COMPILED_SCRIPTS_DIR="${FL_COMPILED_ROOT_DIR}/Scripts"
FL_COMPILED_QUALITY_DIR="${FL_COMPILED_ROOT_DIR}/Quality"

FL_ASSETS_ROOT=${FL_COMPILED_ROOT_DIR}/FleksyQualityPolice
FL_PARLIMENT_ASSET_DIR=${FL_ASSETS_ROOT}/AssetsParliament/${LANG}-${COUNTRY}/
FL_QUALITY_ANALYSIS_DATA=$(baseDir)/data/${LANG}-${COUNTRY}/
FL_QUALITY_ANALYSIS_OUTPUT=$(baseDir)/output
FL_JET_FILE=${FL_COMPILED_ROOT_DIR}/Android/FleksySDKResources/encrypted/resourceArchive-${LANG}-${COUNTRY}.jet


FL_QP=$(baseDir)/bin/QPMeasure
FL_SIM_GRAMS=$(baseDir)/bin/SimNGrams

mkdir -p ${FL_QUALITY_ANALYSIS_OUTPUT}
rm -f ${FL_QUALITY_ANALYSIS_OUTPUT}/*

if [[ ${USE_PARLIMENT_SRC} -eq 1 ]]; then

    PARL_FILE=`ls -l ${FL_PARLIMENT_ASSET_DIR} | awk '{print $9}'`
    PARL_FILE=`echo ${PARL_FILE}`

    # set up variables for runQPMeasure to work
    QPM_SAMPLE=${FL_QUALITY_ANALYSIS_OUTPUT}/parlSample.txt
    QPM_FILE=${FL_PARLIMENT_ASSET_DIR}/${PARL_FILE}
    QPM_SRC_SIZE=${PARL_SRC_SIZE}
    QPM_NOISE_SEQUENCE=${QP_NOISE_SEQUENCE}
    QPM_RUN_SIZE=${QP_RUN_SIZE}
    QPM_OUTPUT_FILE=${FL_QUALITY_ANALYSIS_OUTPUT}/QPOutput.txt
    runQPMeasure parliment
fi




