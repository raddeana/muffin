# 编译语言
export LANG=C

# BootStrap-JDK的安装路径，替换为自己bootstrap-JDK的路径
export ALT_BOOTDIR = /usr/lib/jvm/java-6-openjdk-i386

# 运行hotspot时出现问题替换为oracleJDK，读者可以直接替换为OracleJDK
export ALT_JDK_IMPORT_PATH = /usr/lib/jvm/java-6-openjdk-i386

# 要编译的内容，读者可以根据需要自行选择
export BUILD_LANGTOOLS = true

# export BUILD_JAXWS = false
# export BUILD_JAXP = false
# export BUILD_CORBA = false

export BUILD_HOTSPOT = true
export BUILD_JDK = true
export SKIP_COMPARE_IMAGES = true
BUILD_DEPLOY = false
BUILD_INSTALL = false

# 编译结果存放的路径，建议存放在openjdk源码中build文件夹
export ALT_OUTPUTDIR = /usr/dev/jvm/openjdk/build
export ALLOW_DOWNLOADS = true

# 环境变量需要去掉，不然会出问题
unset JAVA_HOME
unset CLASSPATH
