/*
 * 扫描
 * @author mulberry
 */
const request = require('request')
const child_process = require('child_process')
const parse = require('./parse')
const scanResult = require('./scanResult')

scanResult

/**
 * 扫描器
 * @param {string} 扫描地址
 */
const scan = function (url) {
  request(url, function (error, response, body) {
    const result = parse(body);
    const links = result.links;


  });
}

const scanWithChildProcess = function () {

};