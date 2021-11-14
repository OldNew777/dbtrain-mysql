./build/bin/thdb_clear
./build/bin/thdb_init
mkdir build
cd build
cmake ..
make -j `nproc`
test/test0_test
