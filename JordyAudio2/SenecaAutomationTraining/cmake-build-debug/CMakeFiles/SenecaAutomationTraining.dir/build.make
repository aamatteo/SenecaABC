# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/matteo/clion-2021.1.1/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/matteo/clion-2021.1.1/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/matteo/Desktop/backup/SenecaAutomationTraining

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/matteo/Desktop/backup/SenecaAutomationTraining/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/SenecaAutomationTraining.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SenecaAutomationTraining.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SenecaAutomationTraining.dir/flags.make

CMakeFiles/SenecaAutomationTraining.dir/main.cpp.o: CMakeFiles/SenecaAutomationTraining.dir/flags.make
CMakeFiles/SenecaAutomationTraining.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/matteo/Desktop/backup/SenecaAutomationTraining/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SenecaAutomationTraining.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SenecaAutomationTraining.dir/main.cpp.o -c /home/matteo/Desktop/backup/SenecaAutomationTraining/main.cpp

CMakeFiles/SenecaAutomationTraining.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SenecaAutomationTraining.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/matteo/Desktop/backup/SenecaAutomationTraining/main.cpp > CMakeFiles/SenecaAutomationTraining.dir/main.cpp.i

CMakeFiles/SenecaAutomationTraining.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SenecaAutomationTraining.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/matteo/Desktop/backup/SenecaAutomationTraining/main.cpp -o CMakeFiles/SenecaAutomationTraining.dir/main.cpp.s

# Object files for target SenecaAutomationTraining
SenecaAutomationTraining_OBJECTS = \
"CMakeFiles/SenecaAutomationTraining.dir/main.cpp.o"

# External object files for target SenecaAutomationTraining
SenecaAutomationTraining_EXTERNAL_OBJECTS =

SenecaAutomationTraining: CMakeFiles/SenecaAutomationTraining.dir/main.cpp.o
SenecaAutomationTraining: CMakeFiles/SenecaAutomationTraining.dir/build.make
SenecaAutomationTraining: CMakeFiles/SenecaAutomationTraining.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/matteo/Desktop/backup/SenecaAutomationTraining/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable SenecaAutomationTraining"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SenecaAutomationTraining.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SenecaAutomationTraining.dir/build: SenecaAutomationTraining

.PHONY : CMakeFiles/SenecaAutomationTraining.dir/build

CMakeFiles/SenecaAutomationTraining.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SenecaAutomationTraining.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SenecaAutomationTraining.dir/clean

CMakeFiles/SenecaAutomationTraining.dir/depend:
	cd /home/matteo/Desktop/backup/SenecaAutomationTraining/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/matteo/Desktop/backup/SenecaAutomationTraining /home/matteo/Desktop/backup/SenecaAutomationTraining /home/matteo/Desktop/backup/SenecaAutomationTraining/cmake-build-debug /home/matteo/Desktop/backup/SenecaAutomationTraining/cmake-build-debug /home/matteo/Desktop/backup/SenecaAutomationTraining/cmake-build-debug/CMakeFiles/SenecaAutomationTraining.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SenecaAutomationTraining.dir/depend

