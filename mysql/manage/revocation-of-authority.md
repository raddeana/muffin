#### 撤销权限
```sql
REVOKE privilege_type [(column_list)]      
        [, priv_type [(column_list)]]...
ON [object_type] privilege_level
FROM user [, user]...
```

#### REVOKE
- 在 REVOKE 关键字之后指定要从用户撤销的权限列表，需要用逗号分隔权限
- 在 ON 子句中指定要撤销权限的权限级别
- 在 FROM 子句中指定要撤销的权限的用户帐户

#### 撤销用户的所有权限
```sql
REVOKE ALL PRIVILEGES, GRANT OPTION FROM user [, user]
```

#### 撤销代理用户
```sql
REVOKE PROXY ON user FROM user [, user]
```

#### 命令生效
- 客户端在后续会话中连接到 MySQL 时，对全局权限所做的更改才会生效，这些更改不适用于所有当前连接的用户
- 数据库权限的更改将在下一个 USE 语句之后生效
- 表和列权限的更改将在进行更改之后发出的所有查询时生效

