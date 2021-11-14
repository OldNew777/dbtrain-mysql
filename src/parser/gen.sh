java -jar antlr-4.7-complete.jar MYSQL.g4 -visitor -o ./build -Dlanguage=Cpp
find ./ -name "*.cpp" | awk -F "." '{print $2}' | xargs -i -t mv ./{}.cpp  ./{}.cc
