### tair
tair 是淘宝的一个开源项目，它是一个分布式的key/value结构数据的解决方案
作为一个分布式系统，Tair由一个中心控制节点（config server）和一系列的服务节点（data server）组成
- config server 负责管理所有的data server，并维护data server的状态信息；为了保证高可用（High Available），config server可通过 hearbeat 以一主一备形式提供服务
- data server 对外提供各种数据服务，并以心跳的形式将自身状况汇报给config server；所有的 data server 地位都是等价的

#### tair集群的基本概念
- configID，唯一标识一个tair集群, 每个集群都有一个对应的configID, 在当前的大部分应用情况下configID是存放在diamond中的, 对应了该集群的configserver地址和groupname
- 业务在初始化 tair client 的时候需要配置此ConfigID
- namespace, 又称area, 是tair中分配给应用的一个内存或者持久化存储区域, 可以认为应用的数据存在自己的namespace中
- 同一集群（同一个configID）中namespace是唯一的
- 通过引入namespace，我们可以支持不同的应用在同集群中使用相同的key来存放数据，也就是key相同，但内容不会冲突
- 一个namespace下是如果存放相同的key，那么内容会受到影响，在简单K/V形式下会被覆盖，rdb等带有数据结构的存储引擎内容会根据不同的接口发生不同的变化
- quota配额，对应了每个namespace储存区的大小限制，超过配额后数据将面临最近最少使用（LRU）的淘汰。持久化引擎（ldb）本身没有配额，ldb由于自带了mdb cache，所以也可以设置cache的配额。
- 超过配额后，在内置的mdb内部进行淘汰
- expireTime，数据的过期时间。当超过过期时间之后，数据将对应用不可见，不同的存储引擎有不同的策略清理掉过期的数据

#### 存储引擎
- 非持久化的 tair 可以看成是一个分布式缓存
- 持久化的 tair 将数据存放于磁盘中，为了解决磁盘损坏导致数据丢失，tair 可以配置数据的备份数目
- tair 自动将一份数据的不同备份放到不同的主机上，当有主机发生异常，无法正常提供服务的时候，其余的备份会继续提供服务

#### 三种存储引擎
- mdb，定位于cache缓存，类似于memcache。支持k/v存取和prefix操作
- rdb，定位于cache缓存，采用了redis的内存存储结构。支持k/v，list，hash，set，sortedset等数据结构
- ldb，定位于高性能存储，采用了levelDB作为引擎，并可选择内嵌mdb cache加速，这种情况下cache与持久化存储的数据一致性由tair进行维护
- 支持k/v，prefix等数据结构。今后将支持list，hash，set，sortedset等redis支持的数据结构

#### 分布式策略
tair 的分布采用的是一致性哈希算法，对于所有的key，分到Q个桶中，桶是负载均衡和数据迁移的基本单位

#### Tair
- 负载均衡优先，config server会尽量的把桶均匀的分布到各个data server上，所谓尽量是指在不违背下面的原则的条件下尽量负载均衡: 每个桶必须有COPY_COUNT份数据
- 一个桶的各份数据不能在同一台主机上
- 位置安全优先，一般我们通过控制 _pos_mask（Tair的一个配置项） 来使得不同的机房具有不同的位置信息，一个桶的各份数据不能都位于相同的一个位置（不在同一个机房）
