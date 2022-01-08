mkdir build
cd build
cmake ..
make -j `nproc`
cd ..
./build/bin/dbtrain_mysql_clear
./build/bin/dbtrain_mysql_init
# ./build/test/test1_test
# ./build/test/test2_test
./build/bin/dbtrain_mysql_main