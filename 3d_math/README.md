# 3D math
## Premise
In the directory, there are two CSV files that contain 3D points and 3D normals. The objective is to load them into any Data Structure or STL container and implement the following questions.

1. Generate an axis aligned bounding box of both datasets.
a. Print out the results (Format: Min: x y z | Max: x y z)
b. (Bonus) Calculate the intersection volume between DataA and DataB. Print out
that value.

2. Write a separate function that for each point in DataA, find the closest points in DataB and return vector(s) of that association and with the distances.
a. Find and print out the shortest distance (and the point pair). ONLY THE shortest
distance, not all evaluated distances!

3. Remove all points from DataB (store as DataB2) which have not been assigned to a pair with DataA during step 2 (consider closest first point only).
a. Print out the number of removed points.
Polyga | Confidential - Intended Recipient Only

4. Modify the algorithm so that you can optionally only find points that are also facing the same direction. Each target point can only be assigned once. Consider a maximum angle difference of 20°

## Building
Below is the expected output of building this project.

```bash
$ mkdir build

$ cd build

$ cmake ..
-- The C compiler identification is GNU 4.8.4
-- The CXX compiler identification is GNU 4.8.4
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Configuring done
-- Generating done
-- Build files have been written to: /dev/projects/progChallenges/3d_math/build

$ make
[ 50%] Building CXX object CMakeFiles/3d_math.dir/src/3d_math.cpp.obj
[100%] Linking CXX executable 3d_math
[100%] Built target 3d_math

$ ./3d_math
```

| Note  | On Windows, CMake generates a MSVC solution by default, so if you want to use a different generator, you need to specify in the cmake command. For example, for the MinGW generator, add `-G "MinGW Makefiles"` to the command and build with `mingw32-make`. |
| :- |:-|