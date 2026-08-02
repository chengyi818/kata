# RPG战斗系统机试题 — Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 输出一份包含学生考题（Part A）和考官指南（Part B）的 exam.md 文档

**Architecture:** 单一 markdown 文件 `exams/rpg-battle-system/exam.md`，Part A 为基础任务 + 3个扩展点的题目描述（发给考生），Part B 为评分细则 + 追问示例 + 观察要点（考官内部使用）

**Tech Stack:** Markdown

**Spec:** `/docs/superpowers/specs/2026-08-02-rpg-battle-system-coding-exam-design.md`
**Guidelines:** `/creating-ai-coding-exams.md`

---

## 文件结构

```
exams/rpg-battle-system/
└── exam.md     ← 唯一交付件
```

约束：
- Part A 不能泄露任何设计模式名称、评分标准、考察意图
- 基础任务需求故意模糊，等考生澄清
- 3个扩展点独立自洽，无相互依赖
- Part B 包含完整评分细则、追问示例、观察要点和参考答案

---

### Task 1: 创建目录并编写考题 Part A

**Files:**
- Create: `exams/rpg-battle-system/exam.md`

- [ ] **Step 1: 创建目录**

```bash
mkdir -p exams/rpg-battle-system
```

- [ ] **Step 2: 编写 exam.md — Part A**

写入 `exams/rpg-battle-system/exam.md`：

````markdown
# AI辅助编程机试题：RPG战斗系统

## 考试说明

- 时间：30分钟（基础15分钟 + 扩展15分钟）
- 语言：Python（默认）/ C++ / Java，三选一
- 允许使用AI编程工具
- 交付物：代码 + 设计文档 + 测试用例 + commit记录

---

## 基础任务：勇者之战

实现一个RPG战斗系统：
- 角色拥有：名字、HP（生命值）、攻击力、防御力
- 角色可以攻击另一个角色
- 伤害公式：攻击力 - 防御力，结果至少为1
- 被攻击角色HP减少对应值，HP降到0或以下视为倒下
- 每次攻击需要以可读格式输出战斗日志

**交付要求**：代码 + 设计文档 + 测试用例（覆盖率≥60%）+ commit记录

---

## 扩展任务（考官指定，每项约15分钟）

### 扩展A：攻击方式

给战斗系统增加多种攻击方式：
- 普通攻击：攻击力 - 防御力（当前逻辑）
- 魔法攻击：魔力值 × 2 - 魔法防御，可穿透50%物理防御
- 暴击攻击：先判定暴击率，暴击时伤害×1.5并附带固定真实伤害

角色可以切换攻击方式，需要方便地添加新的攻击方式而不修改现有代码。

**交付要求**：增量设计文档 + 增量测试 + 增量commit

### 扩展B：装备系统

角色现在可以装备武器和防具：
- 武器：增加攻击力（如短剑+5、法杖+8魔力）
- 防具：增加防御力（如盾牌+3、铠甲+5）
- 装备可带有特殊前缀，修改基础属性（如"火焰附魔的短剑" = 短剑+3额外攻击，"损坏的盾牌" = 盾牌-2防御）
- 装备类型和前缀的组合未来会不断新增

**交付要求**：增量设计文档 + 增量测试 + 增量commit

### 扩展C：战斗效果处理

战斗中增加特殊效果处理机制。攻击时按顺序检查以下环节：
- 闪避：目标有一定概率完全闪避本次攻击（不造成伤害，后续环节跳过）
- 格挡：目标有一定概率格挡，格挡成功时伤害减半
- 护盾吸收：目标若存在护盾值，优先扣除护盾，护盾耗尽后剩余伤害才扣HP
- 伤害反弹：攻击者受到最终伤害的一定比例作为反伤

效果之间的执行顺序需要灵活调整（例如某些战斗场景需要"护盾在格挡之前"），且允许未来新增效果类型。

**交付要求**：增量设计文档 + 增量测试 + 增量commit

---

> 考官会在基础任务完成后，从扩展A/B/C中指定1~3项继续完成。
````

- [ ] **Step 3: 自检 Part A 无泄露**

```bash
python -c "
with open('exams/rpg-battle-system/exam.md') as f:
    content = f.read()
# 不能出现的词
forbidden = ['评分', '模式', '策略', '工厂', '装饰器', '责任链',
             '模板方法', 'Template', 'Strategy', 'Factory', 'Decorator',
             'Chain', '钩子', 'OCP', 'LSP', 'SRP', 'DIP', 'ISP', 'SOLID',
             '参考答案', '追问', '考察', '反AI']
found = [w for w in forbidden if w.lower() in content.lower()]
if found:
    print(f'FAIL: Part A leaks: {found}')
else:
    print('PASS: Part A clean')
"
```
Expected: `PASS: Part A clean`

- [ ] **Step 4: Commit**

```bash
git add exams/rpg-battle-system/exam.md
git commit -m "feat: add student-facing exam document (Part A)"
```

---

### Task 2: 编写考官指南 Part B

**Files:**
- Modify: `exams/rpg-battle-system/exam.md` (append Part B)

- [ ] **Step 1: 追加 Part B 到 exam.md**

在 `exams/rpg-battle-system/exam.md` 末尾追加以下内容：

````markdown

---

# 考官指南（内部，勿发给考生）

## 评分总表

| 部分 | 分值 | 考察重心 |
|------|------|----------|
| 基础任务 | 60分 | 需求澄清、模板方法设计、测试验证、AI交互 |
| 扩展A（策略模式） | 20分 | 策略模式识别、OCP实现、增量交付 |
| 扩展B（工厂+装饰器） | 20分 | 工厂/装饰器区分、组合优于继承、增量交付 |
| 扩展C（责任链） | 20分 | 责任链抽象、链中断、可配置性、增量交付 |
| 加分项 | 0~10分 | SDD/TDD流程、额外设计模式运用 |

> 得分要点：得分是给人的而不是给AI的。考核重心在AI交互、设计决策、验收审核。过程大于结果——不能接受功能正确但设计糟糕的实现。

## 基础任务评分细则（60分）

- 需求澄清与追问（18分）：是否主动澄清模糊点。**故意模糊的点：**
  - 伤害公式是否会变化？（预判扩展，考察设计意识）
  - 有哪些类型的攻击？（追问需求边界）
  - 战斗流程的完整形态？（能否拆出攻击前/攻击中/攻击后）
  - 什么是"倒下"？（后续处理——是不能继续攻击？还是从战斗移除？）
  - 战斗日志格式？（可读性标准？需要支持不同输出方式吗？）
- 模板方法设计（18分）：是否将攻击流程拆为模板方法，留钩子（prepare/calcDamage/applyDamage/aftermath）
- 测试用例（12分）：覆盖率≥60%，覆盖正常/边界/异常（正常伤害、防御高于攻击力、HP刚好归零、负HP等）
- AI交互与验证（12分）：是否review AI代码（而非直接接受），是否用测试验证输出（而非信任AI）

## 扩展A：攻击方式 — 评分细则（20分）

- 策略模式识别与应用（10分）：封装为策略接口而非if-else/switch
- OCP验证（5分）：新增攻击方式不改现有代码
- 增量文档/测试/commit（5分）

**追问**：
- "魔法攻击中的'穿透50%物理防御'是什么含义？这部分需求不明确，你是怎么理解的？"
- "如果要再增加一种'吸血攻击'（造成伤害同时回复自身HP），需要改哪些代码？改几处？"
- "AI给你的方案用了什么方式？你觉得这种方案好不好，为什么？"

**参考答案**：
- 策略接口：`DamageStrategy.calcDamage(attacker, defender) -> int`
- 具体策略：NormalStrategy、MagicStrategy、CriticalStrategy
- 注入方式：构造注入 > setter注入（保证角色始终有策略）

## 扩展B：装备系统 — 评分细则（20分）

- 工厂模式正确应用（5分）：装备创建封装为工厂方法/工厂类
- 装饰器模式正确应用（5分）：前缀通过装饰器实现而非继承（如 FlameDecorator、DamagedDecorator）
- 装饰器嵌套正确性（5分）："火焰附魔的 受损的 短剑" = ShortSword + DamagedDecorator + FlameDecorator
- 增量文档/测试/commit（5分）

**追问**：
- "AI用的是继承（FlameSword extends Sword）还是装饰器？两种方案分别有什么优缺点？"
- "假设装备有10种基础类型 × 10种前缀，两种方案各需要多少个类？"
- "请验证你的装饰器嵌套：'火焰附魔的 受损的 短剑'的最终属性是否等于短剑基础值叠加两层修饰？写单元测试证明。"

**参考答案**：
- 装备基类：`Equipment`，方法 `getAttackBonus()`/`getDefenseBonus()`
- 工厂：`EquipmentFactory.createWeapon("短剑")` → Equipment
- 装饰器：`FlameDecorator(equipment)` 包裹基类，重写 bonus 方法，返回 base + 额外值
- 嵌套：装饰器实现相同接口，可无限嵌套

## 扩展C：战斗效果处理 — 评分细则（20分）

- 责任链识别与应用（8分）：抽象出统一Handler接口，链式调用
- 链中断（3分）：闪避成功后正确中断
- 顺序可调/新增效果（4分）：在不修改现有代码的前提下调整顺序或新增效果
- 增量文档/测试/commit（5分）

**追问**：
- "闪避成功后，后续环节（格挡、护盾、反弹）是否还应该继续执行？你的实现是怎样处理的？"
- "如果考官要求'护盾在格挡之前处理'，你需要改几行代码？改什么？"
- "如果要新增一种'反伤护盾'效果（护盾值被消耗时，对攻击者造成等量伤害），你加一个新的Handler能在不改原有代码的前提下完成吗？"

**参考答案**：
- Handler接口：`EffectHandler.handle(DamageContext) -> bool`（true=继续下一节点）
- 上下文：`DamageContext`携带 attacker、defender、damage（可变）等状态
- 链组装：手动 setNext() 或 Builder 模式
- 中断：闪避成功返回 false，不调用下一节点

## 设计模式总结

| 任务 | 期望设计模式 | 关键抽象 |
|------|-------------|----------|
| 基础 | 模板方法 | `BattleAction.attack()` 调用 prepare / calcDamage / applyDamage / aftermath |
| 扩展A | 策略模式 | `DamageStrategy.calcDamage(attacker, defender) -> int` |
| 扩展B | 工厂 + 装饰器 | `EquipmentFactory.create(type, prefix)` + `EquipmentDecorator(base)` |
| 扩展C | 责任链 | `EffectHandler.handle(DamageContext) -> bool` |

## 观察要点

- 是否先探索代码库结构再开始编码（而非直接写代码）
- 是否主动写测试验证AI输出（而非信任AI给的就是对的）
- 是否按task粒度commit（而非一个大杂烩commit）
- 是否对AI方案提出质疑和修改建议（而非照单全收）
- 对于需求模糊处，是否主动向考官追问澄清

## 考试流程

```
给基础任务 → 考生完成 → 考官从扩展A/B/C中指定1~3项 → 观察AI交互过程 → 追问设计决策 → 按细则评分
```
````

- [ ] **Step 2: 验证 Part A + Part B 边界**

Part B 中不能混入 Part A 的"发给考生"区域。验证分界线：

```bash
python -c "
with open('exams/rpg-battle-system/exam.md') as f:
    content = f.read()
# Part B 标记存在
assert '考官指南' in content, 'Missing Part B marker'
# Part A 不应包含 Part B 的内容
part_a, _, _ = content.partition('考官指南')
forbidden_in_part_a = ['评分', '追问', '参考答案', '考察', '反AI']
found = [w for w in forbidden_in_part_a if w in part_a]
if found:
    print(f'FAIL: Part A leaks examiner content: {found}')
else:
    print('PASS: Part A/B boundary clean')
"
```
Expected: `PASS: Part A/B boundary clean`

- [ ] **Step 3: 验证扩展点独立性**

```bash
python -c "
with open('exams/rpg-battle-system/exam.md') as f:
    content = f.read()
part_a, _, _ = content.partition('考官指南')
ext_a = part_a.partition('扩展A')[2].partition('扩展B')[0]
ext_b = part_a.partition('扩展B')[2].partition('扩展C')[0]
ext_c = part_a.partition('扩展C')[2].partition('---')[0]
# 扩展间不应有交叉引用
for label, text in [('扩展A', ext_a), ('扩展B', ext_b)]:
    other_exts = ['扩展B', '扩展C'] if label == '扩展A' else ['扩展A', '扩展C'] if label == '扩展B' else ['扩展A', '扩展B']
    refs = [e for e in other_exts if e in text]
    if refs:
        print(f'FAIL: {label} references {refs}')
if all('扩展B' not in ext_a, '扩展C' not in ext_a, 
       '扩展A' not in ext_b, '扩展C' not in ext_b,
       '扩展A' not in ext_c, '扩展B' not in ext_c):
    print('PASS: All extensions independent')
"
```
Expected: `PASS: All extensions independent`

- [ ] **Step 4: Commit**

```bash
git add exams/rpg-battle-system/exam.md
git commit -m "feat: add examiner guide (Part B) with scoring and probe questions"
```
