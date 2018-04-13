#### 进程模块
process是一个全局进程（node主进程）

#### 事件处理
```javascript
process.on('exit', function () {
　setTimeout(function () {
　  console.log('This will not run')
　}, 100)

  console.log('Bye.')
})
```

#### 与当前进程交互
- process.version: 包含当前node实例的版本号
- process.installPrefix: 包含安装路径
- process.platform: 列举node运行的操作系统的环境，只会显示内核相关的信息
- process.uptime(): 包含当前进程运行的时长（秒）
- process.getgid(), process.setgid(): 获取或者设置group id
- process.getuid(), process.setuid(): 获取或者设计user id
- process.pid: 获取进程id
- process.title: 设置进程名称
- process.execPath: 当前node进程的执行路径，如：/usr/local/bin/node
- process.cwd(): 当前工作目录
- process.memoryUsage(): node进程内存的使用情况，rss代表ram的使用情况，vsize代表总内存的使用大小，包括ram和swap
- process.heapTotal,process.heapUsed: 分别代表v8引擎内存分配和正在使用的大小

#### 事件循环和ticker
node中提供了process.nextTick()方法，允许你访问事件循环和延时那你的工作
他有点类似于setTimeout()，他会在下次tick的时候执行，而且每隔一段事件就会执行一次

```javascript
var http = require('http')

var s = http.createServer(function (req, res) {
　　res.writeHead(200, {})
　　res.end('foo')
  
　　console.log('http response')
　　process.nextTick(function(){console.log('tick')})
})

s.listen(8000)
```

#### 子进程
ode提供了child_process模块，允许你为主进程创建子进程，这样你就可以使用更多的服务器资源，使用更多的cpu
- child_process.exec
```javascript
var cp = require('child_process')
cp.exec('ls -l', function(e, stdout, stderr) {
　　if (!e) {
　　　　console.log(stdout)
　　　　console.log(stderr)
　　}
})
```
- child_process.spawn
```javascript
const cp = require('child_process')
const cat = cp.spawn('cat')

cat.stdout.on('data', function(d) {
　console.log(d.toString())
})

cat.on('exit', function() {
　console.log('kthxbai')
})

cat.stdin.write('meow')
cat.stdin.end()
```
