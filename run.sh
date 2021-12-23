./build/bin/dbtrain_mysql_clear
./build/bin/dbtrain_mysql_init
mkdir build
cd build
cmake ..
make -j `nproc`
test/test1_test
