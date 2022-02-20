#!/bin/bash
# visualize DUECA communication
# by PvanOorschot
#
# Written in bash, because this started out as a few lines of code
# When I started this I didn't know much about the DUECA comms and
# my goal was to just see what modules we had and what channels
# they used. While the project grew, this script grew with it.
# That resulted in this unmaintainable a code, probably - no
# hopefully - the worst code made in the last years.
# 
# This script only checks which modules use which channels 
#  using the comm-objects.lst file and a token check in the
#  header files.
# While it makes a distinction between reading and writing, 
#  it does not take into account user interaction nor timings.
# It does not check what is actually loaded in your dueca.mod
# 
# not (yet) compatible with DUECA2 comms, because I don't need it for now
# 
# modules  : blocks
# channels : circles
# 
# outputs data to dot-file in your project directory
# if you have xdot installed, it will also open the file and convert to pdf & svg
# 

# all with #HC = HARDCODED STUFF FOR SenecaTraining -- using AddLineToListException to reverse line direction


# project location should be provided as input
if [[ -n $1 && -d $1 ]]; then
	PROJECT_PATH=${1};
else
	echo "Project '${1}' not found. Give the project location as input.";
	exit 1;
fi;

# move to project directory
cd $PROJECT_PATH || exit 1;
# project name
PROJECT_NAME=$(basename $(pwd));

# check if we are indeed in a directory that could be a DUECA project, else exit
if [[ ! -d $PROJECT_NAME ]];
then
	# try again, one level up
	cd ..;
	
	if [[ $PROJECT_NAME == $(basename $(pwd)) ]];
	then
		echo "This also works. :)";
	else
		echo "Error 404: DUECA project not found.";
		exit 404;
	fi;
fi;


### STYLES ###
# style and colors for read and write lines
STYLE_READ='color=green';
STYLE_WRITE='color=blue';
STYLE_READWRITE='color=red,dir=both';
# style for modules
STYLE_MOD_OWN='fillcolor=grey67';
STYLE_MOD_BORROWED='fillcolor=grey92';
# style for channels
STYLE_CH_OWN='style=filled,fillcolor=yellow';
STYLE_CH_EVENT='style=dotted';

### SETTINGS ###
# List input and output modules
input_modules=(); # example: "Generic/joystick" "SRSToolbox/GearSelector"
output_modules=(); # example: "SRSMotion/motion-viewer"
# List of (borrowed) projects to ignore
ignore_projects=(); # example: 'SRSMotion'
# List of modules to ignore
ignore_modules=();
# List of channels to ignore
ignore_channels=();
#TODO make a list of some common input and output modules (joystick, ECI, ..., GUI, display)

# auto-fill the lists input_modules and output_modules with best guesses
auto_input_output=true;
# show token names (incomplete)
display_token_names=false;

# name of the dot file we are making
FILE_final="./$PROJECT_NAME.dot";



#--------------------------------------------------------------------------------------------------------#
# Get the projects config

# include config file if it exists in the project directory
[[ -f comms-visualize.conf ]] && . comms-visualize.conf || cat << END_OF_TEMPLATE > comms-visualize.conf
#!/bin/bash
# Configuration for the comms-visualize script
# settings for $PROJECT_NAME

# List input and output modules
input_modules=(); # example: "Generic/joystick" "SRSToolbox/GearSelector"
output_modules=(); # example: "SRSMotion/motion-viewer"

# List of (borrowed) projects to ignore
ignore_projects=(); # example: 'SRSMotion'
# List of modules to ignore
ignore_modules=();
# List of channels to ignore
ignore_channels=();

# auto-fill the lists input_modules and output_modules with best guesses
auto_input_output=true;

END_OF_TEMPLATE



#--------------------------------------------------------------------------------------------------------#
# Define some functions

## Add the current channel to the channel lists
#
# reads
#- $channelname
#- $channelfile_path
#
# arrays
#- list_of_channels
#- list_of_event_channels
#- list_of_stream_channels
#
AddChannelToList() {
	local tmp=false;
	
	# is the channel already on the list
	# note this method has flaws, but good enough for here
	case "${list_of_channels[@]}" in  *"$channelname"*) tmp=true;; esac
	
	if [[ $tmp == false ]]; then
		# add to list
		list_of_channels+=("$channelname");
		
		# type of channel
		if [[ $(getTypeOfChannel "$channelfile_path") == 'event' ]];
		then
			list_of_event_channels+=("$channelname");
		else
			list_of_stream_channels+=("$channelname");
		fi;
		
		# item added to the list
		return 0;
	fi;
	
	# already in the list
	return 1;
}

AddLineToList() {
	local _mod_name_="$(formatModuleName $module_name)";
	
	local label='';
	if [[ $display_token_names == true ]]; then
		label=",label=\"$token\"";      # to add token names
	fi;
#	if [[ -n $_part_ && "$_part_" != 'part' ]]; then
#		label=",label=\"<$_part_>\"";   # to add part
#	fi;
	
	case $1 in
		read      )
			list_of_lines+=("\"$channelname\" -- \"$_mod_name_\" [$STYLE_READ$label]");; # ch --> mod
		read_b    )
			list_of_lines+=("\"$_mod_name_\" -- \"$channelname\" [$STYLE_READ,dir=back$label]");; # mod <-- ch
		write     )
			list_of_lines+=("\"$_mod_name_\" -- \"$channelname\" [$STYLE_WRITE$label]");; # mod --> ch
		write_b   )
			list_of_lines+=("\"$channelname\" -- \"$_mod_name_\" [$STYLE_WRITE,dir=back$label]");; # ch <-- mod   ,style=dotted
		rw_mod_ch )
			list_of_lines+=("\"$_mod_name_\" -- \"$channelname\" [$STYLE_READWRITE$label]"); # mod <--> ch
			list_of_lines+=("//\"$channelname\" -- \"$_mod_name_\" [$STYLE_READWRITE,style=dotted$label]");; # ch <--> mod (commented)
		rw_ch_mod )
			list_of_lines+=("\"$channelname\" -- \"$_mod_name_\" [$STYLE_READWRITE$label]");; # ch <--> mod
		*         )
			echo "Error 2963567"; return 1;;
	esac
	
	return 0;
}

AddLineToListException() { # $1 = action; $2 = module; $3 = channel
	[[ -z $2 ]] && return 9;
	# check channel name
	[[ -n $3 && ${channelname:(-${#3})} != "$3" ]] && return 1;
	# check module name
	if [[ ${module_name:(-${#2})} == "$2" ]];
	then
		AddLineToList "$1";
		return 0;
	fi;
	return 1;
}

# check hxx-files for tokens (r/w) (lines that are commented out should be ignored)
#TODO also remove comments between /* and */
#note: there could be any amount of space between "Token" and "<" and between "<" and "$dconame"
#note: a channel type can be used multiple times with different tokens and parts
CheckForTokens() {
	local line;
	
	# quick check
	egrep -v '(^\s*\t*//)' "$module_name"/*.hxx | grep -q "$dconame" \
		|| { echo "NEGATIVE: $dconame"; return 1; }
	
	# check for write tokens
	while read -r line; do
		# found one
		writetoken=true;
		# add to list
		list_of_found_tokens+=("$line");
		list_of_found_tokens_rw+=("write");
		# statistics
		((n_writes++));
		# details
		getTokenName "$line";
	done < <(egrep -v '(^\s*\t*//)' "$module_name"/*.hxx | grep "WriteToken\s*\t*<\s*\t*$dconame")
	
	# check for read tokens
	while read -r line; do
		# found one
		readtoken=true;
		# add to list
		list_of_found_tokens+=("$line");
		list_of_found_tokens_rw+=("read");
		# statistics
		((n_reads++));
		# details
		getTokenName "$line";
	done < <(egrep -v '(^\s*\t*//)' "$module_name"/*.hxx | grep "ReadToken\s*\t*<\s*\t*$dconame")
	
	#TODO ok, so this finds mutiple occurrences, now have to process each of them
	
	return 0;
}

getTokenName() {
	local string=$*;
	#local token;
	local filename;
	#_part_;
	
	# to get the token name
	#- get everything before the first ;
	#- followed by everything after the last space
	
	string=${string%%;*}; # remove all after first ;
	token=${string##* }; # remove all before last space
	
	#- then we need to find 'this_token(' in the cxx file (file with the same name)
	#- and from that get the specific name (item after dconame) often just part
	
	filename=${string%%.hxx*}; # remove all after first .hxx
	
	_part_=$(egrep -v '(^\s*\t*//)' "$module_name"/*.cxx | grep "$token(") || echo "Error 836352"; #TODO does not always work
	_part_=${_part_#*$dconame}; # remove all before first $dconame
	_part_=${_part_#*,}; # remove all before first ,
	_part_=${_part_%%)*}; # remove all after first )
	_part_=${_part_// /}; # remove all spaces
	_part_=${_part_//\"/}; # this freaks out the editor "} # remove all "
	
	echo "	Found token: $token, part: \"$_part_\", on channel $dconame";
}

# returns stream or event for a given dco file
getTypeOfChannel() { # $1 = path to dco file
	[[ -z $1 ]] && return 9;
	
	# search
	local grep_event=$(grep "(Event " "$1");                   # (Event dconame
	local grep_eventandstream=$(grep "(EventAndStream " "$1"); # (EventAndStream dconame
	local grep_stream=$(grep "(Stream " "$1");                 # (Stream
	
	# return type of channel
	if [[ -n $grep_event ]]; then
		echo "event";
		return 0;
	elif [[ -n $grep_eventandstream ]]; then
		echo "eventandstream";
		return 0;
	elif [[ -n $grep_stream_basic ]]; then #TODO do more with this
		echo "stream";
		return 0;
	else
		echo "Error 2081241: Problem when looking at $1"
		return 1;
	fi;
}

IgnoreModule() { # $1 = module
	[[ -z $1 ]] && return 9;
	# check module name
	if [[ ${module_name:(-${#1})} == "$1" ]];
	then
		echo ">> Ignoring this module";
		return 0;
	fi;
	return 1;
}

IgnoreChannel() { # $1 = module
	[[ -z $1 ]] && return 9;
	# check channel name, could be both with and without the .dco extension
	if [[ $dconame == "$1" || $channelname == "$1" ]];
	then
		echo ">> Ignoring channel $1";
		return 0;
	fi;
	return 1;
}

IgnoreProject() { # $1 = project
	[[ -z $1 ]] && return 9;
	# check project name part of the full module name
	if [[ ${module_name:0:(${#1})} == "$1" ]];
	then
		echo ">> Ignoring this project";
		return 0;
	fi;
	return 1;
}

#DuecaDotModModuleCheck() { #TODO
#	dueca_mod="$PROJECT_NAME/run/solo/solo/dueca.mod";
#	# const char* const ConventionalDisplay::classname = "conventional-display";
#	# const char* const CitationNavigator::classname = "citation-navigator";
#	# const char* const PA34_model::classname = "pa_34_model";
#	grep "::classname = " ./*/*/*.cxx ## do this on a per folder basis instead? maybe even a per cxx-file basis ?
#	grep "(make-module '$nameofthemodule" $dueca_mod;
#}

formatModuleName() {
	# replace / by a newline
	echo ${*//\//<br>};
}

formatChannelName() {
	# replace /comm-objects/ by a newline
	echo ${*//\/comm-objects\//<br>};
}



#--------------------------------------------------------------------------------------------------------#
# Analyze the project
# Modules -> channels used by module -> tokens for channel

list_of_mudules=();
list_of_channels=();
list_of_event_channels=();
list_of_stream_channels=();
list_of_lines=();


# find all comm-objects.lst files
comm_objects_lists=(*/*/comm-objects.lst);

# loop through all comm-objects.lst files
for comm_objects_lst in ${comm_objects_lists[@]};
do
	let n_actions=0;
	let n_writes=0;
	let n_reads=0;
	
	# get module directory for comm-objects.lst file
	module_name=$(dirname "$comm_objects_lst");
	
	# get module name from directory path
	echo "Found module: $module_name";
	
	# check
	[[ '*/*' == "$module_name" ]] && { echo "Error finding comm-objects.lst files"; exit 1; }
	
	# should we ignore this module
	for ii in ${ignore_modules[@]};
	do
		IgnoreModule $ii && continue 2;
	done;
	# should we ignore this project
	for ii in ${ignore_projects[@]};
	do
		IgnoreProject $ii && continue 2;
	done;
	
	# look through comm-objects.lst files to get .dco files
	while channelfile_path=; IFS=$' \t\r\n' read -r channelfile_path || [[ $channelfile_path ]];
	do
		# ignore all empty or commented lines
		[[ -z $channelfile_path ]] || [[ ${channelfile_path:0:1} == '#' ]] && continue;
		
		# all other lines represent a channel
		channelname="$(formatChannelName $channelfile_path)";
		dconame=$(basename $channelfile_path);
		dconame=${dconame/.dco/};
		
		# should we ignore this channel
		for ii in ${ignore_channels[@]};
		do
			IgnoreChannel $ii && continue 2;
		done;
		
		#TODO multiple tokens can exists for each channel
		#TODO instead of a simple yes/no we need more info here >> more loops.....?
		#TODO   CheckForTokens() makes an array, which is put through a while loop here?
		#TODO     how to differenciate between read and write then? .. do that in CheckForTokens()
		#           what about the read and write...
		
		#TODO what needs to be defined?
		# channelname / dco name -> stays constant
		# getTokenName "$tmp"; can be done here
		# throw $tmp in the array then :)
		
		# check for tokens for this channel
		list_of_found_tokens=();
		list_of_found_tokens_rw=();
		writetoken=false;
		readtoken=false;
		CheckForTokens;
		
#		for _token_ in ${list_of_found_tokens[@]};
#		do
#			getTokenName $_token_;
			#TODO set writetoken and readtoken
			
			# from getTokenName()
			
#			if [[ -n $_part_ && "$_part_" != 'part' ]]; then
#				channelname+="<br>$_part_";
#			fi;
		
			# ignore write actions by CitationLogger (CitationReplayer)
			[[ $writetoken == true ]] && { IgnoreModule 'CitationLogger' && writetoken=false; } #HC
		
			# see if it needs to be added to our channels list
			if [[ $writetoken == true || $readtoken == true ]]
			then
				# found some action
				((n_actions++));
				# see if we need to add this channel to our list(s)
				AddChannelToList;
			fi;
			
			# connect modules and channels with line to show r/w
			if [[ $writetoken == true && $readtoken == true ]];
			then		
				AddLineToListException 'rw_ch_mod' 'PA34' 'CitationPilotInput.dco' && continue; #HC ch <--> mod
				AddLineToListException 'rw_ch_mod' 'MCP737GUI' 'MCP737Event.dco' && continue; #HC
				AddLineToListException 'rw_ch_mod' 'CitationNavigator' 'PilotControlConfig.dco' && continue; #HC
		#		AddLineToListException 'rw_ch_mod' 'CitationLogger' && continue; #HC
				AddLineToList 'rw_mod_ch'; # mod <--> ch
			elif [[ $writetoken == true ]];
			then
		#		AddLineToListException 'write_b' 'CitationLogger' && continue; #HC ch <-- mod
				AddLineToList 'write'; # mod --> ch
			elif [[ $readtoken == true ]];
			then
				AddLineToListException 'read_b' 'FCSAdapter' 'CitationOutput.dco' && continue; #HC mod <-- ch
				AddLineToList 'read'; # ch --> mod
			else
				echo -e "\tChannel '$channelfile_path' listed but no token was found";
			fi;
		
		# end of for loop
#		done
		
	# end of while loop
	done < "$comm_objects_lst"
	
	echo -e "\tNumber of channels: $n_actions, of which $n_writes are written and $n_reads are read";
	
	# if module uses one or more channels, add it to the modules list
	if (( $n_actions > 0 ));
	then
		list_of_mudules+=("$module_name");
		
		# what if there is some action but it is neither writes nor reads???
		(( $n_writes == 0 && $n_reads == 0 )) && { echo "Ohoh. Computer says no!"; exit 666; }
		
		if [[ $auto_input_output == true ]]
		then
			(( $n_writes == 0 )) && output_modules+=("$module_name");  # no writing, only reading
			(( $n_reads == 0 )) && input_modules+=("$module_name");    # no reading, only writing
		fi;
	fi;
	
# end of for loop
done;



#TODO check if successful before continuing

echo -e "\nFound ${#list_of_mudules[@]} modules"

(( ${#list_of_mudules[@]} < 1 )) && exit 1;



#--------------------------------------------------------------------------------------------------------#
# Generate the dot file

echo -e "\nWriting figure data to file $FILE_final";

# remove the file if it already exists
[[ -f $FILE_final ]] && rm $FILE_final;

# create empty file
touch $FILE_final || { echo "Cannot access file $FILE_final"; exit 101; }

# start output
echo -e "// Generated on $(date '+%d %b %Y at %Hh%Mm%Ss')
graph $PROJECT_NAME {
	rankdir=LR; // draw from left to right
	margin=0; // no margins
	
	// modules in boxes
	// own modules : [$STYLE_MOD_OWN]
	// borrowed    : [$STYLE_MOD_BORROWED]
	{ node [shape=box,style=filled,fillcolor=white];" >> $FILE_final;

# list all modules
# differentiate between own modules and borrowed modules
for _module_ in "${list_of_mudules[@]}"
do
	_module_="$(formatModuleName $_module_)";
	
	if [[ ${_module_:0:${#PROJECT_NAME}} == "$PROJECT_NAME" ]];
	then
		echo -e "\t\t\"$_module_\" [$STYLE_MOD_OWN];" >> $FILE_final;
	else
		echo -e "\t\t\"$_module_\" [$STYLE_MOD_BORROWED];" >> $FILE_final;
	fi;
done

echo -e "\t};
	
	// channels in ellipses
	node [shape=ellipse];
	
	// lines, you might want to switch some nodes (b--a instead of a--b)
	// read  : \"channel\" -- \"module\" [$STYLE_READ];
	// write : \"module\" -- \"channel\" [$STYLE_WRITE];
	// both  : \"module\" -- \"channel\" [$STYLE_READWRITE];
	edge [dir=forward];" >> $FILE_final;

# output the spiderweb of lines
for _line_ in "${list_of_lines[@]}"
do
	echo -e "\t$_line_;" >> $FILE_final;
done

# list all event channels
echo -e "\n\t// some channels are event channels, give them their own style" >> $FILE_final;
for _channel_ in "${list_of_event_channels[@]}"
do
	echo -e "\t\"$_channel_\" [$STYLE_CH_EVENT];" >> $FILE_final;
done

# and the stream channels
echo -e "\n\t// and some channels are stream channels, just listing them here, no changes made" >> $FILE_final;
for _channel_ in "${list_of_stream_channels[@]}"
do
	echo -e "\t\"$_channel_\";" >> $FILE_final;
done

echo -e " 	
	// manually align
	//{ rank = same; \"ch1-name\"; \"ch2-name\"; };
	" >> $FILE_final;

# make list of input modules
if [[ -n $input_modules ]]; then
	source_list='';
	for _module_ in ${input_modules[@]}; do
		source_list+="\t\t\"$(formatModuleName $_module_)\";\n";
	done;
fi;
# make list of output modules
if [[ -n $output_modules ]]; then
	sink_list='';
	for _module_ in ${output_modules[@]}; do
		sink_list+="\t\t\"$(formatModuleName $_module_)\";\n";
	done;
fi;

# add lists of input and output modules to file
echo -e "\t// list of input modules for on the left" >> $FILE_final;
echo -e "\t{ rank = source;\n$source_list\t};" >> $FILE_final;
echo -e "\t// list of output modules for on the right" >> $FILE_final;
echo -e "\t{ rank = sink;\n$sink_list\t};" >> $FILE_final;

# some extra lines for manually aligned channels
[[ -n $channel_alignments ]] && echo "	$channel_alignments" >> $FILE_final;

# finish the dot file
echo "}" >> $FILE_final;

# add line breaks by replacing <br> by an actual line break
sed -i -- 's/<br>/\\n/g' $FILE_final;



#--------------------------------------------------------------------------------------------------------#
# If xdot is installed
# Open the dot file and convert to SVG and PDF

if [[ -n $(which xdot) ]];
then
	# see if xdot can figure it out :)
	echo -n "Opening figure... ";
	xdot $FILE_final &
	echo "[Done]";
	
	# create SVG
	echo -n "Creating SVG... ";
	dot -Tsvg -o $FILE_final.svg $FILE_final; # -v
	echo "[Done]";
	
	# create PDF
	echo -n "Creating PDF... ";
	dot -Tpdf -o $FILE_final.pdf $FILE_final; # -v
	echo "[Done]";
fi;



#--------------------------------------------------------------------------------------------------------#
echo "End of script";
exit 0
#--------------------------------------------------------------------------------------------------------#



#TODO possible additions
# 
# at some later point this script should only take into account the modules
#	> defined in "modules.solo" or other platform list(s), and
#	> see if they are loaded in dueca.mod
#
# in case a module does both r/w to a channel it is not known what is the direction in time,
#   currently the assumption is that the write direction is more important,
#   works in about half the cases
#	> it is possible to check what triggers a module; if channel, this must mean reading is more important
# 
# 
#DONE
# 
# color boxes based on their project name (or just a different color for borrowed modules and channels)
#	> grey for borrowed items
#
# differentiate between event and stream channels
#	> make function AddChannelToList(ChannelName), which checks if already on list
#	> then calls getTypeOfChannel
#
# AddModuleToList and AddLineToList functions for writing to file
#
# split module and channel names over two lines ( project /n name )
#	> still requires manual work, replace all '<br>' with '\n' ('\\n') >> FIXED
#
# bug; the last line of the file is ignored
#
# getTypeOfChannel() returns stream or event for a given dco file
# color/shape channels based on if they are event or stream
#
# auto replace all '<br>' with '\n' ('\\n')
#	> make sure \n goes in as text and does not create a newline in text file
#
# define a list of ignored modules/channels/projects at the top of the file
#
# array of modules: list_of_mudules
# arrays of channels: list_of_channels, list_of_event_channels
#
# check if modules read/write
#	> modules that only write: mark as source
#	> modules that only read: must as sink
#
# get token name, and check constructor for more details on this comms channel
#
# add token name as label with lines
#
# more unmaintainable code added, some unmaintainable code changed. comes with absolutely no warranty
#



# all comm-objects.lst files -> gives channels used by module (read or write)
find . -type f -name comm-objects.lst

# all .dco files = channels
find . -type f -name "*.dco"

# find write token for PrimaryControls channel in Generic/joystick module header files
egrep -v '(^#|^\s*$|^\s*\t*#|^\s*\t*//)' /home/peter/dueca/SenecaTraining/Generic/joystick/*hxx | grep "WriteToken<PrimaryControls>"
# testing
egrep -v '(^#|^\s*$|^\s*\t*#|^\s*\t*//)' /home/peter/dueca/SenecaTraining/SenecaTraining/CitationLogger/*hxx | grep "Token<"

