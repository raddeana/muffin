let particles = [];

function generateParticle (e = performance.now()) {
	let p = new Particle();
	
  p.pos.x = random(-0.01, 1.01) * width;
	p.pos.y = random(-height_half) - p.r;
	
  if(random() < 0.06) {
		let side = random([ 0, 1 ]);
		p.pos.x = side * width;
		p.pos.y = map(sin(e * 0.001), -1, 1, 0.3, 0.8) * height;
		p.acc.x = -(side || -1) * random(3, 7);
		p.acc.y = random(-5, -10);
	}
  
	particles.push(p);
}

function draw (e) {
	if(particles.length < 4000) {
		for(let i = 0; i < 9; i++) {
			generateParticle(e);
		}
	}
  
	beginPath();
	let gravity = createVector(0, 0.06);
	let mouseDownMult = mouseDown ? 1.4 : 0.8;
	let maxDist = width * 0.5;
	// isPreviewEmbed = () => true;
	let mouse = isPreviewEmbed() ? (
			mouseIn = e < 2000,
			(() => {
				let time = e * 0.001 + PI;
				let w = width * 0.1;
				return createVector(
					cos(time) * w + width_half,
					sin(time) * w + height * 0.3
				)
			})()
		) : mousePos;
	
  for(let i = particles.length - 1; i >= 0; i--) {
		let n = particles[i];
		if(n.pos.y - n.r > height) {
			particles.splice(i, 1);
			generateParticle(e);
			continue;
		}
    
		if(mouseIn) {
			let diff = mouse.copy().sub(n.pos);
			let dist = diff.mag();
			if(dist < maxDist) {
				let limit = mouseDownMult * n.ml * (maxDist - dist) * 0.01;
				n.acc.add(diff.limit(limit));
			}
		}
    
		n.acc.add(gravity);
		n.draw();
	}
  
	fill(hsl(260, 100, 50));
}

class Particle {
	constructor() {
		this.pos = createVector();
		this.vel = createVector();
		this.acc = createVector();
		this.r = random(2, 8);
		this.fr = map(this.r, 2, 8, 0.997, 0.99);
		this.ml = map(this.r, 2, 8, 0.4, 0.05);
	}
	draw() {
		this.vel.add(this.acc).mult(this.fr);
		this.acc.set(0, 0);
		this.pos.add(this.vel);
		rect(this.pos.x, this.pos.y, this.r);
	}
}
