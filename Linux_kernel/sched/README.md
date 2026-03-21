# 谈一谈服务器CPU拓扑架构与Linux调度的问题

原文链接：https://mp.weixin.qq.com/s?__biz=Mzk0NzcwMTUwNQ==&mid=2247484944&idx=1&sn=3b5a8a6475770201d7f3832947d67795&chksm=c298214493f0a8aba86e3717da45eb75387095128a45da1e9976cb4ac58de15bc9543a62a89b&mpshare=1&scene=1&srcid=0309NdalR1EN9ZPvvqCr52VU&sharer_shareinfo=ef2049a7d20820a0dcf60cac12474cac&sharer_shareinfo_first=ef2049a7d20820a0dcf60cac12474cac#rd

作者：独树居士（约 5 年前的文章，部分内容可能已过时）

---

## 一、核心观点

文章围绕 **NUMA（非一致内存访问）** 与 **UMA（一致内存访问）** 的演进，讨论服务器 CPU 拓扑与 Linux 调度之间的关系，强调硬件设计在 **成本、性能、软件友好度** 之间的权衡。

## 二、硬件设计的两条主线

1. **在 Socket 内尽量做到一致延迟**
2. **在 Socket 之间尽量减小 NUMA 直径**（NUMA 直径 = 从一个 NUMA 到另一个 NUMA 的最远 hops 数）

## 三、主要厂商的拓扑演进

| 厂商 | 主要变化 |
|------|----------|
| **Intel** | 从 Ring Bus（Nehalem ~ Broadwell）到 Mesh（Skylake 及以后）；支持 SNC（Sub-NUMA Cluster）；多 Socket 时尽量做到 1–2 hops |
| **AMD** | EPYC 一代用「胶水」把 4 个 DIE 粘合；二代 Rome 用星型设计，把内存和 I/O 独立出来，降低 NUMA 直径；支持 NPS0/NPS1/NPS2/NPS4 等配置 |
| **IBM Power9** | 16 Socket 时任意两 Socket 间不超过 2 hops |
| **鲲鹏 920** | 2 Socket 时出现 3 hops，作者在 2021 年提交了内核调度器拓扑修复补丁 |

## 四、NUMA 对软件的影响（「搬砖」比喻）

- **0 hop**：本 NUMA 内访问（自己家）
- **1 hop**：相邻 NUMA（父母家）
- **2 hops**：更远 NUMA（兄弟姐妹家）
- **3 hops 及以上**：更远（堂表亲等）

Linux 调度器更偏向 **负载均衡**，对 NUMA 亲和性感知有限，可能把任务放到「远房亲戚」的 NUMA 上，导致跨 NUMA 访问和性能下降。

## 五、实践建议

- **NUMA 感知强的 workload**：用 `numactl -N 0` 等工具绑定到指定 NUMA
- **需要整体吞吐的 workload**：可用 `numactl --physcpubind` 把任务分散到各 NUMA
- **NUMA 直径越小**：软件控制越简单，性能越稳定，调试越容易
- **鲲鹏 920**：通过 DIE 交织，将一个 package 作为一个 NUMA，可部署更多虚机，但会略微增加内存访问延迟

## 六、结论

简化 NUMA 拓扑、减小 NUMA 直径，可以降低软件做 CPU、内存、I/O 亲和性控制的难度，提升性能一致性和可调试性。

4888eddfc0e04cb7b04c5129c98cfebe.b0fBJtoLnC6fhf4M