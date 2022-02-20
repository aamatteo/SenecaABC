#!/bin/bash
#
# As all the log files accumulate here
# this script moves them out of the way
# and does some extras because why not
#


yesorno()
{
	local input
	while true;
	do
		echo -n "yes or no (y/n) : "
		read input
		
		[[ ${input:0:1} == 'y' || ${input:0:1} == 'Y' ]] && return 0;
		[[ ${input:0:1} == 'n' || ${input:0:1} == 'N' ]] && continue; # exit 0;
		
		echo "The options are y or n, so not $input";
	done
}


# get today's date
today=$(date +%Y-%m-%d)

# get name of destination directory
# ask for user input
echo "Today is: $today"
echo -n "Destination dir will be ./$today"_
read text
dest_dir="./${today}_${text}/"

# check input
if [[ -z $text ]]; then
	echo "Input required"
	exit 1;
fi;

# make destination directory
[[ -d $dest_dir ]] && { echo "Directory already exists. Continue?"; yesorno; }
mkdir -p $dest_dir

# move all 0*.log files
# technically we could also move all *.log files
mv 0*.log $dest_dir




# usb disk mounts at /media/disk/
if [[ -d /media/disk/SRS_logs ]];
then 
	# ask to copy directory
	echo "Copy data to usb drive?"
	yesorno;
	
	# copy
	# cp -r 2017-05-03_sxx/ /media/disk/SRS_logs/
	cp -r $dest_dir /media/disk/SRS_logs/ && echo "copy complete";
fi;


