#### 查看视图定义
```sql
SHOW CREATE VIEW [database_name].[view_ name];
```

#### 示例
```sql
USE yiibaidb;
CREATE VIEW organization AS
  SELECT 
    CONCAT(E.lastname, E.firstname) AS Employee,
    CONCAT(M.lastname, M.firstname) AS Manager
  FROM
    employees AS E
      INNER JOIN
    employees AS M ON M.employeeNumber = E.ReportsTo
  ORDER BY Manager;
```

```sql
SHOW CREATE VIEW organization;
```

#### 修改视图
```sql
ALTER
  [ALGORITHM =  {MERGE | TEMPTABLE | UNDEFINED}]
  VIEW [database_name].  [view_name]
    AS 
  [SELECT  statement]
```

#### 示例
```sql
ALTER VIEW organization
  AS 
  SELECT CONCAT(E.lastname,E.firstname) AS Employee,
         E.email AS  employeeEmail,
         CONCAT(M.lastname,M.firstname) AS Manager
  FROM employees AS E
  INNER JOIN employees AS M
    ON M.employeeNumber = E.ReportsTo
  ORDER BY Manager;
```

#### CREATE OR REPLACE VIEW
```sql
CREATE OR REPLACE VIEW v_contacts AS
    SELECT 
        firstName, lastName, extension, email, jobtitle
    FROM
        employees;
-- 查询视图数据
SELECT * FROM v_contacts;
```
