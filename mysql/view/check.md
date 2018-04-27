#### WITH CHECK OPTION
```sql
CREATE OR REPLACE VIEW view_name 
AS
  select_statement
  WITH CHECK OPTION;
```

#### 示例
```
CREATE OR REPLACE VIEW vps AS
    SELECT 
        employeeNumber,
        lastname,
        firstname,
        jobtitle,
        extension,
        email,
        officeCode,
        reportsTo
    FROM
        employees
    WHERE
        jobTitle LIKE '%VP%' 
WITH CHECK OPTION;
```
