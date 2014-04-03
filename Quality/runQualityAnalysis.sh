function baseDir() 
{
    echo $(dirname $(cd $(dirname "$0"); pwd -P)/$(basename "$0"))
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
FL_QUALITY_ANALYSIS_OUTPUT=$(baseDir)/output
FL_JET_FILE=${FL_COMPILED_ROOT_DIR}/Android/FleksySDKResources/encrypted/resourceArchive-${LANG}-${COUNTRY}.jet
FL_QP=$(baseDir)/bin/QPMeasure
FL_SIM_GRAMS=$(baseDir)/bin/SimNGrams
QP_OUTPUT_FILE=${FL_QUALITY_ANALYSIS_OUTPUT}/QPOutput.txt

mkdir -p ${FL_QUALITY_ANALYSIS_OUTPUT}
rm -f ${FL_QUALITY_ANALYSIS_OUTPUT}/*

if [[ ${USE_PARLIMENT_SRC} -eq 1 ]]; then
    PARL_SAMPLE=${FL_QUALITY_ANALYSIS_OUTPUT}/parlSample.txt
    PARL_FILE=`ls -l ${FL_PARLIMENT_ASSET_DIR} | awk '{print $9}'`
    PARL_FILE=`echo ${PARL_FILE}`

    echo "Sampling sentences from the parliment source..."
    $PYTHON3 ${FL_COMPILED_QUALITY_DIR}/sampleSentences.py ${FL_PARLIMENT_ASSET_DIR}/${PARL_FILE} ${PARL_SRC_SIZE} > \
	${PARL_SAMPLE}
    
    let CNT=1
    for NOISE in ${QP_NOISE_SEQUENCE}; do
	echo "Launching QP for noise ${NOISE}"
	${FL_QP} ${FL_JET_FILE} ${PARL_SAMPLE} 0 20 $NOISE >> ${QP_OUTPUT_FILE}_$NOISE &
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

    echo "Preparing QP output"
    for NOISE in ${QP_NOISE_SEQUENCE}; do
	cat ${QP_OUTPUT_FILE}_$NOISE >> ${QP_OUTPUT_FILE}
	rm ${QP_OUTPUT_FILE}_$NOISE
    done
fi


