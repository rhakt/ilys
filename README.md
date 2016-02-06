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
cpp-netlib 0.11.2 (http://cpp-netlib.org/) (depends boost >= 1.57.0 and OpenSSL) 
 

### ubuntu

    $ sudo apt-get install libxinerama-dev libxcursor-dev
    $ sudo apt-get install libglew-dev openssl
    
    # get and build and install glfw3, glm, lz4, boost, cpp-netlib
    # notice: apt-get libboost-all-dev is old.
    
    $ git clone https://github.com/rhakt/ilys.git
    $ cd ilys
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    
### windows
    
    # somehow install cmake, pkg-config, Visual Studio
    # somehow build and install glew, glfw, glm, lz4, SOIL, openssl, boost, cpp-netlib, PortAudio
    # set dir of glew.pc, glfw3.pc, lz4.pc to  %PKG_CONFIG_PATH%
    # set dir of glmConfig.cmake, cppnetlibConfig.cmake in %CMAKE_PREFIX_PATH%
    # place SOIL.h in %SOIL_DIR%/include/SOIL, SOIL.lib in %SOIL_DIR%/lib
    # place include folder in %PORTAUDIO_DIR%/include, static link lib in %PORTAUDIO_DIR%/lib
    # notice: PortAudio build with deinfe PA_WDMKS_NO_KSGUID_LIB
    # ! use static library all
    
    $ git clone https://github.com/rhakt/ilys.git
    $ cd ilys
    $ mkdir build
    $ cd build
    $ cmake .. -G "Visual Studio 14"
    
    # open ilys.sln on Visual Studio and build
    
glew.pc
    
    # Requires: glu //<- comment out

