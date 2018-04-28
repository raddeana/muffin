#### 命令的参数
```sql
mysqldump -u [username] –p[password] [database_name] > [dump_file.sql]
```
- [username]：有效的MySQL用户名
- [password]：用户的有效密码, 请注意，-p和密码之间没有空格
- [database_name]: 要备份的数据库名称
- [dump_file.sql]: 要生成的转储文件

#### 仅备份MySQL数据库结构
```sql
mysqldump -u [username] –p[password] –no-data [database_name] > [dump_file.sql]
```

#### 仅备份MySQL数据库数据
```sql
mysqldump -u [username] –p[password] –no-create-info [database_name] > [dump_file.sql]
```

#### 将多个MySQL数据库备份到一个文件
```sql
mysqldump -u [username] –p[password]  [dbname1,dbname2,…] > [all_dbs_dump_file.sql]
mysqldump -u [username] –p[password] –all-database > [all_dbs_dump_file.sql]
```
