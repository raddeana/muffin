#### 删除一个大文件
```cmd
> /path/to/file.log

# 或使用如下格式
: > /path/to/file.log

# 然后删除它
rm /path/to/file.log
```

#### 如何记录终端输出
试试使用script命令行工具来为你的终端输出创建输出记录
```cmd
script my.terminal.sessio

ls
date
sudo service foo stop
```

输入 exit 或者 logout 或者按下 control-D
```cmd
exit
more my.terminal.session
less my.terminal.session
cat my.terminal.session
```

#### 还原被删除的 /tmp 文件夹
意外地删除了/tmp文件夹，要还原它
```cmd
mkdir /tmp
chmod 1777 /tmp
chown root:root /tmp
ls -ld /tmp
```

#### 锁定一个文件夹
```cmd
chmod 0000 /downloads
chmod 0755 /downloads
```

#### 在vim中用密码保护文件
```cmd
vim +X filename
```

#### 清除屏幕上的乱码
```cmd
reset
```

#### 易读格式
```cmd
ls -lh

# 以易读的格式 (比如： 1K 234M 2G)
df -h
df -k

# 以字节、KB、MB 或 GB 输出：
free -b
free -k
free -m
free -g

# 以易读的格式输出 (比如 1K 234M 2G)
du -h

# 以易读的格式显示文件系统权限
stat -c %A /boot

# 比较易读的数字
sort -h -a file

# 在Linux上以易读的形式显示cpu信息

lscpu
lscpu -e
lscpu -e=cpu,node

# 以易读的形式显示每个文件的大小
tree -h
tree -h /boot
```

#### 在Linux系统中显示已知的用户信息
```cmd
## linux 版本 ##
lslogins
## BSD 版本 ##
logins
```

#### 删除意外在当前文件夹下解压的文件
```cmd
cd /var/www/html/
/bin/rm -f "$(tar ztf /path/to/file.tar.gz)"
```

#### top命令的输出感到疑惑
```cmd
sudo htop
```

#### 再次运行相同的命令
```cmd
/myhome/dir/script/name arg1 arg2
# 要再次运行相同的命令
!!

## 以root用户运行最后运行的命令
sudo !!
```

!!会运行最近使用的命令。要运行最近运行的以“foo”开头命令
```cmd
!foo
# 以root用户运行上一次以“service”开头的命令
sudo !service
```

!$用于运行带上最后一个参数的命令
```cmd
# 编辑 nginx.conf
sudo vi /etc/nginx/nginx.conf

# 测试 nginx.conf
/sbin/nginx -t -c /etc/nginx/nginx.conf

# 测试完 "/sbin/nginx -t -c /etc/nginx/nginx.conf"
sudo vi !$
```

#### 终端上提醒你必须得走了
```cmd
leave +hhmm
```

#### 甜蜜的家
```cmd
export CDPATH=/var/www:/nas10
cd html
```
#### 在less浏览时编辑文件
```cmd
less *.c
less foo.html

## 按下v键来编辑文件 ##
## 退出编辑器后，你可以继续用less浏览了 ##
```

#### 列出你系统中的所有文件和目录
要看到你系统中的所有目录
```cmd
find / -type d | less

# 列出$HOME 所有目录
find $HOME -type d -ls | less
```

要看到所有的文件
```cmd
find / -type f | less

# 列出 $HOME 中所有的文件
find $HOME -type f -ls | less
```

#### 用一条命令构造目录树
```cmd
mkdir -p /jail/{dev, bin, sbin, etc, usr, lib, lib64}
ls -l /jail/
```

#### 将文件复制到多个目录中
```cmd
# 不必运行
cp /path/to/file /usr/dir1
cp /path/to/file /var/dir2
cp /path/to/file /nas/dir3

# 运行下面的命令来复制文件到多个目录中
echo /usr/dir1 /var/dir2 /nas/dir3 |  xargs -n 1 cp -v /path/to/file
```

#### 快速找出两个目录的不同
```cmd
ls -l /tmp/r
ls -l /tmp/s

# 使用 diff 比较两个文件夹
diff /tmp/r/ /tmp/s/
```

#### 文本格式化
```cmd
fmt file.txt
fmt -s file.txt
```

#### 可以看见输出并将其写入到一个文件中
```cmd
mycoolapp arg1 arg2 input.file | tee my.log
```
