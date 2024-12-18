#!/bin/bash

# print script usage
print_help () {
    echo "Usage: ./run_tests.sh <subfolder to execute> [-h | -c \"cookie_val\"][-f][-y <year_num>]"
    echo -e "\t-h print help"
    echo -e "\t-c input new cookie"
    echo -e "\t-f force update"
    echo -e "\t-y year number"
    echo ""
    echo "Example 1: ./run_tests.sh Day1 -c mySecret_C00K13"
    echo "Example 2: ./run_tests.sh 1"
}

# set global variables
COOKIE_FILE="cookie.txt"
FOLDER_PREFIX="Day"
SRC_SUFFIX="/src"
INPUT_SUFFIX="$SRC_SUFFIX/input.txt"
PROBLEM_SUFFIX="/problem.md"
NUM_ARGS=0
YEAR=2024
USER_AGENT="https://github.com/irongiant33/AdventOfCode"

# parse command arguments
if [ $# -lt 1 ]
then
    print_help
    exit 1
fi
while [[ $# -gt 0 ]]; do
  case $1 in
    -h|--help)
      print_help
      shift # past argument
      exit 0;
      ;;
    -c|--cookie)
      if [[ $# -gt 1 ]]
      then
        COOKIE="$2"
        shift # past argument
        shift # past value
      else
        print_help
        exit 1;
      fi
      ;;
    -f|--force)
      FORCE_UPDATE="true"
      shift # past argument
      ;;
    -y|--year)
      if [[ $# -gt 1 ]]
      then
        YEAR="$2"
        shift # past argument
        shift # past value
      else
        print_help
        exit 1;
      fi
      ;;
    -*|--*)
      echo "Unknown option $1"
      exit 1
      ;;
    *)
      if [[ $NUM_ARGS -lt 1 ]]
      then
        POSITIONAL_ARG="$1" # save positional arg
        NUM_ARGS=$(( NUM_ARGS + 1))
        shift # past argument
      else
        print_help
        exit 1;
      fi
      ;;
  esac
done

# check to see if cookie file already exists
if [[ -f "$COOKIE_FILE" && -z ${COOKIE+x} ]]
then
    COOKIE="$( < ${COOKIE_FILE} )"
else
    echo ${COOKIE} > ${COOKIE_FILE}
fi

# determine the day number and subfolder name to save the problem input 
found=`echo $POSITIONAL_ARG | grep -e $FOLDER_PREFIX`
if [[ ! -z $found ]]
then
    INPUT_FILE="$POSITIONAL_ARG$INPUT_SUFFIX"
    PROBLEM_FILE="$POSITIONAL_ARG$PROBLEM_SUFFIX"
    DAY_NUM=${POSITIONAL_ARG:3}
else
    DAY_NUM=$POSITIONAL_ARG
    INPUT_FILE="$FOLDER_PREFIX$POSITIONAL_ARG$INPUT_SUFFIX"
    PROBLEM_FILE="$FOLDER_PREFIX$POSITIONAL_ARG$PROBLEM_SUFFIX"
fi

# create subdirectories if they do not exist
if [[ ! -d $FOLDER_PREFIX$POSITIONAL_ARG ]] ; then
    echo "$FOLDER_PREFIX$POSITIONAL_ARG does not exist, creating it"
    mkdir $FOLDER_PREFIX$POSITIONAL_ARG
fi
if [[ ! -d $FOLDER_PREFIX$POSITIONAL_ARG$SRC_SUFFIX ]] ; then
    echo "$FOLDER_PREFIX$POSITIONAL_ARG$SRC_SUFFIX does not exist, creating it"
    mkdir $FOLDER_PREFIX$POSITIONAL_ARG$SRC_SUFFIX
fi

echo -n "Writing to $INPUT_FILE..."
# fetch the problem input and save it
if [[ ! -f "$INPUT_FILE" || ! -z $FORCE_UPDATE ]]
then
    curl "https://adventofcode.com/$YEAR/day/$DAY_NUM/input" -H "cookie: $COOKIE" -A "$USER_AGENT" > "$INPUT_FILE"
    echo "done"
else
    echo "Input at $INPUT_FILE already exists"
fi

echo -n "Writing to $PROBLEM_FILE..."
# fetch the problem statement and save it
if [[ ! -f "$PROBLEM_FILE" || ! -z $FORCE_UPDATE ]]
then
    curl -s "https://adventofcode.com/$YEAR/day/$DAY_NUM" -H "cookie: $COOKIE" -A "$USER_AGENT" | pandoc -f html -t markdown_strict > "$PROBLEM_FILE"
    echo "done"
else
    echo "Input at $PROBLEM_FILE already exists"
fi

cd "Day$DAY_NUM"
cp ../py_tests.sh .
#bash py_tests.sh $YEAR $DAY_NUM $COOKIE $USER_AGENT
cd ..
