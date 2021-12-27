mkdir build
cd build
cmake ..
make -j `nproc`
cd ..
./build/bin/dbtrain_mysql_clear
./build/bin/dbtrain_mysql_init
# test/test1_test
