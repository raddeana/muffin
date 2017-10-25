/*
 * 解析
 * @author mulberry
 */

const defaultConfig = {
	tags: ['img', 'a'],
	attributes: ['href', 'src']
}

/**
 * 解析函数
 * @param {object} 
 */
module.exports = function (config, html) {
	let config = Object.assign({}, defaultConfig, config)
	let query = cheerio.load(html)

	let links = query('a')
	let imgs = query('img')

	let linksArr = []
	let imgsArr = []

	links.forEach((ele) => {
		linksArr.push(ele.href)
	})

	imgs.forEach((ele) => {
		imgsArr.push(ele.src)
	})
}