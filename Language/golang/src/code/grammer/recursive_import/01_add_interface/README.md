# 使用场景
A 是应用程序的框架级结构体，在 A 包含子模块 B 和 C 的指针；
B 为了方便的使用应用的其他子模块（比如 C ）功能，所以在其结构体包含了 A 的指针；
C 要调用 A 包中的某个方法；

# 依赖关系
1. package a 依赖 package b 和 package c
2. package b 依赖 package c
3. package c 也依赖 package a

# 编译报错
```
import cycle not allowed
package code/grammer/recursive_import/01_add_interface
        imports code/grammer/recursive_import/01_add_interface/a
        imports code/grammer/recursive_import/01_add_interface/b
        imports code/grammer/recursive_import/01_add_interface/c
        imports code/grammer/recursive_import/00_intro/a
        imports code/grammer/recursive_import/00_intro/b
        imports code/grammer/recursive_import/00_intro/a
```
