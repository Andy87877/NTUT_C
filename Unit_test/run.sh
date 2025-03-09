 #!/bin/bash
 g++ -pg -fprofile-arcs -ftest-coverage fms.cpp ut.cpp -o ut -lgtest -lpthread
 ./ut
 gcov -c -b fms.cpp
 lcov -c -o ut.info -d . --rc lcov_branch_coverage=1
 genhtml ut.info -o report --branch-coverage