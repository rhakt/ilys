# ilys

[![Build Status](https://drone.io/github.com/rhakt/ilys/status.png)](https://drone.io/github.com/rhakt/ilys/latest)


## Install

require:  
gcc >= 4.9  
cmake >= 2.8.12  
pkg-config  
glew (http://glew.sourceforge.net/)
glfw3 (http://www.glfw.org/) 
glm (http://glm.g-truc.net/0.9.7/index.html)
SOIL (http://www.lonesock.net/soil.html)
lz4 (https://github.com/Cyan4973/lz4)

### ubuntu

    $ sudo apt-get install libxinerama-dev libxcursor-dev
    $ sudo apt-get install libglew-dev libsoil-dev
    
    $ git clone https://github.com/glfw/glfw.git
    $ cd glfw
    $ cmake .
    $ make
    $ sudo make install
    
    $ git clone https://github.com/rhakt/ilys.git
    $ cd ilys
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    
### windows
    
    # somehow install cmake, pkg-config, Visual Studio
    # somehow build and install glew, glfw, glm, lz4, SOIL
    # set dir of glew.pc, glfw3.pc, lz4.pc to  %PKG_CONFIG_PATH%
    # place SOIL.h in %SOIL_DIR%/include/SOIL, SOIL.lib in %SOIL_DIR%/lib
    
    $ git clone https://github.com/rhakt/ilys.git
    $ cd ilys
    $ mkdir build
    $ cd build
    $ set SOIL_DIR=C:\SOIL
    $ cmake .. -G "Visual Studio 14"
    
    # open ilys.sln on Visual Studio and build
    
    ! glew, glfw : user static link library
    
glew.pc
    
    # Requires: glu //<- comment out

