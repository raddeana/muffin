#### Content Provider
```java
public class MyApplication extends  ContentProvider {
}
```

#### 创建内容提供者
- 需要继承类 ContentProviderbase 来创建一个内容提供者类
- 需要定义用于访问内容的你的内容提供者URI地址
- 需要创建数据库来保存内容
- 使用<provider.../>标签在 AndroidManifest.xml 中注册内容提供者

#### 类 ContentProvider 中重写
- onCreate(): 当提供者被启动时调用
- query(): 该方法从客户端接受请求，结果是返回指针(Cursor)对象
- insert(): 该方法向内容提供者插入新的记录
- delete(): 该方法从内容提供者中删除已存在的记录
- update(): 该方法更新内容提供者中已存在的记录
- getType(): 该方法为给定的URI返回元数据类型
