/*
 * 扫描
 * @author mulberry
 */
const request = require('request')
const parse = require('./parse')
const scanResult = require('./scanResult')

/**
 * 扫描器
 * @param {string} 扫描地址
 */
let scan = (url) => {
  request(url, function (error, response, body) {
    
  })
}
