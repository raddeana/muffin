### TDDL
- Master/Salve: 读写分离状态, 也就是一个 Master 节点对应多个 Salve 节点
- 垂直分区: 所谓垂直分区指的是可以根据业务自身的不同，将原本冗余在一个数据库内的业务表拆散，将数据分别存储在不同的数据库中
- 水平分区: 将一个业务表拆分成多个子表
主要用于解决 分库分表场景下的访问路由（持久层与数据访问层的配合）以及异构数据库之间的数据同步
它是一个基于集中式配置的 JDBC DataSource 实现，具有分库分表、 Master/Salve 、动态数据源配置等功能

#### 许多大厂也在出一些更加优秀和社区支持更广泛的 DAL 层产品，比如 Hibernate Shards、Ibatis-Sharding 等
#### TDDL 优点
TDDL 必须要依赖 diamond 配置中心（ diamond 是淘宝内部使用的一个管理持久配置的系统，目前淘宝内部绝大多数系统的配置）
- 数据库主备和动态切换
- 带权重的读写分离
- 单线程读重试
- 集中式数据源信息管理和动态变更
- 剥离的稳定 jboss 数据源
- 支持 mysql 和 oracle 数据库
- 基于 jdbc 规范, 很容易扩展支持实现 jdbc 规范的数据源
- 无 server, client-jar 形式存在, 应用直连数据库
- 读写次数, 并发度流程控制, 动态变更
- 可分析的日志打印, 日志流控, 动态变更

#### 淘宝团队对 TDDL
- TDDL 除了拿到分库分表条件外, 还需要拿到 order by、group by、limit、join 等信息, SUM、MAX、MIN 等聚合函数信息, DISTINCT 信息
- TDDL 行复制需要重新拼写 SQL, 带上 sync_version 字段
- 不通过 sql 解析 , 因为 TDDL 遵守 JDBC 规范
- 不可能去扩充 JDBC 规范里面的接口
- 所以只能通过 SQL 中加额外的字符条件 (也就是 HINT 方式) 或者 ThreadLocal 方式进行传递, 前者使 SQL 过长, 后者难以维护
- 开发 debug 时不容易跟踪, 而且需要判定是在一条 SQL 执行后失效还是 1 个连接关闭后才失效
- TDDL 现在也同时支持 Hint 方式和 ThreadLocal 方式传递这些信息

### Diamond
使用任何一种框架都需要配置一些配置源信息, 毕竟每一种框架都有自己的规范, 使用者务必遵守这些规范来实现自己的业务与基础框架的整合
diamond 为应用系统提供了获取配置的服务，应用不仅可以在启动时从 diamond 获取相关的配置，而且可以在运行中对配置数据的变化进行感知并获取变化后的配置数据
tomcat 是 Damond 的运行容器, 在 diamond-server 源代码根目录下, 执行 mvn clean package -Dmaven.test.skip, 
成功后会在 diamond-server/target 目录下生成 diamond-server.war 

### 动态数据源层的 Master/Salve 读写分离 配置与实现
### Matrix 层的分库分表配置与实现
