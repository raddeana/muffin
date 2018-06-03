#### 触发语法
```sql
CREATE TRIGGER trigger_name trigger_time trigger_event
 ON table_name
 FOR EACH ROW
 BEGIN
 ...
 END;
```

- 将触发器名称放在CREATE TRIGGER语句之后
- 触发器名称应遵循命名约定[trigger time]_[table name]_[trigger event]，例如 before_employees_update
- 触发激活时间可以在之前或之后
- 必须指定定义触发器的激活时间
- 如果要在更改之前处理操作，则使用BEFORE关键字，如果在更改后需要处理操作，则使用AFTER关键字
- 触发事件可以是INSERT，UPDATE或DELETE
- 此事件导致触发器被调用
- 触发器只能由一个事件调用
- 要定义由多个事件调用的触发器，必须定义多个触发器，每个事件一个触发器
- 触发器必须与特定表关联 
- 没有表触发器将不存在，所以必须在ON关键字之后指定表名
- 将SQL语句放在BEGIN和END块之间
- 这是定义触发器逻辑的位置

#### 示例
```sql
DELIMITER $$
CREATE TRIGGER before_employee_update
  BEFORE UPDATE ON employees
  FOR EACH ROW
BEGIN
  INSERT INTO employees_audit
  SET action = 'update',
    employeeNumber = OLD.employeeNumber,
      lastname = OLD.lastname,
      changedat = NOW();
END$$
DELIMITER ;
```
