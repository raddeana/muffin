/*
 * 解析
 * @author mulberry
 */

/**
 * 解析函数
 * @param {string} 模板
 */
module.exports = function (html) {
	let query = cheerio.load(html)

	let links = query('a')
	let imgs = query('img')

	let hrefs = []
	let srcs = []

	links.forEach((ele) => {
		hrefs.push(ele.href)
	})

	imgs.forEach((ele) => {
		srcs.push(ele.src)
	})

	return {
		links: hrefs,
		imgs: srcs
	}
}