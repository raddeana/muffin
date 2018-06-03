/**
 * 初始化
 * @author chenxiangyu
 */
var width = window.innerWidth
var height = window.innerHeight

var scene, 
    camera

var objectScene, 
    objectCamera

var renderer, 
    controls

var depthTexture, 
    normalTexture, 
    sceneTexture

var depthMaterial,
    normalMaterial,
    outlineMaterial,
    cartoonMaterial


/**
 * 初始化
 * @return none
 */
function init () {
  // scene
  scene = new THREE.Scene()                     // 这个场景是用来放置最后贴渲染结果的平面的
  objectScene = new THREE.Scene()               // 坦克和灯光是放在这个场景中

  // camera
  objectCamera = new THREE.PerspectiveCamera(45, width/height, 1, 1000)
  objectCamera.position.set(0, 200, 200)
  objectCamera.position.x = 54
  objectCamera.position.y = 24
  objectCamera.position.z = 72
  objectCamera.lookAt(new THREE.Vector3(0, 0, 0))

  camera = new THREE.OrthographicCamera(- 1, 1, 1, - 1, 0, 1)

  renderer = new THREE.WebGLRenderer({
    antialias: true,
    precision: "highp",
  })

  renderer.setClearColor(0x000000)
  renderer.setSize(width, height)
  renderer.shadowMap.enabled = true                 // 开启阴影
  renderer.shadowMap.type = THREE.PCFSoftShadowMap  // 开启阴影柔滑
  renderer.setPixelRatio(window.devicePixelRatio)   // 防止形变
  document.body.appendChild(renderer.domElement)

  // controls
  controls = new THREE.TrackballControls(objectCamera);
  controls.rotateSpeed = 3.5           // 旋转速度
  controls.zoomSpeed = 3.5             // 变焦速度
  controls.panSpeed = 3.5              // 平移速度
  controls.noZoom = false              // 开启变焦
  controls.noPan = false               // 开启移动
  controls.staticMoving = true
  controls.dynamicDampingFactor = 0.3  // 动态阻尼系数
  controls.keys = [65, 83, 68]         // A-S-D
  controls.addEventListener('change', render)

  addLights()
  draw()
  render()
}

/**
 * 添加光源
 */
function addLights () {
  // 环境光 不能产生阴影
  var Ambient_light = new THREE.AmbientLight(0x666666);
  objectScene.add(Ambient_light);

  var light = new THREE.DirectionalLight('#fff', 1)
  
  light.position.set(60, 60, 120)
  light.castShadow = true
  light.shadow.camera.near = 2
  light.shadow.camera.far = 200
  light.shadow.camera.left = -50
  light.shadow.camera.right = 50
  light.shadow.camera.top = 50
  light.shadow.camera.bottom = -50
  light.shadow.mapSize.width = 1024
  light.shadow.mapSize.height = 1024
  light.shadow.camera.near = 0.5
  light.shadow.camera.far = 500

  objectScene.add(new THREE.CameraHelper(light.shadow.camera))
  objectScene.add(light)
}

/**
 * 绘制图形
 * @return none
 */
function draw () {
  depthMaterial = new THREE.MeshDepthMaterial();
  normalMaterial = new THREE.MeshNormalMaterial();

  outlineMaterial = new THREE.ShaderMaterial({
    uniforms: {
      depthTexture: {
        value: null
      },
      normalTexture: {
        value: null
      },
      sceneTexture: {
        value: null
      }
    },
    vertexShader: document.getElementById('vertexShader').textContent,
    fragmentShader: document.getElementById('outlineFragmentShader').textContent
  });

  // 用于保存深度信息渲染的结果
  depthTexture = new THREE.WebGLRenderTarget(width, height)

  // 用于保存法线信息渲染的结果
  normalTexture = new THREE.WebGLRenderTarget(width, height)

  // 用于保存没有outline效果之前的渲染结果
  sceneTexture = new THREE.WebGLRenderTarget(width, height)

  outlineMaterial.uniforms.depthTexture.value = depthTexture.texture;
  outlineMaterial.uniforms.normalTexture.value = normalTexture.texture;
  outlineMaterial.uniforms.sceneTexture.value = sceneTexture.texture;

  // 卡通材质
  cartoonMaterial = new THREE.ShaderMaterial({
    lights: true,                             // 使用场景的的光源
    uniforms: Object.assign( 
      THREE.UniformsLib[ "common" ], 
      THREE.UniformsLib[ "lights" ]
    ),
    vertexShader: document.getElementById('vertexShader').textContent,
    fragmentShader: document.getElementById('cartoonFragmentShader').textContent
  })

  var plane = new THREE.Mesh(new THREE.PlaneGeometry(128, 128, 16, 16), new THREE.MeshLambertMaterial({
    color: 0x666666,
  }))

  plane.receiveShadow = true
  plane.position.y = -6
  plane.rotation.x = - Math.PI / 2
  objectScene.add(plane)

  // var bodySkin = new THREE.TextureLoader().load('/wheel-skin.jpg', function () {}, function () {
  //   render()
  // })

  // var wheelSkin = new THREE.TextureLoader().load('/tank-skin.jpeg', function () {}, function () {
  //   render()
  // })

  var underpan = new THREE.Mesh(new THREE.BoxGeometry(32, 6, 20, 4, 4), cartoonMaterial)

  underpan.castShadow = true
  underpan.receiveShadow = true
  objectScene.add(underpan)

  var turret = new THREE.Mesh(new THREE.CylinderGeometry(6, 6.5, 4, 6), cartoonMaterial)

  turret.position.x = 0
  turret.position.y = 4.5
  turret.position.z = 0
  turret.castShadow = true
  turret.receiveShadow = true
  objectScene.add(turret)

  var artillery = new THREE.Mesh(new THREE.CylinderGeometry(0.8, 0.8, 18, 60), cartoonMaterial)

  artillery.castShadow = true
  artillery.receiveShadow = true
  artillery.position.x = -13.5
  artillery.position.y = 5.5
  artillery.position.z = 0
  artillery.rotation.z = 1.5
  objectScene.add(artillery)


  var wheel_1 = new THREE.Mesh(new THREE.TorusGeometry(2.5, 2, 12, 30), cartoonMaterial)

  wheel_1.castShadow = true
  wheel_1.receiveShadow = true
  wheel_1.position.x = -10
  wheel_1.position.y = -1.5
  wheel_1.position.z = -10
  objectScene.add(wheel_1)

  var wheel_2 = new THREE.Mesh(new THREE.TorusGeometry(2.5, 2, 12, 30), cartoonMaterial)

  wheel_2.castShadow = true
  wheel_2.receiveShadow = true
  wheel_2.position.x = 0
  wheel_2.position.y = -1.5
  wheel_2.position.z = -10
  objectScene.add(wheel_2)

  var wheel_3 = new THREE.Mesh(new THREE.TorusGeometry(2.5, 2, 12, 30), cartoonMaterial)

  wheel_3.castShadow = true
  wheel_3.receiveShadow = true
  wheel_3.position.x = 10
  wheel_3.position.y = -1.5
  wheel_3.position.z = -10
  objectScene.add(wheel_3)

  var wheel_4 = new THREE.Mesh(new THREE.TorusGeometry(2.5, 2, 12, 30), cartoonMaterial)

  wheel_4.castShadow = true
  wheel_4.receiveShadow = true
  wheel_4.position.x = -10
  wheel_4.position.y = -1.5
  wheel_4.position.z = 10
  objectScene.add(wheel_4)

  var wheel_5 = new THREE.Mesh(new THREE.TorusGeometry(2.5, 2, 12, 30), cartoonMaterial)

  wheel_5.castShadow = true
  wheel_5.receiveShadow = true
  wheel_5.position.x = 0
  wheel_5.position.y = -1.5
  wheel_5.position.z = 10
  objectScene.add(wheel_5)

  var wheel_6 = new THREE.Mesh(new THREE.TorusGeometry(2.5, 2, 12, 30), cartoonMaterial)

  wheel_6.castShadow = true
  wheel_6.receiveShadow = true
  wheel_6.position.x = 10
  wheel_6.position.y = -1.5
  wheel_6.position.z = 10
  objectScene.add(wheel_6)

  var screenPlane = new THREE.PlaneBufferGeometry(2, 2)
  scene.add(new THREE.Mesh(screenPlane, outlineMaterial))
}

/**
 * 窗口size变化
 * @return none
 */
function onWindowResize () {
  width = window.width
  height = window.height

  objectCamera.aspect = width / height    // 设置camera的视口宽高比
  objectCamera.updateProjectionMatrix()   // 更新投影矩阵
  renderer.setSize(width, height)
  controls.handleResize()
  controls.update()

  render()
}

window.addEventListener('resize', onWindowResize, false)

/**
 * 渲染
 * @return none
 */
function render () {
  objectScene.overrideMaterial = normalMaterial
  renderer.render(objectScene, objectCamera, normalTexture)
  objectScene.overrideMaterial = depthMaterial
  renderer.render(objectScene, objectCamera, depthTexture)
  objectScene.overrideMaterial = null
  renderer.render(objectScene, objectCamera, sceneTexture)

  outlineMaterial.uniforms.depthTexture.needsUpdate = true
  outlineMaterial.uniforms.normalTexture.needsUpdate = true
  outlineMaterial.uniforms.sceneTexture.needsUpdate = true

  renderer.render(scene, camera)
}

/**
 * 动画
 * @return none
 */
function animate () {
  requestAnimationFrame(animate)      // 递归
  controls.update()
}

init()
animate()
