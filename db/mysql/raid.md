#### 基础知识
RAID(Redundant Array of Independent Disk) 是一种独立冗余磁盘阵列
把多块硬盘组成一个 group，当成一个逻辑驱动器，从而实现同时从多块硬盘存取数据，那样可以提高了存储的吞吐量，同时也提高了存取速度和扩大存储容量

#### RAID 的几种工作级别
常用的 RAID 级别有 RAID-0、RAID-1、RAID-10/RAID-01、RAID-5，其他的如 RAID-3、RAID-4、RAID-6

- RAID - 0
RAID-0 采用数据分条技术（Striped）把多块磁盘串联成一个更为庞大的磁盘组，可以提高磁盘的性能和吞吐量
- RAID - 1
RAID-1 采用镜像（Mirroring）的方式冗余数据
- RAID - 10
由于 RAID-0 和 RAID-1 都存在明显的优点和缺点，为了结合两者的优点、避免两者的缺点，从而产生了 RAID-10
RAID-10 适合用在速度需求高，又要完全容错，当然成本也很多的应用
- RAID - 5
RAID-5 应该处于 RAID-0 和 RAID-1 之间的一种工作模式，它尽量平衡 RAID-0 和 RAID-1 的优点和缺点，是我们平时使用比较多的一种模式

#### 如何判断 RAID 级别
- 除了 RAID-1 和 RAID-10，其他级别通过 Primary 字段值就可以判断
- 至于 RAID-1 和 RAID-10，还需要结合 Number Of Drives （per span）、Span Depth 两列的值，如果 Span Depth 值为 1 表示为 RAID-1，
不为 1 表示 RAID-10; 还有一种情况：Primary-1, Secondary-3, RAID Level Qualifier-0 也是表示 RAID-10

#### 判断 RAID 写入策略
- WriteBack：表示写入到磁盘缓存上，写入性能好，如果采用此策略，RAID必须支持电池可用，否则一旦断点，数据将丢失
- WriteThrough：表示直接写入到硬盘上，写入性能没有WriteBack好，一般没有电池时采用此策略

#### MySQL 适合的 RAID 存储方案
- 数据文件(frm, ibd)：存储核心的数据，非常重要，安全性要求高，同时需要频繁的写入、更新数据，磁盘性能要求也比较高
- 首先建议物理磁盘是 SSD，对于 RAID 的选择，如果预算足够，建议 RAID-10，其次是 RAID-5

- 二进制日志文件：写入非常频繁，写性能要求高，由于从库依赖该文件，安全性也很重要，综合成本考虑，可以用两块SATA硬盘，做成RAID-1即可
- redo文件，共享表空间文件：安全性要求高，如果预算足够，RAID-10，通常RAID-1也是可以的，一般而言，redo文件和共享表空间和数据文件存储在一起即可
