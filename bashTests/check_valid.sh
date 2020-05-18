#!/bin/sh

if [ -f colors.sh ]; then
	. colors.sh
fi

LEM_IN_EXEC=$1

MAP_PATH=maps/valid
INPUT_DATA=data_valid.txt

print_ok()
{
	printf "${GREEN}%s${RESET}" "$1"
}

print_error()
{
	printf "${RED}%s${RESET}" "$1"
}

print_warning()
{
	printf "${YELLOW}%s${RESET}" "$1"
}

run_test()
{
	local name=`echo $@ | cut -d';' -f1`
	local map=`echo $@ | cut -d';' -f2`

	printf "%-50s" "$map"
	printf "\n"
	if [ -f "${MAP_PATH}/${map}" ];then
		bash checker.sh ${LEM_IN_EXEC} ${MAP_PATH}/${map}
	fi
	printf "\n"
}

run_all_tests()
{
	while read line
	do
		run_test ${line}
	done < ${INPUT_DATA}
}

print_usage_and_exit()
{
	printf "%s\n" "Usage: ./check_invalid_maps.sh exec"
	printf "%s\n" "  -exec   Path to executable"
	exit
}

if [ $# -ne 1 ];then
	print_usage_and_exit
	exit
fi

if [ ! -f $1 ];then
	printf "%s\n" "Executable ($1) not found"
	exit
fi

run_all_tests

