# CMake command manual

## [PROJECT][https://cmake.org/cmake/help/v3.16/command/project.html]:

​	Set the name of the project.

### 	Synopsis:

​	PROJECT(<PROJECT-NAME> [<language-name>...])

​	PROJECT(<PROJECT-NAME>

​						[VERSION <major>[.<minor>[.<patch>[.<>tweak]]]]

​						[DESCRIPTION <project-description-string>]

​						[HOMEPAGE_URL <url-string>]

​						[LANGUAGES <language-name>...])

​	Sets the name of the project, and store it in the variable PROJECT-NAME. When called from the top-level CMakeLists.txt also stores the project name in the variable CMAKE_PROJECT_NAME. 

### 	Example:

​	PROJECT(HELLO)



## [SET][https://cmake.org/cmake/help/v3.16/command/set.html?highlight=set]:

SET(SRC_LIST main.c)