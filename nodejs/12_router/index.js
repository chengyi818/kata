/*
 * File Name: index.js
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 01 May 2019 07:18:03 PM CST
 */

var server = require("./server");
var router = require("./router");

server.start(router.route);
