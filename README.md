# CFLP
### 一、实验题目 

Capacitated Facility Location Problem

容量设备问题的两种解决方案以及对比 (贪心算法+模拟退火SA算法)

***

### 二、问题描述 

Suppose there are n facilities and m customers. We wish to choose:

(1) which of the n facilities to open

(2) the assignment of customers to facilities

(3)The objective is to minimize the sum of the opening cost and the assignment cost.

(4)The total demand assigned to a facility must not exceed its capacity.

***

### 三、问题解析

这是一道容量设备问题，对各个输入案例:

- 有 `m` 个消费者，`n` 个设备。
- 每个设备 `j` 拥有它的固定容量`capacity[j], j = 0, 1, ···, n-1`
- 每个设备 `j` 的开启需要开启费用 `cost[j], j=0,1,···,n-1`。顾名思义，如果你没有分配消费者到这个设备中，这个设备固然不需要花费开启费用。
- 不同的消费者 `i` 到不同的设备 `j` 有一个给定的不同的容量消耗值 `demand[i][j], i=0,1,···,m-1, j=0,1,···,n-1`。当你分配消费者到某个设备中，这个设备就要减少这个固定的容量消耗值。
- 不同的消费者 `i` 到不同的设备 `j` ，还有一个给定的不同的分配耗费`assignment` ， `assignment[j][i], i=0,1,···,m-1, j=0,1,···,n-1`。
- 方案的总消耗费用 = 设备的开启费用 + 消费者的分配费用。
- 题目就是要求解一个分配方案，将消费者都分配到设备中，要求设备不能超容量服务，每个消费者都要被服务。求出最低的总费用。

------

### 四、项目结构

```bash
CFLP/
├── src # 源码
│   ├── main.cpp  # 主程序入口
│   ├── Solution1.h # 贪心算法解法头文件
│   └── Solution1.cpp # 贪心算法实现cpp
│   └── Solution2.h # SA算法解法头文件
│   └── Solution2.cpp # SA算法实现cpp
│
├── Instances # 测试案例
│   ├── p1 # 测试案例1
│   └── p2 # 测试案例2
│   └── ···
│   └── p71 # 测试案例71
│   └── Readme.docx # 测试案例说明
│
└── docs # 文档
    ├── Project.pdf # Project任务说明
    └── Design.md # 设计文档
```

**项目地址：** 

[我的项目仓库](https://github.com/SYSUcarey/CFLP) 

**设计文档：** 

[Design.md](https://github.com/SYSUcarey/CFLP/blob/master/docs/Design.md) 







