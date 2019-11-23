# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/danielg/uni/thesis

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/danielg/uni/thesis

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/danielg/uni/thesis/CMakeFiles /home/danielg/uni/thesis/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/danielg/uni/thesis/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named libmask.so

# Build rule for target.
libmask.so: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 libmask.so
.PHONY : libmask.so

# fast build rule for target.
libmask.so/fast:
	$(MAKE) -f CMakeFiles/libmask.so.dir/build.make CMakeFiles/libmask.so.dir/build
.PHONY : libmask.so/fast

#=============================================================================
# Target rules for targets named inpainting

# Build rule for target.
inpainting: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 inpainting
.PHONY : inpainting

# fast build rule for target.
inpainting/fast:
	$(MAKE) -f CMakeFiles/inpainting.dir/build.make CMakeFiles/inpainting.dir/build
.PHONY : inpainting/fast

#=============================================================================
# Target rules for targets named amss_corner

# Build rule for target.
amss_corner: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 amss_corner
.PHONY : amss_corner

# fast build rule for target.
amss_corner/fast:
	$(MAKE) -f CMakeFiles/amss_corner.dir/build.make CMakeFiles/amss_corner.dir/build
.PHONY : amss_corner/fast

#=============================================================================
# Target rules for targets named corner_detection

# Build rule for target.
corner_detection: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 corner_detection
.PHONY : corner_detection

# fast build rule for target.
corner_detection/fast:
	$(MAKE) -f CMakeFiles/corner_detection.dir/build.make CMakeFiles/corner_detection.dir/build
.PHONY : corner_detection/fast

#=============================================================================
# Target rules for targets named libinpaint.so

# Build rule for target.
libinpaint.so: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 libinpaint.so
.PHONY : libinpaint.so

# fast build rule for target.
libinpaint.so/fast:
	$(MAKE) -f CMakeFiles/libinpaint.so.dir/build.make CMakeFiles/libinpaint.so.dir/build
.PHONY : libinpaint.so/fast

#=============================================================================
# Target rules for targets named libamss.so

# Build rule for target.
libamss.so: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 libamss.so
.PHONY : libamss.so

# fast build rule for target.
libamss.so/fast:
	$(MAKE) -f CMakeFiles/libamss.so.dir/build.make CMakeFiles/libamss.so.dir/build
.PHONY : libamss.so/fast

src/amss/amss.o: src/amss/amss.c.o

.PHONY : src/amss/amss.o

# target to build an object file
src/amss/amss.c.o:
	$(MAKE) -f CMakeFiles/amss_corner.dir/build.make CMakeFiles/amss_corner.dir/src/amss/amss.c.o
	$(MAKE) -f CMakeFiles/libamss.so.dir/build.make CMakeFiles/libamss.so.dir/src/amss/amss.c.o
.PHONY : src/amss/amss.c.o

src/amss/amss.i: src/amss/amss.c.i

.PHONY : src/amss/amss.i

# target to preprocess a source file
src/amss/amss.c.i:
	$(MAKE) -f CMakeFiles/amss_corner.dir/build.make CMakeFiles/amss_corner.dir/src/amss/amss.c.i
	$(MAKE) -f CMakeFiles/libamss.so.dir/build.make CMakeFiles/libamss.so.dir/src/amss/amss.c.i
.PHONY : src/amss/amss.c.i

src/amss/amss.s: src/amss/amss.c.s

.PHONY : src/amss/amss.s

# target to generate assembly for a file
src/amss/amss.c.s:
	$(MAKE) -f CMakeFiles/amss_corner.dir/build.make CMakeFiles/amss_corner.dir/src/amss/amss.c.s
	$(MAKE) -f CMakeFiles/libamss.so.dir/build.make CMakeFiles/libamss.so.dir/src/amss/amss.c.s
.PHONY : src/amss/amss.c.s

src/amss/amss_corner_detection.o: src/amss/amss_corner_detection.c.o

.PHONY : src/amss/amss_corner_detection.o

# target to build an object file
src/amss/amss_corner_detection.c.o:
	$(MAKE) -f CMakeFiles/amss_corner.dir/build.make CMakeFiles/amss_corner.dir/src/amss/amss_corner_detection.c.o
	$(MAKE) -f CMakeFiles/libamss.so.dir/build.make CMakeFiles/libamss.so.dir/src/amss/amss_corner_detection.c.o
.PHONY : src/amss/amss_corner_detection.c.o

src/amss/amss_corner_detection.i: src/amss/amss_corner_detection.c.i

.PHONY : src/amss/amss_corner_detection.i

# target to preprocess a source file
src/amss/amss_corner_detection.c.i:
	$(MAKE) -f CMakeFiles/amss_corner.dir/build.make CMakeFiles/amss_corner.dir/src/amss/amss_corner_detection.c.i
	$(MAKE) -f CMakeFiles/libamss.so.dir/build.make CMakeFiles/libamss.so.dir/src/amss/amss_corner_detection.c.i
.PHONY : src/amss/amss_corner_detection.c.i

src/amss/amss_corner_detection.s: src/amss/amss_corner_detection.c.s

.PHONY : src/amss/amss_corner_detection.s

# target to generate assembly for a file
src/amss/amss_corner_detection.c.s:
	$(MAKE) -f CMakeFiles/amss_corner.dir/build.make CMakeFiles/amss_corner.dir/src/amss/amss_corner_detection.c.s
	$(MAKE) -f CMakeFiles/libamss.so.dir/build.make CMakeFiles/libamss.so.dir/src/amss/amss_corner_detection.c.s
.PHONY : src/amss/amss_corner_detection.c.s

src/amss/chain.o: src/amss/chain.c.o

.PHONY : src/amss/chain.o

# target to build an object file
src/amss/chain.c.o:
	$(MAKE) -f CMakeFiles/amss_corner.dir/build.make CMakeFiles/amss_corner.dir/src/amss/chain.c.o
	$(MAKE) -f CMakeFiles/libamss.so.dir/build.make CMakeFiles/libamss.so.dir/src/amss/chain.c.o
.PHONY : src/amss/chain.c.o

src/amss/chain.i: src/amss/chain.c.i

.PHONY : src/amss/chain.i

# target to preprocess a source file
src/amss/chain.c.i:
	$(MAKE) -f CMakeFiles/amss_corner.dir/build.make CMakeFiles/amss_corner.dir/src/amss/chain.c.i
	$(MAKE) -f CMakeFiles/libamss.so.dir/build.make CMakeFiles/libamss.so.dir/src/amss/chain.c.i
.PHONY : src/amss/chain.c.i

src/amss/chain.s: src/amss/chain.c.s

.PHONY : src/amss/chain.s

# target to generate assembly for a file
src/amss/chain.c.s:
	$(MAKE) -f CMakeFiles/amss_corner.dir/build.make CMakeFiles/amss_corner.dir/src/amss/chain.c.s
	$(MAKE) -f CMakeFiles/libamss.so.dir/build.make CMakeFiles/libamss.so.dir/src/amss/chain.c.s
.PHONY : src/amss/chain.c.s

src/amss/least_squares.o: src/amss/least_squares.c.o

.PHONY : src/amss/least_squares.o

# target to build an object file
src/amss/least_squares.c.o:
	$(MAKE) -f CMakeFiles/amss_corner.dir/build.make CMakeFiles/amss_corner.dir/src/amss/least_squares.c.o
	$(MAKE) -f CMakeFiles/libamss.so.dir/build.make CMakeFiles/libamss.so.dir/src/amss/least_squares.c.o
.PHONY : src/amss/least_squares.c.o

src/amss/least_squares.i: src/amss/least_squares.c.i

.PHONY : src/amss/least_squares.i

# target to preprocess a source file
src/amss/least_squares.c.i:
	$(MAKE) -f CMakeFiles/amss_corner.dir/build.make CMakeFiles/amss_corner.dir/src/amss/least_squares.c.i
	$(MAKE) -f CMakeFiles/libamss.so.dir/build.make CMakeFiles/libamss.so.dir/src/amss/least_squares.c.i
.PHONY : src/amss/least_squares.c.i

src/amss/least_squares.s: src/amss/least_squares.c.s

.PHONY : src/amss/least_squares.s

# target to generate assembly for a file
src/amss/least_squares.c.s:
	$(MAKE) -f CMakeFiles/amss_corner.dir/build.make CMakeFiles/amss_corner.dir/src/amss/least_squares.c.s
	$(MAKE) -f CMakeFiles/libamss.so.dir/build.make CMakeFiles/libamss.so.dir/src/amss/least_squares.c.s
.PHONY : src/amss/least_squares.c.s

src/corner_detection.o: src/corner_detection.c.o

.PHONY : src/corner_detection.o

# target to build an object file
src/corner_detection.c.o:
	$(MAKE) -f CMakeFiles/libmask.so.dir/build.make CMakeFiles/libmask.so.dir/src/corner_detection.c.o
	$(MAKE) -f CMakeFiles/corner_detection.dir/build.make CMakeFiles/corner_detection.dir/src/corner_detection.c.o
.PHONY : src/corner_detection.c.o

src/corner_detection.i: src/corner_detection.c.i

.PHONY : src/corner_detection.i

# target to preprocess a source file
src/corner_detection.c.i:
	$(MAKE) -f CMakeFiles/libmask.so.dir/build.make CMakeFiles/libmask.so.dir/src/corner_detection.c.i
	$(MAKE) -f CMakeFiles/corner_detection.dir/build.make CMakeFiles/corner_detection.dir/src/corner_detection.c.i
.PHONY : src/corner_detection.c.i

src/corner_detection.s: src/corner_detection.c.s

.PHONY : src/corner_detection.s

# target to generate assembly for a file
src/corner_detection.c.s:
	$(MAKE) -f CMakeFiles/libmask.so.dir/build.make CMakeFiles/libmask.so.dir/src/corner_detection.c.s
	$(MAKE) -f CMakeFiles/corner_detection.dir/build.make CMakeFiles/corner_detection.dir/src/corner_detection.c.s
.PHONY : src/corner_detection.c.s

src/corner_detection_main.o: src/corner_detection_main.c.o

.PHONY : src/corner_detection_main.o

# target to build an object file
src/corner_detection_main.c.o:
	$(MAKE) -f CMakeFiles/corner_detection.dir/build.make CMakeFiles/corner_detection.dir/src/corner_detection_main.c.o
.PHONY : src/corner_detection_main.c.o

src/corner_detection_main.i: src/corner_detection_main.c.i

.PHONY : src/corner_detection_main.i

# target to preprocess a source file
src/corner_detection_main.c.i:
	$(MAKE) -f CMakeFiles/corner_detection.dir/build.make CMakeFiles/corner_detection.dir/src/corner_detection_main.c.i
.PHONY : src/corner_detection_main.c.i

src/corner_detection_main.s: src/corner_detection_main.c.s

.PHONY : src/corner_detection_main.s

# target to generate assembly for a file
src/corner_detection_main.c.s:
	$(MAKE) -f CMakeFiles/corner_detection.dir/build.make CMakeFiles/corner_detection.dir/src/corner_detection_main.c.s
.PHONY : src/corner_detection_main.c.s

src/inpainting/inpainting.o: src/inpainting/inpainting.c.o

.PHONY : src/inpainting/inpainting.o

# target to build an object file
src/inpainting/inpainting.c.o:
	$(MAKE) -f CMakeFiles/inpainting.dir/build.make CMakeFiles/inpainting.dir/src/inpainting/inpainting.c.o
	$(MAKE) -f CMakeFiles/libinpaint.so.dir/build.make CMakeFiles/libinpaint.so.dir/src/inpainting/inpainting.c.o
.PHONY : src/inpainting/inpainting.c.o

src/inpainting/inpainting.i: src/inpainting/inpainting.c.i

.PHONY : src/inpainting/inpainting.i

# target to preprocess a source file
src/inpainting/inpainting.c.i:
	$(MAKE) -f CMakeFiles/inpainting.dir/build.make CMakeFiles/inpainting.dir/src/inpainting/inpainting.c.i
	$(MAKE) -f CMakeFiles/libinpaint.so.dir/build.make CMakeFiles/libinpaint.so.dir/src/inpainting/inpainting.c.i
.PHONY : src/inpainting/inpainting.c.i

src/inpainting/inpainting.s: src/inpainting/inpainting.c.s

.PHONY : src/inpainting/inpainting.s

# target to generate assembly for a file
src/inpainting/inpainting.c.s:
	$(MAKE) -f CMakeFiles/inpainting.dir/build.make CMakeFiles/inpainting.dir/src/inpainting/inpainting.c.s
	$(MAKE) -f CMakeFiles/libinpaint.so.dir/build.make CMakeFiles/libinpaint.so.dir/src/inpainting/inpainting.c.s
.PHONY : src/inpainting/inpainting.c.s

src/mask_algo.o: src/mask_algo.c.o

.PHONY : src/mask_algo.o

# target to build an object file
src/mask_algo.c.o:
	$(MAKE) -f CMakeFiles/libmask.so.dir/build.make CMakeFiles/libmask.so.dir/src/mask_algo.c.o
.PHONY : src/mask_algo.c.o

src/mask_algo.i: src/mask_algo.c.i

.PHONY : src/mask_algo.i

# target to preprocess a source file
src/mask_algo.c.i:
	$(MAKE) -f CMakeFiles/libmask.so.dir/build.make CMakeFiles/libmask.so.dir/src/mask_algo.c.i
.PHONY : src/mask_algo.c.i

src/mask_algo.s: src/mask_algo.c.s

.PHONY : src/mask_algo.s

# target to generate assembly for a file
src/mask_algo.c.s:
	$(MAKE) -f CMakeFiles/libmask.so.dir/build.make CMakeFiles/libmask.so.dir/src/mask_algo.c.s
.PHONY : src/mask_algo.c.s

src/utils.o: src/utils.c.o

.PHONY : src/utils.o

# target to build an object file
src/utils.c.o:
	$(MAKE) -f CMakeFiles/libmask.so.dir/build.make CMakeFiles/libmask.so.dir/src/utils.c.o
	$(MAKE) -f CMakeFiles/amss_corner.dir/build.make CMakeFiles/amss_corner.dir/src/utils.c.o
	$(MAKE) -f CMakeFiles/corner_detection.dir/build.make CMakeFiles/corner_detection.dir/src/utils.c.o
.PHONY : src/utils.c.o

src/utils.i: src/utils.c.i

.PHONY : src/utils.i

# target to preprocess a source file
src/utils.c.i:
	$(MAKE) -f CMakeFiles/libmask.so.dir/build.make CMakeFiles/libmask.so.dir/src/utils.c.i
	$(MAKE) -f CMakeFiles/amss_corner.dir/build.make CMakeFiles/amss_corner.dir/src/utils.c.i
	$(MAKE) -f CMakeFiles/corner_detection.dir/build.make CMakeFiles/corner_detection.dir/src/utils.c.i
.PHONY : src/utils.c.i

src/utils.s: src/utils.c.s

.PHONY : src/utils.s

# target to generate assembly for a file
src/utils.c.s:
	$(MAKE) -f CMakeFiles/libmask.so.dir/build.make CMakeFiles/libmask.so.dir/src/utils.c.s
	$(MAKE) -f CMakeFiles/amss_corner.dir/build.make CMakeFiles/amss_corner.dir/src/utils.c.s
	$(MAKE) -f CMakeFiles/corner_detection.dir/build.make CMakeFiles/corner_detection.dir/src/utils.c.s
.PHONY : src/utils.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... libmask.so"
	@echo "... inpainting"
	@echo "... amss_corner"
	@echo "... rebuild_cache"
	@echo "... corner_detection"
	@echo "... libinpaint.so"
	@echo "... libamss.so"
	@echo "... src/amss/amss.o"
	@echo "... src/amss/amss.i"
	@echo "... src/amss/amss.s"
	@echo "... src/amss/amss_corner_detection.o"
	@echo "... src/amss/amss_corner_detection.i"
	@echo "... src/amss/amss_corner_detection.s"
	@echo "... src/amss/chain.o"
	@echo "... src/amss/chain.i"
	@echo "... src/amss/chain.s"
	@echo "... src/amss/least_squares.o"
	@echo "... src/amss/least_squares.i"
	@echo "... src/amss/least_squares.s"
	@echo "... src/corner_detection.o"
	@echo "... src/corner_detection.i"
	@echo "... src/corner_detection.s"
	@echo "... src/corner_detection_main.o"
	@echo "... src/corner_detection_main.i"
	@echo "... src/corner_detection_main.s"
	@echo "... src/inpainting/inpainting.o"
	@echo "... src/inpainting/inpainting.i"
	@echo "... src/inpainting/inpainting.s"
	@echo "... src/mask_algo.o"
	@echo "... src/mask_algo.i"
	@echo "... src/mask_algo.s"
	@echo "... src/utils.o"
	@echo "... src/utils.i"
	@echo "... src/utils.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

