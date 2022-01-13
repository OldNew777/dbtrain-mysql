# dbtrain-mysql

requirements（以ubuntu为例）：

```bash
sudo apt install git make cmake g++
```

antlr4语法生成（生成在build文件夹中，代码自行增量复制进原来的文件）：

```bash
cd ./src/parser/
sh ./gen.sh
```

编译：

```bash
mkdir build
cd build
cmake ..
make -j `nproc`
```

整合为两个sh文件`run.sh/console.sh`，可用如下命令简化：

```bash
sh run.sh
或
sh console.sh
```

