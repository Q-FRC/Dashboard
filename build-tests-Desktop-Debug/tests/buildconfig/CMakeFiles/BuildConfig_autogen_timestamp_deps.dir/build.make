# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /hdd/code/QFRCDashboard/tests

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /hdd/code/QFRCDashboard/build-tests-Desktop-Debug

# Utility rule file for BuildConfig_autogen_timestamp_deps.

# Include any custom commands dependencies for this target.
include tests/buildconfig/CMakeFiles/BuildConfig_autogen_timestamp_deps.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/buildconfig/CMakeFiles/BuildConfig_autogen_timestamp_deps.dir/progress.make

tests/buildconfig/CMakeFiles/BuildConfig_autogen_timestamp_deps: /usr/lib/qt6/uic
tests/buildconfig/CMakeFiles/BuildConfig_autogen_timestamp_deps: /usr/lib/qt6/moc
tests/buildconfig/CMakeFiles/BuildConfig_autogen_timestamp_deps: /usr/lib/libQt6Core.so.6.6.1

BuildConfig_autogen_timestamp_deps: tests/buildconfig/CMakeFiles/BuildConfig_autogen_timestamp_deps
BuildConfig_autogen_timestamp_deps: tests/buildconfig/CMakeFiles/BuildConfig_autogen_timestamp_deps.dir/build.make
.PHONY : BuildConfig_autogen_timestamp_deps

# Rule to build all files generated by this target.
tests/buildconfig/CMakeFiles/BuildConfig_autogen_timestamp_deps.dir/build: BuildConfig_autogen_timestamp_deps
.PHONY : tests/buildconfig/CMakeFiles/BuildConfig_autogen_timestamp_deps.dir/build

tests/buildconfig/CMakeFiles/BuildConfig_autogen_timestamp_deps.dir/clean:
	cd /hdd/code/QFRCDashboard/build-tests-Desktop-Debug/tests/buildconfig && $(CMAKE_COMMAND) -P CMakeFiles/BuildConfig_autogen_timestamp_deps.dir/cmake_clean.cmake
.PHONY : tests/buildconfig/CMakeFiles/BuildConfig_autogen_timestamp_deps.dir/clean

tests/buildconfig/CMakeFiles/BuildConfig_autogen_timestamp_deps.dir/depend:
	cd /hdd/code/QFRCDashboard/build-tests-Desktop-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /hdd/code/QFRCDashboard/tests /hdd/code/QFRCDashboard/lib/buildconfig /hdd/code/QFRCDashboard/build-tests-Desktop-Debug /hdd/code/QFRCDashboard/build-tests-Desktop-Debug/tests/buildconfig /hdd/code/QFRCDashboard/build-tests-Desktop-Debug/tests/buildconfig/CMakeFiles/BuildConfig_autogen_timestamp_deps.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : tests/buildconfig/CMakeFiles/BuildConfig_autogen_timestamp_deps.dir/depend

