### 事务的隔离性
隔离性是指，多个用户的并发事务访问同一个数据库时，一个用户的事务不应该被其他用户的事务干扰，多个并发事务之间要相互隔离

### 事务的干扰
```mysql
### 事务A，先执行，处于未提交的状态：
insert into t values(4, wangwu);
### 事务B，后执行，也未提交：
select * from t;
```

```mysql
### 事务A，先执行：
select * from t where id=1;

### 事务B，后执行，并且提交：
update t set name=xxoo where id=1;
commit;
```

```mysql
### 事务A，先执行：
select * from t where id > 3;
### 事务B，后执行，并且提交：
insert into t values(4, wangwu);
commit;

### 事务A，首次查询了id>3的结果为NULL，于是想插入一条为4的记录：
insert into t values(4, xxoo);
```

### InnoDB实现了哪几种事务的隔离级别
- 读未提交 (Read Uncommitted)
- 读提交 (Read Committed, RC)
- 可重复读 (Repeated Read, RR)
- 串行化 (Serializable)

### InnoDB使用不同的锁策略 (Locking Strategy) 来实现不同的隔离级别
- 读未提交 (Read Uncommitted)
- 串行化 (Serializable)
- 可重复读 (Repeated Read, RR)

### 读提交 (Read Committed, RC)
最常用的隔离级别
- 普通读是快照读
- 加锁的select, update, delete等语句，除了在外键约束检查 (foreign-key constraint checking) 以及重复键检查 (duplicate-key checking) 时会封锁区间

### 总结
- 并发事务之间相互干扰，可能导致事务出现读脏，不可重复度，幻读等问题
- InnoDB实现了SQL92标准中的四种隔离级别
  - 读未提交：select不加锁，可能出现读脏；
  - 读提交(RC)：普通select快照读，锁select /update /delete 会使用记录锁，可能出现不可重复读；
  - 可重复读(RR)：普通select快照读，锁select /update /delete 根据查询条件情况，会选择记录锁，或者间隙锁/临键锁，以防止读取到幻影记录；
  - 串行化：select隐式转化为select ... in share mode，会被update与delete互斥；
