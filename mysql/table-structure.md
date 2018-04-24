可以使用ALTER TABLE语句来更改现有表的结构
ALTER TABLE语句可用来添加列，删除列，更改列的数据类型，添加主键，重命名表等等
```sql
ALTER TABLE table_name action1[, action2 ,…]
```

#### 示例
- 创建表
```sql
DROP TABLE IF EXISTS tasks;

CREATE TABLE tasks (
  task_id INT NOT NULL,
  subject VARCHAR(45) NULL,
  start_date DATE NULL,
  end_date DATE NULL,
  description VARCHAR(200) NULL,
  PRIMARY KEY (task_id),
  UNIQUE INDEX task_id_unique (task_id ASC)
);
```
- 修改表结构
  - 设置列的自动递增属性
    ```sql
      ALTER TABLE tasks
      CHANGE COLUMN task_id task_id INT(11) NOT NULL AUTO_INCREMENT;
    ```
  - 新的列添加到表中
    ```sql
      ALTER TABLE tasks 
      ADD COLUMN complete DECIMAL(2,1) NULL
      AFTER description;
    ```
  - 删除列
    ```sql
      ALTER TABLE tasks
      DROP COLUMN description;
    ```
  - 重命名表
    ```sql
      ALTER TABLE tasks
      RENAME TO work_items;
    ```
  
