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
		this.nodes = nodes || {}
	}
	/**
	 * 插入节点
	 * @param {object}
	 * @param {string}
	 * @return none
	 */
	insertNode (node, parentUrl) {

	}
	/**
	 * 根据url获取节点
	 * @param {string} 节点地址
	 * @return {object} 节点
	 */
	getNode (url) {

	}
	/**
	 * 节点树
	 * @return {object} 节点树
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