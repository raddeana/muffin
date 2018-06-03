// 顶点着色器程序
const VSHADER_SOURCE = document.getElementById('vs').innerText
// 片元着色器
const FSHADER_SOURCE = document.getElementById('fs').innerText

const canvas = document.getElementById('canvas')

let gl = canvas.getContext('webgl', {
	Alpha: true,								 // 提供一个alpha缓冲区到画布上
	depth: true,								 // 得到一个绘图的缓冲区，其中包含至少16位的深度缓冲
	antialias: false, 					 // 得到一个绘图缓冲区，执行抗锯齿
	stencil: true,							 // 得到一个绘图缓冲区，其中包含至少8位的模板缓存
	premultipliedAlpha: true,		 // 得到一个绘图缓冲区，其中包含的颜色与预乘alpha
	preserveDrawingBuffer: true  // 缓冲区将不会被清零，直到被清除或由作者改写将保留它们的值
})

// 编译着色器
var vertShader = gl.createShader(gl.VERTEX_SHADER)
gl.shaderSource(vertShader, VSHADER_SOURCE)
gl.compileShader(vertShader)

var fragShader = gl.createShader(gl.FRAGMENT_SHADER)
gl.shaderSource(fragShader, FSHADER_SOURCE)
gl.compileShader(fragShader)

// 合并程序
var shaderProgram = gl.createProgram()
gl.attachShader(shaderProgram, vertShader)
gl.attachShader(shaderProgram, fragShader)
gl.linkProgram(shaderProgram)
gl.useProgram(shaderProgram)

//绘制一个点
gl.drawArrays(gl.POINTS, 0, 1);