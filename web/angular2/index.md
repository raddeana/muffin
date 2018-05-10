#### 请解释Angular 2应用程序的生命周期hooks
- ngOnChanges: 当Angular设置其接收当前和上一个对象值的数据绑定属性时响应
- ngOnInit: 在第一个ngOnChange触发器之后，初始化组件/指令。这是最常用的方法，用于从后端服务检索模板的数据
- ngDoCheck: 检测并在Angular上下文发生变化时执行。每次更改检测运行时，会被调用
- ngOnDestroy: 在Angular销毁指令/组件之前清除。取消订阅可观察的对象并脱离事件处理程序，以避免内存泄漏

- ngAfterContentInit: 组件内容已初始化完成
- ngAfterContentChecked: 在Angular检查投影到其视图中的绑定的外部内容之后
- ngAfterViewInit: Angular创建组件的视图后
- ngAfterViewChecked: 在Angular检查组件视图的绑定之后

#### Angular 2中的路由工作原理
路由是能够让用户在视图 / 组件之间导航的机制
Angular应用程序具有路由器服务的单个实例, 并且每当URL改变时, 相应的路由就与路由配置数组进行匹配

#### 什么是事件发射器 / 它是如何在Angular2中工作的
- Angular 2不具有双向digest cycle
- 组件中发生的任何改变总是从当前组件传播到其所有子组件中
- 子组件的更改需要反映到其父组件的层次结构中, 我们可以通过使用事件发射器api来发出事件

#### 如何在Angular2 应用程序中使用 codelyzer
- Codelyzer运行在tslint的顶部，其编码约定通常在tslint.json文件中定义
- 所有企业应用程序都会遵循一组编码惯例和准则，以更好的方式维护代码

#### 什么是延迟加载，如何在Angular2中启用延迟加载
- 大多数企业应用程序包含用各式各样的用于特定业务案例的模块
- 延迟加载通过将代码拆分成多个包并以按需加载的方式, 来加速应用程序初始加载过程
- 每个Angular应用程序必须有一个叫 AppModule 的主模块

#### 启用延迟加载的Plunkr示例
- 不需要在根模块中导入或声明延迟加载模块
- 将路由添加到顶层路由（app.routing.ts）并设置loadChildren。loadChildren会从根文件夹中获取绝对路径
- RouterModule.forRoot（）会获取routes数组并配置路由器
- 在子模块中导入模块特定路由
- 在子模块路由中，将路径指定为空字符串“”，也就是空路径。RouterModule.forChild会再次采用路由数组为子模块组件加载并配置路由器
- 导出const路由：ModuleWithProviders = RouterModule.forChild (routes)

#### 在Angular 2
- 避免为你的组件使用/注入动态HTML内容
- 如果使用外部HTML，也就是来自数据库或应用程序之外的地方，那么就需要清理它
- 不要将外部网址放在应用程序中，除非它是受信任的。避免网址重定向，除非它是可信的
- 考虑使用AOT编译或离线编译
- 通过限制api，选择使用已知或安全环境/浏览器的app来防止XSRF攻击

#### 如何优化Angular 2应用程序
- 考虑AOT编译
- 确保应用程序已经经过了捆绑，uglify和tree shaking
- 确保应用程序不存在不必要的import语句
- 确保应用中已经移除了不使用的第三方库
- 所有dependencies 和dev-dependencies都是明确分离的
- 如果应用程序较大时，我会考虑延迟加载而不是完全捆绑的应用程序

#### 不出现编辑器警告的自定义类型
在大多数的情况下，第三方库都带有它的.d.ts 文件，用于类型定义

#### Shadow DOM
- Shadow DOM是HTML规范的一部分, 它允许开发人员封装自己的HTML标记, CSS样式和JavaScript
- Shadow DOM以及其它一些技术, 使开发人员能够像<audio>标签一样构建自己的一级标签, Web组件和API
- Shadow DOM本质上是静态的，同时也是开发人员无法访问的, 所以它是一个很好的候选对象
- 它缓存的DOM将在浏览器中呈现得更快，并提供更好的性能

#### AOT编译
AOT编译代表的是Ahead Of Time编译，其中Angular编译器在构建时，会将Angular组件和模板编译为本机JavaScript和HTML

优点:
- 应用程序已经编译, 许多Angular编译器相关库就不再需要捆绑, 应用程序包变得更小, 所以该应用程序可以更快地下载
- 应用程序没有捆绑来支持延迟加载 (或任何原因), 对于每个关联的HTML和CSS, 都会有一个单独的服务器请求
- 预编译的应用程序会将所有模板和样式与组件对齐d, 因此到服务器的Http请求数量会更少
- 应用程序不是AOT编译，那么应用程序完全加载时, 编译过程会发生在浏览器中
- 需要等待下载所有必需的组件, 然后等待编译器花费时间来编译应用程序; 使用AOT编译，就能实现优化
- 由于预先编译, 可以检测到许多编译时错误, 能够为应用程序提供更好的稳定性

缺点:
- 仅适用于HTML和CSS，其它文件类型需要前面的构建步骤
- 没有watch模式，必须手动完成（bin / ngc-watch.js）并编译所有文件
- 需要维护AOT版本的bootstrap文件（使用cli等工具时不需要）
- 在编译之前，需要清理步骤

#### Observables 和 promises 的核心区别
- 当异步操作完成或失败时, Promise会处理一个单个事件
- Observable类似于（在许多语言中的）Stream，当每个事件调用回调函数时, 允许传递零个或多个事件
- 通常Observable比Promise更受欢迎, 因为它不但提供了Promise特性, 还提供了其它特性

##### Promises vs Observables
- Observable类似于（在许多语言中的）Stream, 当每个事件调用回调函数时, 允许传递零个或多个事件
- 通常Observable比Promise更受欢迎, 因为它不但提供了Promise特性, 还提供了其它特性
Promises:
- 返回单个值
- 不可取消

Observables:
- 可以使用多个值
- 可取消
- 支持map, filter, reduce和类似的操作符
- ES 2016 提议的功能
- 使用反应式扩展 (RxJS)
- 根据时间的变化, 数组成员可以异步获取

