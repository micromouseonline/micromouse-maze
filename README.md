# micromouse-maze
Code for manipulating mazes used in the micromouse contest

This is configured for gitflow. Development is through branches from develop.

This version of the code was used in the CLion IDE and uses cmake for builds. If CLion and CMake are not your thing, there is a Netbeans project as well. Both should build and be able to run the tests.

The CLion project files are part of the repository.

The Netbeans Project is a part of the repository. It remains to be seen how well that works across platforms. It may need a bit of fancy work with .gitignore.

**Data standards:**

Basic integral types should be as defined in <stdint.h> to ensure widths and ranges across platforms. e.g. uint16_t for an unsigned 16 bit integer

**Coding standards:**

Function Names shall be capitalised. e.g. MazeGetCost()

**Testing:**

The project includes the GoogleTest framework for unit tests. These are set up to run easily under Netbeans but should be easy enough to configure for other IDEs. All the testing code is in the folder tests. The googletest framework code is in the folder gtest.
