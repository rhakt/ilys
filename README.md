# ilys

## Install

require:  
gcc >= 4.9  
cmake >= 2.8.12  
pkg-config   
glew 3.1.2 (http://glew.sourceforge.net/)  
glfw 1.13.0 (http://www.glfw.org/)  
glm 0.9.7.2 (http://glm.g-truc.net/0.9.7/index.html)    
lz4 (https://github.com/Cyan4973/lz4)
 

### ubuntu

    $ sudo apt-get install libxinerama-dev libxcursor-dev libglew-dev
    
    # git clone and make and install glfw3, glm, lz4
    
    $ git clone https://github.com/rhakt/ilys.git
    $ cd ilys
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    
### windows
    
    # somehow install cmake, pkg-config, Visual Studio 2015
    # somehow build and install glew, glfw, glm, lz4
    # set dir of glew.pc, glfw3.pc, lz4.pc to  %PKG_CONFIG_PATH%
    # set dir of glmConfig.cmake in %CMAKE_PREFIX_PATH%
    # ! use static library all
    
    $ git clone https://github.com/rhakt/ilys.git
    $ cd ilys
    $ mkdir build
    $ cd build
    $ cmake .. -G "Visual Studio 14"
    
    # open ilys.sln on Visual Studio and build
    
glew.pc
    
    # Requires: glu //<- comment out

