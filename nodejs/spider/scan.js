/*
 * 扫描
 * @author mulberry
 */
var scaner = () => {
	
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
