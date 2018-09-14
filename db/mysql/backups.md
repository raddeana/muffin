#### MyISAM和InnoDB
- MyISAM是MySQL的ISAM扩展格式和缺省的数据库引擎，不支持事务、也不支持外键，但其优势在于访问速度快
- 对事务完整性没有要求，以select，insert为主的应用基本上可以用这个引擎来创建表
- InnoDB提供了具有提交、回滚和崩溃恢复能力的事务安全，支持自动增长列，支持外键约束

#### MyISAM数据备份
- 文件拷贝
  - 为了保持数据备份的一致性，我们可以对相关表执行LOCK TABLES操作，对表执行FLUSH TABLES
- SQL语句备份
  - SELECT INTO ...OUTFILE或BACKUP TABLE都可以进行SQL级别的表备份，需要注意的是这两种方法如果有重名文件，最好是先移除重名文件
- mysqlhotcopy 备份
```shell
  mysqlhotcopy db_name [/path/to/new_directory ] 
  mysqlhotcopy db_name_1 ... db_name_n /path/to/new_directory 
```
- mysqldump 备份
```shell
mysqldump [options] db_name [tables]  
mysqldump [options] ---database DB1 [DB2 DB3...] 
mysqldump [options] --all—database 
```
- 冷备份
  - MyISAM数据备份恢复
    - mysqldump备份，恢复方法是mysql –u root < 备份文件名
    - mysqlhotcopy或文件冷/热拷贝备份，恢复方法是停止MySQL服务，并用备份文件覆盖现有文件
    - BACKUP TABLE备份，使用restore table来恢复
    - SELECT INTO ...OUTFILE备份，使用load data恢复数据或mysqlimport命令

#### InnoDB数据备份
- mysqldump
- copy file
- select into
- 商业工具

#### InnoDB数据备份恢复
在使用特定的恢复方法之前，InnoDB 数据备份恢复还有两个通用的方法，分别是 InnoDB 的日志自动恢复功能，即重启 mysql 服务和 "万能大法" ——重启计算机
- mysqldump完全备份，先恢复完全备份，然后再恢复完全备份后的增量日志备份
- select into备份表，则采用 load data 或 mysqlimport 恢复
- copy file，那么就停止MySQL服务，备份文件覆盖当前文件，并执行上次完全备份后的增量日志备份
