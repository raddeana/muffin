#### 矩阵转换
每个点是 (x, y, z) 组成的数组，比如用 WebGL 的话，相关代码可能是类似这样的
```c
var vertices = [
    1, 0, 0.5,
    -0.5, 0, 0.5,
    0, 1, 0
];

gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
```

```c
gl.viewport(0, 0, this._canvas.width, this._canvas.height);
```

```c
变换后的坐标 = 视口矩阵 x 投影矩阵 x 视图矩阵 x 模型矩阵 x 模型点坐标
```
