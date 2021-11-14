# dbtrain-mysql

requirements（以ubuntu为例）：

```bash
sudo apt install git make cmake g++
```

antlr4语法生成：

```bash
sh ./src/parser/gen.sh
```

编译：

```bash
mkdir build
cd build
cmake ..
make -j `nproc`
```
