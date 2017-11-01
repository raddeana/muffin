/**
 * 扫描结果
 * @author chenxiangyu
 */

class ScanResult {
	nodes;
	/**
	 * 构造函数
	 * @param {object} 节点树
	 */
	constructor (nodes) {
		this.nodes = nodes || []
	}
	/**
	 * 插入节点
	 * @param {object} 节点对象
	 * @param {string} 父级url
	 * @return none
	 */
	insertNode (node, url) {
		let parentNode = this.findNode(url, this.nodes)

		if (!parentNode.children) {
			parentNode.children = []
		}

		parentNode.children.push(node)
	}
	/**
	 * 找到节点
	 * @param {string} 节点url
	 * @param {array} 搜索的数组
	 * @return none
	 */
	findNode (url, nodes) {
		for (var i = 0, len = nodes.length; i < len; i ++) {
			let node = nodes[i]

			if (url === node.url) {
				return node
			} else {
				if (node.children) {
					let findInChildren = this.findNode(url, node.children)

					if (findInChildren) {
						return findInChildren
					}
				}
			}
		}

		return false
	}
	/**
	 * 根据url获取节点
	 * @param {string} 节点url
	 * @return {object} 节点
	 */
	getNode (url) {
		return this.findNode(url, this.nodes)
	}
	/**
	 * 节点树
	 * @return {array} 全部节点数组
	 */
	getNodesTree () {
		return this.nodes
	}
	/**
	 * 插入节点
	 * @param {array} 全部节点数组
	 */
	getAllNodes () {
		return this.nodes
	}
}

module.exports = new ScanResult()