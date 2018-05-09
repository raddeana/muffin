#### 集成到现有原生应用
- 要了解你要集成的 React Native 组件
- 创建一个Podfile，在其中以subspec的形式填写所有你要集成的React Native的组件
- 创建 js 文件，编写React Native组件的js代码
- 添加一个事件处理函数，用于创建一个RCTRootView
- 这个 RCTRootView 正是用来承载你的 React Native 组件的，而且它必须对应你在 index.js 中使用 AppRegistry 注册的模块名字
- 启动React Native的Packager服务，运行应用

