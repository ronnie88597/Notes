# How to install with cmake

## Install:

​	Specify rules to run at install time.

### 	Synopsis:

​		install(TARGETS <target>... [...])

​		install({FILES | PROGRAMS} <file>... [...])

​		install(DIRECTORY <dir>... [...])

​		install(SCRIPT <file> [...])

​		install(CODE <code> [...])

​		install(EXPORT <export-name> [...])

​	This command generates installation rules for a project. Rules specified by calls to this command within a source directory are executed in order during installation. The order across directories is not defined.

### 	The common options are:

#### 	DESTINATION:

​		Specify the directory on disk to which a file will be installed. If a full path(with a leading slash or drive letter) is given it is used directly. If a relative path is given it is interpreted relative to the value of [CMAKE_INSTALL_PREFIX][https://cmake.org/cmake/help/v3.16/variable/CMAKE_INSTALL_PREFIX.html#variable:CMAKE_INSTALL_PREFIX] variable.

### Example:

Source-code directory tree

```
.
├── build
├── CMakeLists.txt
├── COPYRIGHT
├── doc
│   ├── CMakeLists.txt
│   └── hello.txt
├── README
├── runhello.sh
└── src
    ├── CMakeLists.txt
    └── main.c
```

./CMakeLists.txt:

```cmake
cmake_minimum_required(VERSION 3.12)
PROJECT(HELLO)
ADD_SUBDIRECTORY(src src)
ADD_SUBDIRECTORY(doc doc)

#install
INSTALL(FILES COPYRIGHT README DESTINATION .)
INSTALL(PROGRAMS runhello.sh DESTINATION bin)
INSTALL(DIRECTORY doc DESTINATION .)

```

./src/CMakeLists.txt:

```cmake
ADD_EXECUTABLE(hello main.c)
MESSAGE("binary dir-> ${PROJECT_BINARY_DIR}")
MESSAGE("hello binary dir-> ${HELLO_BINARY_DIR}")
MESSAGE("source dir-> ${PROJECT_SOURCE_DIR}")
MESSAGE("hello source dir-> ${HELLO_SOURCE_DIR}")
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
INSTALL(TARGETS hello
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION libstatic
    )
```

./doc/CMakeLists.txt: This file is empty.

Then, Enter 'build' directory, and run command as follow:

```shell
cmake -DCMAKE_INSTALL_PREFIX=${USER_DEFINE_INSTALL_DIR} ../
```

Outputs:

![cmake_inst_outpus.img](./img/cmake_inst_outpus.png)

Finally, run command:

```shell
make install
```

Outputs:

![makeinstall_inst_outpus.img](./img/makeinstall_inst_outpus.png)

View the files in the ${USER_DEFINE_INSTALL_DIR} directory, as follow:

```
.
├── bin
│   ├── hello
│   └── runhello.sh
├── COPYRIGHT
├── doc
│   ├── CMakeLists.txt
│   └── hello.txt
└── README

```

