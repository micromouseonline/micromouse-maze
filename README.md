# micromouse-maze
Project for developing and testing code used for manipulating mazes used in the micromouse contest.

The library code is also available on its own at: https://github.com/micromouseonline/libMaze

Find out more about the micromouse contest at: http://www.micromouseonline.com

This project is configured for gitflow. Development is through branches from develop.

This version of the code was used in the CLion IDE and uses cmake for builds. If CLion and CMake are not your thing, there is a Netbeans project as well. Both should build and be able to run the tests.

The googletest target tests individual libMaze functions

The libMaze_run target runs against a list of maze fies supplied on the command line. For each file, it will simulate a search by the mouse out to the gal and back to the start. After the searches the quality of the solution is evaluated. Mazes which are fully solved are flagged. Mazes that are close to fully solved are flagged and printed out for visual inspection. These are the 'take a chance' mazes that it may be worth the mouse performing a speedrun to get a good score under non-Japan rules. At the end of the listthe total number mazes, the number of solved mazes and the number of 'take a chance' mazes will be displayed.

**Git**

This project uses git submodules for library stuff - the liMaze and mazefiles content for example.

If you are not familiar with git, you might find cloning the repo a bit annoying if the submodules do not arrive with the main repo.
The CLion project files are part of the repository.

To clone by hand, including the submodules:

    git clone --recurse-submodules https://github.com/micromouseonline/micromouse-maze.git
    
If you forgot the submodules bit, you can can still get them like this.

    git clone https://github.com/micromouseonline/micromouse-maze.git
    cd micromouse-maze
    git submodule init
    git submodule update
    
    
**CMake**

The build system here is CMake. To build the code, first create a folder for the build artefacts. Then change to that folder and run cmake, followed by make:


    mkdir cmake-build-debug
    cd cmake-build-debug
    cmake ..
    make
    
You will probably want to add the build folder to .gitignore.

Assuming the build works out, the tests can be run from the build folder with

   ./tests/test_suite/runTestSuite
  
The main program can be run with commands like:

    ./libmaze_run ../tests/mazes/japan2007ef_classic.maz    
   

**Data standards:**

Basic integral types should be as defined in <stdint.h> to ensure widths and ranges across platforms. e.g. uint16_t for an unsigned 16 bit integer

**Coding standards:**

In a perfect world, the sources would comply with a well known style guide like this one:

    https://google.github.io/styleguide/cppguide.html
    
but that seems unlikely for now :)

**Testing:**

The project includes the GoogleTest framework for unit tests. These are set up to run easily under Netbeans but should be easy enough to configure for other IDEs. All the testing code is in the folder tests. The googletest framework code is in the folder gtest.
