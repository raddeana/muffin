#### Code Splitting with ES2015
- webpack2 的ES2015 loader中提供了 import() 方法在运行时动态按需加载ES2015 Module
- webpack将import()看做一个分割点并将其请求的module打包为一个独立的chunk
- import () 以模块名称作为参数名并且返回一个Promise对象

#### import() 语法
```javascript
import("./module").then(module => {
    return module.default;
}).catch(err => {
    console.log("Chunk loading failed");
});
```

- import () 使用须知
  - import()目前还是处于TC39 proposal阶段
  - 在Babel中使用import()方法, 需要安装 dynamic-import 插件并选择使用 babel-preset-stage-3 处理解析错误
- 动态表达式 Dynamic expressions
  - import () 中的传参可支持部分表达式的写法了, 如果之前有接触过 CommonJS 中 require() 表达式写法
  - 它的操作其实和 CommonJS 类似，给所有可能的文件创建一个环境，当你传递那部分代码的模块还不确定的时候，webpack 会自动生成所有可能的模块，然后根据需求加载
  - import () 会针对每一个读取到的module创建独立的chunk

#### bundle-loader
- bundle-loader 是webpack官方提供的loader
- 作用就是对require.ensure的抽象封装为一个wrapper函数来动态加载模块代码
- 避免require.ensure将分割点所有模块代码打包为一个chunk体积过大的问题

##### 使用语法
```javascript
// 在require bundle时，浏览器会立即加载
var waitForChunk = require("bundle!./file.js");
 
// 使用lazy模式，浏览器并不立即加载，只在调用wrapper函数才加载
var waitForChunk = require("bundle?lazy!./file.js");
 
// 等待加载，在回调中使用
waitForChunk(function(file) {
    var file = require("./file.js");
});
```

##### wrapper 函数
###### 默认普通模式 wrapper
```javascript
var cbs = [],data;
module.exports = function(cb) {
  if(cbs) cbs.push(cb);
  else cb(data);
},
require.ensure([], function(require) {
  data = require('./file.js');
  var callbacks = cbs;
  cbs = null;

  for(var i = 0, l = callbacks.length; i < l; i++) {
    callbacks[i](data);
  }
});
```

###### lazy 模式 wrapper
```javascript
module.exports = function (cb) {
  require.ensure([], function(require) {
    var app = require('./file.js');
    cb(app);
  });
};
```

###### 支持自定义Chunk名称
```javascript
require("bundle-loader?lazy&name=my-chunk!./file.js");
```

#### promise-loader
- promise-loader是bundle-loader的lazy模式的变种，其核心就是使用Promise语法来替代原先的callback回调机制
- 与bundle-loader类似，require模块的时候只是引入了wrapper函数，
- 不同之处在于调用函数时得到的是一个对模块引用的promise对象，需要在then方法中获取模块对象，并可以使用catch方法来捕获模块加载中的错误
- promise-loader支持使用第三方Promise基础库（如：bluebird）或者使用global参数来指定使用运行环境已经存在的 Promise 库

##### 使用语法
```javascript
// 使用Bluebird promise库
const load = require("promise?bluebird!./file.js");
// 使用全局Promise对象
const load = require("promise?global!./file.js");
load().then(function(file) {});
```

##### wrapper函数
```javascript
const Promise = require('bluebird');

module.exports = function (namespace) {
  return new Promise(function (resolve) {
    require.ensure([], function (require) {
      resolve(require('./file.js')[namespace]));
    });
  });
};
```

##### es6-promise-loader
es6-promise-loader 相比 promise-loader区别就在于使用原生的ES6 Promise对象

###### 使用语法
```javascript
const load = require("es6-promise!./file.js");

load(namespace).then(function(file) {
    console.log(file);
});
```

###### wrapper函数
```javascript
module.exports = function (namespace) {
  return new Promise(function (resolve) {
    require.ensure([], function (require) {
      resolve(require('./file.js')[namespace]));
    });
  });
};
```

#### React按需加载实现方案
##### React router动态路由
- react-router的 标签有一个叫做 getComponent 的异步的方法去获取组件
- 是一个function接受两个参数，分别是location和callback
- 当react-router执行回调函数 callback(null, ourComponent)时，路由只渲染指定组件ourComponent

###### getComponent异步方法
```javascript
<Router history={history}>
  <Route 
    path="/"
    getComponent={(nextState, callback) => {
      callback(null, HomePage)
    }}
  />
   <Route
    path="/faq"
    getComponent={(nextState, callback) => {
      callback(null, FAQPage);
    }}
  />
</Router>
```

###### require.ensure
webpack提供的require.ensure可以定义分割点来打包独立的chunk，再配合react-router的getComponent方法就可以实现React组件的按需加载

#### React懒加载组件
提到使用React动态路由来按需加载react组件，但实际项目开发中很多时候不需要或者没法引入react-router
我们就可以使用webpack官方封装的React懒加载组件来动态加载指定的React组件

##### LazilyLoad懒加载组件
###### LazilyLoad使用
```javascript
<LazilyLoad modules={{
  TodoHandler: () => importLazy(import('./components/TodoHandler')),
  TodoMenuHandler: () => importLazy(import('./components/TodoMenuHandler')),
  TodoMenu: () => importLazy(import('./components/TodoMenu')),
}}>
{({TodoHandler, TodoMenuHandler, TodoMenu}) => (
  <TodoHandler>
    <TodoMenuHandler>
      <TodoMenu />
    </TodoMenuHandler>
  </TodoHandler>
)}
</LazilyLoad>
```

###### importLazy方法是为了兼容Babel/ES2015模块，返回模块的default属性
```javascript
export const importLazy = (promise) => (
  promise.then((result) => result.default || result)
);
```

#### React 高阶组件懒加载
高阶组件 (Higher Order Component)就是一个 React 组件包裹着另外一个 React 组件

##### 封装懒加载组件LazilyLoad的高阶组件工厂函数
LazilyLoadFactory
```javascript
export const LazilyLoadFactory = (Component, modules) => {
  return (props) => (
    <LazilyLoad modules={modules}>
      {(mods) => <Component {...mods} {...props} />}
    </LazilyLoad>
  );
};
```

##### 使用高阶组件实现按需加载
```javascript
class Load_jQuery extends React.Component {
  componentDidMount() {
    console.log('Load_jQuery props:', this.props);
  }

  render() {
    return (
      <div ref={(ref) => this.props.$(ref).css('background-color', 'red')}>Hello jQuery</div>
    );
  }
};

// 使用工厂函数封装Load_jQuery为高阶组件，将异步加载的jQuery模块对象以props的形式来获取并使用
export default LazilyLoadFactory(Load_jQuery, {
  $: () => import('jquery')
});
```

##### ES Decorator
- 除了工厂函数方式扩展实现高阶组件
- Decorator 可以通过返回特定的 descriptor 来 "修饰" 类属性，也可以直接”修饰”一个类
- 即传入一个已有的类，通过 Decorator 函数 "修饰" 成了一个新的类
```javascript
// ES Decorators函数实现高阶组件封装
// 参考 http://technologyadvice.github.io/es7-decorators-babel6/
const LazilyLoadDecorator = (Component) => {

    return LazilyLoadFactory(Component, {
        $: () => require('jquery')(),
    });
};

// ES Decorators语法
// 需要依赖babel-plugin-transform-decorators-legacy
// babel-loader配置使用plugins: ["transform-decorators-legacy"]
@LazilyLoadDecorator
export default class Load_jQuery extends React.Component {

    componentDidMount() {
        console.log('Load_jQuery props:', this.props);

    }

    render() {
        return (
            <div ref={(ref) => this.props.$(ref).css('background-color', 'red')}>
                Hello jQuery
            </div>
        );
    }

};
```

##### 引用被高阶组件包裹的普通组件
```javascript
import Load_jQuery from './js/Load_jQuery';

class App extends React.Component {
    constructor () {
      super(...arguments);
      this.state = {
        load: false,
      };
      
      this.handleClick = this.handleClick.bind(this);
    }

    handleClick() {
      this.setState({
        load: !this.state.load,
      });
    }

    render () {
      return (
        <div>
          <p>
            <a
              style={{ color: 'blue', cursor: 'pointer' }}
              onClick={this.handleClick}
            >点击加载jQuery</a>
          </p>

          { this.state.load ? <div><Load_jQuery /></div> : null }
        </div>
      );
    }
}
```
