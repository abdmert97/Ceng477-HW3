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
include lib\glfw\examples\CMakeFiles\offscreen.dir\depend.make

# Include the progress variables for this target.
include lib\glfw\examples\CMakeFiles\offscreen.dir\progress.make

# Include the compile flags for this target's objects.
include lib\glfw\examples\CMakeFiles\offscreen.dir\flags.make

lib\glfw\examples\CMakeFiles\offscreen.dir\offscreen.c.obj: lib\glfw\examples\CMakeFiles\offscreen.dir\flags.make
lib\glfw\examples\CMakeFiles\offscreen.dir\offscreen.c.obj: ..\lib\glfw\examples\offscreen.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\selim\Desktop\Fall 2019-2020\ceng477\hw3\Ceng477-HW3\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object lib/glfw/examples/CMakeFiles/offscreen.dir/offscreen.c.obj"
	cd C:\Users\selim\Desktop\FALL20~1\ceng477\hw3\CENG47~1\CMAKE-~1\lib\glfw\examples
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoCMakeFiles\offscreen.dir\offscreen.c.obj /FdCMakeFiles\offscreen.dir\ /FS -c "C:\Users\selim\Desktop\Fall 2019-2020\ceng477\hw3\Ceng477-HW3\lib\glfw\examples\offscreen.c"
<<
	cd C:\Users\selim\Desktop\FALL20~1\ceng477\hw3\CENG47~1\CMAKE-~1

lib\glfw\examples\CMakeFiles\offscreen.dir\offscreen.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/offscreen.dir/offscreen.c.i"
	cd C:\Users\selim\Desktop\FALL20~1\ceng477\hw3\CENG47~1\CMAKE-~1\lib\glfw\examples
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe > CMakeFiles\offscreen.dir\offscreen.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\selim\Desktop\Fall 2019-2020\ceng477\hw3\Ceng477-HW3\lib\glfw\examples\offscreen.c"
<<
	cd C:\Users\selim\Desktop\FALL20~1\ceng477\hw3\CENG47~1\CMAKE-~1

lib\glfw\examples\CMakeFiles\offscreen.dir\offscreen.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/offscreen.dir/offscreen.c.s"
	cd C:\Users\selim\Desktop\FALL20~1\ceng477\hw3\CENG47~1\CMAKE-~1\lib\glfw\examples
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\offscreen.dir\offscreen.c.s /c "C:\Users\selim\Desktop\Fall 2019-2020\ceng477\hw3\Ceng477-HW3\lib\glfw\examples\offscreen.c"
<<
	cd C:\Users\selim\Desktop\FALL20~1\ceng477\hw3\CENG47~1\CMAKE-~1

lib\glfw\examples\CMakeFiles\offscreen.dir\glfw.rc.res: lib\glfw\examples\CMakeFiles\offscreen.dir\flags.make
lib\glfw\examples\CMakeFiles\offscreen.dir\glfw.rc.res: ..\lib\glfw\examples\glfw.rc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\selim\Desktop\Fall 2019-2020\ceng477\hw3\Ceng477-HW3\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building RC object lib/glfw/examples/CMakeFiles/offscreen.dir/glfw.rc.res"
	cd C:\Users\selim\Desktop\FALL20~1\ceng477\hw3\CENG47~1\CMAKE-~1\lib\glfw\examples
	C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\rc.exe $(RC_DEFINES) $(RC_INCLUDES) $(RC_FLAGS) /fo CMakeFiles\offscreen.dir\glfw.rc.res "C:\Users\selim\Desktop\Fall 2019-2020\ceng477\hw3\Ceng477-HW3\lib\glfw\examples\glfw.rc"
	cd C:\Users\selim\Desktop\FALL20~1\ceng477\hw3\CENG47~1\CMAKE-~1

lib\glfw\examples\CMakeFiles\offscreen.dir\__\deps\glad.c.obj: lib\glfw\examples\CMakeFiles\offscreen.dir\flags.make
lib\glfw\examples\CMakeFiles\offscreen.dir\__\deps\glad.c.obj: ..\lib\glfw\deps\glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\selim\Desktop\Fall 2019-2020\ceng477\hw3\Ceng477-HW3\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building C object lib/glfw/examples/CMakeFiles/offscreen.dir/__/deps/glad.c.obj"
	cd C:\Users\selim\Desktop\FALL20~1\ceng477\hw3\CENG47~1\CMAKE-~1\lib\glfw\examples
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoCMakeFiles\offscreen.dir\__\deps\glad.c.obj /FdCMakeFiles\offscreen.dir\ /FS -c "C:\Users\selim\Desktop\Fall 2019-2020\ceng477\hw3\Ceng477-HW3\lib\glfw\deps\glad.c"
<<
	cd C:\Users\selim\Desktop\FALL20~1\ceng477\hw3\CENG47~1\CMAKE-~1

lib\glfw\examples\CMakeFiles\offscreen.dir\__\deps\glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/offscreen.dir/__/deps/glad.c.i"
	cd C:\Users\selim\Desktop\FALL20~1\ceng477\hw3\CENG47~1\CMAKE-~1\lib\glfw\examples
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe > CMakeFiles\offscreen.dir\__\deps\glad.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\selim\Desktop\Fall 2019-2020\ceng477\hw3\Ceng477-HW3\lib\glfw\deps\glad.c"
<<
	cd C:\Users\selim\Desktop\FALL20~1\ceng477\hw3\CENG47~1\CMAKE-~1

lib\glfw\examples\CMakeFiles\offscreen.dir\__\deps\glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/offscreen.dir/__/deps/glad.c.s"
	cd C:\Users\selim\Desktop\FALL20~1\ceng477\hw3\CENG47~1\CMAKE-~1\lib\glfw\examples
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\offscreen.dir\__\deps\glad.c.s /c "C:\Users\selim\Desktop\Fall 2019-2020\ceng477\hw3\Ceng477-HW3\lib\glfw\deps\glad.c"
<<
	cd C:\Users\selim\Desktop\FALL20~1\ceng477\hw3\CENG47~1\CMAKE-~1

# Object files for target offscreen
offscreen_OBJECTS = \
"CMakeFiles\offscreen.dir\offscreen.c.obj" \
"CMakeFiles\offscreen.dir\glfw.rc.res" \
"CMakeFiles\offscreen.dir\__\deps\glad.c.obj"

# External object files for target offscreen
offscreen_EXTERNAL_OBJECTS =

lib\glfw\examples\offscreen.exe: lib\glfw\examples\CMakeFiles\offscreen.dir\offscreen.c.obj
lib\glfw\examples\offscreen.exe: lib\glfw\examples\CMakeFiles\offscreen.dir\glfw.rc.res
lib\glfw\examples\offscreen.exe: lib\glfw\examples\CMakeFiles\offscreen.dir\__\deps\glad.c.obj
lib\glfw\examples\offscreen.exe: lib\glfw\examples\CMakeFiles\offscreen.dir\build.make
lib\glfw\examples\offscreen.exe: lib\glfw\src\glfw3.lib
lib\glfw\examples\offscreen.exe: lib\glfw\examples\CMakeFiles\offscreen.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\selim\Desktop\Fall 2019-2020\ceng477\hw3\Ceng477-HW3\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable offscreen.exe"
	cd C:\Users\selim\Desktop\FALL20~1\ceng477\hw3\CENG47~1\CMAKE-~1\lib\glfw\examples
	"C:\Program Files\JetBrains\CLion 2019.3.2\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\offscreen.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\mt.exe --manifests  -- C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\offscreen.dir\objects1.rsp @<<
 /out:offscreen.exe /implib:offscreen.lib /pdb:"C:\Users\selim\Desktop\Fall 2019-2020\ceng477\hw3\Ceng477-HW3\cmake-build-debug\lib\glfw\examples\offscreen.pdb" /version:0.0  /machine:X86 /debug /INCREMENTAL /subsystem:console ..\src\glfw3.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<
	cd C:\Users\selim\Desktop\FALL20~1\ceng477\hw3\CENG47~1\CMAKE-~1

# Rule to build all files generated by this target.
lib\glfw\examples\CMakeFiles\offscreen.dir\build: lib\glfw\examples\offscreen.exe

.PHONY : lib\glfw\examples\CMakeFiles\offscreen.dir\build

lib\glfw\examples\CMakeFiles\offscreen.dir\clean:
	cd C:\Users\selim\Desktop\FALL20~1\ceng477\hw3\CENG47~1\CMAKE-~1\lib\glfw\examples
	$(CMAKE_COMMAND) -P CMakeFiles\offscreen.dir\cmake_clean.cmake
	cd C:\Users\selim\Desktop\FALL20~1\ceng477\hw3\CENG47~1\CMAKE-~1
.PHONY : lib\glfw\examples\CMakeFiles\offscreen.dir\clean

lib\glfw\examples\CMakeFiles\offscreen.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" "C:\Users\selim\Desktop\Fall 2019-2020\ceng477\hw3\Ceng477-HW3" "C:\Users\selim\Desktop\Fall 2019-2020\ceng477\hw3\Ceng477-HW3\lib\glfw\examples" "C:\Users\selim\Desktop\Fall 2019-2020\ceng477\hw3\Ceng477-HW3\cmake-build-debug" "C:\Users\selim\Desktop\Fall 2019-2020\ceng477\hw3\Ceng477-HW3\cmake-build-debug\lib\glfw\examples" "C:\Users\selim\Desktop\Fall 2019-2020\ceng477\hw3\Ceng477-HW3\cmake-build-debug\lib\glfw\examples\CMakeFiles\offscreen.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : lib\glfw\examples\CMakeFiles\offscreen.dir\depend

