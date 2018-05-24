#### GC调优
GC调优(Tuning Garbage Collection)和其他性能调优是同样的原理
- 列出性能调优指标(State your performance goals)
- 执行测试(Run tests)
- 检查结果(Measure the results)
- 与目标进行对比(Compare the results with the goals)
- 如果达不到指标, 修改配置参数, 然后继续测试(go back to running tests)

#### 三个维度是通用
- Latency(延迟)
- Throughput(吞吐量)
- Capacity(系统容量)

#### 核心概念
- Latency(延迟)
- Throughput(吞吐量)
- Capacity(系统容量)

| 堆内存大小(Heap) |	GC算法(GC Algorithm)     | 有效时间比(Useful work) | 最长停顿时间(Longest pause) |
| -Xmx12g	        | -XX:+UseConcMarkSweepGC  | 89.8%	                | 560 ms                     |
| -Xmx12g         |	-XX:+UseParallelGC       | 91.5%	                | 1,104 ms                   |
| -Xmx8g          |	-XX:+UseConcMarkSweepGC  | 66.3%	                | 1,610 ms                   |

#### Tuning for Latency(调优延迟指标)
```java
java -Xmx12g -XX:+UseConcMarkSweepGC Producer
```

#### Tuning for Capacity(调优系统容量)

```java
java -Xmx12g -XX:+UseConcMarkSweepGC Producer
```

#### next chapter
https://blog.csdn.net/renfufei/article/details/56678064
