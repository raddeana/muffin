#### 授予权限
```sql
GRANT privilege, [privilege],.. ON privilege_level 
TO user [IDENTIFIED BY password]
[REQUIRE tsl_option]
[WITH [GRANT_OPTION | resource_option]];
```

#### GRANT
- 在 GRANT 关键字之后指定一个或多个特权
- 指定确定特权应用级别的 privilege_level
- 放置要授予权限的用户
- 可选的WITH GRANT OPTION子句允许此用户授予其他用户或从其他用户删除您拥有的权限

