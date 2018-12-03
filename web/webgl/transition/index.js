var c = document.getElementById('container'),
    next = document.getElementById('next'),
    prev = document.getElementById('prev'),
    boxes = [],
    currentTL = 6,
    numTLs = 9;

window["t"+currentTL]();

// 1. Sketchy hairball
function t1(){
  var n = makeBoxes(25); 
  TweenMax.to(c, 0.4, {perspective:200, backgroundColor:'#eee'})
  
  for (var i=0; i<boxes.length; i++){
    var b = boxes[i];
    new TimelineMax({repeat:-1})
      .set(b, {
        borderRadius:'50%',
        background:'none',
        backgroundImage:'url(https://www.creativeocean.com/dev/spheres/v5/pattern.png)',
        clearProps:'transform'
      }, 0)
      .fromTo(b, 2.5, {
          scaleX:0
        },{
          scaleX:i/n,
          ease:Power4.easeInOut,
          yoyo:true
      }, 0)
      .fromTo(b, 5, {
          rotationY:0,
          rotationZ:i/n*360,
          transformOrigin:String("50% 50% -"+i/n*100)
        },{
          rotationY:360,
          repeat:-1,
          ease:Linear.easeNone
        }, i/n)
      .progress(i/n/100)
    
    // Intro
    TweenMax.from(b, 1, {
      scale:0,
      delay:i/n/2,
      ease:Power4.easeInOut
    });
  }
}

// 2. Thumbnails globe
function t2(){
  var n = makeBoxes(50);
  TweenMax.to(c, 0.4, {perspective:200, backgroundColor:'#111'})
  for (var i=0; i<boxes.length; i++){
    var b = boxes[i];
    new TimelineMax()
      .set(b, {
        borderRadius:'20%',
        background:'#fff',
        clearProps:'transform'
      })
		  .fromTo(b, 5, {
        rotationX:i/n*360,
        rotationY:Math.random()*360,      
        rotationZ:Math.random()*360,
        transformOrigin:String("50% 50% -100px")
      },{
        rotationY:'-=360',
        repeat:-1,
        ease:Linear.easeNone
      })
      .timeScale(0.15)
    
    // Intro
    TweenMax.fromTo(b, 1, {
      alpha:0,
      scale:0,
      scaleZ:0.5
    }, {
      alpha:0.15+(i/n*0.35),
      scale:0.2-Math.random()*0.15,
      scaleZ:1.4+0.26*Math.random(),
      delay:i/n/2,
      ease:Power4.easeOut
    });
  }
}


// 3. Thumbnails belt
function t3(){
  var n = makeBoxes(30);
  TweenMax.to(c, 0.4, {perspective:200, backgroundColor:'#fff'})
  for (var i=0; i<boxes.length; i++){
    var b = boxes[i];
    new TimelineMax()
      .set(b, {
        borderRadius:'20%',
        background:'none',
        backgroundImage:'url(https://picsum.photos/300/?image='+String(i+50),
        clearProps:'transform',
        backfaceVisibility:'hidden'
      })
		  .fromTo(b, 5, {
        rotationX:i/n*360 - 90,
        transformOrigin:String("50% 50% -100px")
      },{
        rotationX:'-=360',
        repeat:-1,
        ease:Linear.easeNone
      })
      .timeScale(0.07)
    
    // Intro
    TweenMax.fromTo(b, 1, {
      alpha:0,
      scale:0,
      scaleZ:1
    }, {
      alpha:1,
      scale:0.11,
      scaleZ:2,
      delay:i/n/2,
      ease:Power4.easeOut
    });
    
    b.addEventListener('mouseover', function(e){
      e.currentTarget.style.cursor='pointer';
      TweenMax.pauseAll();
      TweenMax.to('.box', 0.2, {alpha:0.1});
    	TweenMax.to(e.currentTarget, 0.2, {alpha:1});
    });
    
    b.addEventListener('mouseout', function(e){
     	TweenMax.to('.box', 0.5, {alpha:1, ease:Power1.easeInOut});
      TweenMax.resumeAll();
    });
    
    b.addEventListener('click', function(e){
      window.open(e.currentTarget.style.background.slice(5,-2), '_blank')
    });
  }
}


// 4. Something alien
function t4(){
  (window['arms']==undefined) ? arms = [120,99,111,150,140] : arms.push(arms.shift());
  var n = makeBoxes(arms[0]); //console.log(n)
  TweenMax.to(c, 0.4, {perspective:200, backgroundColor:'#333'})
  
  for (var i=0; i<boxes.length; i++){
    var b = boxes[i];
    new TimelineMax({repeat:-1})
      .set(b, {
        borderRadius:'50%',
        background:'radial-gradient(rgba(246,69,111,0.9) 25%, rgba(246,69,111,0) 60%)',
        clearProps:'transform',
        // alpha:0.8
      }, 0)
      .fromTo(b, 5, {
          rotationY:0,
          rotationX:i/n*-(i/3),
          rotationZ:i/n*(n*0.76), //change the (n*0.76) to play with the direction of the 'arms'
          transformOrigin:String("50% 50% -"+String(i/n*300))
        },{
          rotationY:'+=360',
          repeat:-1,
          ease:Linear.easeNone
        }, i/n)
      .progress(i/n/100)
      .timeScale(0.25)
    
    // Intro
    TweenMax.fromTo(b, 1, {
      scale:0
    },{
      scale:0.2,
      delay:i/n,
      ease:Power4.easeInOut
    });
  }
}



// 5. Blue Trail
function t5(){
  var n = makeBoxes(16); 
  TweenMax.to(c, 0.4, {perspective:99})
  TweenMax.fromTo(c, 2, {backgroundColor:'rgb(18,0,96)'},{backgroundColor:'rgb(20,46,130)', yoyo:true, repeat:-1, ease:Power1.easeInOut})
  
  for (var i=0; i<n; i++){
    var b = boxes[i];
    new TimelineMax({repeat:-1})
      .set(b, {
        borderRadius:'50%',
        background:'radial-gradient(rgba(255,255,255,0.8) 10%, rgba(46,69,255,0.05) 60%)',
        clearProps:'transform',
        // backfaceVisibility:'hidden'
      }, 0)
      .fromTo(b, 0.2, {alpha:0},{alpha:1}, 0)
      .fromTo(b, 1, {
          rotationX:0,
          scaleX:0.1,      
          transformOrigin:String("50% 50% 100%")
        },{
          rotationX:'+=180',
          scaleX:1.5,
          yoyo:true,
          // repeat:-1,
          ease:Power0.easeNone
        }, 0)
      .progress(i/n)
      // .timeScale(0.25)
  }
  // Intro
  //TweenMax.fromTo(c, 1, { alpha:0 },{ alpha:1 });
}

// 6. Rings
function t6(){
  var n = makeBoxes(15); 
  TweenMax.to(c, 0.4, {perspective:750, backgroundColor:'#000'})
  
  for (var i=0; i<n; i++){
    var b = boxes[i];
    new TimelineMax({repeat:-1})
      .set(b, {
        borderRadius:'50%',
        background:'radial-gradient(rgba(0,0,0,0) 65%, rgba('+String(i/n*255)+',50,255,0.25) 70%, rgba(0,0,0,0) 80%)',
        clearProps:'transform',
        transformOrigin:String("50% 55% -200%"),
        // backfaceVisibility:'hidden'
      }, 0)
      .fromTo(b, 0.3, {alpha:0}, {alpha:1, ease:Power3.easeInOut}, i/n)
      .fromTo(b, 2.1, {
          rotationX:i/n*180,
          scaleX:0,      
          y:-i*2,
        },{
          rotationX:'+=270',
          scale:1.5,
          y:0,
          repeat:-1,
          ease:Power0.easeNone
       // ease:Power1.easeInOut
        }, i/n)
      // .timeScale(0.25)
  }
}


// 7. Fabric wave
function t7(){
  var n = makeBoxes(175); 
  TweenMax.to(c, 0.4, {perspective:750, backgroundColor:'#eee'})
  
  for (var i=0; i<n; i++){
    var b = boxes[i];
    new TimelineMax({repeat:0})
      .set(b, {
        borderRadius:'10px',
        background:'#000',
        clearProps:'transform',
        transformOrigin:String("50% 50% 0")
      }, 0)
      .fromTo(b, 3, {rotationY:90}, {rotationY:0, ease:Back.easeOut.config(10)}, i/n)
      .fromTo(b, 0.5, {
          y:i*4,
          height:6,
          top:0
        },{
          scaleX:0.75,
          alpha:i/n,
          yoyo:true,
          repeat:4,
          ease:Sine.easeInOut
        }, i/n)
  }
}

// 8. Equalizer
function t8(){
  var n = makeBoxes(31); 
  TweenMax.to(c, 0.4, {perspective:0, backgroundColor:'#555'})
  
  for (var i=0; i<n; i++){
    var b = boxes[i];
    if (i<n-1){
      new TimelineMax()
        .set(b, {
          borderRadius:'0',
          background:'linear-gradient(#111 91%, red 92%, rgba(255,2,50,0.25) 100%)',
          clearProps:'transform',
          transformOrigin:String("50% 0% 0")
        }, 0)
        .fromTo(b, 0.8, {
            height:275-Math.random()*50,
            x:i*10,
            width:10
          },{
            height:'-='+String(100*Math.random()),
            // alpha:i/n,
            yoyo:true,
            repeat:-1,
            ease:SteppedEase.config(6)
          }, i/n)
    } else {
      TweenMax.set(b, {background:"url(https://www.creativeocean.com/dev/img/grid4.png)", boxShadow:"0 0 40px rgba(0,0,0,0.5)"});
    }
  }
  // Intro
  TweenMax.fromTo('.box', 0.8, {alpha:0}, {alpha:1, ease:Power4.easeIn});
}


// 9. Bird
function t9(){
  var n = makeBoxes(40); 
  TweenMax.to(c, 0.4, {perspective:0, backgroundColor:'#fff'});
  
  for (var i=0; i<n; i++){
    var b = boxes[i];
    TweenMax.set(b, {
        borderRadius:'50%',
        background:'linear-gradient(to left, rgba(0,0,0,0.15) 15%, rgba(0,0,0,1) 100%)',
        clearProps:'transform',
        transformOrigin:String(i*-2)+"% 0% 0%",
        width:33,
        height:4
    });
    
    TweenMax.fromTo(b, 1, {y:100}, {y:140, yoyo:true, repeat:-1, ease:Power1.easeInOut});
    
    if (i==0) {
      TweenMax.fromTo(b, 1, {
        transformOrigin: "25px 1.5px 0%",
        rotation: 4,
        x: 140,
        width: 85,
        scaleY: n/8,
        background: 'radial-gradient(farthest-side at 30% 33%, rgba(0,0,0,1) 35%, rgba(0,0,0,0) 100%)',
      }, {
        rotation: -2,
        yoyo: true,
        repeat: -1,
        ease: Power2.easeInOut
      });
    } else if (i < n/2) { // right wing
      new TimelineMax()
        .fromTo(b, 1, {
          x: 150,
          scale: i * 0.2,
          rotation: -25,
        }, {
          rotation: '+=36',
          yoyo: true,
          repeat: -1,
          ease: Power2.easeInOut
        }, i/n)
    } else { // left wing
      new TimelineMax()
        .set(b, {
          transformOrigin: String(i*5+"% 0% 0%")
        }, 0)
        .fromTo(b, 1, {
          x:140,
          scale:i/2*0.1,
          rotation:25
        }, {
          rotation:'-=36',
          yoyo:true,
          repeat:-1,
          ease:Power2.easeInOut
        }, i/n/2)
    }
  }
}

next.addEventListener('click', function(){
  (currentTL<numTLs) ? currentTL++ : currentTL=1;
  window["t"+currentTL]();
})

prev.addEventListener('click', function(){
  (currentTL>1) ? currentTL-- : currentTL=numTLs;
  window["t"+currentTL]();
})

function makeBoxes(n){
  TweenMax.killAll();
  c.innerHTML = "";
  boxes = [];

  for (var i=0; i<n; i++){
    var b = document.createElement('div');
    b.className += 'box';
    boxes.push(b);
    c.appendChild(b);
  }
  
  return n;
}
