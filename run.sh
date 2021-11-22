./build/bin/db_clear
./build/bin/db_init
mkdir build
cd build
cmake ..
make -j `nproc`
test/test1_test
