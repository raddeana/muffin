// Global vars & consts
// *****************************************
const PI    = Math.PI;
const toRad = deg => deg * (180/PI);
const toDeg = rad => rad * (PI/180);

const WW = _ => window.innerWidth * 2;  // Window width
const WH = _ => window.innerHeight * 2; // Window height
let O = {x: WW()/4, y: WH()/4};  // Layout center

let angle = 0;

const BG   = '#222';
const RED  = '#c38a8a';
const BLUE = '#9bfcfc';
// *****************************************



// Settings [EDIT THIS TO GET NEW SHAPES]
// *****************************************
let startRadius = 70
let N = 3;
let dt = 0;
let debug = {circles: 1, lines: 1};
let Circles = [
  {r: 50, speed:  -36},
  {r: 20, speed:   72},
  {r: 10, speed:   144},
]
// *****************************************




// Core
// *****************************************
const ctx = document.querySelector('#canvas').getContext('2d');
const ctx2 = document.querySelector('#canvasfade').getContext('2d');


// Init animation
function init() {
  ctx.canvas.width = WW()/2;
  ctx.canvas.height = WH()/2;
  ctx2.canvas.width = WW()/2;
  ctx2.canvas.height = WH()/2;
  O = {x: WW()/4, y: WH()/4}
}


// Redraw canvas
function draw() {
  // Clear
  Painter.clearScreen();
  
  // Calculations goes here
  const Points = getPoints(Circles);
  
  // Drawing goes here
  if (debug.circles) {
    Painter.drawCircle(O, startRadius);
  }
  
  for (let i = 1; i <= N; i++) {
    let angleOffset = (2*PI) / N * i-1;
    
    let prevCircle;
    Circles.forEach((c, i) => {
      let center;

      if (i === 0 && !prevCircle) {
        center = {
          x: O.x + (c.r + startRadius) * Math.cos(angleOffset + PI / 360 * c.speed * dt),
          y: O.y + (c.r + startRadius) * Math.sin(angleOffset + PI / 360 * c.speed * dt)
        };
      } else {
        center = {
          x: prevCircle.center.x + (c.r + prevCircle.r) * Math.cos(angleOffset + PI / 360 * c.speed * dt),
          y: prevCircle.center.y + (c.r + prevCircle.r) * Math.sin(angleOffset + PI / 360 * c.speed * dt)
        };
      };

      if (debug.circles) {
        Painter.drawCircle(center, c.r);
      };

      if (debug.lines) {
        if (prevCircle) {
          Painter.drawLine(prevCircle.center, center);
        } else {
          Painter.drawLine(O, center);
        }
      };

      if (i === Circles.length-1) {
        Painter.drawPoint(center);
      };

      prevCircle = {...c, center};
    }); 
  }
  
  dt += 1/36;
  

  
  
  // Loop
  window.requestAnimationFrame(draw);
}


function start() {
  init();
  
  window.addEventListener('resize', init);
  window.requestAnimationFrame(draw);
}


// Start animation
start();
//*****************************************








// Draw functions
// *****************************************
class Paint {
  clearScreen() {
    ctx.fillStyle = BG;
    ctx.clearRect(0, 0, WW(), WH());
    // ctx2.fillStyle = BG;
    // ctx2.globalAlpha = 0.05;
    // ctx2.fillRect(0, 0, WW(), WH());
    // ctx2.globalAlpha = 1;
  }
  
  drawPoint(p) {
    ctx2.beginPath();
    ctx2.fillStyle = "#FFF";
    ctx2.arc(p.x, p.y, 1, 0, 2*PI);
    ctx2.fill();
    ctx2.closePath();
  }
  
  drawCircle(p, r, alpha=1) {
    ctx.beginPath();
    ctx.lineWidth = 1;
    ctx.globalAlpha = alpha;
    ctx.strokeStyle = BLUE;
    ctx.arc(p.x, p.y, r, 0, 2*PI);
    ctx.stroke();
    ctx.closePath();
    ctx.globalAlpha = 1;
  }
  
  drawLine(p1, p2) {
    ctx.beginPath();
    ctx.lineWidth = 1;
    ctx.strokeStyle = RED;
    ctx.moveTo(p1.x, p1.y);
    ctx.lineTo(p2.x, p2.y);
    ctx.stroke();
    ctx.closePath();
  }
}

const Painter = new Paint();
// *****************************************








// Calculations
// *****************************************
function getPoints(circles) {
}
// *****************************************







// Classes
// *****************************************
// *****************************************
