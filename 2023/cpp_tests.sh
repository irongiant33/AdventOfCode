rm -rf build 2>/dev/null
mkdir build
cmake -S . -B build
cmake --build build
cd build && ctest -V
cd ..