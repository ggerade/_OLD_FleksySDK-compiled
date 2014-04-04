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
	${FL_QP} ${FL_JET_FILE} ${QPM_SAMPLE} 0 ${NOISE} ${QPM_TRIALS} >> \
	    ${QPM_OUTPUT_FILE}_$NOISE &
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

function runSimNGrams()
{
    TYPE=$1
    FILE=$2

    echo "Simulating NGrams for ${TYPE} with file ${FILE}"
    LENGTH=`wc -l $FILE | awk '{print $1}'`
    SUB_LENGTH=$(( $LENGTH/${NUM_PROCS} ))

    for i in `seq 1 ${NUM_PROCS}`; do 
	START=$(( ($i-1)*$SUB_LENGTH + 1 ))
	END=$(( $START + $SUB_LENGTH - 1 ))
	sed -n "$START,${END}p" $FILE > ${FL_QUALITY_ANALYSIS_OUTPUT}/_${i}.txt
    done

    for i in `seq 1 ${NUM_PROCS}`; do
	${FL_SIM_GRAMS} ${FL_JET_FILE} ${FL_QUALITY_ANALYSIS_OUTPUT}/_${i}.txt \
	    ${SG_TRIALS} 1 ${SG_OFFSET} ${SG_STD} > \
	    ${SG_OUTPUT}_$i &
	ID[$i]=$!
    done

    echo "waiting for processes to finish...."
    for i in `seq 1 ${NUM_PROCS}`; do
	waitProc ${ID[$i]} 10
    done

    for i in `seq 1 ${NUM_PROCS}`; do
	rm ${FL_QUALITY_ANALYSIS_OUTPUT}/_${i}.txt
	cat ${SG_OUTPUT}_$i >> ${SG_OUTPUT}
	rm ${SG_OUTPUT}_$i
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
    if [[ ${RUN_QP} -eq 1 ]]; then 
	PARL_FILE=`ls -l ${FL_PARLIMENT_ASSET_DIR} | awk '{print $9}'`
	PARL_FILE=`echo ${PARL_FILE}`

	# set up variables for runQPMeasure to work
	QPM_SAMPLE=${FL_QUALITY_ANALYSIS_OUTPUT}/parlSample.txt
	QPM_FILE=${FL_PARLIMENT_ASSET_DIR}/${PARL_FILE}
	QPM_SRC_SIZE=${PARL_QP_SRC_SIZE}
	QPM_NOISE_SEQUENCE=${PARL_QP_NOISE_SEQUENCE}
	QPM_TRIALS=${PARL_QP_TRIALS}
	QPM_OUTPUT_FILE=${FL_QUALITY_ANALYSIS_OUTPUT}/QPParlOutput.txt
	runQPMeasure parliment
    fi

    if [[ ${RUN_SG} -eq 1 ]]; then
	SG_OFFSET=${PARL_SG_OFFSET}
	SG_STD=${PARL_SG_STD}
	SG_TRIALS=${PARL_SG_TRIALS}
	SG_OUTPUT=${FL_QUALITY_ANALYSIS_OUTPUT}/SGParlBigrams.txt    
	echo ""
	runSimNGrams parliment ${FL_QUALITY_ANALYSIS_DATA}/parlBigrams.txt

	SG_OUTPUT=${FL_QUALITY_ANALYSIS_OUTPUT}/SGParlTrigrams.txt    
	echo ""
	runSimNGrams parliment ${FL_QUALITY_ANALYSIS_DATA}/parlTrigrams.txt
    fi
fi

if [[ ${USE_ENGINE_SRC} -eq 1 ]]; then
    if [[ ${RUN_SG} -eq 1 ]]; then
	SG_OFFSET=${ENG_SG_OFFSET}
	SG_STD=${ENG_SG_STD}
	SG_TRIALS=${ENG_SG_TRIALS}
	SG_OUTPUT=${FL_QUALITY_ANALYSIS_OUTPUT}/SGEngBigrams.txt    
	echo ""
	runSimNGrams engine ${FL_QUALITY_ANALYSIS_DATA}/engBigrams.txt

	SG_OUTPUT=${FL_QUALITY_ANALYSIS_OUTPUT}/SGEngTrigrams.txt    
	echo ""
	runSimNGrams engine ${FL_QUALITY_ANALYSIS_DATA}/engTrigrams.txt
    fi
fi

if [[ ${USE_USER_SRC} -eq 1 ]]; then
    if [[ ${RUN_QP} -eq 1 ]]; then 
	# set up variables for runQPMeasure to work
	QPM_SAMPLE=${FL_QUALITY_ANALYSIS_OUTPUT}/userSample.txt
	QPM_FILE=${FL_QUALITY_ANALYSIS_DATA}/userText.txt
	QPM_SRC_SIZE=${USER_QP_SRC_SIZE}
	QPM_NOISE_SEQUENCE=${USER_QP_NOISE_SEQUENCE}
	QPM_TRIALS=${USER_QP_TRIALS}
	QPM_OUTPUT_FILE=${FL_QUALITY_ANALYSIS_OUTPUT}/QPUserOutput.txt
	runQPMeasure user
    fi

    if [[ ${RUN_SG} -eq 1 ]]; then
	SG_OFFSET=${USER_SG_OFFSET}
	SG_STD=${USER_SG_STD}
	SG_TRIALS=${USER_SG_TRIALS}
	SG_OUTPUT=${FL_QUALITY_ANALYSIS_OUTPUT}/SGUserBigrams.txt    
	echo ""
	runSimNGrams user ${FL_QUALITY_ANALYSIS_DATA}/userBigrams.txt

	SG_OUTPUT=${FL_QUALITY_ANALYSIS_OUTPUT}/SGUserTrigrams.txt    
	echo ""
	runSimNGrams user ${FL_QUALITY_ANALYSIS_DATA}/userTrigrams.txt
    fi
fi


