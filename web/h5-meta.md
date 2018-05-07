#### 常用属性
```html
<meta name="viewport" content="width=device-width, initial-scale=1.0,maximum-scale=1.0,minimum=1.0,user-scalable=no">
<meta name="format-detection" content="telephone=no, email=no">
```

- viewport
设置显示方式，一般适配移动设备用来避免缩放和影响体验的滚动条 
width=device-width: 宽度为设备宽度 
initial-scale: 初始的缩放比例 （范围从>0到 10 ） 
minimum-scale: 允许用户缩放到的最小比例 
maximum-scale: 允许用户缩放到的最大比例 
user-scalable: 用户是否可以手动缩放

- format-detection 
忽略页面对手机号和email的识别 
telephone：yes|no 
email：yes|no

#### Safari
```html
<meta name="apple-mobile-web-app-capable" content="yes">
<meta name="apple-mobile-web-app-status-bar-style" content="black">
<meta name="apple-mobile-web-app-title" content="APP name">
```
- apple-mobile-web-app-capable 
- 隐藏浏览器的地址栏和toolbar, 页面显示为全屏, 不加此meta则默认显示地址栏和toolbar 
- content: yes|no
- apple-mobile-web-app-status-bar-style
- content: default | black | black-translucent, 即白色、黑色、灰色半透明
- apple-mobile-web-app-title
- 添加到主屏后的标题

#### UC
```html
<meta name="screen-orientation" content="landscape">
<meta name="full-screen" content="yes">
<meta name="browsermode" content="application">
<meta name="layoutmode" content="fitscreen">
<meta name="nightmode" content="disable">
<meta name="imagemode" content="force">
```
- screen-orientation 屏幕方向 
  - 强制页面横屏或竖屏显示 
  - content：landscape | portrait
- full-screen 全屏 
  - 进入全屏后，页面隐藏菜单栏, 生成一个悬浮标, 点击悬浮标可显示菜单栏
- browsermode 应用模式 
  - 应用模式是为方便 web 应用及游戏开发者设置的综合开关, 通过 meta 标签进行指示打开, 当进入应用模式时, 长按菜单、默认手势、夜间模式失效
- layoutmode 排版模式 
  - UC 浏览器供适屏模式及标准模式，其中适屏模式简化了一些页面的处理，使得页面内容更适合进行页面阅读、节省流量及响应更快。而标准模式则能按照标准规范对页面进行排版及渲染。 
  - content：fitscreen | standard
- nightmode 禁用夜间模式 
  - 禁止页面使用 UC 浏览器自定义的夜间模式
- imagemode 强制图片显示 
  - 为了节省流量及加快速度，通过强制图片显示的功能可以保证图片显示不受用户的设置影响

#### QQ
```html
<meta name="x5-orientation" content="landscape">
<meta name="x5-fullscreen" content="true">
<meta name="x5-page-mode" content="default">
```
- x5-orientation 横竖屏控制 
  - 强制横/竖屏以及跟随浏览器设置 [默认] 
  - content: landscape | portrait | auto
- x5-fullscreen 全屏控制 
  - 强制全屏以及跟随浏览器设置 [默认] 
  - content: true|auto
- x5-page-mode 页面模式 
  - 普通浏览模式 [默认] 以及网页应用模式 [定制工具栏，全屏显示] 
  - content：default|app

