# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2019.3.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2019.3.2\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\selim\Desktop\Fall 2019-2020\ceng477\hw3\Ceng477-HW3"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\selim\Desktop\Fall 2019-2020\ceng477\hw3\Ceng477-HW3\cmake-build-debug"

# Include any dependencies generated for this target.
include lib\glew\CMakeFiles\libglew_static.dir\depend.make

# Include the progress variables for this target.
include lib\glew\CMakeFiles\libglew_static.dir\progress.make

# Include the compile flags for this target's objects.
include lib\glew\CMakeFiles\libglew_static.dir\flags.make

lib\glew\CMakeFiles\libglew_static.dir\src\glew.c.obj: lib\glew\CMakeFiles\libglew_static.dir\flags.make
lib\glew\CMakeFiles\libglew_static.dir\src\glew.c.obj: ..\lib\glew\src\glew.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\selim\Desktop\Fall 2019-2020\ceng477\hw3\Ceng477-HW3\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object lib/glew/CMakeFiles/libglew_static.dir/src/glew.c.obj"
	cd C:\Users\selim\Desktop\FALL20~1\ceng477\hw3\CENG47~1\CMAKE-~1\lib\glew
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoCMakeFiles\libglew_static.dir\src\glew.c.obj /FdCMakeFiles\libglew_static.dir\libglew_static.pdb /FS -c "C:\Users\selim\Desktop\Fall 2019-2020\ceng477\hw3\Ceng477-HW3\lib\glew\src\glew.c"
<<
	cd C:\Users\selim\Desktop\FALL20~1\ceng477\hw3\CENG47~1\CMAKE-~1

lib\glew\CMakeFiles\libglew_static.dir\src\glew.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/libglew_static.dir/src/glew.c.i"
	cd C:\Users\selim\Desktop\FALL20~1\ceng477\hw3\CENG47~1\CMAKE-~1\lib\glew
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe > CMakeFiles\libglew_static.dir\src\glew.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\selim\Desktop\Fall 2019-2020\ceng477\hw3\Ceng477-HW3\lib\glew\src\glew.c"
<<
	cd C:\Users\selim\Desktop\FALL20~1\ceng477\hw3\CENG47~1\CMAKE-~1

lib\glew\CMakeFiles\libglew_static.dir\src\glew.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/libglew_static.dir/src/glew.c.s"
	cd C:\Users\selim\Desktop\FALL20~1\ceng477\hw3\CENG47~1\CMAKE-~1\lib\glew
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\libglew_static.dir\src\glew.c.s /c "C:\Users\selim\Desktop\Fall 2019-2020\ceng477\hw3\Ceng477-HW3\lib\glew\src\glew.c"
<<
	cd C:\Users\selim\Desktop\FALL20~1\ceng477\hw3\CENG47~1\CMAKE-~1

lib\glew\CMakeFiles\libglew_static.dir\build\glew.rc.res: lib\glew\CMakeFiles\libglew_static.dir\flags.make
lib\glew\CMakeFiles\libglew_static.dir\build\glew.rc.res: ..\lib\glew\build\glew.rc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\selim\Desktop\Fall 2019-2020\ceng477\hw3\Ceng477-HW3\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building RC object lib/glew/CMakeFiles/libglew_static.dir/build/glew.rc.res"
	cd C:\Users\selim\Desktop\FALL20~1\ceng477\hw3\CENG47~1\CMAKE-~1\lib\glew
	C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\rc.exe $(RC_DEFINES) $(RC_INCLUDES) $(RC_FLAGS) /fo CMakeFiles\libglew_static.dir\build\glew.rc.res "C:\Users\selim\Desktop\Fall 2019-2020\ceng477\hw3\Ceng477-HW3\lib\glew\build\glew.rc"
	cd C:\Users\selim\Desktop\FALL20~1\ceng477\hw3\CENG47~1\CMAKE-~1

# Object files for target libglew_static
libglew_static_OBJECTS = \
"CMakeFiles\libglew_static.dir\src\glew.c.obj" \
"CMakeFiles\libglew_static.dir\build\glew.rc.res"

# External object files for target libglew_static
libglew_static_EXTERNAL_OBJECTS =

lib\glewd.lib: lib\glew\CMakeFiles\libglew_static.dir\src\glew.c.obj
lib\glewd.lib: lib\glew\CMakeFiles\libglew_static.dir\build\glew.rc.res
lib\glewd.lib: lib\glew\CMakeFiles\libglew_static.dir\build.make
lib\glewd.lib: lib\glew\CMakeFiles\libglew_static.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\selim\Desktop\Fall 2019-2020\ceng477\hw3\Ceng477-HW3\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking C static library ..\glewd.lib"
	cd C:\Users\selim\Desktop\FALL20~1\ceng477\hw3\CENG47~1\CMAKE-~1\lib\glew
	$(CMAKE_COMMAND) -P CMakeFiles\libglew_static.dir\cmake_clean_target.cmake
	cd C:\Users\selim\Desktop\FALL20~1\ceng477\hw3\CENG47~1\CMAKE-~1
	cd C:\Users\selim\Desktop\FALL20~1\ceng477\hw3\CENG47~1\CMAKE-~1\lib\glew
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\link.exe /lib /nologo /machine:X86 /out:..\glewd.lib @CMakeFiles\libglew_static.dir\objects1.rsp 
	cd C:\Users\selim\Desktop\FALL20~1\ceng477\hw3\CENG47~1\CMAKE-~1

# Rule to build all files generated by this target.
lib\glew\CMakeFiles\libglew_static.dir\build: lib\glewd.lib

.PHONY : lib\glew\CMakeFiles\libglew_static.dir\build

lib\glew\CMakeFiles\libglew_static.dir\clean:
	cd C:\Users\selim\Desktop\FALL20~1\ceng477\hw3\CENG47~1\CMAKE-~1\lib\glew
	$(CMAKE_COMMAND) -P CMakeFiles\libglew_static.dir\cmake_clean.cmake
	cd C:\Users\selim\Desktop\FALL20~1\ceng477\hw3\CENG47~1\CMAKE-~1
.PHONY : lib\glew\CMakeFiles\libglew_static.dir\clean

lib\glew\CMakeFiles\libglew_static.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" "C:\Users\selim\Desktop\Fall 2019-2020\ceng477\hw3\Ceng477-HW3" "C:\Users\selim\Desktop\Fall 2019-2020\ceng477\hw3\Ceng477-HW3\lib\glew" "C:\Users\selim\Desktop\Fall 2019-2020\ceng477\hw3\Ceng477-HW3\cmake-build-debug" "C:\Users\selim\Desktop\Fall 2019-2020\ceng477\hw3\Ceng477-HW3\cmake-build-debug\lib\glew" "C:\Users\selim\Desktop\Fall 2019-2020\ceng477\hw3\Ceng477-HW3\cmake-build-debug\lib\glew\CMakeFiles\libglew_static.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : lib\glew\CMakeFiles\libglew_static.dir\depend

