#### JNI
- JNI是什么：JNI是Java Native Interface的缩写，提供了若干API实现了Java和其他语言的通信 (主要是C&C++)
- 为什么要用JNI：在C/C++中写的程序可以避开JVM的内存开销过大的限制、处理高性能的计算、调用系统服务(例如驱动)等功能
- JVM: jvm是java虚拟机在jni层的代表，全局只有一个
- JNIENV: 代表了java在本线程的运行环境，每个线程都有一个
- JOBJECT: 在JNI中除了基本类型数组、Class、String和Throwable外其余所有Java对象的数据类型在JNI中都用jobject表示

#### JNI工作原理
- java层调用system.load方法
- 通过classloader拿到了so的绝对路径，然后调用nativeload()方法
- 通过linux下的dlopen方法，加载并查找so库里的方法，如有jni_onload会优先加载
- 当前线程下的jnienv会将所有的jni方法注册到了同一个vm中，so和class到了同一个进程空间
- 通过当前线程的jnienv即可调用对应的对象方法了

#### JNI里的缓存类型
Global Reference: 全局引用生存周期为创建后，直到程序员显示的释放它，否则一直存在
Local Reference: 局部引用生存周期为创建后，直到DeleteLocalRef . 或在该方法结束后没有被JVM发现有JAVA层引用而被 JVM 回收并释放
Weak Global Reference: 弱全局引用生命周期为创建之后，直到DeleteGlobalRef。或在内存紧张时进行回收而被释放

#### 缓存方法推荐
- jobject 默认是 local Ref，函数环境消失时会跟随消失
- 在 jni_onload 初始化全局引用和弱全局引用
- jmethodID / jfielID和jobject没有继承关系，他不是个 object，只是个整数，不存在被释放与否的问题，可用全局变量保存
- jclass 是由 jobject 继承而来的类，所以它是个 jobject，需要用弱全局引用来缓存jclass对象
- 局部引用管理 new 出来的对象，注意及时 delete
