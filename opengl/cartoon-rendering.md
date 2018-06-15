#### MVP 矩阵
- 变换后的坐标 = 视口矩阵 X 投影矩阵 X 视图矩阵 X 模型矩阵 X 模型点坐标向量
- 一个物体的三维坐标向量，乘以模型视图矩阵后，能够得到它在试图坐标系中的位置，也就是它相对于摄像机的坐标位置


#### 光照计算
- 将光源位置（这是通过参数传入的）乘以模型视图矩阵（这是着色器提供给我们的），就能得到光源相对于摄像机的位置
- 将这一位置归一化（就是计算单位向量），得到光源相对于摄像机的角度
- 将其点乘单位法向量，得到亮度值（回想一下，两个向量点乘的意思是，获得一个向量在另一个向量上的投影，所以，这里得到的是光源在法向量方向的投影长度，它决定了一个点有多亮）

#### 着色器基础知识
#### 顶点着色器
```c
uniform vec3 color;
uniform vec3 light;

varying vec3 vColor;
varying vec3 vNormal;
varying vec3 vLight;

void main()
{
    // pass to fs
    vColor = color;
    vNormal = normalize(normalMatrix * normal);

    vec4 viewLight = viewMatrix * vec4(light, 1.0);
    vLight = viewLight.xyz;

    gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 1.0);
}
```

- (无)（默认值），在当前着色器程序或函数参数中的可读写变量
- const	编译时能确定的常量，或只读函数参数
- attribute	从 OpenGL 代码传入顶点着色器的变量，每个顶点分别对应一个值
- uniform	从 OpenGL 代码传入顶点着色器的变量，所有顶点对应同样的值
- varing 从顶点着色器传入片元着色器的变量

```javascript
const material = new THREE.ShaderMaterial({
    vertexShader: '',  // 可以通过 AJAX 加载 *.vs 代码，内容传给这个变量
    fragmentShader: '',
    uniforms: {
        color: {                                // 苹果的基础色
            type: 'v3',                         // 指定变量类型为三维向量
            value: new THREE.Color('#60371b'),
        },
        // 光源位置
        light: {
            type: 'v3',
            value: keyLight.position
        }
    }
});

mesh.material = material;
```

#### Varing
varing 类型的变量是从顶点着色器往片元着色器传递的，因为 OpenGL 不能直接给片元着色器传信息
- vColor 表示苹果基础色
- vNormal 表示顶点法向量
- vLight 表示光源相对于摄像机的坐标

#### 变量类型
- int
- float
- bool
- vec2
- vec3
- vec4
- mat2
- mat3
- mat4
- sampler2D
- samplerCuber

#### 片元着色器
```c
varying vec3 vColor;
varying vec3 vNormal;
varying vec3 vLight;

void main() {
    float diffuse = dot(normalize(vLight), vNormal);
    
    if (diffuse > 0.8) {
        diffuse = 1.0;
    } else if (diffuse > 0.5) {
        diffuse = 0.6;
    } else if (diffuse > 0.2) {
        diffuse = 0.4;
    } else {
        diffuse = 0.2;
    }

    gl_FragColor = vec4(vColor * diffuse, 1.0);
}
```

- 判断面片朝向，找到正反面交汇处的边
- 将面片沿法向量方向放大，渲染作为描边之后，再次渲染模型
- 将深度缓冲区或法向量绘制到一张临时纹理，用图像处理的方法，找到突变的地方作为边缘
- 将法向量接近平行屏幕所在平面的点作为边缘

#### 面片朝向
（a）模型
（b）正面
（c）反面
（d）位于正反面相界处的边

#### 伪代码
```c
遍历模型中的每个三角形：
  计算三角形是正面还是反面

遍历模型中的每条边：
  如果某条边既包含在正面的三角形中，又包含在反面的三角形中：
    将这条边作为描边绘制
```

#### 前向面与后向面
前向面（front face）与后向面（back face）
任何一个平面可以描述为 Ax + By + Cz + D = 0

#### 优劣分析
该算法的优点在于，由于是用 OpenGL 画线的方式实现的描边，因而线宽是可控而且等宽的
由于是用 OpenGL 画线的方式实现的描边，因而线宽是可控而且等宽的

#### 沿法向量放大
这一算法解释起来就容易得多了

#### 图像处理
使用图像处理的方式，可以将法向量或深度缓冲区绘制到一张纹理，然后通过边缘检测算法，得到画面中法向量和深度突变的地方，通常这些可以作为边缘描绘

```c
void main () {
    float zbuffer = gl_FragCoord.z * gl_FragCoord.w * 100.0;
    gl_FragColor = vec4(zbuffer, zbuffer, zbuffer, 1.0);
}
```

- gl_FragCoord.z 是深度信息
- gl_FragCoord.w 是缩放因子

#### 平行屏幕方向的法向量
在片元着色器中，根据视觉坐标系下的法向量，找到平行屏幕的片元，作为边缘
```c
varying vec3 vNormal;

void main () {
    float silhouette = length(vNormal * vec3(0.0, 0.0, 1.0));
    
    if (silhouette < 0.5) {
        silhouette = 0.0;
    } else {
        silhouette = 1.0;
    }

    gl_FragColor = vec4(silhouette, silhouette, silhouette, 1.0);
}
```

#### 结合卡通渲染
```c
uniform vec3 color;
uniform vec3 light;

varying vec3 vColor;
varying vec3 vNormal;
varying vec3 vLight;

void main () {
    // pass to fs
    vColor = color;
    vNormal = normalize(normalMatrix * normal);

    vec4 viewLight = viewMatrix * vec4(light, 1.0);
    vLight = viewLight.xyz;

    gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 1.0);
}
```

#### 片元着色器
```c
varying vec3 vColor;
varying vec3 vNormal;
varying vec3 vLight;

void main() {
    float silhouette = length(vNormal * vec3(0.0, 0.0, 1.0));
    
    if (silhouette < 0.5) {
        silhouette = 0.0;
    } else {
        silhouette = 1.0;
    }

    float diffuse = dot(normalize(vLight), vNormal);
    
    if (diffuse > 0.8) {
        diffuse = 1.0;
    } else if (diffuse > 0.5) {
        diffuse = 0.6;
    } else if (diffuse > 0.2) {
        diffuse = 0.4;
    } else {
        diffuse = 0.2;
    }
    
    diffuse = diffuse * silhouette;
    gl_FragColor = vec4(vColor * diffuse, 1.0);
}
```

#### 面片朝向
#### 前向面与后向面
前向面（front face）与后向面（back face）

#### 沿法向量放大
它的核心思想是，将每个顶点沿法线方向延伸（如图 b），然后填充放大的模型（如图 c，并且通常只填充后向面），在此基础上，再绘制原始模型叠加上去（如图 d）

#### 优劣分析
该算法可以在着色器中实现，效率较高，实现方式也比前一种直观方便

#### 图像处理
使用图像处理的方式，可以将法向量或深度缓冲区绘制到一张纹理，然后通过边缘检测算法，得到画面中法向量和深度突变的地方，通常这些可以作为边缘描绘
```c
void main () {
    float zbuffer = gl_FragCoord.z * gl_FragCoord.w * 100.0;
    gl_FragColor = vec4(zbuffer, zbuffer, zbuffer, 1.0);
}
```

- gl_FragCoord.z 是深度信息
- gl_FragCoord.w 是缩放因子

#### 平行屏幕方向的法向量
在片元着色器中，根据视觉坐标系下的法向量，找到平行屏幕的片元，作为边缘
```c
varying vec3 vNormal;

void main() {
    float silhouette = length(vNormal * vec3(0.0, 0.0, 1.0));
    
    if (silhouette < 0.5) {
        silhouette = 0.0;
    } else {
        silhouette = 1.0;
    }

    gl_FragColor = vec4(silhouette, silhouette, silhouette, 1.0);
}
```

#### 结合卡通渲染
```c
uniform vec3 color;
uniform vec3 light;

varying vec3 vColor;
varying vec3 vNormal;
varying vec3 vLight;

void main () {
    // pass to fs
    vColor = color;
    vNormal = normalize(normalMatrix * normal);

    vec4 viewLight = viewMatrix * vec4(light, 1.0);
    vLight = viewLight.xyz;

    gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 1.0);
}
```

```c
varying vec3 vColor;
varying vec3 vNormal;
varying vec3 vLight;

void main() {
    float silhouette = length(vNormal * vec3(0.0, 0.0, 1.0));
    
    if (silhouette < 0.5) {
        silhouette = 0.0;
    } else {
        silhouette = 1.0;
    }

    float diffuse = dot(normalize(vLight), vNormal);
    
    if (diffuse > 0.8) {
        diffuse = 1.0;
    } else if (diffuse > 0.5) {
        diffuse = 0.6;
    } else if (diffuse > 0.2) {
        diffuse = 0.4;
    } else {
        diffuse = 0.2;
    }
    
    diffuse = diffuse * silhouette;
    gl_FragColor = vec4(vColor * diffuse, 1.0);
}
```
