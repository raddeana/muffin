#### 重要的步骤
- 创建广播接收器
- 注册广播接收器

#### 系统事件
- android.intent.action.BATTERY_CHANGED 持久的广播，包含电池的充电状态，级别和其他信息
- android.intent.action.BATTERY_LOW 标识设备的低电量条件
- android.intent.action.BATTERY_OKAY 标识电池在电量低之后，现在已经好了
- android.intent.action.BOOT_COMPLETED 在系统完成启动后广播一次
- android.intent.action.BUG_REPORT 显示报告bug的活动
- android.intent.action.CALL 执行呼叫数据指定的某人
- android.intent.action.CALL_BUTTON 用户点击"呼叫"按钮打开拨号器或者其他拨号的合适界面
- android.intent.action.DATE_CHANGED 日期发生改变
- android.intent.action.REBOOT 设备重启

#### 创建广播接收器
```java
public class MyReceiver extends BroadcastReceiver {
   @Override
   public void onReceive(Context context, Intent intent) {
      Toast.makeText(context, "Intent Detected.", Toast.LENGTH_LONG).show();
   }
}
```
#### 注册广播接收器
```xml
<application
   android:icon="@drawable/ic_launcher"
   android:label="@string/app_name"
   android:theme="@style/AppTheme" >
   <receiver android:name="MyReceiver">

      <intent-filter>
         <action android:name="android.intent.action.BOOT_COMPLETED">
         </action>
      </intent-filter>

   </receiver>
</application>
```

#### 广播自定义意图
```java
public void broadcastIntent(View view)
{
   Intent intent = new Intent();
   intent.setAction("cn.uprogrammer.CUSTOM_INTENT");
   sendBroadcast(intent);
}
```

```xml
 <receiver android:name="MyReceiver">
    <intent-filter>
       <action android:name="cn.uprogrammer.CUSTOM_INTENT">
       </action>
    </intent-filter>
 </receiver>
```

