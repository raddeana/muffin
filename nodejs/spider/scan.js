/*
 * 扫描
 * @author mulberry
 */
const http = require('http');
const fs = require('fs');
const cheerio = require('cheerio');
const request = require('request');

/**
 * 扫描器
 */
let scan = () => {
	
}

app.get('/', function(req, res) {
 
  request('https://www.ibm.com/us-en/', function (error, response, body) {
    if (!error && response.statusCode == 200) {
      $ = cheerio.load(body)
      res.json({
          cat: $('.cate_menu_item').length
      })
    }
  })
})
