# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/clion-2018.2.5/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion-2018.2.5/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/SERILOCAL/l.gagliano/PersonalRepository/OpenCL-Samples/Simple-OpenCL-Program/QueringPlatforms

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/SERILOCAL/l.gagliano/PersonalRepository/OpenCL-Samples/Simple-OpenCL-Program/QueringPlatforms/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/basic-template.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/basic-template.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/basic-template.dir/flags.make

CMakeFiles/basic-template.dir/main.cpp.o: CMakeFiles/basic-template.dir/flags.make
CMakeFiles/basic-template.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/SERILOCAL/l.gagliano/PersonalRepository/OpenCL-Samples/Simple-OpenCL-Program/QueringPlatforms/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/basic-template.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/basic-template.dir/main.cpp.o -c /home/SERILOCAL/l.gagliano/PersonalRepository/OpenCL-Samples/Simple-OpenCL-Program/QueringPlatforms/main.cpp

CMakeFiles/basic-template.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/basic-template.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/SERILOCAL/l.gagliano/PersonalRepository/OpenCL-Samples/Simple-OpenCL-Program/QueringPlatforms/main.cpp > CMakeFiles/basic-template.dir/main.cpp.i

CMakeFiles/basic-template.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/basic-template.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/SERILOCAL/l.gagliano/PersonalRepository/OpenCL-Samples/Simple-OpenCL-Program/QueringPlatforms/main.cpp -o CMakeFiles/basic-template.dir/main.cpp.s

# Object files for target basic-template
basic__template_OBJECTS = \
"CMakeFiles/basic-template.dir/main.cpp.o"

# External object files for target basic-template
basic__template_EXTERNAL_OBJECTS =

basic-template: CMakeFiles/basic-template.dir/main.cpp.o
basic-template: CMakeFiles/basic-template.dir/build.make
basic-template: /usr/local/cuda-10.0/lib64/libOpenCL.so
basic-template: CMakeFiles/basic-template.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/SERILOCAL/l.gagliano/PersonalRepository/OpenCL-Samples/Simple-OpenCL-Program/QueringPlatforms/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable basic-template"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/basic-template.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/basic-template.dir/build: basic-template

.PHONY : CMakeFiles/basic-template.dir/build

CMakeFiles/basic-template.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/basic-template.dir/cmake_clean.cmake
.PHONY : CMakeFiles/basic-template.dir/clean

CMakeFiles/basic-template.dir/depend:
	cd /home/SERILOCAL/l.gagliano/PersonalRepository/OpenCL-Samples/Simple-OpenCL-Program/QueringPlatforms/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/SERILOCAL/l.gagliano/PersonalRepository/OpenCL-Samples/Simple-OpenCL-Program/QueringPlatforms /home/SERILOCAL/l.gagliano/PersonalRepository/OpenCL-Samples/Simple-OpenCL-Program/QueringPlatforms /home/SERILOCAL/l.gagliano/PersonalRepository/OpenCL-Samples/Simple-OpenCL-Program/QueringPlatforms/cmake-build-debug /home/SERILOCAL/l.gagliano/PersonalRepository/OpenCL-Samples/Simple-OpenCL-Program/QueringPlatforms/cmake-build-debug /home/SERILOCAL/l.gagliano/PersonalRepository/OpenCL-Samples/Simple-OpenCL-Program/QueringPlatforms/cmake-build-debug/CMakeFiles/basic-template.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/basic-template.dir/depend

