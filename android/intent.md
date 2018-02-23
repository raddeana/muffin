#### intent
intent 是一个要执行的操作的抽象描述。它可以通过 startActivity 来启动一个活动，broadcastIntent 来发送广播到任何对它感兴趣的广播接受器组件，startService(Intent) 或者bindService(Intent， ServiceConnection, int) 来与后台服务通讯。
意图本身（一个 Intent 对象）是一个被动的数据结构，保存着要执行操作的抽象描述

```java
Intent email = new Intent(Intent.ACTION_SEND, Uri.parse("mailto:"))
email.putExtra(Intent.EXTRA_EMAIL, recipients)
email.putExtra(Intent.EXTRA_SUBJECT, subject.getText().toString())
email.putExtra(Intent.EXTRA_TEXT, body.getText().toString())
startActivity(Intent.createChooser(email, "Choose an email client from..."))
```

#### 意图对象
- 动作 这是意图对象中必须的部分，被表现为一个字符串
- 数据 添加数据规格到意图过滤器
- 类别 类别是意图中可选的部分，是一个字符串，包含该类型组件需要处理的意图的附加信息
- 附加数据 这是传递给需要处理意图的组件的以键值对描述的附加信息
- 标记 这些标记是意图的可选部分
- 组件名称对象是一个可选的域，代表活动、服务或者广播接收器类

#### 意图的类型
- 显式意图
- 隐式意图
