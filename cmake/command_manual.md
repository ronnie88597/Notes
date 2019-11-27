# CMake command manual

## Basic Cmake Usage and Syntax

​	Using CMake is simple. The build process is controlled by creating one or more CMakeLists files in each of the directories that make up a project. The CMake language is expressed as a series of commands. Each command is evaluated in the order that it appears in the CMakeLists file. The commands have the form:

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

## add_library:

## set_target_properties:

### 	options:

​		CLEAN_DIRECT_OUTPUT
​		VERSION
​		SOVERSION

## get_target_properties:

## include_directories:

## link_directories:

## target_link_directories:

## add_definitions:

## add_dependencies:

## add_test:

## enable_testing:

## aux_source_directory:

## cmake_mininum_required:

## exec_program:

## [file][https://cmake.org/cmake/help/v3.16/command/file.html?highlight=file]:

​	File manipulation command.
​	Synopsis:
​		Reading

​			`file(READ <filename> <variable> [OFFSET <offset>] [LIMIT <max-in>] [HEX])`, Read content from a file called <filename> and store it in a <variable>. Optionally start from the given <offset> and read at most <max-in> bytes. The HEX option causes data to be converted to a hexadecimal representation (useful for binary data).

​			`file(STRINGS <filename> <variable> [<options>...])`, Parse a list of ASCII strings from <filename> and store it in <variable>. Binary data in the file are ignored. Carriage return (\r, CR) characters are ignored. 

​			`file(<HASH> <filename> <variable>)`, Compute a cryptographic hash of the content of <filename> and store it in a <variable>. The supported <HASH> algorithm names are those listed by the [string(<HASH>)][https://cmake.org/cmake/help/v3.16/command/string.html#supported-hash-algorithms] command.

​			`file(TIMESTAMP <filename> <variable> [<format>] [UTC])`, Compute a string representation of the modification time of <filename> and store it in <variable>. Should the command be unable to obtain a timestamp variable will be set to the empty string("").
​			See the [string(TIMESTAMP)][https://cmake.org/cmake/help/v3.16/command/string.html#command:string] command for documentation of the <format> and UTC options.

​			`file(GET_RUNTIME_DEPENDENCIES
  			[RESOLVED_DEPENDENCIES_VAR <deps_var>]
  			[UNRESOLVED_DEPENDENCIES_VAR <unresolved_deps_var>]
  			[CONFLICTING_DEPENDENCIES_PREFIX <conflicting_deps_prefix>]
  			[EXECUTABLES [<executable_files>...]]
  			[LIBRARIES [<library_files>...]]
  			[MODULES [<module_files>...]]
  			[DIRECTORIES [<directories>...]]
  			[BUNDLE_EXECUTABLE <bundle_executable_file>]
  			[PRE_INCLUDE_REGEXES [<regexes>...]]
  			[PRE_EXCLUDE_REGEXES [<regexes>...]]
  			[POST_INCLUDE_REGEXES [<regexes>...]]
  			[POST_EXCLUDE_REGEXES [<regexes>...]]
  			)`, Recursively get the list of libraries depended on by the given files. 

​		Writing
​			`file({WRITE | APPEND} <filename> <content>...)`, Write <content> into a file called <filename>. If the file dose not exist, it will be created. If the file already exists, WRITE mode will overwrite it and APPEND mode will append to the end. Any directories in the path specified by <filename> that do not exist will be created.
​			If the file is a build input, use the [configure_file()][https://cmake.org/cmake/help/v3.16/command/configure_file.html#command:configure_file] command to update the file only when its content changes.

​			`file({TOUCH | TOUCH_NOCREATE} [<file>...])`, create a file with no content if it does not yet exist. If the file already exists, its access and/or modification will be updated to the time when the function call is executed.
​			Use TOUCH_NOCREATE to touch a file if it exists but not create it. If a file does not exist it will be silently ignored.
​			With TOUCH and TOUCH_NOCREATE the contents of an existing file will not be modified.

​			`file(GENERATE OUTPUT <output-file> [...])`, generate an output file for each build configuration supported by the current [CMake Generator][https://cmake.org/cmake/help/v3.16/manual/cmake-generators.7.html#manual:cmake-generators(7)]. Evaluate [generator expression][https://cmake.org/cmake/help/v3.16/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)] from the input content to produce the output content. 

​		Filesystem
​			`file({GLOB | GLOB_RECURSE} <out-var> [...] [<globbing-expr>...])`
​			`file(RENAME <oldname> <newname>)`
​			`file({REMOVE | REMOVE_RECURSE} [<files>...])`
​			`file(MAKE_DIRECTORY [<dir>...])`
​			`file({COPY | INSTALL} <file>... DESTINATION <dir> [...])`
​			`file(SIZE <filename> <out-var>)`
​			`file(READ_SYMLINK <linkname> <out-var>)`
​			`file(CREATE_LINK <original> <linkname> [...])`

​		Path Conversion
​			`file(RELATIVE_PATH <out-var> <directory> <file>)`
​			`file({TO_CMAKE_PATH | TO_NATIVE_PATH} <path> <out-var>)`

​		Transfer
​			`file(DOWNLOAD <url> <file> [...])`
​			`file(UPLOAD <file> <url> [...])`

​		Locking
​			`file(LOCK <path> [...])`

## include:

​	Load and run CMake code from a file or module.
​	Synopsis;
​		include(<file|module> 
​					[OPTIONAL] 
​					[RESULT_VARIABLE <var>]
​					[NO_POLITY_SCOPE])

​	Variable reads and writes access the scope of the caller (dynamic scoping). If OPTIONAL is present, then no error is raised if the file does not exist. If RESULT_VARIABLE is given the variable <var> will be set to the full filename which has been included or NOTFOUND if it failed.
​	If a module is specified instead of a file, the file with name <modulename>. cmake is searched first in [CMAKE_MODULE_PATH][https://cmake.org/cmake/help/v3.16/variable/CMAKE_MODULE_PATH.html#variable:CMAKE_MODULE_PATH], then in the CMake module directory. There is one exception to this: if the file which calls include() is located itself in the CMake builtin module directory, then first the CMake builtin module directory is searched and [CMAKE_MODULE_PATH][https://cmake.org/cmake/help/v3.16/variable/CMAKE_MODULE_PATH.html#variable:CMAKE_MODULE_PATH] afterwards. See also policy [CMP0017][https://cmake.org/cmake/help/v3.16/policy/CMP0017.html#policy:CMP0017].
​	See the [cmake_policy()][https://cmake.org/cmake/help/v3.16/command/cmake_policy.html#command:cmake_policy] command documentation for discussion of the NO_POLICY_SCOPE option.

## find_file:

​	This command is used to find a full path to named file.
​	Synopsis:
​		A short-hand signature is:
​		`find_file(<var> name1 [path1 path2 ...])`
​		The general signature is:
​		find_file(<var>
​					name | NAMES name1 [name2 ...]
​					[HINTS path1 [path2 ... ENV var]]
​					[PATHS path1 [path2 ... ENV var]]
​					[PATH_SUFFIXES suffix1 [suffix2 ...]]
​					[DOC "cache documentation string"]
​					[NO_DEFAULT_PATH]
​					[NO_PACKAGE_ROOT_PATH]
​					[NO_CMAKE_PATH]
​					[NO_CMAKE_ENVIRONMENT_PATH]
​					[NO_SYSTEM_ENVIRONMENT_PATH]
​					[NO_CMAKE_SYSTEM_PATH]
​					[CMAKE_FIND_ROOT_PATH_BOTH |  ONLY_CMAKE_FIND_ROOT_PATH |
​					NO_CMAKE_FIND_ROOT_PATH]
)
​	A cache entry named by <var> is created to store the result of this command. If the full path to a file is found the result is stored in the variable and the search will not be repeated unless the variable is cleared. If nothing is found, the result will be <var>-NOTFOUND, and the search will be attempted again the next time find_file is invoked with the same variable.


## find_library:

## find_path:

## find_program:

## find_package:

## [if/else/elseif/endif][https://cmake.org/cmake/help/v3.16/command/if.html?highlight=#command:if]:

​	Conditionally execute a group of command.
​	Synopsis:
​		if(<condition>)
​			<commands>
​		elseif(<condition>) # optional block, can be repeated
​			<commands>
​		else()              # optional block
​			<commands>
​		endif()
​	Evaluates the condition argument of the if clause according to the [Condition syntax][https://cmake.org/cmake/help/v3.16/command/if.html?highlight=#condition-syntax] described below. If the result is true, then the commands in the if block are executed. Otherwise, optional elseif blocks are processed in the same way. Finally, if no condition is true, commands in the optional else block are executed. 

## [while/endwhile][https://cmake.org/cmake/help/v3.16/command/while.html?highlight=while]:

​	Evaluate a group of commands while a condition is true.
​	Synopsis:
​		while(<condition>)
​			<commands>
​		endwhile
​	All command between while and the matching endwhile() are recorded without being invoked. Once the endwhile() is evaluated, the recorded list of commands is invoked as long as the <condition> is true.
​	The <condition> has the same syntax and is evaluated using the same logic as described at length for the [if()][https://cmake.org/cmake/help/v3.16/command/if.html#command:if] command.
​	The commands [break()][https://cmake.org/cmake/help/v3.16/command/break.html#command:break] and [continue()][https://cmake.org/cmake/help/v3.16/command/continue.html#command:continue] provide means to escape from the normal control flow.

## [foreach/endforeach][https://cmake.org/cmake/help/v3.16/command/foreach.html?highlight=#command:foreach]:

​	Evaluate a group of commands for each value in a list.
​	Synopsis:
​		foreach(<loop_var> <items>)
​			<commands>
​		endforeach()
​	Where <items> is a list of items that are separated by semicolon or whitespace. All commands between foreach and the matching endforeach are recorded without being invoked. Once the endforeach is evaluated, the recorded list of commands is invoked once for each item in <items>. At the beginning of each iteration the variable loop_var will be set to the value of the current item.
​	The commands [break()][https://cmake.org/cmake/help/v3.16/command/break.html#command:break] and [continue()][https://cmake.org/cmake/help/v3.16/command/continue.html#command:continue] provide means to escape from the normal control flow.