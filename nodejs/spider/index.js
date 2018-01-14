/*
 * 爬虫
 * @author mulberry
 */

let http = require('http')
let scan = require('./scan')

/*
 * 爬虫
 * @param {string} 网页地址
 * @return none
 */
module.exports = function (url) {
	scan(url);
}