#### 在同一台服务器上复制一个MySQL数据库
- 使用CREATE DATABASE语句创建一个新的数据库
- 使用mysqldump工具导出要复制的数据库的所有数据库对象和数据
- 将SQL转储文件导入新的数据库

```cmd
mysqldump -u root -p --databases database > /database_bak/db.sql
```

#### 复制数据库的步骤
- 将源服务器上的数据库导出到SQL转储文件。
- 将SQL转储文件复制到目标服务器
- 将SQL转储文件导入到目标服务器

导入数据库
```cmd
mysql -u root -p database < /database_bak/db.sql
```
