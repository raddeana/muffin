$('.slider').clone().removeAttr('id').attr('id', 'slider-2').appendTo('body');

$('#slider-1').slick({
    arrows: false,
    speed: 750,
    asNavFor: '#slider-2',
    dots: false
}).on('mousedown touchstart', function () {
  $('body').addClass('down');
}).on('mouseleave mouseup touchend', function () {
  $('body').removeClass('down');
});

$(window).on('keydown', function () {
  $('body').addClass('down');
}).on('keyup', function () {
  $('body').removeClass('down');
});

$('#slider-2').slick({
  fade: true,
  arrows: false,
  speed: 300,
  asNavFor:
  '#slider-1',
  dots: false
});

setTimeout(function(){
  $(window).trigger('keydown');
  setTimeout(function(){
    $('#slider-1').slick('slickNext');
    setTimeout(function(){
      $(window).trigger('keyup');
    }, 500);
  }, 600);
}, 1500);

$('#slider-1 image').removeAttr('mask');

$(window).on('resize', function () {
  $('#donutmask circle').attr({
    cx: $(window).width() / 2,
    cy: $(window).height() / 2
  });
  $('#donutmask #outer').attr({
    r: $(window).height() / 2.6
  });
  $('#donutmask #inner').attr({
    r: $(window).height() / 4.5
  });
}).resize();

$(window).on('mousemove', function(e){
  $('.cursor').css({
    top: e.pageY + 'px',
    left: e.pageX + 'px',
  })
});
