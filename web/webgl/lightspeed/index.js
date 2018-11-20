"use strict";

const { PI, cos, sin, abs, sqrt, pow, random, atan2 } = Math;
const HALF_PI = 0.5 * PI;
const TAU = 2 * PI;
const rand = n => n * random();
const randIn = (min, max) => rand(max - min) + min;
const fadeIn = (t, m) => t / m;
const angle = (x1, y1, x2, y2) => atan2(y2 - y1, x2 - x1);

const starCount = 1000;

let canvas;
let ctx;
let center;
let positions;
let velocities;
let lifeSpans;
let hues;

function setup () {
	createCanvas();
	createStars();
	draw();
}

function createCanvas () {
	canvas = {
		a: document.createElement("canvas"),
		b: document.createElement("canvas")
	};
  
	canvas.b.style = `
		position: absolute;
		top: 0;
		left: 0;
		width: 100%;
		height: 100%;
	`;
	
  document.body.appendChild(canvas.b);
  
	ctx = {
		a: canvas.a.getContext("2d"),
		b: canvas.b.getContext("2d")
	};
  
	center = [];
	resize();
}

function resize () {
	const { innerWidth, innerHeight } = window;
	
	canvas.a.width = canvas.b.width = innerWidth;
	canvas.a.height = canvas.b.height = innerHeight;
	
	center[0] = 0.5 * innerWidth;
	center[1] = 0.5 * innerHeight;
}

function checkBounds (x, y) {
	return(
		x > canvas.a.width ||
		x < 0 ||
		y > canvas.a.height ||
		y < 0
	);
}

function createStars () {
	positions = new Float32Array(starCount * 2);
	velocities = new Float32Array(starCount * 2);
	hues = new Float32Array(starCount);
	lifeSpans = new Float32Array(starCount * 2);

	let i, x, y, t, s, vx, vy;
	
	for (i = 0; i < starCount * 2; i += 2) {
		resetStar(i);
	}
}

function resetStar (i) {
	let iy, rd, rt, cx, sy, x, y, rv, vx, vy, t, h, l, ttl;
	
	iy = i + 1;
	rd = rand(100);
	rt = rand(TAU);
	cx = cos(rt);
	sy = sin(rt);
	x = center[0] + cx * rd;
	y = center[1] + sy * rd;
	rv = randIn(0.1,1);
	vx = rv * cx;
	vy = rv * sy;
	h = rand(360);
	l = 0;
	ttl = randIn(20,100);
	
	positions[i] = x;
	positions[iy] = y;
	velocities[i] = vx;
	velocities[iy] = vy;
	hues[0.5 * i | 0] = h;
	lifeSpans[i] = l;
	lifeSpans[iy] = ttl;
}

function drawStar (i) {
	let iy, x, y, tx, ty, vx, vy, h, l, dl, ttl, c;

	iy = i + 1;
	x = positions[i];
	y = positions[iy];
	vx = velocities[i];
	vy = velocities[iy];
	tx = x + vx;
	ty = y + vy;
	vx *= 1.15;
	vy *= 1.15;
	h = hues[0.5 * i | 0];
	l = lifeSpans[i];
	ttl = lifeSpans[iy];
	dl = fadeIn(l, ttl);
	c = `hsla(${h},50%,80%,1)`;

	l++;
	
	ctx.a.save();
	ctx.a.lineWidth = dl;
	ctx.a.lineCap = 'round';
	ctx.a.strokeStyle = c;
	ctx.a.beginPath();
	ctx.a.moveTo(x, y);
	ctx.a.lineTo(tx, ty);
	ctx.a.stroke();
	ctx.a.closePath();
	ctx.a.restore();

	positions[i] = tx;
	positions[iy] = ty;
	velocities[i] = vx;
	velocities[iy] = vy;
	lifeSpans[i] = l;

	checkBounds(x, y) && resetStar(i);
}

function draw () {
	ctx.a.clearRect(0,0,canvas.a.width,canvas.a.height);
	ctx.b.clearRect(0,0,canvas.b.width,canvas.b.height);
	
	ctx.b.fillStyle = 'rgba(0,0,0,0.5)';
	ctx.b.fillRect(0,0,canvas.b.width,canvas.b.height);
	
	let i;
	
	for (i = 0; i < starCount * 2; i += 2) {
		drawStar(i);
	}
	
	ctx.b.save();
	ctx.b.filter = 'blur(10px)';
	ctx.b.drawImage(canvas.a, 0, 0);
	ctx.b.restore();
	
	ctx.b.save();
	ctx.b.globalCompositeOperation = 'lighter';
	ctx.b.drawImage(canvas.a, 0, 0);
	ctx.b.restore();
	
	window.requestAnimationFrame(draw);
}

window.addEventListener("load", setup);
window.addEventListener("resize", resize);
