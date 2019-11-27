# CMake command manual

## Basic Cmake Usage and Syntax

​	Using Cmake is simple. The build process is controlled by creating one or more CMakeLists files in each of the directories that make up a project.The CMake language is expressed as a series of commands.Each command is evaluated in the order that it appears in the CMakeLists file. The commands have the form:

```cmake
command (args...)
```

​	Where 'command' is the name of command, and 'args' is a white-space separated list of argument. If the argument or its name contains white-space,  it must be double quoted, otherwise an unexpected error will occur.

​	CMake is case insensitive to command names. So where you see 'command' you could see COMMAND or Command instead.



## [project][https://cmake.org/cmake/help/v3.16/command/project.html]:

​	Set the name of the project.

### 	Synopsis:

​	project(<PROJECT-NAME> [<language-name>...])

​	project(<PROJECT-NAME>

​						[VERSION <major>[.<minor>[.<patch>[.<>tweak]]]]

​						[DESCRIPTION <project-description-string>]

​						[HOMEPAGE_URL <url-string>]

​						[LANGUAGES <language-name>...])

​	Sets the name of the project, and store it in the variable PROJECT-NAME. When called from the top-level CMakeLists.txt also stores the project name in the variable CMAKE_PROJECT_NAME. 

### 	Example:

​	project(HELLO)

### Useful Tips:

​	**Maybe, you are confused about <project-name> and <executable-name>. The <project-name> is only name of project, it is a variable. The <executable-name> corresponds to the logical target name and must be globally unique within a project. There is no relationship between the <project-name> and <executable-name>.**



## [set][https://cmake.org/cmake/help/v3.16/command/set.html?highlight=set]:

​	Set a normal, cache, or environment variable to a given value. See the [cmake-language(7) variables][https://cmake.org/cmake/help/v3.16/manual/cmake-language.7.html#cmake-language-variables] documentation for the scopes and interaction of normal variables and cache entries.

​	Signatures of this command that specify a <value>... placeholder expect zero or more arguments. Multiple arguments will be joined as a [semicolon-separated list][https://cmake.org/cmake/help/v3.16/manual/cmake-language.7.html#cmake-language-lists] to form the actual variable value to be set. Zero arguments will cause normal variables to be unset. See the [unset()][https://cmake.org/cmake/help/v3.16/command/unset.html#command:unset] command to unset variables explicitly.

### Set Normal Variable

​	set(<variable> <value>...[PARENT_SCOPE])

​	Sets the given<variable> in the current function or directory scope.

​	If the PARENT_SCOPE option is given the variable will be set in the scope above the current scope. Each new directory or function creates a new scope. This command will set the value of a variable into the parent directory or calling function(whichever is applicable to the case at hand). The previous state of the variable's value stays the same in the current scope(e.g., if it was undefined before, it is still undefined and if it had a value, it is still that value).Example:

​	set(SRC_LIST main.c)

### Set Cache Entry

​	set(<variable> <value>... CACHE <type> <docstring> [FORCE])

​	Sets the given cache <variable> (cache entry). Since cache entries are meant to provide user-settable values this does not overwrite existing cache entries by default. Use the FORCE option to overwrite existing entries.

​	The <type> must be specified as one of:

​	BOOL: Boolean ON/OFF value. [cmake-gui(1)][https://cmake.org/cmake/help/v3.16/manual/cmake-gui.1.html#manual:cmake-gui(1)] offers a checkbox.

​	FILEPATH: Path to a file on disk. [cmake-gui(1)][https://cmake.org/cmake/help/v3.16/manual/cmake-gui.1.html#manual:cmake-gui(1)] offers a file dialog.

​	PATH: Path to a directory on disk. [cmake-gui(1)][https://cmake.org/cmake/help/v3.16/manual/cmake-gui.1.html#manual:cmake-gui(1)] offers a file dialog.

​	STRING: A line of text. [cmake-gui(1)][https://cmake.org/cmake/help/v3.16/manual/cmake-gui.1.html#manual:cmake-gui(1)] offers a text field or a drop-down selection if the STRINGS cache entry property is set.

​	INTERNAL: A line of text. [cmake-gui(1)][https://cmake.org/cmake/help/v3.16/manual/cmake-gui.1.html#manual:cmake-gui(1)] dose not show internal entries. They may be used to store variables persistently across runs. Use of this type impiles FORCE.

​	The <docstring> must be specified as a line of text providing a quick summary of the option for presentation to [cmake-gui(1)][https://cmake.org/cmake/help/v3.16/manual/cmake-gui.1.html#manual:cmake-gui(1)] users.

​	It is possiable for the cache entry to exist prior to the call but have no type set if it was created on the [cmake][https://cmake.org/cmake/help/v3.16/manual/cmake.1.html#manual:cmake(1)] command line by a user through the -D<var>=<value> option without specifying a type. In this case the set command will add the type. Furthermore, if the <type> is PATH or FILEPATH and the <value> provided on the command line is a relative path, then the set command will treat the path as relative to the current working directory and convert it to an absolute path.

### Set Environment variable

​	set(ENV{variable} [<value>])

​	Sets an [Environment variable][https://cmake.org/cmake/help/v3.16/manual/cmake-env-variables.7.html#manual:cmake-env-variables(7)] to the given value. Subsequent calls of $ENV{<variable>} will return the new value.

​	This command affects only the current CMake process, not the process from which CMake was called, nor the system environment at large, nor the environment of subsequent build or test processes.

​	If no argument is given after ENV{<variable>} of if <value> is an empty string, then this command will clear any existing value of the environment variable.

​	Arguments after <value> are ignored. If extra arguments are found, then an author warning issued.

## message:

## add_executable:

## add_subdirectory:

## set(EXECUTABLE_OUTPUT_PATH ${USER_DEFINED_BINARY_DIR}:

## set(LIBRARY_OUTPUT_PATH ${USER_DEFINED_LIBRARY_DIR}):

## install:





