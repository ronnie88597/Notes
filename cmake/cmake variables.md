# cmake variables

### CMAKE_BINARY_DIR

### PROJECT_BINARY_DIR

### <project-name>_BINARY_DIR



### CMAKE_SOURCE_DIR

### PROJECT_SOURCE_DIR

### <project-name>_SOURCE_DIR



### CMAKE_CURRENT_SOURCE_DIR

### CMAKE_CURRENT_BINARY_DIR

​	Using `ADD_SUBDIRECTORY(src bin)` command will change `CMAKE_CURRENT_BINARY_DIR` value.

### CMAKE_CURRENT_LIST_FILE

### CMAKE_CURRENT_LIST_LINE

### CMAKE_MODULE_PATH:

​	If there is a complex project, maybe, you will write some self-define cmake modules. In order to locate these modules and invoke them, when the cmake processes CMakeLists.txt, you need to use SET command to specify the modules path. e.g.:`SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake`.

### EXECUTABLE_OUTPUT_PATH

### LIBRARY_OUTPUT_PATH

### PROJECT_NAME

### CMAKE_INCLUDE_PATH

### CMAKE_LIBRARY_PATH

### CMAKE_MAJOR_VERSION

### CMAKE_MINOR_VERSION

### CMAKE_PATCH_VERSION

### CMAKE_SYSTEM

### CMAKE_SYSTEM_NAME

### CMAKE_SYSTEM_VERSION

### CMAKE_SYSTEM_PROCESSOR

### UNIX

### WIN32

### CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS

### BUILD_SHARED_LIBS

### CMAKE_C_FLAGS

### CMAKE_CXX_FLAGS

### CMAKE_GENERATOR

### CMAKE_BUILD_TYPE

### CMAKE_CONFIGURATION_TYPE