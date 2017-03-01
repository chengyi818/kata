[数据结构]
    manager:
        各cpu运行历史
        正在准备的进程
        已经结束的进程

    cpu:
        可运行队列,runqueue

    runqueue:
        可运行进程的数量 nr_running
        CPU负载因子
        正在运行的进程 current
        指向活动进程链表
        进程迁移:
            active_balance
            migration_queue


    进程描述符, task_struct
        进程id:
            pid
        进程状态 state:
            stopped
            running
            dead
        时间片:
            等待时间片 timestamp
            需要时间片
            已运行时间片
        优先级:
            静态优先级 static_prio
            动态优先级 prio
            实时优先级 rt_priority
        运行队列:
            前一个进程
            后一个进程
            所属cpu
        调度类型 policy:
            NORMAL
            FIFO
        能执行的CPU位掩码 cpus_allowed


[重要函数]
    维持当前最新的time_slice计时器
        scheduler_tick()
        1. 获取本地运行时间
        2. 检查当前进程是否为swapper进程,如果是:
            2.1 检查本地队列是否还有其他待运行进程,TIF_NEED_RESHED置位
            2.2 没有,跳到第4步
        3. 递减当前进程的时间片计数器
            3.1 更新FIFO进程的时间片
            3.2 更新普通进程的时间片
                3.2.1 更新时间片计数器
                3.2.2 更新动态优先级 effective_prio(current)

        4. rebalance_tick(),保证不同cpu队列包含数量基本相同的可运行进程

    唤醒进程
        try_to_wake_up()
        1. 分配运行队列
            1.1 CPU空闲
            1.2 CPU亲和性
            1.3 运行队列的平衡
        2. activate_task()
            2.1 recalc_task_prio()
            2.2 将进程加入活动进程集合
        3. 比较本进程和运行队列当前curr进程优先级
            3.1 抢占rq->curr,resched_task() 
                3.1.1 单处理器仅置位TIF_NEED_RESHED
                3.1.2 多处理器?
        4. 设置进程状态running

    recalc_task_prio()
        更新进程动态优先级 effective_prio(current)

    schedule()
        选择要被执行的新进程
