#### 修改事件
```
ALTER EVENT event_name
ON SCHEDULE schedule
ON COMPLETION [NOT] PRESERVE
RENAME TO new_event_name
ENABLE | DISABLE
DO
  event_body
```
