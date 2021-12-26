# ./build/bin/dbtrain_mysql_clear
# ./build/bin/dbtrain_mysql_init
cd build
make
cd ..
./build/bin/dbtrain_mysql_shell
