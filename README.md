# micromouse-maze
Code for manipulating mazes used in the micromouse contest

This is configured for gitflow. Development is through branches from develop.

This version of the code was used in the CLion IDE and uses cmake for builds.

The googletest target tests individual libMaze functions

The libMaze_run target runs against a list of maze fies supplied on the command line. For each file, it will simulate a search by the mouse out to the gal and back to the start. After the searches the quality of the solution is evaluated. Mazes which are fully solved are flagged. Mazes that are close to fully solved are flagged and printed out for visual inspection. These are the 'take a chance' mazes that it may be worth the mouse performing a speedrun to get a good score under non-Japan rules. At the end of the listthe total number mazes, the number of solved mazes and the number of 'take a chance' mazes will be displayed.

The CLion project files are part of the repository.

**Data standards:**

Basic integral types should be as defined in <stdint.h> to ensure widths and ranges across platforms. e.g. uint16_t for an unsigned 16 bit integer

**Coding standards:**

Function Names shall be capitalised. e.g. MazeGetCost()

**Testing:**

The project includes the GoogleTest framework for unit tests. These are set up to run easily under Netbeans but should be easy enough to configure for other IDEs. All the testing code is in the folder tests. The googletest framework code is in the folder gtest.
