# micromouse-maze
Code for manipulating mazes used in the micromouse contest

This is configured for gitflow. Development is through branches from develop.

The Netbeans Project is a part of the repository. It remains to be seen how well that works across platforms. It may need a bit of fancy work with .gitignore.

Data standards

Basic integral types should be as defined in <stdint.h> to ensure widths and ranges across platforms. e.g. uint16_t for an unsigned 16 bit integer

Coding standards:

Function Names shall be capitalised. e.g. MazeGetCost()

Testing:

The project includes the GoogleTest framework for unit tests. These are set up to run easily under Netbeans but should be easy enough to configure for other IDEs. All the testing code is in the folder tests. The googletest framework code is in the folder gtest.
