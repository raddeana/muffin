#### 创建角色
```sql
CREATE ROLE IF NOT EXISTS 'crm_dev', 'crm_read', 'crm_write';
```

#### 授予角色权限
```sql
GRANT ALL ON crmdb.* TO crm_dev;
```

#### 角色分配给用户帐户
```sql
GRANT crm_dev TO crm_read1@localhost;
```

#### 查看角色状态
```sql
SELECT current_role();
```

#### 设置默认角色
```sql
SET DEFAULT ROLE ALL TO crm_read1@localhost;
```

#### 活动角色
```sql
SET ROLE NONE;
SET ROLE ALL;
SET ROLE DEFAULT;
```

#### 撤销角色的权限
```sql
REVOKE INSERT, UPDATE, DELETE ON crmdb.* FROM crm_write;
```

#### 删除角色
```sql
DROP ROLE role_name, role_name, ...;
```

#### 将权限从用户帐户复制到另一个用户
```sql
CREATE USER crm_dev2@localhost IDENTIFIED BY 'passwd1990';
```
