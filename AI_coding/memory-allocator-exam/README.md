# AI辅助编程机试题：Linux内存管理 - 内存分配器

## 题目概述

本题要求你实现一个简化版的内存分配器，模拟Linux内核中的Buddy System和Slab分配器。

**时间限制**：30分钟（基础15min + 扩展15min）
**默认语言**：C（允许使用其他语言，但推荐C）
**AI辅助**：允许使用AI编程工具，但题目设计确保AI无法直接生成完美答案

---

## 背景知识

### Linux Buddy System（伙伴系统）
Linux内核使用Buddy System管理物理内存页。其核心思想：
- 将内存划分为大小为2^n个页框的块
- 分配时找到最小的能满足请求的块，必要时递归对半分割
- 释放时尝试与"伙伴"（buddy）合并——两个大小相同且地址相邻的块
- 优点：减少外部碎片，分配/释放速度快（O(log n)）

### Linux Slab分配器
Slab分配器建立在Buddy System之上，用于内核对象的高效分配：
- 预先从Buddy System获取页框，切分为固定大小的对象槽位
- 每个slab缓存一种固定大小的内核对象（如inode、dentry）
- 对象分配/释放为O(1)操作，无碎片
- 采用着色（coloring）技术优化CPU缓存行利用

---

## 任务要求

### Part 1：基础实现（~15分钟）

实现一个简化版的内存分配器，模拟固定大小内存池上的动态内存管理。

**具体要求：**

1. **内存池初始化**
   - 创建1MB的固定大小内存池（使用`malloc`从堆上分配）
   - 实现`allocator_t`结构体和初始化/销毁函数
   - **初始化失败（如内存不足）时必须释放已分配的资源后返回NULL，不得泄漏**

2. **内存分配（my_malloc）**
   - 必须使用**首次适配（First-Fit）**策略：遍历空闲链表，返回第一个足够大的空闲块
   - 如果找到的块大于请求大小，进行分割（split），剩余部分放回空闲链表
   - 返回8字节对齐的指针（注意：对齐不仅取决于请求大小的取整，还取决于块头部`block_header_t`自身占用的空间是否8字节对齐）
   - 内存不足时返回NULL

3. **内存释放（my_free）**
   - 将被释放的块标记为空闲
   - 合并相邻的空闲块（coalesce），减少碎片
   - 对传入的指针进行合法性校验：判断是否位于当前内存池`[pool, pool+pool_size)`范围内，非法指针应安全忽略而非导致崩溃

> **关键陷阱**：合并相邻空闲块时，**链表相邻不等于物理内存相邻**。如果你的空闲链表未按内存地址排序，直接合并链表上的相邻节点将遗漏可以合并的物理相邻块。请在实现coalesce时注意此区别。

4. **碎片统计（加分项）**
   - 实现`print_stats()`，输出：总空闲字节、空闲块数量、最大空闲块、碎片率
   - 实现`print_blocks()`，输出所有块的地址、大小、状态

5. **设计文档**
   - 在`design-doc-template.md`中填写你的设计决策

**注意：基础实现中，First-Fit策略必须硬编码在my_malloc内部。不要提前设计策略接口——这是扩展部分的要求。**

---

### Part 2：扩展实现（~15分钟）

将基础版本重构为可扩展架构，支持多种分配策略。

**具体要求：**

1. **策略模式重构**
   - 定义`alloc_strategy_t`接口，至少包含`allocate()`和`deallocate()`方法
   - 将First-Fit逻辑从核心分配器代码中抽离为独立策略实现
   - 核心分配器（allocator）通过策略接口委托分配/释放操作

2. **实现至少4种策略**
   - **First-Fit**：选择第一个足够大的空闲块
   - **Best-Fit**：选择最小的能满足请求的空闲块（减少碎片）
   - **Worst-Fit**：选择最大的空闲块（保留大块给后续大请求）
   - **简化版Buddy System**：分配大小向上取整为2的幂次，分割时递归对半切分，释放时执行buddy合并

3. **工厂模式**
   - 实现`strategy_factory_create()`，根据策略类型枚举返回对应策略实例
   - 添加新策略时不需要修改已有策略的实现代码

4. **SOLID原则体现**
   - **单一职责（SRP）**：每个策略文件只负责一种分配算法
   - **开闭原则（OCP）**：添加新策略不需要修改核心allocator或已有策略
   - **依赖倒置（DIP）**：allocator依赖策略抽象接口，不依赖具体实现

5. **设计文档更新**
   - 分析基础版本中违反SOLID原则的地方
   - 说明扩展版本如何修复这些违反
   - 绘制扩展版本的架构图（标注各组件之间的关系）

---

## 文件结构

```
linux-memory-allocator-exam/
├── README.md                  # 本题（题目描述）
├── DESIGN_DOC_TEMPLATE.md     # 设计文档模板
├── Makefile
└── reference/
    ├── basic/                 # 基础实现
    │   ├── allocator.h
    │   ├── allocator.c
    │   └── main.c
    ├── extended/              # 扩展实现
    │   ├── allocator.h
    │   ├── allocator.c
    │   ├── strategy_factory.h
    │   ├── strategy_factory.c
    │   ├── strategy_first_fit.c
    │   ├── strategy_best_fit.c
    │   ├── strategy_worst_fit.c
    │   ├── strategy_buddy.c
    │   └── main.c
    └── tests/                 # 测试代码
        ├── test_basic.c
        └── test_extended.c
```

---

## 接口定义参考

基础版本的接口建议如下（你可以调整）：

```c
typedef struct block_header {
    size_t size;          // 可用字节数（不含header）
    int    is_free;       // 1=空闲, 0=已分配
    struct block_header *next;
} block_header_t;

typedef struct {
    void           *pool;       // 内存池起始地址
    size_t          pool_size;  // 内存池总大小
    block_header_t *free_list;  // 空闲链表头指针
} allocator_t;

allocator_t* allocator_create(void);
void         allocator_destroy(allocator_t *alloc);
void*        my_malloc(allocator_t *alloc, size_t size);
void         my_free(allocator_t *alloc, void *ptr);
void         print_stats(allocator_t *alloc);
void         print_blocks(allocator_t *alloc);
```

扩展版本的接口在此基础上增加策略抽象：

```c
typedef struct alloc_strategy {
    const char *name;
    void* (*allocate)(struct alloc_strategy *self,
                      allocator_t *alloc, size_t size);
    void  (*deallocate)(struct alloc_strategy *self,
                        allocator_t *alloc, void *ptr);
} alloc_strategy_t;
```

---

## 评估标准

| 维度 | 权重 | 说明 |
|------|------|------|
| 基础功能正确性 | 30% | malloc/free语义正确、内存不泄漏、指针对齐 |
| 碎片统计 | 10% | 正确统计空闲块数、最大空闲块、碎片率 |
| 策略模式重构 | 20% | 接口设计合理、First-Fit正确抽离为独立策略 |
| 多种策略实现 | 15% | Best-Fit、Worst-Fit逻辑正确，Buddy System取整正确 |
| SOLID分析与设计文档 | 15% | 准确分析基础版本违反的SOLID原则，扩展版本如何修复 |
| 代码质量 | 10% | 命名规范、无内存泄漏、错误处理、边界条件 |

---

## 反AI设计说明（出题人参考）

本题通过以下机制确保即使使用AI工具，候选人仍需展现真实能力：

1. **Phase Trap**：基础部分要求硬编码First-Fit。如果AI生成时提前做了策略抽象，说明候选人没有遵循"先实现后重构"的要求，暴露出对需求理解不足。
2. **重构理解**：从硬编码到策略模式的重构，需要候选人理解"为什么"这样做，而非仅仅"怎么做"——AI可以生成代码，但无法替候选人完成SOLID违反分析的论述。
3. **Buddy System简化**：简化版Buddy System没有标准库实现，AI生成的代码容易出现边界错误（如2的幂次取整、buddy地址计算、递归分割终止条件）——候选人需要理解算法才能调试通过。
4. **设计文档**：要求分析基础版本的SOLID违反和扩展版本的修复——这种批判性思维是AI难以替代的。

---

## 提交要求

1. 完成`basic/`目录下的所有文件
2. 完成`extended/`目录下的所有文件
3. 填写`DESIGN_DOC_TEMPLATE.md`
4. 确保`make test_basic`和`make test_extended`均通过
5. 代码中不要包含任何使用AI生成代码的注释
