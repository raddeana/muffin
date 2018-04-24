#### SQL性能优化十条经验
- 查询的模糊匹配
  - 尽量避免在一个复杂查询里面使用 LIKE '%parm1%'
  - 百分号会导致相关列的索引无法使用
- 索引问题
  - 避免对索引字段进行计算操作
  - 避免在索引字段上使用not，<>，!=
  - 避免在索引列上使用IS NULL和IS NOT NULL
  - 避免在索引列上出现数据类型转换
  - 避免在索引字段上使用函数
  - 避免建立索引的列中使用空值
- 复杂操作
  - 部分UPDATE、SELECT 语句 写得很复杂（经常嵌套多级子查询）——可以考虑适当拆成几步，先生成一些临时数据表，再进行关联操作
- update
  - 同一个表的修改在一个过程里出现好几十次
- 在可以使用 UNION ALL 的语句里，使用了 UNION
  - UNION 因为会将各查询子集的记录做比较，故比起UNION ALL，通常速度都会慢上许多
- 在 WHERE 语句中，尽量避免对索引字段进行计算操作
  - 避免在WHERE子句中使用in，not  in，or 或者having
  ```sql
    SELECT * FROM ORDERS WHERE CUSTOMER_NAME NOT IN 
    (SELECT CUSTOMER_NAME FROM CUSTOMER)
  ```
  ```sql
    SELECT * FROM ORDERS WHERE CUSTOMER_NAME not exist 
    (SELECT CUSTOMER_NAME FROM CUSTOMER)
  ```
  - 不要以字符格式声明数字，要以数字格式声明字符值
    ```sql
      SELECT emp.ename, emp.job FROM emp WHERE emp.empno = 7369;
      SELECT emp.ename, emp.job FROM emp WHERE emp.empno = "7369";
    ```
- 对 Where 语句的法则
- 对 Select 语句的法则
  - 在应用程序、包和过程中限制使用 select * from table 这种方式
```sql
  SELECT empno, ename, category FROM emp WHERE empno = "7369";
  SELECT * FROM emp WHERE empno = "7369";
```
- 排序
  - 避免使用耗费资源的操作，带有 DISTINCT, 
  
  , MINUS, INTERSECT, ORDER BY 的 SQL 语句会启动 SQL 引擎执行，耗费资源的排序(SORT)功能。
  - DISTINCT需要一次排序操作, 而其他的至少需要执行两次排序
- 临时表
  - 慎重使用临时表可以极大的提高系统性能
