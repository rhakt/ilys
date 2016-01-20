# ilys

[![Build Status](https://drone.io/github.com/rhakt/ilys/status.png)](https://drone.io/github.com/rhakt/ilys/latest)


## Install

require:  
gcc >= 4.8  
cmake >= 2.8.12  
pkg-config  
glew  
glfw3  
glm 

### ubuntu

    $ sudo apt-get install libxinerama-dev libxcursor-dev
    $ sudo apt-get install libglew-dev libglm-dev
    
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
    # somehow build glew, glfw
    # set %PKG_CONFIG_PATH%
    
    $ git clone https://github.com/rhakt/ilys.git
    $ cd ilys
    $ mkdir build
    $ cd build 
    $ cmake .. -G "Visual Studio 14"
    
    # open ilys.sln on Visual Studio and build

