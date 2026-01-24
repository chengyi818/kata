# Kata - 个人编程练习项目

> **Kata**（形）：源自日本武道，指通过反复练习基本动作来精进技艺。本项目是个人的编程练习集合，涵盖多种编程语言、系统编程、算法等领域。

---

## 📁 项目结构

```
kata/
├── Algorithm/        # 算法与数据结构
├── Android/          # Android 开发学习
├── ARM/              # ARM 汇编与交叉编译
├── book/             # 读书笔记
├── compile_tool/     # 编译工具学习 (CMake, Makefile)
├── Compiler/         # 编译原理与 ELF 文件分析
├── Language/         # 编程语言学习
├── Linux_driver/     # Linux 驱动开发
├── Linux_kernel/     # Linux 内核编程
├── Linux_system/     # Linux 系统编程
├── Linux_tool/       # Linux 工具配置
├── MBTI/             # MBTI 人格测试
├── nodejs/           # Node.js 学习
└── tina/             # C 语言算法练习
```

---

## 📚 目录详细说明

### 🧮 Algorithm - 算法与数据结构

| 子目录 | 内容 |
|--------|------|
| `leetcode/` | LeetCode 算法题解 (C 语言实现) |
| `rb_tree/` | 红黑树实现 (Python)，包含可视化绘制 |

### 📱 Android - Android 开发

| 子目录 | 内容 |
|--------|------|
| `binder/` | Android Binder IPC 机制深入研究，包含 Framework 层和 Kernel 层源码分析 |
| `firstLineAnroid/` | 《第一行代码 Android》书籍配套练习 (Chapter 1-14) |
| `protobuftest/` | Android 中使用 Protocol Buffers 的示例 |
| `weiqing/` | 其他 Android 实验项目 |

### 🔧 ARM - ARM 架构学习

ARM 平台下的 C/C++ 程序编译与运行，包含 Android NDK 编译配置：
- 基础语法：`for`, `if_else`, `switch`, `while`
- C++ 特性：`c++_class`, `c++_stl`
- 交叉编译：Android.mk 与 Makefile

### 📖 book - 读书笔记

| 书籍 | 内容 |
|------|------|
| 《人生得遇苏东坡》 | 完整读书笔记，包含人生轨迹、核心感悟、金句摘录等 |

### 🛠️ compile_tool - 编译工具

| 子目录 | 内容 |
|--------|------|
| `cmake/` | CMake 的应用与实践，多个示例项目 |
| `Makefile/` | Makefile 编写，从简单到复杂的递进示例 |

### ⚙️ Compiler - 编译原理

- ELF 文件格式分析
- 目标文件 (.o) 结构解析
- 链接过程研究

### 💻 Language - 编程语言

#### 汇编语言 (assemble/)
| 平台 | 内容 |
|------|------|
| `aarch64/` | ARM64 汇编 |
| `x86/` | x86 汇编 |
| `c_inline_asm/` | C 语言内联汇编 |

#### C 语言 (c/)
- `GNU_GCC/` - GCC 扩展特性
- `grammer/` - C 语言语法练习
- `K&&R_C/` - K&R《C 程序设计语言》习题
- `unit_test/` - 单元测试框架

#### C++ (cpp/)
- `grammer/` - C++ 语法与特性
- `stl/` - STL 容器与算法
- `data_structure/` - 数据结构实现
- `design_pattern/` - 设计模式

#### Go 语言 (golang/)
- 大量 Go 语言练习 (192+ 个 .go 文件)
- 涵盖语法、并发、网络等主题

#### Java (java/)
- `design_pattern/` - 设计模式实现
- `beauty_xml/` - XML 处理

#### Python (python/)
| 子目录 | 内容 |
|--------|------|
| `grammer/` | Python 语法练习 (78+ 文件) |
| `module/` | 标准库与第三方库使用 (121+ 文件) |
| `crypto/` | 密码学实现 |
| `design_pattern/` | 设计模式 |
| `database/` | 数据库操作 |
| `python_source_analysis/` | Python 源码分析 |
| `python_web_server/` | Web 服务器实现 |

#### Rust (rust/)
- `The_Rust_Programming_Language/` - 官方教程练习
- `rust_first_class/` - Rust 入门
- `design_pattern/` - 设计模式
- `grammer/` - 语法练习

### 🐧 Linux_driver - Linux 驱动开发

| 子目录 | 内容 |
|--------|------|
| `cdev/` | 字符设备驱动 |
| `kobject/` | Kobject 子系统 |
| `LKMPG/` | Linux Kernel Module Programming Guide 示例 |
| `scsi/` | SCSI 驱动 |
| `workqueue/` | 工作队列机制 |

### 🔬 Linux_kernel - Linux 内核编程

- `crypto/` - 内核加密 API
- `list_head/` - 内核链表使用
- `process_schedue/` - 进程调度模拟

### 🖥️ Linux_system - Linux 系统编程

- 链表实现
- 进程调度算法

### 🔨 Linux_tool - Linux 工具

- `spacemacs/` - Spacemacs 配置与 PlantUML 图表
- `xmodmap/` - 键盘映射配置

### 🧠 MBTI - 人格类型测试

| 文件 | 内容 |
|------|------|
| `MBTI介绍.md` | MBTI 四维度详解（E/I、S/N、T/F、J/P）及 16 种人格类型 |
| `MBTI测试题.md` | 200 题完整自评测试 |
| `我的MBTI测试结果.md` | 个人测试结果：**ENFJ**（主人公/教育者） |

### 🌐 nodejs - Node.js 学习

系统化的 Node.js 学习路径：

| 章节 | 主题 |
|------|------|
| 01 | 第一个应用 |
| 05 | 回调函数 |
| 06 | 事件驱动 |
| 07 | EventEmitter |
| 09 | Stream 流 |
| 10 | 模块系统 |
| 12 | 路由 |
| 15 | 文件系统 |
| 16 | GET/POST 请求 |
| 18 | Web 开发 |
| 19 | Express 框架 |
| 20 | RESTful API |
| 21 | 多进程 |
| 24 | MongoDB |

### 📝 tina - C 语言练习

- 最大路径游戏算法
- 顺序栈实现
- 其他 C 语言练习

---

## 🛠️ 涉及技术栈

### 编程语言
![C](https://img.shields.io/badge/-C-A8B9CC?style=flat&logo=c&logoColor=white)
![C++](https://img.shields.io/badge/-C++-00599C?style=flat&logo=cplusplus&logoColor=white)
![Python](https://img.shields.io/badge/-Python-3776AB?style=flat&logo=python&logoColor=white)
![Go](https://img.shields.io/badge/-Go-00ADD8?style=flat&logo=go&logoColor=white)
![Rust](https://img.shields.io/badge/-Rust-000000?style=flat&logo=rust&logoColor=white)
![Java](https://img.shields.io/badge/-Java-007396?style=flat&logo=java&logoColor=white)
![JavaScript](https://img.shields.io/badge/-JavaScript-F7DF1E?style=flat&logo=javascript&logoColor=black)

### 系统与平台
![Linux](https://img.shields.io/badge/-Linux-FCC624?style=flat&logo=linux&logoColor=black)
![Android](https://img.shields.io/badge/-Android-3DDC84?style=flat&logo=android&logoColor=white)
![ARM](https://img.shields.io/badge/-ARM-0091BD?style=flat&logo=arm&logoColor=white)

### 工具
![CMake](https://img.shields.io/badge/-CMake-064F8C?style=flat&logo=cmake&logoColor=white)
![Node.js](https://img.shields.io/badge/-Node.js-339933?style=flat&logo=nodedotjs&logoColor=white)
![Express](https://img.shields.io/badge/-Express-000000?style=flat&logo=express&logoColor=white)

---

## 📊 项目统计

| 类别 | 数量 |
|------|------|
| 主要目录 | 14 个 |
| 编程语言 | 8+ 种 |
| Python 文件 | 300+ |
| Go 文件 | 190+ |
| C/C++ 文件 | 200+ |
| Rust 文件 | 70+ |

---

## 📌 使用说明

1. **克隆仓库**
   ```bash
   git clone <repo-url>
   cd kata
   ```

2. **各子目录独立运行**
   - 大部分子目录包含独立的 `Makefile` 或构建脚本
   - 参考各子目录的 `README.md` 获取详细说明

3. **环境要求**
   - GCC/Clang (C/C++)
   - Python 3.x
   - Go 1.x
   - Rust (cargo)
   - Node.js
   - Android SDK/NDK (Android 相关)

---

## 📝 License

个人学习项目，仅供参考。

---

*持续学习，不断精进。*
