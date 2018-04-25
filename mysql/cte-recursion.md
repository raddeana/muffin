#### MySQL递归CTE
引用CTE名称本身的子查询的CTE
```sql
WITH RECURSIVE cte_name AS (
    initial_query  -- anchor member
    UNION ALL
    recursive_query -- recursive member that references to the CTE name
)

SELECT * FROM cte_name;
```

递归CTE由三个主要部分组成
- 形成CTE结构的基本结果集的初始查询(initial_query)，初始查询部分被称为锚成员
- 递归查询部分是引用CTE名称的查询，因此称为递归成员。递归成员由一个UNION ALL或UNION DISTINCT运算符与锚成员相连
- 终止条件是当递归成员没有返回任何行时，确保递归停止


递归CTE的执行顺序如下
- 将成员分为两个: 锚点和递归成员
- 执行锚成员形成基本结果集(R0)，并使用该基本结果集进行下一次迭代
- 将Ri结果集作为输入执行递归成员，并将Ri+1作为输出
- 重复第三步，直到递归成员返回一个空结果集，换句话说，满足终止条件
- 使用 UNION ALL 运算符将结果集从 R0 到 Rn 组合

递归成员不能包含以下结构:
- 聚合函数，如MAX，MIN，SUM，AVG，COUNT
- GROUP BY 子句
- ORDER BY 子句
- LIMIT 子句
- DISTINCT

MySQL递归CTE示例
```sql
WITH RECURSIVE cte_count (n) AS (
  SELECT 1
  UNION ALL
  SELECT n + 1 
  FROM cte_count 
  WHERE n < 3
)

SELECT n FROM cte_count;
```

递归CTE的执行步骤
- 分离锚和递归成员
- 锚定成员形成初始行 (SELECT 1)，因此第一次迭代在 n = 1 时产生 1 + 1 = 2
- 第二次迭代对第一次迭代的输出 (2) 进行操作，并且在 n = 2 时产生 2 + 1 = 3
- 在第三次操作 (n = 3) 之前，满足终止条件 (n <3)，因此查询停止
- 使用UNION ALL运算符组合所有结果集 1, 2 和 3

使用MySQL递归CTE遍历分层数据
```sql
WITH RECURSIVE employee_paths AS
  ( SELECT employeeNumber,
           reportsTo managerNumber,
           officeCode, 
           1 lvl
   FROM employees
   WHERE reportsTo IS NULL
     UNION ALL
     SELECT e.employeeNumber,
            e.reportsTo,
            e.officeCode,
            lvl+1
     FROM employees e
     INNER JOIN employee_paths ep ON ep.employeeNumber = e.reportsTo )
SELECT employeeNumber,
       managerNumber,
       lvl,
       city
FROM employee_paths ep
INNER JOIN offices o USING (officeCode)
ORDER BY lvl, city;
```

将查询分解成更小的部分
- 使用以下查询形成锚成员
```sql
SELECT 
    employeeNumber, reportsTo managerNumber, officeCode
FROM
    employees
WHERE
    reportsTo IS NULL
```

- 通过引用CTE名称来执行递归成员
```sql
SELECT 
    e.employeeNumber, e.reportsTo, e.officeCode
FROM
    employees e
        INNER JOIN
    employee_paths ep ON ep.employeeNumber = e.reportsTo
```

- 使用employee_paths的查询将CTE返回的结果集与offices表结合起来，以得到最终结果集合
