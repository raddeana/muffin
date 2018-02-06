#### 在代码访问资源
当 Android 应用程序被编译，生成一个 R 类，其中包含了所有 res/ 目录下资源的 ID; 你可以使用 R 类，通过子类 + 资源名或者直接使用资源 ID 来访问资源

#### 在XML中访问
<?xml version="1.0" encoding="utf-8"?>
<resources>
   <color name="opaque_red">#f00</color>
   <string name="hello">Hello!</string>
</resources>

<?xml version="1.0" encoding="utf-8"?>
<EditText xmlns:android="http://schemas.android.com/apk/res/android"
    android:layout_width="fill_parent"
    android:layout_height="fill_parent"
    android:textColor="@color/opaque_red"
    android:text="@string/hello" />
