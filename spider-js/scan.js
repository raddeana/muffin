/*
 * 插入排序
 * param {array} 排序对象
 * return {array} 排序结果
 */
var scaner = function () {

};

module.exports = function () {
	
};

app.get('/', function(req, res) {
 
  request('http://www.jd.com', function (error, response, body) {
    if (!error && response.statusCode == 200) {
      $ = cheerio.load(body);
      res.json({
          cat: $('.cate_menu_item').length
      });
    }
  })
});
