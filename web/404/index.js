var Shape = Isomer.Shape;
var Point = Isomer.Point;
var Color = Isomer.Color;
canvas = document.getElementById("can")
var iso = new Isomer(canvas);
ctx = canvas.getContext("2d")

var points = [
  [0,4,3],[0,6,4],[0,5,4],[0,4,4],[0,4,5],[0,6,5], [0,1,3],[0,0,3],[0,-1,3],[0,1,4],[0,-1,4],
  [0,1,5],[0,0,5],[0,-1,5], [0,-6,3],[0,-4,4],[0,-5,4],[0,-6,4],[0,-6,5],[0,-4,5]
];

var cubes = []

setInterval(function () {
  ctx.clearRect(0,0,canvas.width, canvas.height)

  for (i=0; i<cubes.length; i++) {
    color = [Math.floor(Math.random()*50),Math.floor(Math.random()*150)+105,Math.floor(Math.random()*150)+105]
    iso.add(Shape.Prism(new Point(points[i][0], points[i][1], points[i][2])), new Color(color[0],color[1],color[2]))
  }

  cubes.push(points.splice(0,0)[0])
}, 120)
